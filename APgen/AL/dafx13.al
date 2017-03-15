global {
	biquad 		filter[2];
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
		string		tstr;
		rational 	fs;
		rational 	f;
		rational 	g;
		rational 	q;
		rational	f2;
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
		ui[obj=lGreen, index=0, uuid=32, func=initLED, parent=p, pIndex=0];
		// right button
		ui[obj=bRight, index=0, func=dim, x=450, y=400, xle=50, yle=50];
		ui[obj=bRight, index=0, uuid=23, func=initButton, parent=p, pIndex=0];
		// open string
		tstr = "left=LP LP;middle=HP LP;right=HP HP";
		
	// init constants
		// set sample frequency to 48kHz
		fs = 48000;
		q = 1.0;
		g = 2.0;
	
		
		// UI behavior
		ui[obj=d, func=print, text=tstr];
		ui[obj=lRed, func=LED, on=0];
		ui[obj=lGreen, func=LED, on=0];
		
		for [;;]{
			checkButtonPressed(bLeft) {
				f = 70.0;
				biquad[obj=filter, index=0, type=LP, fs=fs, fc=f ];
				biquad[obj=filter, index=1, type=LP, fs=fs, fc=f];
				ui[obj=lRed, func=LED, on=1];
				ui[obj=lGreen, func=LED, on=0];
				update(filter);
			}
			
			checkButtonPressed(bMiddle) {
				f = 1000.0;
				f2 = 2000.0;
				biquad[obj=filter, index=0, type=HP, fs=fs, fc=f];
				biquad[obj=filter, index=1, type=LP, fs=fs, fc=f2];
				ui[obj=lRed, func=LED, on=0];
				ui[obj=lGreen, func=LED, on=1];
				update(filter);
			}
			
			checkButtonPressed(bRight) {
				f = 4000.0;
				biquad[obj=filter, index=0, type=HP, fs=fs, fc=f];
				biquad[obj=filter, index=1, type=HP, fs=fs, fc=f];
				ui[obj=lRed, func=LED, on=1];
				ui[obj=lGreen, func=LED, on=1];
				update(filter);
			}
		}
	}
}



main (ADSP) {
	local {
		rational 	fs;
		rational 	f;
		rational x[512];
	}

	code {
		fs = 48000.0;
		f = 1000.0;
		
		biquad[obj=filter, index=0, type=LP, fs=fs, fc=f];
		biquad[obj=filter, index=1, type=LP, fs=fs, fc=f];

		for [;;] {
			sampleIO[operation=read ,dest=x, channel=1];
			x = filter * x;
			sampleIO[operation=write ,src=x, channel=2];
		}
	}	
}

main (MSP430) {
	local {
	}
	code {
		[] = UI[];
	}	
}

main (PC) {
	local {
	}
	code {
		[] = UI[];
	}	
}