#ifndef COORDONNEE_H
#define COORDONNEE_H

// Grid size
#define caseTaille 70 // -> les cases font 70x70 px
#define bordureEpaisseur 45

//Structures :

typedef struct
{
	char x;
	int y;
} ChessGrid; //Coordonnee version grille d'echec

typedef struct
{
    int x;
    int y;
} PixGrid; //Coordonne version grille de Pixel

//Prototypes :

//Donne des coordonnee x et y en fonction d'une case
PixGrid PixelCoordonnee(ChessGrid carreau);

//Donne une case en fonction des coordonnee x et y
ChessGrid GridCoordonnee(PixGrid pos);

//Renvoie la case sur laquelle on clique
ChessGrid clicCase();


#endif
