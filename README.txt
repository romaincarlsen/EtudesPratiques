- oral : nombre de profondeur n�cessaire � chaque taille de plateau pour �tudier toutes les solutions de fin de parties possible et temps correspondant pour notre programme

- incoh�rence des choix quand threads, du surement au fait que tout les simulations soit lanc�es en m�me temps (n�cessaire de faire l'un apr�s l'autre pour alpha-beta), et pour negmax je sais pas, tanpis

- finir chacun sa fonction de co�t
1 - fonction de base
2 - fonction fab
3 - fonction ???
4 - fonction ???
5 - fonction random

Finir le rapport + doc technique + doc utilisateur
donner les images n�cessaires aux rapports � Sylvain

Faire le diapo

checker toutes le fautes d'orthographe de tout les rendus


FACULTATIF :

- enlever les delete sur les vector et les appels � leurs destructeurs si il y en a

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

- Dans le diapo, une am�lioration possible serait que la fonction de co�t fasse de l'auto-apprentissage