global {
	rational	sens;
	biquad 		impactNoiseF;
	integer 	impactNoiseBypass;
	noisegate 	noiseG;
	compressor	compressor;
	biquad 		EQ[3];
	rational 	gain;
	rational 	panLeft;
}

// processes a vector of input samples with the defined channel strip
// the function results into an endless loop
function processChannelStrip {
	interface {
		in		rational	x;
		out		rational	y;
	}

	local {
		integer v;
	}

	code {
		y = x * sens;
		if [impactNoiseBypass == 0] {
			y = y * impactNoiseF;
		}
		y = y * noiseG;
		y = y * compressor;
		y = y * EQ;
		y = y * gain;
		y = y * panLeft; 
	}
}

function initChannelStrip {
	interface {}

	local {
		rational fs;
		rational f;
		rational g;
		rational q;
		}

	code {
	// set sample frequency to 48kHz
	fs = 48000.0;

	// init sensitiy to 1
	sens = 1.0;
	
	// int impact noise filter
	
	// impact noise filter
	f = 70.0;
	biquad[obj=impactNoiseF, type=HP, fs=fs, fc=f];
	impactNoiseBypass = 0;
	
	// init noisegate
	// tav = 1/50hz / 1/48000kHz = 0.000458240509
	// AT = 0.4
	// RT = 0.01
	// NT = 0.5 NS = 0.0
	noisegate[obj=noiseG, TAV = 0.000458240509, AT = 0.4, RT = 0.01, NT = 0.5, NS = 0.0];
	
	// init compressor
	compressor[obj=compressor, TAV = 0.000458240509, AT = 0.4, RT = 0.01, CT = 0.8, CS = 0.0];
	
	// init EQ
	
	f = 70.0;
	q = 1.0;
	g = 2.0;
	
	// EQ 1 - low frequ. shelf.
	biquad[obj=EQ, index=0, type=lowShelv, fs=fs, fc=f, q=q, g=g];
	// EQ 2 - peak. f
	f = 1000.0;
	biquad[obj=EQ, index=1, type=Peak, fs=fs, fc=f, q=q, g=g];
	// EQ 3 - high. frequ. shelf.
	f = 4000.0;
	biquad[obj=EQ, index=2, type=highShelv, fs=fs, fc=f, q=q, g=g];
	
	// gain
	gain = 2.0;
	
	// pan left
	panLeft = 1.0;
	}
}

function UI {
	interface {}

	local {
		panel		p;
		button		bLeft;
		button		bMiddle;
		button		bRight;
		led			lRed;
		led			lGreen;
		display		d;
		string		dispalyStr[3];
		integer		state;
		string		txtOpening;
		string		txtFloorNoiseFon;
		string		txtFloorNoiseFoff;
		string		txtFloorNoiseSelect;
		string		tstr;
	}

	code {
	// init UI
		// the panel
		ui[obj=p, index=0, func=dim, x=0, y=0, xle=550, yle=500];
		ui[obj=p, index=0, uuid=1, func=initPanel];
		// the display
		ui[obj=d, index=0, func=dim, x=10, y=10, xle=500, yle=300];
		ui[obj=d, index=0, uuid=11, func=initDisplay, parent=p, pIndex=0];
		// left button
		ui[obj=bLeft, index=0, func=dim, x=50, y=400, xle=50, yle=50];
		ui[obj=bLeft, index=0, uuid=21, func=initButton, parent=p, pIndex=0];
		// red led
		ui[obj=lRed, index=0, func=dim, x=150, y=400, xle=50, yle=50];
		ui[obj=lRed, index=0, uuid=31, func=initLED, parent=p, pIndex=0];
		// middle button
		ui[obj=bMiddle, index=0, func=dim, x=250, y=400, xle=50, yle=50];
		ui[obj=bMiddle, index=0, uuid=22, func=initButton, parent=p, pIndex=0];
		// green led
		ui[obj=lGreen, index=0, func=dim, x=350, y=400, xle=50, yle=50];
		ui[obj=lGreen, index=0, uuid=31, func=initLED, parent=p, pIndex=0];
		// right button
		ui[obj=bRight, index=0, func=dim, x=450, y=400, xle=50, yle=50];
		ui[obj=bRight, index=0, uuid=23, func=initButton, parent=p, pIndex=0];
		// some strings
		txtOpening = "AL-AP select with left button(lb)";
		txtFloorNoiseFon = "noise floorfilter ON\nlb to continue";
		txtFloorNoiseFoff = "noise floorfilter OFF\nlb to continue";
		txtFloorNoiseSelect = "noise floorfilter\nmb=on rb=off";
		
		tstr = " peter ";
		
	// UI behavior
	ui[obj=d, func=print, text=txtOpening];
	state = 0;
	txtFloorNoiseSelect = "";
	for [;;]{
		checkButtonPressed(bLeft) {
			if [state == 0] {
				ui[obj=d, func=print, text=txtFloorNoiseSelect];
				txtFloorNoiseSelect += tstr;
				state = 1;
			} else {
				ui[obj=d, func=print, text=txtOpening];
				state = 0;
			}
		}
		
	// of for
	}
	// of code
	}
}



main (ADSP) {
	local {
		rational x[512];
	}

	code {
		[] = initChannelStrip [];
		for [;;] {
			sampleIO[operation=read ,dest=x, channel=1];
			[x] = processChannelStrip[x];
			sampleIO[operation=write ,src=x, channel=1];
		}
	}	
}

main (GUI) {
	local {
	}
	code {
		[] = UI[];
	}	
}