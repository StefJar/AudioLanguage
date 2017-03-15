global {
	biquad		bqf1[2];
	biquad		bqf2[2];
}

main(RPi_DSP) {
	local {
		rational	in1[1024];
		rational	in2[1024];
		rational	out1[1024];
		rational	out2[1024];
		rational	fs;
		rational	f;
	}
	code {
		fs = 44100.0;
		f = 1000.0;

		biquad[type=LP, obj=bqf1, index=0, fs=fs, fc=f];
		biquad[type=LP, obj=bqf1, index=1, fs=fs, fc=f];
	
		biquad[type=HP, obj=bqf2, index=0, fs=fs, fc=f];
		biquad[type=HP, obj=bqf2, index=1, fs=fs, fc=f];
	
	
		for [;;] {
			// read input channels
			// first read operation waits for a new sample frame
			sampleIO[operation=read ,dest=in1, channel=0, wait=1];
			// second extract 2nd channel from frame -> so no waiting
			sampleIO[operation=read ,dest=in2, channel=1, wait=0];
			// process input signals
			out1 = in1 * bqf1;
			out2 = in2 * bqf2;
			// process output signals and write them to the outputs
			sampleIO[operation=write ,src=out1, channel=0];
			sampleIO[operation=write ,src=out2, channel=1];
			}
		
	}
}

main(RPi_UI) {
	local {
		panel		p;
		button		bLeft;
		button		bMiddle;
		button		bRight;
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
		ui[obj=d, index=0, uuid=1, func=initDisplay, parent=p, pIndex=0];
		// left button
		ui[obj=bLeft, index=0, func=dim, x=50, y=400, xle=50, yle=50];
		ui[obj=bLeft, index=0, uuid=1, func=initButton, parent=p, pIndex=0];
		// middle button
		ui[obj=bMiddle, index=0, func=dim, x=250, y=400, xle=50, yle=50];
		ui[obj=bMiddle, index=0, uuid=2, func=initButton, parent=p, pIndex=0];
		// right button
		ui[obj=bRight, index=0, func=dim, x=450, y=400, xle=50, yle=50];
		ui[obj=bRight, index=0, uuid=3, func=initButton, parent=p, pIndex=0];
		// open string
		tstr = "left=LP LP;middle=HP LP;right=HP HP";
		
	// init constants
		// set sample frequency to 48kHz
		fs = 44100.0;
		q = 1.0;
		g = 2.0;
	
		
		// UI behavior
		ui[obj=d, func=print, text=tstr];
		
		for [;;]{
			checkButtonPressed(bLeft) {
				f = 70.0;

				biquad[obj=bqf1, index=0, type=LP, fs=fs, fc=f];
				biquad[obj=bqf1, index=1, type=LP, fs=fs, fc=f];
				biquad[obj=bqf2, index=0, type=LP, fs=fs, fc=f];
				biquad[obj=bqf2, index=1, type=LP, fs=fs, fc=f];

				update(bqf1);
				update(bqf2);

			}

			checkButtonPressed(bMiddle) {
				f = 1000.0;
				f2 = 2000.0;
				biquad[obj=bqf1, index=0, type=HP, fs=fs, fc=f];
				biquad[obj=bqf1, index=1, type=LP, fs=fs, fc=f2];
				biquad[obj=bqf2, index=0, type=HP, fs=fs, fc=f];
				biquad[obj=bqf2, index=1, type=LP, fs=fs, fc=f2];
				
				update(bqf1);
				update(bqf2);
			}
			
			checkButtonPressed(bRight) {
				f = 4000.0;
				biquad[obj=bqf1, index=0, type=HP, fs=fs, fc=f];
				biquad[obj=bqf1, index=1, type=HP, fs=fs, fc=f];
				biquad[obj=bqf2, index=0, type=HP, fs=fs, fc=f];
				biquad[obj=bqf2, index=1, type=HP, fs=fs, fc=f];

				update(bqf1);
				update(bqf2);
			}

			
		}
	
	}
}
