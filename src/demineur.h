/*!
*\file demineur.h
*\brief Fichier d'entête des fonctions de chaine de caractères
*\author Theo Julien (julientheo@eisti.eu)
*\version 1 
*\date 2020-11-27
*/

#ifndef __demineur_
#define __demineur_


/**
* Une structure pour représenter une case
*/
struct caseDemineur
{
    int int_mine; /**< 0 n'est pas une mine/1 est une mine */
    int int_decouvert; /**< 0 caché/1 découvert */
    int int_drap; /**< 0 n'a pas de drapeau/1 a un drapeau */
    int int_aff; /**< Nombre à afficher (-1 pour F et -2 pour non découvert)*/
    int int_nbMine; /**< Nombre de mines chez les voisins */
};

/**
* Une structure avec les variables nécéssaire pour le jeu
*/
struct grilleDemineur
{
    struct caseDemineur** ppCaseD_grille; /**< Grille de jeu */
    int int_ligne; /**< Nombre de ligne de la grille */
    int int_colonne; /**< Nombre de colonne de la grille */
    int int_nbBombes; /**< Nombre de bombes dans la grille */
    int int_caseRestante; /**< Nombre de case restante à découvrir avant de gagner/-1 Boom */
};


/* Création de type équivalent */
typedef struct grilleDemineur grilleD;
typedef struct caseDemineur caseD;

/*----Importation des bibliothèques de base----*/
#include "lectureSecurisee.h"

/**
*\fn int estDedans(int* pint_tab,int int_x,int int_taille)
*\author Theo Julien <julientheo@eisti.eu>
*\version 0.1 initiale
*\date 2020-11-27
*\brief Détermine si un élément est dans le tableau
*\param pint_tab Tableau qui contient les éléments
*\param int_x Element a tester
*\param int_taille Taille du tableau
*\return Vrai/Faux en fonction de si l'élément est dans le tableau
*/
int estDedans(int* pint_tab,int int_x,int int_taille);

/**
*\fn grilleD affectationBombe(grilleD gd_plateau)
*\author Theo Julien <julientheo@eisti.eu>
*\version 0.1 initiale
*\date 2020-11-27
*\brief Initialisation des bombes
*\param gd_plateau Plateau avec les bombes à initialiser
*\return Plateau de jeu avec placement des bombes
*/
grilleD affectationBombe(grilleD gd_plateau);

/**
*\fn grilleD remplissageG(grilleD gd_plateau)
*\author Theo Julien <julientheo@eisti.eu>
*\version 0.1 initiale
*\date 2020-11-27
*\brief Pré-remplie toute la grille
*\param gd_plateau Plateau du jeu
*\return Plateau de jeu avec affichage déjà rempli
*/
grilleD remplissageG(grilleD gd_plateau);

/**
*\fn grilleD initGrilleD(grilleD gd_plateau)
*\author Theo Julien <julientheo@eisti.eu>
*\version 0.1 initiale
*\date 2020-11-27
*\brief initialisation de la grille de jeu
*\param gd_plateau Plateau à initialiser
*\return Plateau de jeu initialisée
*/
grilleD initGrilleD(grilleD gd_plateau);

/**
*\fn void affichageD(grilleD gd_plateau)
*\author Theo Julien <julientheo@eisti.eu>
*\version 0.1 initiale
*\date 2020-11-27
*\brief Affiche le plateau de jeu
*\param gd_plateau Plateau à afficher
*/
void affichageD(grilleD gd_plateau);

/**
*\fn int calculNombreMine(grilleD gd_plateau,int int_y,int int_x)
*\author Theo Julien <julientheo@eisti.eu>
*\version 0.1 initiale
*\date 2020-11-27
*\brief Calcule le nombre de mine autour d'une case
*\param gd_plateau Plateau du jeu
*\param int_x Abscisse de la case
*\param int_y Ordonnée de la case
*\return Nombre de mine autour de la case
*/
int calculNombreMine(grilleD gd_plateau,int int_y,int int_x);

/**
*\fn grilleD decouverte(grilleD gd_plateau,int int_y,int int_x)
*\author Theo Julien <julientheo@eisti.eu>
*\version 0.1 initiale
*\date 2020-11-27
*\brief Découvre une case
*\param gd_plateau Plateau du jeu
*\param int_x Abscisse de la case à découvrir
*\param int_y Ordonnée de la case à découvrir
*\return Grille avec les cases découvertes
*/
grilleD decouverte(grilleD gd_plateau,int int_x,int int_y);

/**
*\fn void partie()
*\author Theo Julien <julientheo@eisti.eu>
*\version 0.1 initiale
*\date 2020-11-27
*\brief Lance la partie de déminage
*/
void partie();
#endif