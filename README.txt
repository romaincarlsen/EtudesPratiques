- oral : nombre de profondeur nécessaire à chaque taille de plateau pour étudier toutes les solutions de fin de parties possible et temps correspondant pour notre programme

- incohérence des choix quand threads, du surement au fait que tout les simulations soit lancées en même temps (nécessaire de faire l'un après l'autre pour alpha-beta), et pour negmax je sais pas, tanpis

- finir chacun sa fonction de coût
1 - fonction de base
2 - fonction fab
3 - fonction ???
4 - fonction ???
5 - fonction random

Finir le rapport + doc technique + doc utilisateur
donner les images nécessaires aux rapports à Sylvain

Faire le diapo

checker toutes le fautes d'orthographe de tout les rendus


FACULTATIF :

- enlever les delete sur les vector et les appels à leurs destructeurs si il y en a

continuer à remplacer les pointeurs par des référence si possible et enlever tout les new et delete correspondants
- Checkerboard* => FAIT
- Player* => serait compliqué à caise des (player=P1 ? P1 : P2)   ??
- Game* => possible ?
- ...

signification de
- #pragma omp single {
	ce qui est dans le bloc n'est exécuté que par un seul thread
}
- #pragma omp task {
	ce qui est dans le bloc peut être exécuté par plusieurs threads
	#pragma omp taskwait permet d'attendre que tout les threads est effectué la tache jusqu'à ce point avant de continuer.
}

- Dans le diapo, une amélioration possible serait que la fonction de coût fasse de l'auto-apprentissage