#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#include "Timer.h"
#include "GfxLib.h"
#include "ESLib.h"

//Ici il y a toutes les fonctions par rapport à la gestion de temps

double TempsActuel;
double AncienTemps;
double Ecart;

//Decompte du temps si necessaire
GestionTime Decompte(bool EtatTimer,bool EtatJoueur, GestionTime GestionTemps)
{



//Si le compteur vaut 1
	if (EtatTimer) 
	{ 	
		
		//ON affecte a une variable la valeur du temps actuel
		TempsActuel=tempsReel();
		
		//ON vérifie l'écart de temps avec l'ancienne valeur stockée
		Ecart=TempsActuel-AncienTemps;
		
		//Si celle ci >1 et que c'est aux blancs de jouer
		if((Ecart>=1)&&(!EtatJoueur))
		{
			AncienTemps=TempsActuel; //ON stock le temps actuel pour les prochaines comparaisons
			GestionTemps.compteurWhite=GestionTemps.compteurWhite-1; //On décremente compteur
					
		}

		//Si celle ci >1 et que c'est aux noirs de jouer
		if((Ecart>=1)&&(EtatJoueur))
		{
			AncienTemps=TempsActuel; //ON stock le temps actuel pour les prochaines comparaisons
			GestionTemps.compteurBlack=GestionTemps.compteurBlack-1; //On décremente compteur
			
		}
			
	
		
	}
	
	
	
return GestionTemps; //On renvoit compteur
}



//Transforme les int en char pour les afficher
GestionTime TransformCompteur(GestionTime GestionTemps)
{
			
			
			GestionTemps.ValeurMinutesWhite=GestionTemps.compteurWhite/60; //Recupere le reste en minutes de compteur
			GestionTemps.ValeurSecondesWhite=GestionTemps.compteurWhite%60; //Recupere le reste en secondes de compteur
			
			sprintf (GestionTemps.ChaineMinutesWhite, "%d", GestionTemps.ValeurMinutesWhite); //On transforme le int en char
			sprintf (GestionTemps.ChaineSecondesWhite, "%d", GestionTemps.ValeurSecondesWhite);//On transforme le int en char

//----------------------------------------------------------------------------

			GestionTemps.ValeurMinutesBlack=GestionTemps.compteurBlack/60; //Recupere le reste en minutes de compteur
			GestionTemps.ValeurSecondesBlack=GestionTemps.compteurBlack%60; //Recupere le reste en secondes de compteur
			
			sprintf (GestionTemps.ChaineMinutesBlack, "%d", GestionTemps.ValeurMinutesBlack); //On transforme le int en char
			sprintf (GestionTemps.ChaineSecondesBlack, "%d", GestionTemps.ValeurSecondesBlack);//On transforme le int en char

return GestionTemps;
}

void AfficheTemps(GestionTime GestionTemps)
{
	//Affichage du temps restant
        		epaisseurDeTrait(2);


	//Affichage temps Noir	
        		couleurCourante(0,0,0);   //noire
				
				afficheChaine("Temps noir",13,720,597);

				afficheChaine(GestionTemps.ChaineMinutesBlack,20,720,571); //On affiche la chaine des minutes
				afficheChaine("m",20,745,571);
				afficheChaine(GestionTemps.ChaineSecondesBlack,20,767,571); //On affiche la chaine des secondes
				afficheChaine("s",20,793,571);


	//Affichage temps blanc
				

				afficheChaine("Temps blanc",13,720,517);

				afficheChaine(GestionTemps.ChaineMinutesWhite,20,720,491); //On affiche la chaine des minutes
				afficheChaine("m",20,745,491);
				afficheChaine(GestionTemps.ChaineSecondesWhite,20,767,491); //On affiche la chaine des secondes
				afficheChaine("s",20,793,491);

				
}


