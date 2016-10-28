package com.example.romain.faustinstrument;

import android.content.Context;
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

import com.dsp_faust.dsp_faust;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        int SR = 48000;
        int blockSize = 128;
        dsp_faust.init(SR,blockSize);
        dsp_faust.start();
        dsp_faust.setParamValue("/synth/gate",1);

        /*
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
        */
    }

    @Override
    public void onDestroy(){
        super.onDestroy();
        dsp_faust.stop();
        dsp_faust.destroy();
    }
}
