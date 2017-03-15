global {
	biquad		bqf1;
	biquad		bqf2;
	
	panel		p;
	display		d;
	button		bUp;
	button		bDown;
	button		bSelect;

	integer		uiState;
	integer		uiSel;
	integer		uiUpdate;		
	
	rational 	fs;
	rational 	fc;
	rational 	g;
	rational 	gNeg;
	rational 	q;
	rational	gain;
}

// init the GUI by setting the GUI dimensions
function getTextToID {
	interface {
		in		integer	selID;
		out		string	txt;
	}

	local {
	}

	code {
		if [selID == 0] {
			txt = "bypass";
		}
		if [selID == 1] {
			txt = "low pass";
		}
		if [selID == 2] {
			txt = "high pass";
		}
		if [selID == 3] {
			txt = "low shelv g+";
		}
		if [selID == 4] {
			txt = "low shelv g-";
		}
		if [selID == 5] {
			txt = "high shelv g+";
		}
		if [selID == 6] {
			txt = "high shelv g-";
		}
		if [selID == 7] {
			txt = "peak g+";
		}
		if [selID == 8] {
			txt = "peak g-";
		}
	}
}

function uiInit {
	interface {
	}

	local {
	}
	
	code {
	// init UI
	// the panel
	ui[obj=p, index=0, uuid=1, func=initPanel];
	// the display
	ui[obj=d, index=0, uuid=1, func=initDisplay, parent=p, pIndex=0];
	ui[obj=d, uuid=0, func=setTextDim, charsPerLine=16, lines=2];

	//  up button
	ui[obj=bUp, index=0, uuid=8, func=initButton, parent=p, pIndex=0];
	//  down button
	ui[obj=bDown, index=0, uuid=7, func=initButton, parent=p, pIndex=0];
	//  reset button
	ui[obj=bSelect, index=0, uuid=6, func=initButton, parent=p, pIndex=0];
	
	uiState = 0;
	uiSel = 0;
	uiUpdate = 1;
	}
}

function guiInit {
	interface {
	}

	local {
	}
	
	code {
		// the panel
		ui[obj=p, func=dim, x=0, y=0, xle=520, yle=260];
		// upper buttons
		ui[obj=bUp, func=dim, x=380, y=10, xle=50, yle=50];
		ui[obj=bSelect, func=dim, x=430, y=10, xle=50, yle=50];
		ui[obj=bDown, func=dim, x=480, y=10, xle=50, yle=50];
		
		// the display
		ui[obj=d, func=dim, x=25, y=70, xle=500, yle=100];
	}
} 

function ui {
	interface {
	}

	local {
		string		selText;
		string		actText;
	}

	code {
		checkButtonPressed(bUp) {
			if [uiState < 8] {
				uiState = uiState + 1;
			} else {
				uiState = 0;
			}
			uiUpdate = 1;
		}

		checkButtonPressed(bDown) {				
			if [uiState > 0] {
				uiState = uiState - 1;
			} else {
				uiState = 8;
			}
			uiUpdate = 1;
		}

		checkButtonPressed(bSelect) {
			if [uiState == 0] {
				biquad[type=coeff, obj=bqf1, index=0, a0=1.0, a1=0.0, a2=0.0, b1=0.0, b2=0.0];
				biquad[type=coeff, obj=bqf2, index=0, a0=1.0, a1=0.0, a2=0.0, b1=0.0, b2=0.0];
			}
			if [uiState == 1] {
				biquad[type=LP, obj=bqf1, index=0, fs=fs, fc=fc];
				biquad[type=LP, obj=bqf2, index=0, fs=fs, fc=fc];
			}
			if [uiState == 2] {
				biquad[type=HP, obj=bqf1, index=0, fs=fs, fc=fc];
				biquad[type=HP, obj=bqf2, index=0, fs=fs, fc=fc];
			}
			if [uiState == 3] {
				biquad[type=lowShelv, obj=bqf1, index=0, fs=fs, fc=fc, g=g];
				biquad[type=lowShelv, obj=bqf2, index=0, fs=fs, fc=fc, g=g];
			}
			if [uiState == 4] {
				biquad[type=lowShelv, obj=bqf1, index=0, fs=fs, fc=fc, g=gNeg];
				biquad[type=lowShelv, obj=bqf2, index=0, fs=fs, fc=fc, g=gNeg];
			}
			if [uiState == 5] {
				biquad[type=highShelv, obj=bqf1, index=0, fs=fs, fc=fc, g=g];
				biquad[type=highShelv, obj=bqf2, index=0, fs=fs, fc=fc, g=g];
			}
			if [uiState == 6] {
				biquad[type=highShelv, obj=bqf1, index=0, fs=fs, fc=fc, g=gNeg];
				biquad[type=highShelv, obj=bqf2, index=0, fs=fs, fc=fc, g=gNeg];
			}
			if [uiState == 7] {
				biquad[type=Peak, obj=bqf1, index=0, fs=fs, fc=fc, g=g, q=q];
				biquad[type=Peak, obj=bqf2, index=0, fs=fs, fc=fc, g=g, q=q];
			}
			if [uiState == 8] {
				biquad[type=Peak, obj=bqf1, index=0, fs=fs, fc=fc, g=gNeg, q=q];
				biquad[type=Peak, obj=bqf2, index=0, fs=fs, fc=fc, g=gNeg, q=q];
			}
			uiSel = uiState;
			uiUpdate = 1;
			
			update(bqf1);
			update(bqf2);
			update(uiState);
			update(uiSel);
			update(uiUpdate);
		}

		if [uiUpdate == 1] {
			if [uiSel == uiState] {
				actText = ">";
			} else {
				actText = " ";
			}
			[selText] = getTextToID[uiState];
			actText += selText;
			
			ui[obj=d, func=print, text=actText];
			
			uiUpdate = 0;
		}
	}
}


main(PC) {
	local {
	}
	code { 
		[] = guiInit [];
		[] = uiInit [];
		for[;;] {
			[] = ui [];
		}
	} 
} 

main(RPi) {
	local {
		rational	in1[1024];
		rational	in2[1024];
		rational	out1[1024];
		rational	out2[1024];		
	}

	code {
		// init UI
		[] = uiInit [];
			
		// set sample frequency to 44.1kHz
		fs = 44100.0;
		q = 1.0;
		g = 2.0;
		fc = 1000.0;
		gNeg = g * -1.0;
	
		biquad[type=coeff, obj=bqf1, index=0, a0=1.0, a1=0.0, a2=0.0, b1=0.0, b2=0.0];
		biquad[type=coeff, obj=bqf2, index=0, a0=1.0, a1=0.0, a2=0.0, b1=0.0, b2=0.0];
				
		for [;;]{
			// ----------------------
			// ui processing
			// ----------------------
			[] = ui[];
							
			// ----------------------
			// signal processing
			// ----------------------
	
			// read input channels
			// first read operation waits for a new sample frame
			sampleIO[operation=read ,dest=in1, channel=0, wait=1];
			// second extract 2nd channel from frame -> so no waiting
			sampleIO[operation=read ,dest=in2, channel=1, wait=0];

			// filter
			out1 = in1 * bqf1;
			out2 = in2 * bqf2;
			
			// process output signals and write them to the outputs
			sampleIO[operation=write ,src=out1, channel=0];
			sampleIO[operation=write ,src=out2, channel=1];


		// main loop	
		}
	// of code
	} 
}
