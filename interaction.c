#include <stdio.h>
#include "coordonnee.h"




ChessGrid recupereCommandeTapee(char touche, char *tableau_commande, int case_remplie)
{
	ChessGrid commande;
	tableau_commande[case_remplie] = touche;
	commande.x = tableau_commande[0];
	commande.y = tableau_commande[1] -'0';

	return commande;
}

void afficheCommandeTapee1(ChessGrid *commande)
{
	char commandeEcrite[3];
	commandeEcrite[0] = (char)commande->x;
	commandeEcrite[1] = (char)commande->y+'0';
	commandeEcrite[2] = '\0';
	
	epaisseurDeTrait(2);
	couleurCourante(0,0,0);
	afficheChaine(commandeEcrite, 15, 720, 183);
}

void afficheCommandeTapee2(ChessGrid *commande)
{
	char commandeEcrite[3];
	commandeEcrite[0] = (char)commande->x;
	commandeEcrite[1] = (char)commande->y+'0';
	commandeEcrite[2] = '\0';
	
	epaisseurDeTrait(2);
	couleurCourante(0,0,0);
	afficheChaine("en", 15, 745, 183);
	afficheChaine(commandeEcrite, 15, 770, 183);
}