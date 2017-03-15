global {
	// GUI elements
	panel		pan;
	display		dis;
	button		db1;
	button		db2;
	button		db3;
	button		db4;
	button		db5;
	button		ub1;
	button		ub2;
	button		ub3;
	
	// the gain
	rational	gain;
	
	// the ui state
	integer 	uiState;
}

// inits the UI
function initUI {
	interface {
	}

	local {
	}

	code {
		// the panel
		ui[obj=pan, uuid=0, func=initPanel];
		
		// upper buttons
		ui[obj=ub1, uuid=6, func=initButton, parent=pan];
		ui[obj=ub2, uuid=7, func=initButton, parent=pan];
		ui[obj=ub3, uuid=8, func=initButton, parent=pan];
	
		
		// the display
		ui[obj=dis, uuid=0, func=initDisplay, parent=pan];
		ui[obj=dis, uuid=0, func=setTextDim, charsPerLine=16, lines=2];
		
		
		// lower buttons
		// from left to right
		ui[obj=db1, uuid=1, func=initButton, parent=pan];
		ui[obj=db2, uuid=2, func=initButton, parent=pan];	
		ui[obj=db3, uuid=3, func=initButton, parent=pan];
		ui[obj=db4, uuid=4, func=initButton, parent=pan];
		ui[obj=db5, uuid=5, func=initButton, parent=pan];
		
		uiState = 1;
	}
}

// init the GUI by setting the GUI dimensions
function initGUI {
	interface {
	}

	local {
	}

	code {
		// the panel
		ui[obj=pan, func=dim, x=0, y=0, xle=520, yle=260];
		// upper buttons
		ui[obj=ub1, func=dim, x=380, y=10, xle=50, yle=50];
		ui[obj=ub2, func=dim, x=430, y=10, xle=50, yle=50];
		ui[obj=ub3, func=dim, x=480, y=10, xle=50, yle=50];
		
		// the display
		ui[obj=dis, func=dim, x=25, y=70, xle=500, yle=100];
	
		// lower buttons
		// from left to right
		ui[obj=db1, func=dim, x=10, y=190, xle=50, yle=50];
		ui[obj=db2, func=dim, x=70, y=190, xle=50, yle=50];
		ui[obj=db3, func=dim, x=130, y=190, xle=50, yle=50];
		ui[obj=db4, func=dim, x=190, y=190, xle=50, yle=50];
		ui[obj=db5, func=dim, x=320, y=190, xle=50, yle=50];
	}
}

// init the GUI by setting the GUI dimensions
function checkUI {
	interface {
	}

	local {
		string		gaintext;
		string		gainStr; 
	}

	code {
		checkButtonPressed(ub2) {
			ui[obj=dis, func=print, text="reset"];
			gain = 1.0;
			uiState = 2;
			update(gain);
			update(uiState);			
		}
		
		checkButtonPressed(ub3) {
			if [gain < 10.0] {
				gain = gain + 0.1;
			}
			uiState = 2;
			update(gain);
			update(uiState);			
		}

		checkButtonPressed(ub1) {				
			gain = gain - 0.1;
			if [gain < 0.0] {
				gain = 0.0;
			}
			uiState = 2;
			update(gain);
			update(uiState);			
		}
		
		if [uiState == 1] {
			ui[obj=dis, func=print, text="UI Remote Control\nDemo"];
			uiState = 0;
		}
		if [uiState == 2] {
			gaintext = "gain: \n";
			gainStr = gain;
			gaintext += gainStr;
			ui[obj=dis, func=print, text=gaintext];
			uiState = 0;
		}
	}
}



// RPi target
main(RPi) {
	local {
		rational	in1[1024];
		rational	in2[1024];
		rational	out1[1024];
		rational	out2[1024];
	}

	code {
		[] = initUI[];	
		for [;;]{
			// ----------------------
			// ui processing
			// ----------------------
			[] = checkUI[];		
			// ----------------------
			// signal processing
			// ----------------------
	
			// read input channels
			// first read operation waits for a new sample frame
			sampleIO[operation=read ,dest=in1, channel=0, wait=1];
			// second extract 2nd channel from frame -> so no waiting
			sampleIO[operation=read ,dest=in2, channel=1, wait=0];

			// gain
			in1 = in1 * gain;
			in2 = in2 * gain;

			// process output signals and write them to the outputs
			sampleIO[operation=write ,src=out1, channel=0];
			sampleIO[operation=write ,src=out2, channel=1];


		// main loop	
		}
	// of code
	} 
}

// Remote Control target
main(RC) {
	local {
	}

	code {
		[] = initGUI[];
		[] = initUI[];	
		for [;;]{
			// ----------------------
			// ui processing
			// ----------------------
			[] = checkUI[];		
			// ----------------------
			// signal processing
			// ----------------------


		// main loop	
		}
	// of code
	} 

}
