- oral : nombre de profondeur n�cessaire � chaque taille de plateau pour �tudier toutes les solutions de fin de parties possible et temps correspondant pour notre programme

continuer � remplacer les pointeurs par des r�f�rence si possible et enlever tout les new et delete correspondants
- Checkerboard* => FAIT
- Player* => serait compliqu� � caise des (player=P1 ? P1 : P2)   ??
- Game* => possible ?
- ...

signification de
- #pragma omp single {
	ce qui est dans le bloc n'est ex�cut� que par un seul thread
}
- #pragma omp task {
	ce qui est dans le bloc peut �tre ex�cut� par plusieurs threads
	#pragma omp taskwait permet d'attendre que tout les threads est effectu� la tache jusqu'� ce point avant de continuer.
}

- enlever les delete sur les vector et les appels � leurs destructeurs si il y en a

- CHOIX BIZARRES DE L'IA A CORRIGER ??? d� � playerTurn() dans fonctions de co�t ? l'enlever ?

- finir chacun sa fonction de co�t
1 - fonction de base
2 - fonction fab
3 - fonction ???
4 - fonction ???
5 - fonction random

Finir le rapport + doc technique + doc utilisateur
donner les images n�cessaires aux rapports � Sylvain

Faire le diapo

algorithme th�orique sur lequel on s'est bas� (pour mettre dans le rapport ou autre)
//function negamax(node, depth, color)
//if depth = 0 or node is a terminal node
//    return color * the heuristic value of node
//bestValue := -infini
//foreach child of node
//    val := -negamax(child, depth - 1, -color)
//    bestValue := max( bestValue, val )
//return bestValue
//
//Initial call for Player A's root node
//rootNodeValue := negamax( rootNode, depth, 1)
//
//Initial call for Player B's root node
//rootNodeValue := -negamax( rootNode, depth, -1)