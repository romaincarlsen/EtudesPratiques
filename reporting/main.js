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
			tree.draw(0) ;
        };
         
        fr.readAsText(file);
    };
};

function readReporting() {
       
    var data = reporting.split(";") ;
    var size_board = parseInt(data[cursor]) ;
    cursor++ ;
	tree = new node(size_board,data) ;
	
};
