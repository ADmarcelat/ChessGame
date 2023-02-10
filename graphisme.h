#ifndef GRAPHISME_H
#define GRAPHISME_H


#include "coordonnee.h"
//Ici tous les prototypes de fonctions servant aux graphismes et animations

//ecris une image avec le fond bleu "1" en transparent
void ecrisImageTransparence(int x, int y, int largeur, int hauteur, const unsigned char *donnees);

//Prend en entré un carreau est colore la case en vert semi-transparent
void caseVerte(ChessGrid carreau);
//Prend en entré un carreau est colore la case en rouge semi-transparent
void caseRouge(ChessGrid carreau);

// Affiche le menu
void afficheMenu();

#endif
