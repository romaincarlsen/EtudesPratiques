	
	
	function node(size_board,data) {
		this.size_board = size_board ;	
		this.board = data[cursor] ;
		cursor++ ;
		this.depth = parseInt(data[cursor]) ;
		cursor++ ;
		this.value = parseInt(data[cursor]) ;
		cursor++ ;
		this.nb_child = parseInt(data[cursor]) ;
		cursor++ ;
		
		this.child = new Array() ;
		
		for (var i=0 ; i<this.nb_child ; i++) {
			this.child.push(new node(size_board,data)) ;	
		}

		
		this.draw = function(indice_x) {
			ctx.font = "20pt Calibri,Geneva,Arial";
		    ctx.fillStyle = "rgb(0,20,180)";
		    
		    ctx.fillText(this.value,100*indice_x,100*this.depth+20) ;
		    i
		    for (var i=0 ; i<this.board.length ; i++) {
		    	var img = char_to_img(this.board[i]) ;
			    ctx.drawImage(img, 0, 0, img.width, img.height, 100*indice_x + 20*(i%this.size_board), 100*this.depth + 25 + 20*(i/this.size_board), 20, 20);
		    }
		       
		    for (var i=0 ; i<this.child.length ; i++) {
		    	this.child[i].draw(i) ;		    	
		    }
		}
	}