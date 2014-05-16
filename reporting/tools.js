	function loadImage(url) {
		image = new Image();
		image.src = url;
		return image ;
	}
	
function char_to_img(c) {
	switch(c) {
		case "x" : return img_white_piece ;
		case "X" : return img_white_king ;
		case "o" : return img_black_piece ;
		case "O" : return img_black_king ;
		case "v" : return img_empty ;
		case "#" : return img_lock ;
		default : return null ;		
	}
}
