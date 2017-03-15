global {
	biquad		bqf1[2];
	biquad		bqf2[2];
}

main(RPitest2) {
	local {
		panel		p;
		display		d;
		button		bBypass;
		button		bLP;
		button		bBP;
		button		bHP;
		button		bUp;
		button		bDown;
		button		bReset;
		
		
		
		rational 	fs;
		rational 	fLP;
		rational	fHP;
		
		rational 	g;
		rational 	q;
		rational	gain;
		

		rational	in1[1024];
		rational	in2[1024];
		rational	out1[1024];
		rational	out2[1024];
		
		integer		byPassFlag;
		string		gaintext;
		string		gainStr;

	}

	code {
	// init UI
		// the panel
		ui[obj=p, index=0, uuid=1, func=initPanel];
		// the display
		ui[obj=d, index=0, uuid=1, func=initDisplay, parent=p, pIndex=0];

		//  bypass button
		ui[obj=bBypass, index=0, uuid=1, func=initButton, parent=p, pIndex=0];
		//  low pass button
		ui[obj=bLP, index=0, uuid=2, func=initButton, parent=p, pIndex=0];
		//  band pass button
		ui[obj=bBP, index=0, uuid=3, func=initButton, parent=p, pIndex=0];
		//  band pass button
		ui[obj=bHP, index=0, uuid=4, func=initButton, parent=p, pIndex=0];

		//  up button
		ui[obj=bUp, index=0, uuid=8, func=initButton, parent=p, pIndex=0];
		//  down button
		ui[obj=bDown, index=0, uuid=7, func=initButton, parent=p, pIndex=0];
		//  reset button
		ui[obj=bReset, index=0, uuid=6, func=initButton, parent=p, pIndex=0];
		
		// set sample frequency to 44.1kHz
		fs = 44100.0;
		q = 1.0;
		g = 2.0;
		fLP = 8000.0;
		fHP = 1000.0;
		gain = 1.0;

		biquad[type=LP, obj=bqf1, index=0, fs=fs, fc=fLP];
		biquad[type=LP, obj=bqf1, index=1, fs=fs, fc=fLP];
	
		biquad[type=HP, obj=bqf2, index=0, fs=fs, fc=fHP];
		biquad[type=HP, obj=bqf2, index=1, fs=fs, fc=fHP];
			
		byPassFlag = 1;
		
		// UI behavior
		ui[obj=d, func=print, text="select: 1-bypass\n2-LP 3-BP 4-HP"];
		
		for [;;]{
			// ----------------------
			// ui processing
			// ----------------------
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

			checkButtonPressed(bBypass) {
				ui[obj=d, func=print, text="> byPass \n0-LP 1-BP 2-HP"];
				byPassFlag = 1;
			}

	
			checkButtonPressed(bLP) {
				byPassFlag = 0;
				ui[obj=d, func=print, text="> LP \n0-LP 1-BP 2-HP"];
				biquad[obj=bqf1, index=0, type=LP, fs=fs, fc=fLP];
				biquad[obj=bqf1, index=1, type=LP, fs=fs, fc=fLP];
				biquad[obj=bqf2, index=0, type=LP, fs=fs, fc=fLP];
				biquad[obj=bqf2, index=1, type=LP, fs=fs, fc=fLP];

			}

			checkButtonPressed(bBP) {
				byPassFlag = 0;
				ui[obj=d, func=print, text="> BP \n0-LP 1-BP 2-HP"];

				biquad[obj=bqf1, index=0, type=HP, fs=fs, fc=fHP];
				biquad[obj=bqf1, index=1, type=LP, fs=fs, fc=fLP];
				biquad[obj=bqf2, index=0, type=HP, fs=fs, fc=fHP];
				biquad[obj=bqf2, index=1, type=LP, fs=fs, fc=fLP];
			}
			
			checkButtonPressed(bHP) {
				byPassFlag = 0;
				ui[obj=d, func=print, text="> HP \n0-LP 1-BP 2-HP"];

				biquad[obj=bqf1, index=0, type=HP, fs=fs, fc=fHP];
				biquad[obj=bqf1, index=1, type=HP, fs=fs, fc=fHP];
				biquad[obj=bqf2, index=0, type=HP, fs=fs, fc=fHP];
				biquad[obj=bqf2, index=1, type=HP, fs=fs, fc=fHP];

			}
		
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

			// process input signals
			if [byPassFlag == 1] {
				out1 = in1;
				out2 = in2;
			} else {
				// filter
				out1 = in1 * bqf1;
				out2 = in2 * bqf2;
			}
			// process output signals and write them to the outputs
			sampleIO[operation=write ,src=out1, channel=0];
			sampleIO[operation=write ,src=out2, channel=1];


		// main loop	
		}
	// of code
	} 
}
