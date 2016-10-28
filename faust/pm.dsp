import("stdfaust.lib");

modeFilter(f,t60) = fi.tf2(b0,b1,b2,a1,a2)
with{
	b0 = 1;
	b1 = 0;
	b2 = -1;
	w = 2*ma.PI*f/ma.SR;
	r = pow(0.001,1/float(t60*ma.SR));
	a1 = -2*r*cos(w);
	a2 = r^2;
};

freq = hslider("freq",400,50,2000,0.01);
t60 = hslider("t60",2,0.01,5,0.01);
gate = button("gate");

fc = (1,
1.2,
1.4,
1.6,
1.8,
2,
2.2,
2.4,
2.6,
2.8
);
freqScaler(i) = ba.take(i+1,fc);


model = gate : ba.impulsify <: par(i,10,modeFilter(freq*freqScaler(i),t60*(10-i)*0.1)) :> *(0.1) <: _,_;

process = model;
