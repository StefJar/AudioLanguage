global {
}

// init the GUI by setting the GUI dimensions
function a {
	interface {
		in		integer	in;
		out		integer	out;
	}

	local {
	}

	code {
	out = in;
	}
}

function b {
	interface {
	}

	local {
		integer x;
		integer y;
	}
	
	code {
		[y] = a[x];
	}
}

main(test) {
	local {
	}
	code { 
		[] = b [];
	} 
} 