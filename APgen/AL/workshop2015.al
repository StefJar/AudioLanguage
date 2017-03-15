main(simple) {
	local {
		rational	x[1024];
		rational	y[1024];
	}
	code {
		for [;;]{
			sampleIO[operation=read ,dest=x, channel=0, wait=1];
			y = x * 2.0;
			sampleIO[operation=write ,src=y, channel=0];
		}
	} 
}