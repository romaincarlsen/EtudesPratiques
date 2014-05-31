﻿// paramétrable

var internet_browser_canvas_size_limit = 32000 ;
var square_size = 20;
var text_size = 15 ;
var marge_height = 75 ;
var marge_width = 10 ;
var marge_behind_text = 5 ;
var line_width = 2 ;
var marge_width_tree = 100 ;
var marge_height_tree = 100 ;
var cost_value_width = 50 ;

var img_white_piece =  loadImage("img/white_piece.png") ;
var img_white_king =  loadImage("img/white_king.png") ;
var img_black_piece =  loadImage("img/black_piece.png") ;
var img_black_king =  loadImage("img/black_king.png") ;
var img_empty =  loadImage("img/empty.png") ;
var img_lock =  loadImage("img/lock.png") ;


//----------------------------------------------------------------------------------------

var canvas ;
var ctx ;
var reporting ;
var tree ;
var loaded = false ;
var cursor = 0 ;

var tree_width = 0 ;
var tree_height = 0 ;

var nb_node_by_depth = {} ;
var current_node_by_depth = {} ;
var tree_node_dimension ;