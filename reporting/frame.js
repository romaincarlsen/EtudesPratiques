	window.onresize = function() {
		resize() ;
	}
	
	window.onload = function() {
		initFrame() ;
		resize() ;
		initReporting() ;	
	}
	
	function resize() {
		var width = tree_width + marge_width_tree ;
		var	height = tree_height + marge_height_tree ;
		if (width > internet_browser_canvas_size_limit)
			canvas.width = internet_browser_canvas_size_limit ;
		else
			canvas.width = width ;
		if (height > internet_browser_canvas_size_limit)
			canvas.height = internet_browser_canvas_size_limit ;
		else
			canvas.height = height ;
		
		if (loaded)
			repaint() ;
	}
	
	function initFrame() {
		canvas = document.getElementById('canvas');
		ctx = canvas.getContext('2d');
	}