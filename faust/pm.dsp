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

fc = (0, 2, 4, 5, 7, 9, 11, 12,
0, 2, 3, 5, 7, 8, 11, 12,
0, 2, 4, 6, 8, 10, 12, 14,
-5, 0, 2, 4, 7, 9, 12, 14,
-5, 0, 2, 3, 4, 7, 9, 12,
-5, 0, 3, 5, 7, 10, 12, 16,
-5, 0, 3, 4, 5, 7, 10, 12,
0, 2, 3, 5, 6, 8, 9, 11,
0, 2, 3, 6, 7, 8, 11, 12,
0, 1, 4, 5, 7, 8, 11, 12);
freqs(i,j) = ba.take(i+1+j*8,fc)+60 : ba.midikey2hz;

/*
fc = (70,72,74,76,78,80,82,84);
freqs(i) = ba.take(i+1,fc) : ba.midikey2hz;
*/

gain = hslider("gain",1,0,1,0.01);
t60 = hslider("t60",2.5,0.01,5,0.01);
scale = hslider("scale[acc: 0 0 -10 0 10]",0.5,0,1,0.01)*0.3;
spread = hslider("spread[acc: 1 0 0 0 10]",0.5,0,1,0.01);
feedback = hslider("feedback[acc: 1 0 0 0 10]",0,0,1,0.01);
delLeg = hslider("delLeg",0.1,0.01,1,0.01);
noteScale = hslider("noteScale",0,0,9,1) : int;
gate = button("gate");

excitation(i) = no.noise*en.ar(0.001,0.001,(ctl : ba.impulsify))*(ctl^2)
with{
	w = i+22;
	ctl = hslider("ctl%i[midi: ctrl %i]",0,0,1,0.01);
	//ctl = hslider("ctl%i[acc: 0 0 -10 0 10]",0,0,1,0.01);
};

model(freq,j) = excitation(j) <: 
	par(i,N,modeFilter(
	freq*(1+i*((scale+spread)*2)),
	t60*((N-i)*(1/N))^3)
	*((N-i)*(1/N))^3) 
	:> *(1/N);

echo(d,f) = +~(de.delay(65536,l)*f)
with{
	l = ma.SR*d;
};

process = par(i,8,model(sum(j,10,freqs(i,j)*(noteScale==j)),i)) :> echo(0.07,0.3)*gain : echo(delLeg,feedback) <: _,_;
