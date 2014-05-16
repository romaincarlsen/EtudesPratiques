	window.onresize = function() {
		resize() ;
	}
	
	window.onload = function() {
		initFrame() ;
		resize() ;
		initReporting() ;	
	}
	
	function resize() {
		canvas.width = window.innerWidth*95/100;
		canvas.height = window.innerHeight*90/100;
		if (loaded)
			tree.draw() ;
	}
	
	function initFrame() {
		canvas = document.getElementById('canvas');
		ctx = canvas.getContext('2d');
	}