global {
	// Filters
	biquad LinFilter[3];
	biquad RinFilter[3];
	biquad LoutFilter[3];
	biquad RoutFilter[3];
	// routing constants
	// 0 - from Lin
	// 1 - from Rin
	// 2 - mute
	integer LoutInpSel;
	integer RoutInpSel;
	// volume
	rational volume;
	
	// UI
	panel		p;
	display		d;
	button		bUp;
	button		bDown;
	button		bSelect;

	integer		uiState;
	integer		uiSel;
	integer		uiUpdate;
	integer		uiSelChannel;
	integer		uiMenuSel;
	integer		uiFilterBankSel;
	// 0 - input left
	// 1 - input right
	// 2 - output left
	// 3 - output right
	integer		uiFilterIndex;
	integer		uiFilterTypeSel;
	// 0 - bypass
	// 1 - lowpass
	// 2 - highpass
	// 3 - low shelf
	// 4 - high shelf
	// 5 - peak
	rational 	ffreq;
	rational 	fgain;
	rational 	fquality;
	rational	fs;
}

function dspInit {
	interface {
	}

	local {
		integer i;
	}
	
	code {
		i = 0;
		while [i < 3] {
			biquad[type=coeff, obj=LinFilter, index=i, a0=1.0, a1=0.0, a2=0.0, b1=0.0, b2=0.0];
			biquad[type=coeff, obj=RinFilter, index=i, a0=1.0, a1=0.0, a2=0.0, b1=0.0, b2=0.0];
			biquad[type=coeff, obj=LoutFilter, index=i, a0=1.0, a1=0.0, a2=0.0, b1=0.0, b2=0.0];
			biquad[type=coeff, obj=RoutFilter, index=i, a0=1.0, a1=0.0, a2=0.0, b1=0.0, b2=0.0];
			i = i+ 1;
			}
		LoutInpSel = 0;
		RoutInpSel = 1;
		fs = 48000.0;
		volume = 1.0;
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

	// up button
	ui[obj=bUp, index=0, uuid=8, func=initButton, parent=p, pIndex=0];
	// down button
	ui[obj=bDown, index=0, uuid=7, func=initButton, parent=p, pIndex=0];
	// select button
	ui[obj=bSelect, index=0, uuid=6, func=initButton, parent=p, pIndex=0];
	
	uiState = 0;
	uiSel = 0;
	uiUpdate = 1;
	uiSelChannel = 0;
	uiMenuSel = 0;
	
	uiFilterBankSel = 0;
	uiFilterIndex = 0;
	uiFilterTypeSel = 0;
	ffreq = 7500.0;
	fgain = 1.0;
	fquality = 1.0;
	}
}

function getHeaderText {
	interface {
		out string txt;
	}

	local {
	}
	
	code {
		if [uiState == 0] {
			txt = "RPi AL/AP demo";		
		}
		if [uiState == 10] {
			txt = "select part";
		}

		if [uiState == 20] {
			txt = "filter bank";
		}

		if [uiState == 21] {
			txt = "filter index";
		}

		if [uiState == 22] {
			txt = "filter type";
		}

		if [uiState == 23] {
			txt = "frequency";
		}

		if [uiState == 24] {
			txt = "gain";
		}

		if [uiState == 25] {
			txt = "quality";
		}

		if [uiState == 30] {
			txt = "volume";
		}

		if [uiState == 40] {
			txt = "routing";
		}

		if [uiState == 41] {
			txt = "left output";
		}

		if [uiState == 42] {
			txt = "right output";
		}


	}
}

function getSelText {
	interface {
		out string txt;
	}

	local {
		string valToStr;
	}
	
	code {
		// start screen
		if [uiState == 0] {
			txt = "press select";
		}
		// input, output, signal routing select
		if [uiState == 10] {
			if [uiMenuSel == uiSel] {
				txt = "> ";
			} else {
				txt = "  ";
			} 
			if [uiSel == 0] {
				txt += "filter bank";
			}
		
			if [uiSel == 1] {
				txt += "routing";
			}

			if [uiSel == 2] {
				txt += "volume";
			}

		}
		// filter bank
		if [uiState == 20] {
			if [uiFilterBankSel == uiSel] {
				txt = "> ";
			} else {
				txt = "  ";
			} 
			if [uiSel == 0] {
				txt += "left in";
			}
			if [uiSel == 1] {
				txt += "right in";
			}
			if [uiSel == 2] {
				txt += "left out";
			}
			if [uiSel == 3] {
				txt += "right out";
			}
		}
		
		// filter index
		if [uiState == 21] {
			if [uiFilterIndex == uiSel] {
				txt = "> ";
			} else {
				txt = "  ";
			} 
			txt += "index ";
			valToStr = uiSel; 
			txt += valToStr;
		}

		// filter type
		if [uiState == 22] {
			if [uiFilterTypeSel == uiSel] {
				txt = "> ";
			} else {
				txt = "  ";
			} 
			if [uiSel == 0] {
				txt += "bypass";
			}
			if [uiSel == 1] {
				txt += "lowpass";
			}
			if [uiSel == 2] {
				txt += "highpass";
			}
			if [uiSel == 3] {
				txt += "low shelf";
			}
			if [uiSel == 4] {
				txt += "high shelf";
			}
			if [uiSel == 5] {
				txt += "peak";
			}
		}

		// freqency
		if [uiState == 23] {
			txt = ffreq;
			txt += " Hz";
		}

		// gain
		if [uiState == 24] {
			txt = fgain;
		}

		// quality
		if [uiState == 25] {
			txt = fquality;
		}

		// volume
		if [uiState == 30] {
			txt = volume;
		}


		// signal routing
		if [uiState == 40] {
			if [uiSelChannel == uiSel] {
				txt = "> ";
			} else {
				txt = "  ";
			}
			if [uiSel == 0] {
				txt += "left in";
			}
			if [uiSel == 1] {
				txt += "right in";
			}

		}
		
		// signal routing left channel
		if [uiState == 41] {
			if [uiSelChannel == uiSel] {
				txt = "> ";
			} else {
				txt = "  ";
			}
			if [uiSel == 0] {
				txt += "left out";
			}
			if [uiSel == 1] {
				txt += "right out";
			}
			if [uiSel == 2] {
				txt += "mute";
			}
		}
		// signal routing right channel
		if [uiState == 42] {
			if [uiSelChannel == uiSel] {
				txt = "> ";
			} else {
				txt = "  ";
			}
			if [uiSel == 0] {
				txt += "left out";
			}
			if [uiSel == 1] {
				txt += "right out";
			}
			if [uiSel == 2] {
				txt += "mute";
			}
		}
	}
}

function processFilterSet {
	interface {
	}

	local {
	}
	
	code {
		// uiFilterBankSel
		// 0 - input left
		// 1 - input right
		// 2 - output left
		// 3 - output right
		
		// uiFilterTypeSel
		// 0 - bypass
		// 1 - lowpass
		// 2 - highpass
		// 3 - low shelf
		// 4 - high shelf
		// 5 - peak
	
	
		// all pass
		if [uiFilterTypeSel == 0] {
			if [uiFilterBankSel == 0] {
				biquad[type=coeff, obj=LinFilter, index=uiFilterIndex, a0=1.0, a1=0.0, a2=0.0, b1=0.0, b2=0.0];
			}
			if [uiFilterBankSel == 1] {
				biquad[type=coeff, obj=RinFilter, index=uiFilterIndex, a0=1.0, a1=0.0, a2=0.0, b1=0.0, b2=0.0];
			}
			if [uiFilterBankSel == 2] {
				biquad[type=coeff, obj=LoutFilter, index=uiFilterIndex, a0=1.0, a1=0.0, a2=0.0, b1=0.0, b2=0.0];
			}
			if [uiFilterBankSel == 3] {
				biquad[type=coeff, obj=RoutFilter, index=uiFilterIndex, a0=1.0, a1=0.0, a2=0.0, b1=0.0, b2=0.0];
			}
		}

		// low pass
		if [uiFilterTypeSel == 1] {
			if [uiFilterBankSel == 0] {
				biquad[type=LP, obj=LinFilter, index=uiFilterIndex, fs=fs, fc=ffreq];
			}
			if [uiFilterBankSel == 1] {
				biquad[type=LP, obj=RinFilter, index=uiFilterIndex, fs=fs, fc=ffreq];
			}
			if [uiFilterBankSel == 2] {
				biquad[type=LP, obj=LoutFilter, index=uiFilterIndex, fs=fs, fc=ffreq];
			}
			if [uiFilterBankSel == 3] {
				biquad[type=LP, obj=RoutFilter, index=uiFilterIndex, fs=fs, fc=ffreq];
			}
		}

		// high pass
		if [uiFilterTypeSel == 2] {
			if [uiFilterBankSel == 0] {
				biquad[type=HP, obj=LinFilter, index=uiFilterIndex, fs=fs, fc=ffreq];
			}
			if [uiFilterBankSel == 1] {
				biquad[type=HP, obj=RinFilter, index=uiFilterIndex, fs=fs, fc=ffreq];
			}
			if [uiFilterBankSel == 2] {
				biquad[type=HP, obj=LoutFilter, index=uiFilterIndex, fs=fs, fc=ffreq];
			}
			if [uiFilterBankSel == 3] {
				biquad[type=HP, obj=RoutFilter, index=uiFilterIndex, fs=fs, fc=ffreq];
			}
		}

		// low shelf
		if [uiFilterTypeSel == 3] {
			if [uiFilterBankSel == 0] {
				biquad[type=lowShelv, obj=LinFilter, index=uiFilterIndex, fs=fs, fc=ffreq, g=fgain];
			}
			if [uiFilterBankSel == 1] {
				biquad[type=lowShelv, obj=RinFilter, index=uiFilterIndex, fs=fs, fc=ffreq, g=fgain];
			}
			if [uiFilterBankSel == 2] {
				biquad[type=lowShelv, obj=LoutFilter, index=uiFilterIndex, fs=fs, fc=ffreq, g=fgain];
			}
			if [uiFilterBankSel == 3] {
				biquad[type=lowShelv, obj=RoutFilter, index=uiFilterIndex, fs=fs, fc=ffreq, g=fgain];
			}
		}

		// high shelf
		if [uiFilterTypeSel == 4] {
			if [uiFilterBankSel == 0] {
				biquad[type=highShelv, obj=LinFilter, index=uiFilterIndex, fs=fs, fc=ffreq, g=fgain];
			}
			if [uiFilterBankSel == 1] {
				biquad[type=highShelv, obj=RinFilter, index=uiFilterIndex, fs=fs, fc=ffreq, g=fgain];
			}
			if [uiFilterBankSel == 2] {
				biquad[type=highShelv, obj=LoutFilter, index=uiFilterIndex, fs=fs, fc=ffreq, g=fgain];
			}
			if [uiFilterBankSel == 3] {
				biquad[type=highShelv, obj=RoutFilter, index=uiFilterIndex, fs=fs, fc=ffreq, g=fgain];
			}
		}

		// peak
		if [uiFilterTypeSel == 5] {
			if [uiFilterBankSel == 0] {
				biquad[type=Peak, obj=LinFilter, index=uiFilterIndex, fs=fs, fc=ffreq, g=fgain, q=fquality];
			}
			if [uiFilterBankSel == 1] {
				biquad[type=Peak, obj=RinFilter, index=uiFilterIndex, fs=fs, fc=ffreq, g=fgain, q=fquality];
			}
			if [uiFilterBankSel == 2] {
				biquad[type=Peak, obj=LoutFilter, index=uiFilterIndex, fs=fs, fc=ffreq, g=fgain, q=fquality];
			}
			if [uiFilterBankSel == 3] {
				biquad[type=Peak, obj=RoutFilter, index=uiFilterIndex, fs=fs, fc=ffreq, g=fgain, q=fquality];
			}
		}

		// update
		if [uiFilterBankSel == 0] {
			update(LinFilter);
		}
		if [uiFilterBankSel == 1] {
			update(RinFilter);
		}
		if [uiFilterBankSel == 2] {
			update(LoutFilter);
		}
		if [uiFilterBankSel == 3] {
			update(RoutFilter);
		}
	}
}

function uiDisplay {
	interface {
	}

	local {
		string		selText;
		string		headerText;
		string		dispText;
		integer		stateChange;
	}
	
	code {
		// select button check
		checkButtonPressed(bSelect) {
			// start screen
			if [uiState == 0] {
				uiState = 10;
				stateChange = 1;
			}
			// dsp/routing select
			if [stateChange == 0] { 
				if [uiState == 10] {
					uiMenuSel = uiSel;
					if [uiSel == 0] {
						uiState = 20;
					}
					if [uiSel == 1] {
						uiState = 40;
						uiSel = uiSelChannel;
					}
					if [uiSel == 2] {
						uiState = 30;
					}
					stateChange = 1;
					update(uiMenuSel);
				}
			}

			// filter bank select
			if [stateChange == 0] { 
				if [uiState == 20] {
					uiFilterBankSel = uiSel;
					uiSel = uiFilterIndex;
					uiState = 21;
					stateChange = 1;
					update(uiFilterBankSel);
				}
			}

			// filter index select
			if [stateChange == 0] { 
				if [uiState == 21] {
					uiFilterIndex = uiSel;
					uiSel = uiFilterTypeSel;
					uiState = 22;
					stateChange = 1;
					update(uiFilterIndex);
				}
			}

			// filter type select
			if [stateChange == 0] { 
				if [uiState == 22] {
					uiFilterTypeSel = uiSel;
					update(uiFilterTypeSel);
					// exit for bypass
					if [uiFilterTypeSel == 0] {
						[] = processFilterSet[];
						uiState = 10;
						uiSel = 0;
					} else {
						uiState = 23;
					}
					stateChange = 1;
				}
			}

			// filter freq select
			if [stateChange == 0] { 
				if [uiState == 23] {
					// exit for low/high pass
					if [uiFilterTypeSel < 3] {
						[] = processFilterSet[];
						uiState = 10;
						uiSel = 0;
					} else {
						uiState = 24;
					}
					update(ffreq);
					stateChange = 1;
				}
			}

			// filter gain select
			if [stateChange == 0] { 
				if [uiState == 24] {
					// exit for shelving filters
					if [uiFilterTypeSel < 5] {
						[] = processFilterSet[];
						uiState = 10;
						uiSel = 0;
					} else {
						uiState = 25;
					}
					update(fgain);
					stateChange = 1;
				}
			}

			// filter qaulity select
			if [stateChange == 0] { 
				if [uiState == 25] {
					// exit for shelving filters
					[] = processFilterSet[];
					uiState = 10;
					uiSel = 0;
					update(fquality);
					stateChange = 1;
				}
			}

			// volume
			if [stateChange == 0] { 
				if [uiState == 30] {
					uiState = 10;
					stateChange = 1;
				}
			}

			// routing source select
			if [stateChange == 0] {
				if [uiState == 40] {
					uiSelChannel = uiSel;
					if [uiSelChannel == 0] {
						uiState = 41;
						uiSel = LoutInpSel;
						uiSelChannel = LoutInpSel;
					} else {
						uiState = 42;
						uiSel = RoutInpSel;
						uiSelChannel = RoutInpSel;
					}
					update(uiSelChannel);
					stateChange = 1;
				}
			}

			// routing left destination select
			if [stateChange == 0] {
				if [uiState == 41] {
					if [uiSel == 2] {
						LoutInpSel = uiSel;
						stateChange = 1;
						uiState = 10;
						uiSelChannel = 0;
						uiSel = 0;					
					} else {
						if [RoutInpSel != uiSel] {
							LoutInpSel = uiSel;
							stateChange = 1;
							uiState = 10;
							uiSelChannel = 0;
							uiSel = 0;
						}
					}
					update(LoutInpSel);
				}
			}

			// routing right destination select
			if [stateChange == 0] {
				if [uiState == 42] {
					if [uiSel == 2] {
						RoutInpSel = uiSel;
						stateChange = 1;
						uiState = 10;
						uiSelChannel = 0;
						uiSel = 0;					
					} else {
						if [LoutInpSel != uiSel] {
							RoutInpSel = uiSel;
							stateChange = 1;
							uiState = 10;
							uiSelChannel = 0;
							uiSel = 0;
						}
					}
					update(RoutInpSel);
				}
			}
			uiUpdate = 1;

			update(uiState);
			update(uiSel);
			update(uiUpdate);

			stateChange = 0;			
		}

		// up button check
		checkButtonPressed(bUp) {
			// DSP element select
			if [uiState == 10] {
				if [uiSel < 2] {
					uiSel = uiSel + 1;
				} else {
					uiSel= 0;
				}
				update(uiSel);
			}
			// filter bank sel
			if [uiState == 20] {
				if [uiSel < 3] {
					uiSel = uiSel + 1;
				} else {
					uiSel= 0;
				}
				update(uiSel);
			}
			// filter index sel
			if [uiState == 21] {
				if [uiSel < 2] {
					uiSel = uiSel + 1;
				} else {
					uiSel= 0;
				}
				update(uiSel);
			}
			// filter type sel
			if [uiState == 22] {
				if [uiSel < 5] {
					uiSel = uiSel + 1;
				} else {
					uiSel= 0;
				}
				update(uiSel);
			}

			// filter frequency
			if [uiState == 23] {
				if [ffreq < 15000.0] {
					ffreq = ffreq + 100.0;
				} else {
					ffreq = 100.0;
				}
				update(ffreq);
			}

			// filter gain
			if [uiState == 24] {
				if [fgain < 5.0] {
					fgain = fgain + 0.1;
				} else {
					fgain = -5.0;
				}
				update(fgain);
			}

			// filter quality
			if [uiState == 25] {
				if [fquality < 5.0] {
					fquality = fquality + 0.1;
				} else {
					fquality = 0.1;
				}
				update(fquality);
			}

			// volume
			if [uiState == 30] {
				if [volume < 10.0] {
					volume = volume + 0.1;
					update(volume);
				}
			}


			// channel up/down			
			if [uiState == 40] {
				if [uiSel == 0] {
					uiSel = 1;
				} else {
					uiSel= 0;
				}
				update(uiSel);
			}
			// channel left routing
			if [uiState == 41] {
				if [uiSel < 2] {
					uiSel = uiSel + 1;
				} else {
					uiSel= 0;
				}
				update(uiSel);
			}
			// channel right routing
			if [uiState == 42] {
				if [uiSel < 2] {
					uiSel = uiSel + 1;
				} else {
					uiSel= 0;
				}
				update(uiSel);
			}
			uiUpdate = 1;
			update(uiUpdate);
			
		}
		// down button check
		checkButtonPressed(bDown) {
			// DSP element select
			if [uiState == 10] {
				if [uiSel > 0] {
					uiSel = uiSel - 1;
				} else {
					uiSel = 2;
				}
				update(uiSel);
			}
			// filter bank sel
			if [uiState == 20] {
				if [uiSel > 0] {
					uiSel = uiSel - 1;
				} else {
					uiSel = 3;
				}
				update(uiSel);
			}
			// filter index sel
			if [uiState == 21] {
				if [uiSel > 0] {
					uiSel = uiSel - 1;
				} else {
					uiSel = 2;
				}
				update(uiSel);
			}

			// filter type sel
			if [uiState == 22] {
				if [uiSel > 0] {
					uiSel = uiSel - 1;
				} else {
					uiSel = 5;
				}
				update(uiSel);
			}

			// filter frequency
			if [uiState == 23] {
				if [ffreq > 100.0] {
					ffreq = ffreq - 100.0;
				} else {
					ffreq = 15000.0;
				}
				update(ffreq);
			}

			// filter gain
			if [uiState == 24] {
				if [fgain > -5.0] {
					fgain = fgain - 0.1;
				} else {
					fgain = 5.0;
				}
				update(fgain);
			}

			// filter quality
			if [uiState == 25] {
				if [fquality > 0.1] {
					fquality = fquality - 0.1;
				} else {
					fquality = 5.0;
				}
				update(fquality);
			}

			// volume
			if [uiState == 30] {
				if [volume > 0.0] {
					volume = volume - 0.1;
					update(volume);
				} 
				
			}


			// channel up/down
			if [uiState == 40] {
				if [uiSel == 1] {
					uiSel = 0;
				} else {
					uiSel= 1;
				}
				update(uiSel);
			}
			// channel left routing
			if [uiState == 41] {
				if [uiSel > 0] {
					uiSel = uiSel - 1;
				} else {
					uiSel = 2;
				}
				update(uiSel);
			}
			// channel right routing
			if [uiState == 42] {
				if [uiSel > 0] {
					uiSel = uiSel - 1;
				} else {
					uiSel = 2;
				}
				update(uiSel);
			}
			uiUpdate = 1;
			update(uiUpdate);
		}

		// display
		if [uiUpdate == 1] {
			[headerText] = getHeaderText[];
			[selText] = getSelText[];
		
			dispText = headerText;
			dispText += "\n";
			dispText += selText;
			
			ui[obj=d, func=print, text=dispText];
			
			uiUpdate = 0;
		}
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


main(PC) {
	local {
	}

	code {
		[] = dspInit[];
		[] = guiInit[];
		[] = uiInit[];
		for [;;]{
			// ----------------------
			// ui processing
			// ----------------------
			[] = uiDisplay[];							
		}
	}
}


main(ADSP) {
	local {
		rational	inL[1024];
		rational	inR[1024];
		rational	outL[1024];
		rational	outR[1024];		
	}

	code {
		[] = dspInit[];
		for [;;]{
			// ----------------------
			// signal processing
			// ----------------------
	
			// read input channels
			// first read operation waits for a new sample frame
			sampleIO[operation=read ,dest=inL, channel=0, wait=1];
			// second extract 2nd channel from frame -> so no waiting
			sampleIO[operation=read ,dest=inR, channel=1, wait=0];

			// input filtering
			inL = inL * LinFilter;
			inR = inR * RinFilter;
			// signal routing & and DSP
			// left output
			if [LoutInpSel == 0] {
				outL = inL * LoutFilter;
			}
			if [LoutInpSel == 1] {
				outL = inR * LoutFilter;
			}
			if [LoutInpSel == 2] {
				outL = 0.0;
			}
			// right output
			if [RoutInpSel == 0] {
				outR = inL * RoutFilter;
			}
			if [RoutInpSel == 1] {
				outR = inR * RoutFilter;
			}
			if [RoutInpSel == 2] {
				outR = 0.0;
			}
			// set the volume
			outL = outL * volume;
			outR = outR * volume;
			
			// process output signals and write them to the outputs
			sampleIO[operation=write ,src=outL, channel=0];
			sampleIO[operation=write ,src=outR, channel=1];


		// main loop	
		}
	// of code
	} 
}