#include "mpr121.h"
#include <Wire.h>
#include "MIDI.h"
#include "Encoder.h"

int IRQPIN = 2;
#define INPUT_COUNT (8)
#define ledPin (13)      // select the pin for the LED
#define TOUCH_THRESHOLD       (5)
#define PIEZO_THRESHOLD       (100)
#define triggerThreshold 5
#define initialHitReadDuration 200
#define midiVelocityScaleDownAmount 2
#define inputPin A0
#define CC_BASE 0

// Getting the ideal balance of these two constants will ensure that fast subsequent hits are perceived accurately, but false hits are not generated
#define subsequentHitThreshold 1.7
#define subsequentHitThresholdDecaySpeed 14

uint16_t highestYet;
uint32_t startReadingTime;
uint32_t highestValueTime;
boolean hitOccurredRecently = false;

// Current body-contact states for instrument metal keys.
boolean gPrevTouchStates[INPUT_COUNT];
boolean gTouchStates[INPUT_COUNT];
int gPiezoValue = 0;
int gPrevPiezoValue = 0;

boolean checkInterrupt( void )
{
  return digitalRead(IRQPIN);
}


void set_register(  int address, 
                    unsigned char r, 
                    unsigned char v )
{
  Wire.beginTransmission(address);
  Wire.write(r);
  Wire.write(v);
  Wire.endTransmission();
}

void mpr121_setup()
{

    set_register(0x5A, ELE_CFG, 0x00); 
  
    // Section A - Controls filtering when data is > baseline.
    set_register(0x5A, MHD_R, 0x01);
    set_register(0x5A, NHD_R, 0x01);
    set_register(0x5A, NCL_R, 0x00);
    set_register(0x5A, FDL_R, 0x00);

    // Section B - Controls filtering when data is < baseline.
    set_register(0x5A, MHD_F, 0x01);
    set_register(0x5A, NHD_F, 0x01);
    set_register(0x5A, NCL_F, 0xFF);
    set_register(0x5A, FDL_F, 0x02);
  
    // Section C - Sets touch and release thresholds for each electrode
    set_register(0x5A, ELE0_T, TOU_THRESH);
    set_register(0x5A, ELE0_R, REL_THRESH);
 
    set_register(0x5A, ELE1_T, TOU_THRESH);
    set_register(0x5A, ELE1_R, REL_THRESH);
  
    set_register(0x5A, ELE2_T, TOU_THRESH);
    set_register(0x5A, ELE2_R, REL_THRESH);
  
    set_register(0x5A, ELE3_T, TOU_THRESH);
    set_register(0x5A, ELE3_R, REL_THRESH);
  
    set_register(0x5A, ELE4_T, TOU_THRESH);
    set_register(0x5A, ELE4_R, REL_THRESH);
  
    set_register(0x5A, ELE5_T, TOU_THRESH);
    set_register(0x5A, ELE5_R, REL_THRESH);
  
    set_register(0x5A, ELE6_T, TOU_THRESH);
    set_register(0x5A, ELE6_R, REL_THRESH);
  
    set_register(0x5A, ELE7_T, TOU_THRESH);
    set_register(0x5A, ELE7_R, REL_THRESH);
  
    set_register(0x5A, ELE8_T, TOU_THRESH);
    set_register(0x5A, ELE8_R, REL_THRESH);
  
    set_register(0x5A, ELE9_T, TOU_THRESH);
    set_register(0x5A, ELE9_R, REL_THRESH);
  
    set_register(0x5A, ELE10_T, TOU_THRESH);
    set_register(0x5A, ELE10_R, REL_THRESH);
  
    set_register(0x5A, ELE11_T, TOU_THRESH);
    set_register(0x5A, ELE11_R, REL_THRESH);
  
    // Section D
    // Set the Filter Configuration
    // Set ESI2
    set_register(0x5A, 0x5C, 0x3F);
    set_register(0x5A, FIL_CFG, 0xC6);
  
    // Section E
    // Electrode Configuration
    // Set ELE_CFG to 0x00 to return to standby mode
    //set_register(0x5A, ELE_CFG, 0x0C);  // Enables all 12 Electrodes
  
  
    // Section F
    // Enable Auto Config and auto Reconfig
    /*set_register(0x5A, ATO_CFG0, 0x0B);
    set_register(0x5A, ATO_CFGU, 0xC9);  // USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   set_register(0x5A, ATO_CFGL, 0x82);  // LSL = 0.65*USL = 0x82 @3.3V
    set_register(0x5A, ATO_CFGT, 0xB5);*/  // Target = 0.9*USL = 0xB5 @3.3V
  
    set_register(0x5A, ELE_CFG, 0xCA);  
} // void mpr121_setup(...)

void readTouchInputs( void )
{
  int i;
  // if (!checkInterrupt() ) {
    // uint16_t touched = 0;
      
    // MPR TOUCH COMMS
    // ---------------
    // read the touch state from the MPR121
    Wire.requestFrom(0x5A, 2); 
      
    byte LSB = Wire.read();
    byte MSB = Wire.read();
      
    // touched = ((MSB << 8) | LSB); //16bits that make up the touch states
  
    // if ( touched ) {
      Wire.beginTransmission(0x5A);
      Wire.send( 0x04 );   
      Wire.endTransmission();
      Wire.requestFrom( 0x5A, 30 );
          
      // Discard the first four values.
      Wire.read();
      Wire.read();
      Wire.read();
      Wire.read();
          
      for ( i = 0; i < INPUT_COUNT; ++i ) {
        int val = 0;
        LSB = Wire.read();
        MSB = Wire.read();
        val = 1023 - ((MSB << 8) | LSB);

        if ( abs(val) > TOUCH_THRESHOLD ) {
          gTouchStates[i] = true;
        } // for ( i = ...
        else {
          gTouchStates[i] = false;
        }
      } // for ( i = ...
      // } // if ( touched )
  // } // if ( !checkInterrupt() )  
} // void readTouchInputs()

void readPiezoInput( void ) {
  // Assume the normal hit-threshold
  uint16_t thresholdNow = triggerThreshold;
 
  // But, if a hit occurred very recently, we need to set a higher threshold for triggering another hit, otherwise the dissipating vibrations
  // of the previous hit would trigger another one now
  if (hitOccurredRecently) {
 
    // Work out how high a reading we'd need to see right now in order 
    // to conclude that another hit has occurred
    uint16_t currentDynamicThreshold =
      (highestYet >> ((micros() - highestValueTime) >> 
      subsequentHitThresholdDecaySpeed)) * subsequentHitThreshold;
 
    // If that calculated threshold is now as low as the regular 
    // threshold, we can go back to just waiting for a regular, isolated hit
    if (currentDynamicThreshold <= triggerThreshold) {
      hitOccurredRecently = false;
    }
    // Otherwise, do use this higher threshold
    else {
      thresholdNow = currentDynamicThreshold;
    }
  }
 
  // Read the piezo
  uint16_t value = analogRead(inputPin);
  gPiezoValue = value;
  if (gPrevPiezoValue != gPiezoValue) {
    if (gPiezoValue > 100) {
      // Serial.print("...Piezo changes to: ");
      // Serial.println(gPiezoValue);
    }
  }
  if (gPiezoValue < PIEZO_THRESHOLD) {
    gPiezoValue = 0;
  }
  gPrevPiezoValue = gPiezoValue;
  
 /*
  // If we've breached the threshold, it means we've got a hit!
  if (value >= thresholdNow) {
    startReadingTime = micros();
    highestYet = 0;
 
    // For the next few milliseconds, look out for the highest "spike" 
    // in the reading from the piezo. Its height is representative of 
    // the hit's velocity
    do {
      if (value > highestYet) {
        highestYet = value;
        highestValueTime = micros();
      }
      value = analogRead(inputPin);
    } while (timeGreaterOrEqual(startReadingTime + initialHitReadDuration, 
             micros()));
 
    hitOccurredRecently = true;
    gPiezoValue = value;
  }
  else {
    gPiezoValue = 0;
  }
  */
}

void generateMidi()
{
  // Loop through previous and current touch states to determine whether 
  // a key hold or release has occurred.
  int i;
  for (i = 0; i < INPUT_COUNT; ++i) {
    if (gTouchStates[i] != gPrevTouchStates[i]) {
      if (gPiezoValue > 0) {
          // Send the midi CC event.
          usbMIDI.sendControlChange(
                    CC_BASE + i,
                    gPiezoValue,
                    0 );
          Serial.print("----> HIT VALUE of key ");
          Serial.print(i);
          Serial.print(" is ");
          Serial.println(gPiezoValue);
      }
      else {
          // Send the midi CC event.
          usbMIDI.sendControlChange(
                    CC_BASE + i,
                    0,
                    0 );
          Serial.print("----> DAMP VALUE of key ");
          Serial.print(i);
          Serial.print(" is ");
          Serial.println(gPiezoValue);
      }
      gPrevTouchStates[i] = gTouchStates[i];
    }
  }
}

// Compares times without being prone to problems when the micros() counter 
// overflows, every ~70 mins
boolean timeGreaterOrEqual(uint32_t lhs, uint32_t rhs) {
  return (((lhs - rhs) & 2147483648) == 0);
}

void setup() {
  int i;

  Serial.print("I'M ALIVE!");
  // put your setup code here, to run once:
  pinMode(IRQPIN, INPUT);
  digitalWrite(IRQPIN, HIGH); //enable pullup resistor
  
  Serial.begin(9600);
  Wire.begin();

  mpr121_setup();

  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);

  for (i = 0; i < INPUT_COUNT; ++i) {
    gPrevTouchStates[i] = false;
    gTouchStates[i] = false;
  } 
}

void loop() {
  readTouchInputs();
  readPiezoInput();
  generateMidi();
  delay(25);
}



