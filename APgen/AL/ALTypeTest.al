typedef myTestType {
	rational 	a;
	biquad 		b[2];
}

typedef myTestType2 {
	myTestType	x;
	rational 	y[3];
}

typedef myTestType3 {
	myTestType	x;
	myTestType2	y[3];
}


global {
	myTestType3 gv;
}

main (ALTypeTest) {
	local {
	}
	code {
		gv.x.a = 123;
		biquad[obj=gv.x.b, index=0, type=LP, fs=48000, fc=2000];
	}	
}