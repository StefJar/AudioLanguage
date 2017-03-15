main(DAFx2012) {
	local {
		rational	x[512];	
		rational	y[512];
		biquad		filter[8];
	}
	code {
		biquad[obj=filter, type=HP, fs=48000, fc=90, index=0];	
		biquad[obj=filter, type=HP, fs=48000, fc=90, index=1];
		biquad[obj=filter, type=HP, fs=48000, fc=90, index=2];
		biquad[obj=filter, type=HP, fs=48000, fc=90, index=3];

		biquad[obj=filter, type=LP, fs=48000, fc=1000, index=4];	
		biquad[obj=filter, type=LP, fs=48000, fc=1000, index=5];
		biquad[obj=filter, type=LP, fs=48000, fc=1000, index=6];
		biquad[obj=filter, type=LP, fs=48000, fc=1000, index=7];
		
		for [;;] {
			// read input channel
			sampleIO[operation=read ,dest=x, channel=1, wait=1];
			
			// process sampels
			y = filter * x;
			
			// write output channel
			sampleIO[operation=write ,src=y, channel=2];
		}
		
	}
}
