#ifndef PIECES_H
#define PIECES_H

#include "coordonnee.h"


typedef struct 
{
    char name; // le nom de la pièce
    char color;// la couleur de la pièce
    int index; // l'indice de position de la pièce dans sont tableau respectif
} CheckCase; 


//Prototypes :

// Prend une case en entrée et renvoie ce qu'il y a sur la case
CheckCase caseValue(ChessGrid carreau);

//ON définit la position initiale de chaque pion
void DefPositionInitPieces();
//On affiche chacun des pions à leur place
void AffichePieces();
//Permet de tuer la pièce se situant sur la case en entrée de la focntion
void killPiece(ChessGrid carreau);
//Permet de sauvegarder la partie:
void save();
//Permet de load la last save:
void load();

//---------------------PAWNS -----------------------------


//Verifie si on clique sur un pion
void CheckPawn(ChessGrid pos, bool EtatJoueur);

//Affiche les déplacements disponibles et vérifient leur faisabilité
bool Pawn(bool EtatJoueur);

//Permet de placer le pion en ChoosenCase
bool PlacePion(ChessGrid ChoosenCase, int EtatJoueur);

//---------------------TOWERS -----------------------------

//Verifie si on clique sur une tour
void CheckTower(ChessGrid pos, bool EtatJoueur);
//Affiche les déplacements disponibles et vérifient leur faisabilité
bool Tower(bool EtatJoueur);
//Permet de placer la tour en ChoosenCase
bool PlaceTower(ChessGrid ChoosenCase, int EtatJoueur);

//---------------------KNIGHT---------------------------------
//Verifie si on clique sur un cavalier
void CheckKnights(ChessGrid pos, bool EtatJoueur);

//Affiche les déplacements disponibles et vérifient leur faisabilité
bool Knight(bool EtatJoueur);
//Permet de placer Knight en ChoosenCase
bool PlaceKnight(ChessGrid ChoosenCase, int EtatJoueur);

//---------------------BISHOP--------------------------------
//Verifie si on clique sur un fou
void CheckBishop(ChessGrid pos, bool EtatJoueur);
//Affiche les déplacements disponibles et vérifient leur faisabilité
bool Bishop(bool EtatJoueur);
//Permet de placer Bishop en ChoosenCase
bool PlaceBishop(ChessGrid ChoosenCase, int EtatJoueur);

//----------------------QUEEN------------------------------------
//Verifie si on clique sur une reine
void CheckQueen(ChessGrid pos, bool EtatJoueur);
//Affiche les déplacements disponibles et vérifient leur faisabilité
bool Queen(bool EtatJoueur);
//Permet de place la reine en ChoosenCase
bool PlaceQueen(ChessGrid ChoosenCase, int EtatJoueur);

//-------------------KING--------------------------------
//Verifie si on clique sur une reine
void CheckKing(ChessGrid pos, bool EtatJoueur);
//Affiche les déplacements disponible et vérifient leur faisabailité
bool King(bool EtatJoueur);
//Permet de place la reine en ChoosenCase
bool PlaceKing(ChessGrid ChoosenCase, int EtatJoueur);

#endif
