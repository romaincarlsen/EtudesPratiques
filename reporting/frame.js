	window.onresize = function() {
		resize() ;
	}
	
	window.onload = function() {
		initFrame() ;
		resize() ;
		initReporting() ;	
	}
	
	function resize() {
		if (tree_width > internet_browser_canvas_size_limit)
			canvas.width = internet_browser_canvas_size_limit ;
		else
			canvas.width = tree_width ;
		if (tree_height > internet_browser_canvas_size_limit)
			canvas.height = internet_browser_canvas_size_limit ;
		else
			canvas.height = tree_height ;
		
		if (loaded)
			repaint() ;
	}
	
	function initFrame() {
		canvas = document.getElementById('canvas');
		ctx = canvas.getContext('2d');
	}