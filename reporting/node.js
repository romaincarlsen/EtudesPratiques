	
	
	function node(size_board,data,ghost,nieme_child,depth) {
		this.size_board = size_board ;	
		
		this.ghost = ghost ;
		
		this.height = square_size*this.size_board + text_size + marge_behind_text ;
		this.width = square_size*this.size_board ;
		
		this.nieme_child = nieme_child ;
		this.depth = depth ;
		
		if (nb_node_by_depth[this.depth] == undefined) {
			nb_node_by_depth[this.depth] = 1 ;
		}
		else {
			nb_node_by_depth[this.depth]++ ;			
		}
		
		if (!this.ghost) {
			this.board = data[cursor] ;
			cursor++ ;
			this.value = parseInt(data[cursor]) ;
			cursor++ ;
			this.time = parseInt(data[cursor]) ;
			cursor++ ;
			this.nb_child = parseInt(data[cursor]) ;
			cursor++ ;
			this.nb_child_treated = parseInt(data[cursor]) ;
			cursor++ ;
			
			this.child = new Array() ;
			
			for (var i=0 ; i<this.nb_child ; i++) {
				this.child.push(new node(size_board,data,i>=this.nb_child_treated,i,this.depth+1)) ;	
			}
		}
		
		this.draw = function() {
			ctx.font = "" + text_size + "pt Calibri,Geneva,Arial";
		    ctx.fillStyle = "rgb(0,20,180)";  
		    var step_x = tree_width/nb_node_by_depth[this.depth] ;
		    var x = step_x*(current_node_by_depth[this.depth]+1) - step_x/2 ;
		    	    		    
		    var y = (this.height + marge_height)*this.depth ;
		    
		    if (this.ghost) {
		    	ctx.fillText("X",x, y + text_size) ;
		    }
		    else {
			    ctx.fillText(this.value,x, y + text_size) ;
				
				ctx.font = "" + text_size*0.75 + "pt Calibri,Geneva,Arial";
				ctx.fillStyle = "rgb(180,20,0)";  
			    ctx.fillText(this.time,x + cost_value_width, y + text_size) ;
				
			    for (var i=0 ; i<this.board.length ; i++) {
			    	var img = char_to_img(this.board[i]) ;
				    ctx.drawImage(img, 0, 0, img.width, img.height, x + square_size*(i%this.size_board), y + text_size + marge_behind_text + square_size*parseInt(i/this.size_board), square_size, square_size);
			    }
			       
			    for (var i=0 ; i<this.child.length ; i++) {
			    	var step_x = tree_width/nb_node_by_depth[this.child[i].depth] ;
			    	var child_x = step_x*(current_node_by_depth[this.child[i].depth]+1) - step_x/2 ;
			    	var child_y = (this.child[i].height + marge_height)*this.child[i].depth ;
			    	
			    	this.drawLineBetween(x,y,this,child_x,child_y,this.child[i]) ;
			    	this.child[i].draw() ;
			    }
			}
			
			current_node_by_depth[this.depth]++ ;
		}
		
		this.drawLineBetween = function(x_parent,y_parent,parent,x_child,y_child,child) {
			ctx.strokeStyle = "rgb(0,20,180)";
			ctx.lineWidth= "" + line_width ;
			
			ctx.beginPath();
			ctx.moveTo(x_parent + parent.width/2, y_parent+parent.height);
			ctx.lineTo(x_child + child.width/2, y_child );
			ctx.stroke(); 	
		}
	}