	window.onresize = function() {
		resize() ;
	}
	
	window.onload = function() {
		initFrame() ;
		resize() ;
		initReporting() ;	
	}
	
	function resize() {
			
		canvas.width = tree_width ;
		canvas.height = tree_height ;
		
		if (loaded)
			repaint() ;
	}
	
	function initFrame() {
		canvas = document.getElementById('canvas');
		ctx = canvas.getContext('2d');
	}