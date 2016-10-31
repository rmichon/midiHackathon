import("stdfaust.lib");

feedback = hslider("feedback[acc: 1 0 0 0 10]",0,0,1,0.01);
delLeg = hslider("delLeg",0.1,0.01,1,0.01);

echo(d,f) = +~(de.delay(65536,l)*f)
with{
	l = ma.SR*d;
};

process = echo(delLeg,feedback),echo(delLeg,feedback);
