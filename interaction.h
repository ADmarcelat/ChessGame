#ifndef INTERACTION_H
#define INTERACTION_H

#include "coordonnee.h"



//Prototypes :

// Récupère la commande taper
ChessGrid recupereCommandeTapee(char touche, char *tableau_commande, int case_remplie);


// Affiche une case dans l'interface visuelle
void afficheCommandeTapee(ChessGrid *commande);


#endif