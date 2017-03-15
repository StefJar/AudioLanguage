
// ------------------------------------------------
// signal processing types & functions
// ------------------------------------------------

// type for the input line
typedef tDAPinput {
	rational	g;
	delay		d;
	biquad		eq[5];	
}

// type of the output line
typedef tDAPoutput {
	delay		d;
	biquad		xo[3];
	biquad		eq[5];
	rational	g;
	limiter		l;
}


// processes a vector of input samples with the defined channel strip
// the function results into an endless loop
function processInputChannel {
	interface {
		in		rational	x[256];
		in		tDAPinput	ichannel;
		out		rational	y[256];
	}

	local {
	}

	code {
		y = x * ichannel.d;
		y = y * ichannel.g;
		y = y * ichannel.eq;
	}
}

// processes the output channel
function processOutputChannel {
	interface {
		in		rational	x[256];
		in		tDAPoutput	ochannel;
		out		rational	y[256];
	}

	local {
	}

	code {
		y = x * ochannel.d;
		y = y * ochannel.xo;
		y = y * ochannel.eq;
		y = y * ochannel.g;
		y = y * ochannel.l;
	}
}

// inits the input channel
function initInputChannel {
	interface {
		in		tDAPinput	ichannel;
	}

	local {
	}

	code {
		ichannel.g = 1.0;
		delay[obj=ichannel.d, N=1, Nindx=0, offset=0];
		biquad[type=coeff, obj=ichannel.eq, index=0];
		biquad[type=coeff, obj=ichannel.eq, index=1];
		biquad[type=coeff, obj=ichannel.eq, index=2];
		biquad[type=coeff, obj=ichannel.eq, index=3];
		biquad[type=coeff, obj=ichannel.eq, index=4];
	}
}

// inits the output channel
function initOutputChannel {
	interface {
		in		tDAPoutput	ochannel;
	}

	local {
	}

	code {
		delay[obj=ochannel.d, N=1, Nindx=0, offset=0];
		// crossover filter
		biquad[type=coeff, obj=ochannel.xo, index=0];
		biquad[type=coeff, obj=ochannel.xo, index=1];
		biquad[type=coeff, obj=ochannel.xo, index=2];
		
		// EQ
		biquad[type=coeff, obj=ochannel.eq, index=0];
		biquad[type=coeff, obj=ochannel.eq, index=1];
		biquad[type=coeff, obj=ochannel.eq, index=2];
		biquad[type=coeff, obj=ochannel.eq, index=3];
		biquad[type=coeff, obj=ochannel.eq, index=4];
		// gain
		ochannel.g = 1.0;
		// limiter
		limiter[obj=ochannel.l, ATpeak=0.9, RTpeak=0.7, ATsmooth=0.045,RTsmooth=0.056, LT=0.045, LS=0.0465];
	}
}


// ------------------------------------------------
// UI types & functions
// ------------------------------------------------

// UI controls
typedef tUIcontrolPanel {
	panel	p;
	display	d;
	button	rb;
	button	lb;
	button	mb;
	led		rLED;
	led		gLED;
}

function UIcontrolInit {
	interface {
		in		tUIcontrolPanel	cp;
	}

	local {
	}

	code {
	// the panel
	ui[obj=cp.p, index=0, func=dim, x=0, y=0, xle=550, yle=500];
	ui[obj=cp.p, index=0, uuid=1, func=initPanel];
	
	// the display
	ui[obj=cp.d, index=0, func=dim, x=10, y=10, xle=500, yle=300];
	ui[obj=cp.d, index=0, uuid=11, func=initDisplay, parent=cp.p, pIndex=0];
	
	// left button
	ui[obj=cp.lb, index=0, func=dim, x=50, y=400, xle=50, yle=50];
	ui[obj=cp.lb, index=0, uuid=21, func=initButton, parent=cp.p, pIndex=0];
	
	// red led
	ui[obj=cp.rLED, index=0, func=dim, x=150, y=400, xle=50, yle=50];
	ui[obj=cp.rLED, index=0, uuid=31, func=initLED, parent=cp.p, pIndex=0];
	
	// middle button
	ui[obj=cp.mb, index=0, func=dim, x=250, y=400, xle=50, yle=50];
	ui[obj=cp.mb, index=0, uuid=22, func=initButton, parent=cp.p, pIndex=0];
	
	// green led
	ui[obj=cp.gLED, index=0, func=dim, x=350, y=400, xle=50, yle=50];
	ui[obj=cp.gLED, index=0, uuid=32, func=initLED, parent=cp.p, pIndex=0];
	
	// right button
	ui[obj=cp.rb, index=0, func=dim, x=450, y=400, xle=50, yle=50];
	ui[obj=cp.rb, index=0, uuid=23, func=initButton, parent=cp.p, pIndex=0];


	
	// open string
	ui[obj=cp.d, func=print, text="DAP 26"];
	ui[obj=cp.rLED, func=LED, on=0];
	ui[obj=cp.gLED, func=LED, on=0];
	}
}

// function for selecting the input and output channel
function UIselectInputOutput {
	interface {
		// the control panel
		in		tUIcontrolPanel	cp;
		// sel = 0 -> input
		// sel = 1 -> output
		out		integer			sel; 
	}
	local {
		// control flag
		integer cf;
	}
	code {
		// display start text
		ui[obj=cp.d, func=print, text="input <-\noutput"];
		sel = 0;
		cf = 0;
		// loop till the right button is pressed
		while [cf != 2] {
			// check left button
			checkButtonPressed(cp.lb) {
				if [sel == 0] {
					sel = 1;
				} else {
					sel = 0;
				}
				cf = 1;
			}
			// check middle button
			checkButtonPressed(cp.mb) {
				if [sel == 0] {
					sel = 1;
				} else {
					sel = 0;
				}
				cf = 1;
			}
			// check right button
			checkButtonPressed(cp.rb) {
				ui[obj=cp.d, func=print, text="aa"];
				cf = 2;
			}
			// display new text if something changed
			if [cf == 1] {
				if [sel == 0] {
					ui[obj=cp.d, func=print, text="input <-\noutput"];
				} else {
					ui[obj=cp.d, func=print, text="input\noutput <-"];
				}
				cf = 0;
			}
		}			
	}
}


function UIselectChannel {
	interface {
		// the control panel
		in		tUIcontrolPanel	cp;
		// sel = 1	channel 1
		// sel = 2 channel 2
		out		integer			sel; 
	}
	local {
		// control flag
		integer cf;
	}
	code {
		// display start text
		ui[obj=cp.d, func=print, text="channel 1"];
		sel = 1;
		cf = 0;
		// loop till the right button is pressed
		while [cf != 2] {
			// check left button
			checkButtonPressed(cp.lb) {
				sel = sel - 1;
				if [sel < 1] {
					sel = 2;
				}
				cf = 1;
			}
			// check middle button
			checkButtonPressed(cp.mb) {
				sel = sel + 1;
				if [sel > 2] {
					sel = 1;
				}
				cf = 1;
			}
			// check right button
			checkButtonPressed(cp.rb) {
				cf = 2;
			}
			// display new text if something changed
			if [cf == 1] {
				if [sel == 1] {
					ui[obj=cp.d, func=print, text="channel 1"];
				}
				if [sel == 2] {
					ui[obj=cp.d, func=print, text="channel 2"];
				}
				cf = 0;
			}
		}			
	}
}

function UIselectInputElement {
	interface {
		// the control panel
		in		tUIcontrolPanel	cp;
		// sel = 0 -> back
		// sel = 1	-> gain
		// sel = 2 -> delay
		// sel = 3 -> eq	
		out		integer			sel; 
	}
	local {
		// control flag
		integer cf;
	}
	code {
		// display start text
		ui[obj=cp.d, func=print, text="gain"];
		sel = 1;
		cf = 0;
		// loop till the right button is pressed
		while [cf != 2] {
			// check left button
			checkButtonPressed(cp.lb) {
				sel = sel - 1;
				if [sel < 0] {
					sel = 3;
				}
				cf = 1;
			}
			// check middle button
			checkButtonPressed(cp.mb) {
				sel = sel + 1;
				if [sel > 3] {
					sel = 0;
				}
				cf = 1;
			}
			// check right button
			checkButtonPressed(cp.rb) {
				sel = 0;
				cf = 2;
			}
			// display new text if something changed
			if [cf == 1] {
				if [sel == 0] {
					ui[obj=cp.d, func=print, text="back"];
				}
				if [sel == 1] {
					ui[obj=cp.d, func=print, text="gain"];
				}
				if [sel == 2] {
					ui[obj=cp.d, func=print, text="delay"];
				}
				if [sel == 3] {
					ui[obj=cp.d, func=print, text="equalizer"];
				}
				cf = 0;
			}
		}			
	}
}

function UIsetGain {
	interface {
		// the control panel
		in		tUIcontrolPanel	cp;
		// gain variable 
		in		rational		g;
		// lower bound
		in		rational		gMin;
		// upper bound
		in		rational		gMax;
		// step sitz
		in		rational		gStep;
	}
	local {
		// control flag
		integer 	cf;
		string		displayStrBasic;
		string		valueStr;
		string		displayStr;
	}
	code {
		// display start text
		displayStrBasic = "gain value:\n";
		
		displayStr = displayStrBasic;
		valueStr = g;
		displayStr += valueStr;
		
		ui[obj=cp.d, func=print, text=displayStr];
		cf = 0;
		// loop till the right button is pressed
		while [cf != 2] {
			// check left button
			checkButtonPressed(cp.lb) {
				g = g - gStep;
				cf = 1;
			}
			// check middle button
			checkButtonPressed(cp.mb) {
				g = g + gStep;
				cf = 1;
			}
			// check right button
			checkButtonPressed(cp.rb) {
				cf = 2;
			}
			// bounds check
			if [cf != 0] {
				if [g < gMin] {
					g = gMin;
				}
				if [g > gMax] {
					g = gMax;
				}
			}
			
			// display new text if something changed
			if [cf == 1] {
				displayStr = displayStrBasic;
				valueStr = g;
				displayStr += valueStr;
				cf = 0;
			}
		}			
	}
}

function UIsetInpChannelValues {
	interface {
		// the control panel
		in		tUIcontrolPanel	cp;
		//
		in		tDAPinput		iCh;	
	}
	local {
		// control flag
		integer		sel;
	}
	code {
		sel = 0;
		// loop till the right button is pressed
		while [sel != 0] {
			[sel] = UIselectInputElement[cp];
			if [sel == 1] {
				[] = UIsetGain[cp, iCh.g, 0.0, 1.0, 0.1];
			}
		}
	}
}



global {
		tDAPinput	iChan1;	
		tDAPinput	iChan2;
		tDAPoutput	oChan1;
		tDAPoutput	oChan2;
		tDAPoutput	oChan3;
		tDAPoutput	oChan4;
}

main(DAP26_ADSP) {
	local {
		rational	in1[256];
		rational	in2[256];
		rational	out[256];
	}
	code {
		[] = initInputChannel[iChan1];
		[] = initInputChannel[iChan2];
		
		[] = initOutputChannel[oChan1];
		[] = initOutputChannel[oChan2];
		[] = initOutputChannel[oChan3];
		[] = initOutputChannel[oChan4];
	
	
		for [;;] {
			// read input channels
			// first read operation waits for a new sample frame
			sampleIO[operation=read ,dest=in1, channel=1, wait=1];
			// second extract 2nd channel from frame -> so no waiting
			sampleIO[operation=read ,dest=in2, channel=2, wait=0];
			// process input signals
			[in1] = processInputChannel[in1,iChan1];
			[in2] = processInputChannel[in2,iChan1];
			// process output signals and write them to the outputs
			[out] = processOutputChannel[in1,oChan1];
			sampleIO[operation=write ,src=out, channel=1];
			
			[out] = processOutputChannel[in1,oChan2];
			sampleIO[operation=write ,src=out, channel=2];

			[out] = processOutputChannel[in2,oChan3];
			// sampleIO[operation=write ,src=out, channel=3];
			
			[out] = processOutputChannel[in2,oChan4];
			// sampleIO[operation=write ,src=out, channel=4];
		}
		
	}
}

main(DAP26_UI) {
	local {
		tUIcontrolPanel		cp;
		integer				sel;
	}
	code {
		// select input / output
		[] = UIcontrolInit[cp];
		for [;;] {
			[sel] = UIselectInputOutput[cp];
			if [sel == 0] {
				// select input channel
				[sel] = UIselectChannel[cp];
				if [sel == 1] {
					// select & set the values for input channel 1
					[] = UIsetInpChannelValues[cp, iChan1];
				}
				if [sel == 2] {
					// select & set the values for input channel 2
					[] = UIsetInpChannelValues[cp, iChan2];
				}
				
			} 
		}
	}
}
