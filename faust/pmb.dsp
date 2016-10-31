import("stdfaust.lib");

N = 30;

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

fc = (70,72,74,76,78,80,82,84);
freqs(i) = ba.take(i+1,fc)-14 : ba.midikey2hz;


gain = hslider("gain",1,0,1,0.01);
freq = hslider("freq",200,50,2000,0.01);
t60 = hslider("t60[acc: 0 0 -10 0 10]",2.5,0.01,5,0.01);
scale = hslider("scale[acc: 0 0 -10 0 10]",0.5,0,1,0.01)*0.3;
spread = hslider("spread[acc: 1 0 0 0 10]",0.5,0,1,0.01);
feedback = hslider("feedback[acc: 1 0 0 0 10]",0,0,1,0.01);
delLeg = hslider("delLeg",0.1,0.01,1,0.01);
gate = button("gate");

excitation = no.noise*en.ar(0.001,0.001,gate)*(gain)
with{
	w = i+22;
	ctl = hslider("ctl%i[midi: ctrl %i]",0,0,1,0.01);
	//ctl = hslider("ctl%i[acc: 0 0 -10 0 10]",0,0,1,0.01);
};

model = excitation <: 
	par(i,N,modeFilter(
	freq*(1+i*((scale+spread)*2)),
	t60*((N-i)*(1/N))^3)
	*((N-i)*(1/N))^3) 
	:> *(1/N);

process = model :> _ <: _,_;
