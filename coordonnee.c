#include <stdlib.h> // pour le malloc 
#include <stdio.h>
#include "coordonnee.h"
#include "GfxLib.h"

// Ici il y a toute les fonctions qui gère les coordonnées



//Convertis les coordonnee en case
ChessGrid GridCoordonnee(PixGrid pos){
    ChessGrid chessGrid;
   int Sumx =bordureEpaisseur; // entre le bord et la grille il y a 45 pixel en x
   int Sumy =bordureEpaisseur; // entre le bord et la grille il y a 45 pixel en y
   int condBoucle =0;
   while (condBoucle!=2)
   {

       // Abscisse
       if (pos.x >Sumx && pos.x<Sumx+caseTaille){
           chessGrid.x = 97+((Sumx-bordureEpaisseur)/caseTaille);// on ajoute 97 car 97=a en ASCII et on démarre au a
           condBoucle++;
       }
       Sumx +=70; // Une case fait 70 px de largeur

       // Ordonnee
       if (pos.y >Sumy && pos.y<Sumy+70){
           chessGrid.y =((Sumy-bordureEpaisseur)/caseTaille)+1;
           condBoucle++;
       }
       Sumy +=70; // Une case fait 70 px de hauteur
   }

    // renvoie les coordonne version chessGrid
    return chessGrid;
}


//Convertis les cases en coordoonne
PixGrid PixelCoordonnee(ChessGrid carreau)
{
    PixGrid pixGrid; // coordonne des pixel x et y 
    int i=97; // le a=97 en ascii
    int j=1;
    int Sumx=bordureEpaisseur;
    int Sumy=bordureEpaisseur;
    int condBoucle =0;
    while (condBoucle !=2)
    {
	// Abscisse
        if (carreau.x >= i && carreau.x <= i++) {
            pixGrid.x = Sumx;
            i++;
            condBoucle++;
        }
        Sumx+=caseTaille;
	// Ordonee
        if (carreau.y >= j && carreau.y <= j++){
            pixGrid.y=Sumy;
            Sumy++;
            condBoucle ++;
        }
        Sumy+=caseTaille;
    }
    return pixGrid;
}

//Renvoie la case sur laquelle on relache clique
ChessGrid clicCase()
{
    PixGrid mouse;
    ChessGrid pos;

    if (etatBoutonSouris() == GaucheRelache)
    {
		mouse.x= abscisseSouris();
		mouse.y= ordonneeSouris();
		pos = GridCoordonnee(mouse);//ON donne a pos les coordonnées en echec de la souris

	}

    return pos;
}