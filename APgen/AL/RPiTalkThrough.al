main(RPitest2) {
	local {

		rational	in1[1024];
		rational	in2[1024];
		rational	out1[1024];
		rational	out2[1024];
		
		panel		p;
		display		d;

		button		bUp;
		button		bDown;
		button		bReset;

		rational	gain;
		
		string		gaintext;
		string 		gainStr;
	}

	code {
		gain = 1.0;
		
		// the panel
		ui[obj=p, index=0, uuid=1, func=initPanel];
		// the display
		ui[obj=d, index=0, uuid=1, func=initDisplay, parent=p, pIndex=0];
		
		//  up button
		ui[obj=bUp, index=0, uuid=7, func=initButton, parent=p, pIndex=0];
		//  down button
		ui[obj=bDown, index=0, uuid=8, func=initButton, parent=p, pIndex=0];
		//  reset button
		ui[obj=bReset, index=0, uuid=6, func=initButton, parent=p, pIndex=0];
		
		
		for [;;]{
			checkButtonPressed(bReset) {
				ui[obj=d, func=print, text="reset"];
				gain = 1.0;
			}

	
			checkButtonPressed(bUp) {
				if [gain < 10.0] {
					gain = gain + 0.1;
				}
				gaintext = "gain up\nValue:";
				gainStr = gain;
				gaintext += gainStr;
				ui[obj=d, func=print, text=gaintext];
			}

			checkButtonPressed(bDown) {				
				gain = gain - 0.1;
				if [gain < 0.0] {
					gain = 0.0;
				}
				gaintext = "gain down\nValue:";
				gainStr = gain;
				gaintext += gainStr;
				ui[obj=d, func=print, text=gaintext];				
			}
		
		
		
			// ----------------------
			// signal processing
			// ----------------------
	
			// read input channels
			// first read operation waits for a new sample frame
			sampleIO[operation=read ,dest=in1, channel=0, wait=1];
			// second extract 2nd channel from frame -> so no waiting
			sampleIO[operation=read ,dest=in2, channel=1, wait=0];

			out1 = in1 * gain;
			out2 = in2 * gain;

			// process output signals and write them to the outputs
			sampleIO[operation=write ,src=out1, channel=0];
			sampleIO[operation=write ,src=out2, channel=1];


		// main loop	
		}
	// of code
	} 
}
