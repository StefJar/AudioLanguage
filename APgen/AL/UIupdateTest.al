global {
	integer 	tv1;
	string		tv2;
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
		txtOpening = "test update";
		
		
	// UI behavior
	ui[obj=d, func=print, text=txtOpening];
	state = 0;
	tv1=1;
	tv2="";

	for [;;]{
		checkButtonPressed(bLeft) {
			tv1 += 1;
			tv2 += "ab";
			ui[obj=d, func=print, text=tv2];
		}
		checkButtonPressed(bRight) {
			update(tv1);
			update(tv2);
		}
		
		
	// of for
	}
	// of code
	}
}



main (UI) {
	local {
	}
	code {
		[] = UI[];
	}	
}