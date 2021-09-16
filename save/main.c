/**
*\file main.c
*\author Theo Julien (julientheo@eisti.eu)
*\brief main du TP
*\version 0.1
*\date 2020-10-23
*/

#include "demineur.h"

/*!
*\fn int main(int argc, char const *argv[])
*\author Theo Julien <julientheo@eisti.eu>
*\version 0.1 Initiale
*\date 13 novembre 2020
*\brief 
*\param argc nombre d'arguments en entree
*\param argv valeur des arguments en entree
*\return 0 si tout s'est bien passe
*/
int main(int argc, char **argv)
{
    srand(time(NULL));
    /* Lancement de la partie */
    partie();
    /*Fin de programme : Tout est OK*/
    return (0);
}