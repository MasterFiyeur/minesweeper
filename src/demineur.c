/**
*\file demineur.c
*\brief fichier d'entête (fonctions)
*	fonctions pour les chaines de caractères
*\author Theo Julien (julientheo@eisti.eu)
*\version 1
*\date 2020-11-27
*/

#include "demineur.h"

int estDedans(int* pint_tab,int int_x,int int_taille){
	/* Déclaration de variable de boucle */
	int i;
	/* Parcours du tableau */
	for (i = 0; i < int_taille; i++)
	{
		/* Test de la condition */
		if(int_x==pint_tab[i]){
			/* Element dans le tableau */
			return(1);
		}
	}
	/* Element pas dans le tableau */
	return(0);
}

grilleD affectationBombe(grilleD gd_plateau){
	/* Déclaration de variable de boucle */
	int i;
	int j;
	/* Déclaration du tableau d'entier */
	int* pint_tabAlea;
	/* Déclaration du nombre aléatoire */
	int int_alea;
	/* Allocation du tableau */
	pint_tabAlea = malloc(gd_plateau.int_nbBombes * sizeof(int));
	/* Initialisation du tableau */
	for (i = 0; i < gd_plateau.int_nbBombes; i++)
	{
		/* Valeur négative car nécessaire pour l'étape d'après */
		pint_tabAlea[i]= -1;
	}
	/* Initialisation du tableau de l'emplacement des bombes */
	for(i=0;i<gd_plateau.int_nbBombes;i++){
		/* Affectation d'un nombre aléatoire */
		int_alea = rand() % (gd_plateau.int_ligne*gd_plateau.int_colonne);
		/* On ajoute 1 jusqu'à ce que le nombre ne soit pas dans le tableau */
		while(estDedans(pint_tabAlea,int_alea,gd_plateau.int_nbBombes)){
			/* Incrémentation de 1 */
			int_alea = (int_alea + 1) % (gd_plateau.int_ligne*gd_plateau.int_colonne);
		}
		/* Affectation de la valeur au tableau */
		pint_tabAlea[i] = int_alea;
	}
	/* Parcours du tableau */
	for (i = 0; i < gd_plateau.int_ligne; i++)
	{
		for (j = 0; j < gd_plateau.int_colonne; j++)
		{
			/* Si la case correspond à une valeur du tableau alors c'est une mine */
			if(estDedans(pint_tabAlea, (i*gd_plateau.int_colonne)+j, gd_plateau.int_nbBombes)){
				/* Case correspondant à une mine */
				gd_plateau.ppCaseD_grille[i][j].int_mine = 1;
			}
		}
	}
	afficherTab(pint_tabAlea,gd_plateau.int_nbBombes);
	free(pint_tabAlea);
	gd_plateau = remplissageG(gd_plateau);
	return(gd_plateau);
}

grilleD remplissageG(grilleD gd_plateau){
	/* Déclaration de variable de boucle */
	int i;
	int j;
	/* Boucle de parcours de la grille */
	for (i = 0; i < gd_plateau.int_ligne; i++)
	{
		for (j = 0; j < gd_plateau.int_colonne; j++)
		{
			/* Attribution nombre de mine */
			gd_plateau.ppCaseD_grille[i][j].int_nbMine = calculNombreMine(gd_plateau,i,j);
			gd_plateau.ppCaseD_grille[i][j].int_aff = gd_plateau.ppCaseD_grille[i][j].int_nbMine;
		}
	}
	return(gd_plateau);
}

grilleD initGrilleD(grilleD gd_plateau){
	/* Declaration de variable de boucle */
	int i;
	int j;
	/* Demande du nombre de ligne à l'utilisateur */
	printf("Saisissez le nombre de ligne : ");
	gd_plateau.int_ligne = saisieInt();
	/* Demande du nombre de colonne à l'utilisateur */
	printf("Saisissez le nombre de colonne : ");
	gd_plateau.int_colonne = saisieInt();
	/* Condition de nombre de bombe */
	do{
		/* Demande du nombre de bombes */
		printf("Veuillez saisir le nombre de bombe : ");
		gd_plateau.int_nbBombes = saisieInt();
	}while(gd_plateau.int_nbBombes>=gd_plateau.int_ligne*gd_plateau.int_colonne);
	/* Allocation de la grille */
	gd_plateau.ppCaseD_grille = malloc(gd_plateau.int_ligne * sizeof(caseD*));
	for (i = 0; i < gd_plateau.int_ligne; i++)
	{
		gd_plateau.ppCaseD_grille[i] = malloc(gd_plateau.int_colonne * sizeof(caseD));
		/* Initialisation de la case */
		for (j = 0; j < gd_plateau.int_colonne; j++)
		{
			gd_plateau.ppCaseD_grille[i][j].int_mine = 0;
			gd_plateau.ppCaseD_grille[i][j].int_decouvert=0;
			gd_plateau.ppCaseD_grille[i][j].int_drap=0;
			gd_plateau.ppCaseD_grille[i][j].int_aff=-2;
			gd_plateau.ppCaseD_grille[i][j].int_nbMine=0;
		}
	}
	/* Définition du nombre de case à découvrir */
	gd_plateau.int_caseRestante=(gd_plateau.int_colonne*gd_plateau.int_ligne)-gd_plateau.int_nbBombes;
	/* Renvoi de la grille initialisée */
	return(affectationBombe(gd_plateau));
}

void affichageD(grilleD gd_plateau){
	/* Declaration de variables de boucle */
    int i;
    int j;
    int k;
    /* Effacage du terminal */
	/*clrscr();*/
    /* Affichage du repere abscisse */
    printf("     ");
    for(i=0; i<gd_plateau.int_colonne; i++){
		/* Gestion de l'affichage */
		if(i>9){
        	printf("%d  ",i);
		}else{
        	printf("%d   ",i);
		}
    }
    /* Affichage début ligne du haut */
    printf("\n   ┌───");
    /* Affichage du milieu de la ligne du haut */
    for (i=1; i<gd_plateau.int_colonne; i++){
        printf("┬───");
    }
    /* Affichage fin ligne du haut */
    printf("┐\n");
    /* Boucle pour parcourir les lignes */
    for (i = 0; i < gd_plateau.int_ligne; i++)
    {
        /* Affichage du repere ordonnee */
		if(i>9){
			/* Gestion affichage */
        	printf("%d ",i);
		}else{
        	printf("%d  ",i);
		}
        /* Boucle pour parcourir les colonnes */
        for (j = 0; j < gd_plateau.int_colonne; j++)
        {
			/* Affichage de la bombe si perdu */
			if(gd_plateau.ppCaseD_grille[i][j].int_mine==1 && gd_plateau.ppCaseD_grille[i][j].int_decouvert==1){
				printf("│ B ");
			}else if(gd_plateau.ppCaseD_grille[i][j].int_decouvert==1){
				/* Affichage en fonction du nombre de la case */
				switch (gd_plateau.ppCaseD_grille[i][j].int_aff){
				case 0:
					/* Affichage d'une case découverte nulle */
					printf("│ . ");
					break;
				default:
					/* Affichage du nombre de bombe autour */
					printf("│ %d ",gd_plateau.ppCaseD_grille[i][j].int_aff);
					break;
				}
			}else if(gd_plateau.ppCaseD_grille[i][j].int_drap){
				/* Affichage d'une case drapeau*/
				printf("│ F ");
			}else{
				/* Affichage d'une case non découverte*/
				printf("│   ");
			}
        }
        /* On affiche pas la derniere ligne car elle est differente */
        if(i != gd_plateau.int_ligne-1){
            /* Affichage de la bordure droite et debut ligne de séparation */
            printf("│\n   ├───");
            /* Affichage milieu ligne de séparation */
            for(k=1 ; k<gd_plateau.int_colonne; k++){
                printf("┼───");
            }
            /* Affichage de la fin de la ligne de séparation */
            printf("┤\n");
        }else{
            /* On affiche la bordure droite */
            printf("│\n");
        }
    }
    /* Affichage début derniere ligne */
    printf("   └───");
    /* Affichage milieu dernière ligne */
    for(k=1; k<gd_plateau.int_colonne; k++){
        printf("┴───");
    }
    /* Affichage fin dernière ligne */
    printf("┘\n");

}

int calculNombreMine(grilleD gd_plateau,int int_y,int int_x){
	/* Déclaration de l'accumulateur */
	int int_acc;
	/* Initialisation de l'accumulateur */
	int_acc = 0;
	/* Cases du dessous */
	if(int_y+1<gd_plateau.int_ligne){
		/* Ajout de la valeur int_mine de la case du dessous */
		int_acc += gd_plateau.ppCaseD_grille[int_y+1][int_x].int_mine;
		/* Case du dessous gauche */
		if(int_x-1>=0){
			int_acc += gd_plateau.ppCaseD_grille[int_y+1][int_x-1].int_mine;
		}
		/* Case du dessous droite */
		if(int_x+1<gd_plateau.int_colonne){
			int_acc += gd_plateau.ppCaseD_grille[int_y+1][int_x+1].int_mine;
		}
	}
	/* Case de droite */
	if(int_x+1<gd_plateau.int_colonne){
		int_acc += gd_plateau.ppCaseD_grille[int_y][int_x+1].int_mine;
	}
	/* Case de gauche */
	if(int_x-1>=0){
		int_acc += gd_plateau.ppCaseD_grille[int_y][int_x-1].int_mine;
	}
	if(int_y-1>=0){
		int_acc += gd_plateau.ppCaseD_grille[int_y-1][int_x].int_mine;
		if(int_x-1>=0){
			int_acc += gd_plateau.ppCaseD_grille[int_y-1][int_x-1].int_mine;
		}
		if(int_x+1<gd_plateau.int_colonne){
			int_acc += gd_plateau.ppCaseD_grille[int_y-1][int_x+1].int_mine;
		}
	}
	/* Renvoi de l'accumulateur */
	return(int_acc);
}

grilleD decouverte(grilleD gd_plateau,int int_y,int int_x){
	/* La case n'est pas dans la grille ou si la case est déjà découverte on stop */
	if((int_y>=gd_plateau.int_ligne || int_y<0) || (int_x>=gd_plateau.int_colonne || int_x<0) || gd_plateau.ppCaseD_grille[int_y][int_x].int_decouvert==1){
		return(gd_plateau);
	}
	/* La case est une bombe */
	if(gd_plateau.ppCaseD_grille[int_y][int_x].int_mine==1){
		/* Découverte de la bombe */
		gd_plateau.ppCaseD_grille[int_y][int_x].int_decouvert = 1;
		/* Indication fin de partie par explosion*/
		gd_plateau.int_caseRestante=-1;
		/* Renvoi du plateau */
		return(gd_plateau);
	}
	/* Calcul du nombre de mine autour */
	gd_plateau.ppCaseD_grille[int_y][int_x].int_decouvert = 1;
	/* Enlève le drapeau */
	if(gd_plateau.ppCaseD_grille[int_y][int_x].int_drap==1){
		/* Remplace le drapeau par le nombre de mine */
		gd_plateau.ppCaseD_grille[int_y][int_x].int_aff = gd_plateau.ppCaseD_grille[int_y][int_x].int_nbMine;
	}
	/* Décrémentation du nombre de case à découvrir */
	gd_plateau.int_caseRestante--;
	/* Découverte de toute les voisins si la case n'a pas de mine autour */
	if(gd_plateau.ppCaseD_grille[int_y][int_x].int_nbMine==0){
		/* Check des cases toutes autour */
		if(int_y+1<gd_plateau.int_ligne ){
			/* Ajout de la valeur int_mine de la case du dessous */
			if(!gd_plateau.ppCaseD_grille[int_y+1][int_x].int_decouvert){
				gd_plateau = decouverte(gd_plateau,int_y+1,int_x);
			/* Case du dessous gauche */
			}
			if(int_x-1>=0 && !gd_plateau.ppCaseD_grille[int_y+1][int_x-1].int_decouvert){	
				gd_plateau = decouverte(gd_plateau,int_y+1,int_x-1);
			/* Case du dessous droite */
			}
			if(int_x+1<gd_plateau.int_colonne && !gd_plateau.ppCaseD_grille[int_y+1][int_x+1].int_decouvert){
				gd_plateau = decouverte(gd_plateau,int_y+1,int_x+1);
			}
		/* Case de droite */
		}
		if(int_x+1<gd_plateau.int_colonne && !gd_plateau.ppCaseD_grille[int_y][int_x+1].int_decouvert){
			gd_plateau = decouverte(gd_plateau,int_y,int_x+1);
		/* Case de gauche */
		}
		if(int_x-1>=0 && !gd_plateau.ppCaseD_grille[int_y][int_x-1].int_decouvert){
			gd_plateau = decouverte(gd_plateau,int_y,int_x-1);
		/* Case du haut */
		}
		if(int_y-1>=0){
			if(!gd_plateau.ppCaseD_grille[int_y-1][int_x].int_decouvert){
				gd_plateau = decouverte(gd_plateau,int_y-1,int_x);
			/* Case haut gauche */
			}
			if(int_x-1>=0 && !gd_plateau.ppCaseD_grille[int_y-1][int_x-1].int_decouvert){
				gd_plateau = decouverte(gd_plateau,int_y-1,int_x-1);
			/* Case bas droite */
			}
			if(int_x+1<gd_plateau.int_colonne && !gd_plateau.ppCaseD_grille[int_y-1][int_x+1].int_decouvert){
				gd_plateau = decouverte(gd_plateau,int_y-1,int_x+1);
			}
		}
	}
	return(gd_plateau);
}

void partie(){
	/* Déclaration du plateau */
	grilleD gd_plateau;
	/* Déclaration variable de boucle */
	int i;
	/* Déclaration des coordonnées */
	int int_x;
	int int_y;
	/* Initialisation de la grille */
	gd_plateau = initGrilleD(gd_plateau);
	/* Lancement de jeu */
	do{
		/* Affichage du tableau */
		affichageD(gd_plateau);
		/* Affichage de la légende */
		printf("'.' : Case découverte sans mine autour\n' ' : Case non découverte\n");
		/* Demande de la case à l'utilisateur */
		do
		{
			/* Demande de l'ordonnée */
			printf("Ligne : ");
			int_y = saisieInt();
			/* Demande de l'abscisse */
			printf("Colonne : ");
			int_x = saisieInt();
		} while ((int_x<0 || int_x>=gd_plateau.int_colonne) || (int_y<0 || int_y>=gd_plateau.int_ligne));
		/* Demande si c'est pour un drapeau */
		printf("Voulez-vous placer un drapeau (1:oui) ?");
		i = saisieInt();
		/* Découvre ou place un drapeau en fonction du choix */
		if(i==1){
			/* Placement d'un drapeau */
			gd_plateau.ppCaseD_grille[int_y][int_x].int_drap = 1;
			gd_plateau.ppCaseD_grille[int_y][int_x].int_aff = -1;
		}else{
			/* Découverte de la case */
			gd_plateau = decouverte(gd_plateau,int_y,int_x);
		}
	}while(gd_plateau.int_caseRestante>0);
	/* Affichage du plateau */
	affichageD(gd_plateau);
	/* Arrêt par victoire */
	if(gd_plateau.int_caseRestante==0){
		printf("Bravo vous avez gagné !\n");
	/* Arrêt par explosion */
	}else{
		printf("BOUM !\nVous avez perdu\n");
	}
	/* Désallocation de la grille */
	for (i = 0; i < gd_plateau.int_ligne; i++)
	{
		free(gd_plateau.ppCaseD_grille[i]);
	}
	free(gd_plateau.ppCaseD_grille);
}