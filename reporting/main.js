function initReporting() {
    var f = document.getElementById('file');
    var res = document.getElementById('resultat');
    f.onchange = function() {
        var file = f.files[0],
            fr = new FileReader();
             
        fr.onprogress = function() {
            res.innerHTML = 'Chargement...';
        };
        fr.onerror = function() {
            res.innerHTML = 'Oups, une erreur s\'est produite...';
        };
        fr.onload = function() {
            res.innerHTML = '';
			reporting = fr.result ;
			readReporting() ;
			loaded = true ;
			tree_node_dimension = analyse_tree_dimension() ;
			tree_width = (tree.width + marge_width)*tree_node_dimension.x ;
			tree_height = (tree.height + marge_height)*tree_node_dimension.y ;
						
			resize() ;
						
        };
         
        fr.readAsText(file);
    };
};

function readReporting() {
       
    var data = reporting.split(";") ;
    var size_board = parseInt(data[cursor]) ;
    cursor++ ;
    
	tree = new node(size_board,data,false,0,0) ;
};

function repaint() {
	var depth = 0 ;
	while (nb_node_by_depth[depth] != undefined) {
		current_node_by_depth[depth] = 0 ;
		depth++ ;
	}
	tree.draw() ;
}

function analyse_tree_dimension() {
	var depth = 0 ;
	var max = 0 ;
	while (nb_node_by_depth[depth] != undefined) {
		if (nb_node_by_depth[depth] > max)
			max = nb_node_by_depth[depth] ;
		depth++ ;
	}
	return {x : max, y : depth} ;
}
