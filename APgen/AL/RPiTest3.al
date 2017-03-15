main(RPitest2) {
	local {
		panel		p;
		display		d;

		button		bBypass;
		button		bLimiter;
		button		bDelay;

		button		bUp;
		button		bDown;
		button		bReset;
		
		rational 	fs;
		rational	gain;
		delay		del1;
		delay		del2;
		limiter		lim1;		
		limiter		lim2;
		

		rational	c1[1024];
		rational	c2[1024];
		rational 	dc[1024];
		
		integer		byPassFlag;
		integer		limFlag;
		integer		delayFlag;
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
		//  delay button
		ui[obj=bDelay, index=0, uuid=2, func=initButton, parent=p, pIndex=0];
		//  limter button
		ui[obj=bLimiter, index=0, uuid=3, func=initButton, parent=p, pIndex=0];

		//  up button
		ui[obj=bUp, index=0, uuid=8, func=initButton, parent=p, pIndex=0];
		//  down button
		ui[obj=bDown, index=0, uuid=7, func=initButton, parent=p, pIndex=0];
		//  reset button
		ui[obj=bReset, index=0, uuid=6, func=initButton, parent=p, pIndex=0];
		
		// set sample frequency to 44.1kHz
		fs = 44100.0;
		gain = 1.0;

		// 100ms = 44100 1/s * 100ms --> N = 4410
		delay[obj=del1, index=0, N=4410, index=0];
		delay[obj=del2, index=0, N=4410, index=0];
		
		// limter
		// for Peak: tAT = 0.04ms tRT = 130ms
		// for Smother: tAT = 0.4s tRT = 0.01s
		// treshold LT = 0.3 slope LS = 1.0
		limiter[obj=lim1, index=0, ATpeak=0.00004, RTpeak=0.130, ATsmooth=0.04, RTsmooth=0.01, LT=0.3, LS=1.0];
		limiter[obj=lim2, index=0, ATpeak=0.00004, RTpeak=0.130, ATsmooth=0.04, RTsmooth=0.01, LT=0.3, LS=1.0];
		
		byPassFlag = 1;
		limFlag = 0;
		delayFlag = 0;
		
		// UI behavior
		ui[obj=d, func=print, text="select: 1-bypass\n2-Delay 3-Limiter"];
		
		for [;;]{
			// ----------------------
			// ui processing
			// ----------------------
			checkButtonPressed(bReset) {
				ui[obj=d, func=print, text="reset"];
				gain = 1.0;
				limFlag = 0;
				delayFlag = 0;
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
				ui[obj=d, func=print, text="bypass on"];
				byPassFlag = 1;
				limFlag = 0;
				delayFlag = 0;
			}

	
			checkButtonPressed(bDelay) {
				byPassFlag = 0;
				if [delayFlag == 0] {
					ui[obj=d, func=print, text="delay on"];
					delayFlag = 1;
				} else {
					ui[obj=d, func=print, text="delay off"];
					delayFlag = 0;
				}

			}

			checkButtonPressed(bLimiter) {
				byPassFlag = 0;
				if [limFlag == 0] {
					ui[obj=d, func=print, text="limter on"];
					limFlag  = 1;
				} else {
					ui[obj=d, func=print, text="limter off"];
					limFlag = 0;
				}
			}
					
			// ----------------------
			// signal processing
			// ----------------------
	
			// read input channels
			// first read operation waits for a new sample frame
			sampleIO[operation=read ,dest=c1, channel=0, wait=1];
			// second extract 2nd channel from frame -> so no waiting
			sampleIO[operation=read ,dest=c2, channel=1, wait=0];

			// gain
			c1 = c1 * gain;
			c2 = c2 * gain;

			// process input signals
			if [byPassFlag != 1] {
				// delay
				if [delayFlag == 1] {
					c1 = c1 * del1;
					// c2 = c2 * del2;
				}
				// limiter
				if [limFlag == 1] {
					c1 = c1 * lim1;
					c2 = c2 * lim1;
				}
			}
			// process output signals and write them to the outputs
			sampleIO[operation=write ,src=c1, channel=0];
			sampleIO[operation=write ,src=c2, channel=1];


		// main loop	
		}
	// of code
	} 
}
