package com.example.romain.faustinstrument;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.media.midi.MidiDevice;
import android.media.midi.MidiDeviceInfo;
import android.media.midi.MidiManager;
import android.media.midi.MidiOutputPort;
import android.media.midi.MidiReceiver;
import android.os.Handler;
import android.os.Looper;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;

import com.dsp_faust.dsp_faust;

public class MainActivity extends AppCompatActivity implements SensorEventListener, AdapterView.OnItemSelectedListener {

    private SensorManager sensorManager;
    private Sensor accelerometer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        int SR = 48000;
        int blockSize = 128;
        dsp_faust.init(SR,blockSize);
        dsp_faust.start();

        sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        sensorManager.registerListener(this, accelerometer, SensorManager.SENSOR_DELAY_NORMAL);

        Spinner spinner = (Spinner) findViewById(R.id.spinner);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this,
                R.array.scale_array, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(adapter);
        spinner.setOnItemSelectedListener(this);

        class MyReceiver extends MidiReceiver {
            public void onSend(byte[] data, int offset,
                               int count, long timestamp) {
                // we only consider MIDI messages containing 3 bytes (see is just an example)
                if(count%3 == 0) {
                    int nMessages = count / 3; // in case the event contains several messages
                    for (int i = 0; i < nMessages; i++) {
                        int type = (int) (data[offset + i*3] & 0xF0);
                        int channel = (int) (data[offset + i*3] & 0x0F);
                        int data1 = (int) data[offset + 1 + i*3];
                        int data2 = (int) data[offset + 2 + i*3];
                        dsp_faust.propagateMidi(3, timestamp, type, channel, data1, data2);
                    }
                }
            }
        }

        Context context = getApplicationContext();
        final MidiManager m = (MidiManager)context.getSystemService(Context.MIDI_SERVICE);
        final MidiDeviceInfo[] infos = m.getDevices();

        // opening all the available ports and devices already connected
        for(int i=0; i<infos.length; i++){
            final int currentDevice = i;
            m.openDevice(infos[i], new MidiManager.OnDeviceOpenedListener() {
                @Override
                public void onDeviceOpened(MidiDevice device) {
                    if (device == null) {
                        Log.e("", "could not open device");
                    } else {
                        for(int j=0; j<infos[currentDevice].getOutputPortCount(); j++) {
                            MidiOutputPort outputPort = device.openOutputPort(j);
                            outputPort.connect(new MyReceiver());
                        }
                    }
                }
            }, new Handler(Looper.getMainLooper()));
        }

        // adding any newly connected device
        m.registerDeviceCallback(new MidiManager.DeviceCallback() {
            public void onDeviceAdded( final MidiDeviceInfo info ) {
                m.openDevice(info, new MidiManager.OnDeviceOpenedListener() {
                    @Override
                    public void onDeviceOpened(MidiDevice device) {
                        if (device == null) {
                            Log.e("", "could not open device");
                        } else {
                            for(int j=0; j<info.getOutputPortCount(); j++) {
                                MidiOutputPort outputPort = device.openOutputPort(j);
                                outputPort.connect(new MyReceiver());
                            }
                        }
                    }
                }, new Handler(Looper.getMainLooper()));
            }
        }, new Handler(Looper.getMainLooper()));



    }

    public boolean onTouchEvent(MotionEvent event)  {
        if(event.getAction() == MotionEvent.ACTION_DOWN){
            Log.d("Event", "Action Dowm");
            return true;
        }

        if(event.getAction()== MotionEvent.ACTION_MOVE){
            dsp_faust.setParamValue("/0x00/t60",event.getY()/2600*5);
            return true;

        }
        return super.onTouchEvent(event);
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        for (int i = 0 ;i<event.values.length;i++){
            dsp_faust.propagateAcc(i, event.values[i]);
        }
    }

    @Override
    public void onItemSelected(AdapterView<?> parent, View v, int position, long id) {
        Log.d("Checkbox", " " + position);
        dsp_faust.setParamValue("/0x00/scale", position);

    }
    @Override
    public void onNothingSelected(AdapterView<?> parent) {
    }

    @Override
    public void onDestroy(){
        super.onDestroy();
        dsp_faust.stop();
        dsp_faust.destroy();
    }
}
