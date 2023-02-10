#include <stdlib.h>
#include <stdio.h>
#include "GfxLib.h"
#include "BmpLib.h"
#include "ESLib.h"
#include "coordonnee.h"
#include "graphisme.h"
#include "pieces.h"
#include "Timer.h"
#include "interaction.h"

// Window Size
#define LargeurFenetre 850
#define HauteurFenetre 650



//Prototypes de fontion

void gestionEvenement(EvenementGfx evenement);


//Initialisation des variables

GestionTime GestionTemps; //Variable de gestion des timers et leur affichage



bool EtatTimer=false;
bool PartieLancee=false;
bool Reset=false;
bool menu = true;

char tableau_commande[3] = {0};
char tableau_commande2[3] = {0};

ChessGrid commande;
ChessGrid commande2; 
bool alternCommande = false;


bool EtatJoueur=false; // Si 0 -> Aux blancs de jouer/Si 1 -> Aux noirs de jouer

//Main


int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);

	GestionTemps.compteurWhite=900; //On initialise le temps des blancs a 15 mins
	GestionTemps.compteurBlack=900; //On initialise le temps des noirs a 15 mins

	prepareFenetreGraphique("Chess Isen",LargeurFenetre, HauteurFenetre);
	lanceBoucleEvenements();
	return 0;
}




//Event
void gestionEvenement(EvenementGfx evenement)
{
	//Initialisation des variables

	static DonneesImageRGB *grid = NULL; 

	PixGrid mouse;
	ChessGrid pos;


	int initialisation = 0;



	
	
	switch(evenement){
		
		case Initialisation:

			//Initialisation des images
			grid = lisBMPRGB("images/grid.bmp"); //lis l'image attention le bmp en 24 bit
			demandeTemporisation(20);
			break;

		case Temporisation:
			
			GestionTemps=Decompte(EtatTimer, EtatJoueur, GestionTemps);

			GestionTemps=TransformCompteur(GestionTemps);

			rafraichisFenetre();

			break;	

		case Affichage:
			//Affiche l'image du menu de base
			if (menu == true)
			{
				afficheMenu();
			}
			
			//Affichage d'un image

			if (menu == false)
			{

			if (grid != NULL){
                	ecrisImage(0,0,grid->largeurImage,grid->hauteurImage,grid->donneesRGB);
        		}
			
			AfficheTemps(GestionTemps);
			//Affiche les pions si la partie est lancer

			epaisseurDeTrait(3);
			couleurCourante(0,0,0);
			afficheChaine("LAST MOVE", 15, 715, 208);

			afficheCommandeTapee1(&commande);
			afficheCommandeTapee2(&commande2);
			}
			
			AfficheTemps(GestionTemps);

			//On affiche les positions disponibles de déplacement
			if(PartieLancee)
			{
				AffichePieces(); //Affiche en continue les pieces
				EtatJoueur=Pawn(EtatJoueur); 
				EtatJoueur=Tower(EtatJoueur);
				EtatJoueur=Knight(EtatJoueur);
				EtatJoueur=Bishop(EtatJoueur);
				EtatJoueur=Queen(EtatJoueur);
				EtatJoueur=King(EtatJoueur);
				
			}
			//Si Reset==1
			if(Reset)
			{
				AffichePieces(); //On reaffiche les pieces à leur position
				GestionTemps.compteurWhite=900; // On reset les temps 
				GestionTemps.compteurBlack=900;
				EtatJoueur=false; //On redonne le tour aux blancs
				Reset=false; //On empeche un re-reset instantanné
			}
			
			break;

		case BoutonSouris:
			
			//Gestion des coordonées x & y
			if (etatBoutonSouris() == GaucheAppuye){
				mouse.x= abscisseSouris();
				mouse.y= ordonneeSouris();
				
				pos = GridCoordonnee(mouse);//On donne a pos les coordonnées en echec de la souris
				
			}


			
			//Si on appuie sur lancer la partie
			if((pos.x=='j')&&(pos.y==6)&&(PartieLancee==0))
			{
				EtatTimer=!EtatTimer; //Changer la valeur associée au depart du timer
				PartieLancee=1; 
				DefPositionInitPieces(); //On définis la position des pièces
			}

			//Si on appuie sur reset
			if((pos.x=='k')&&(pos.y==6))
			{
				DefPositionInitPieces(); //On définit la position des pieces
				Reset=true; //On active le reset
			}

			
			if((pos.x=='l')&&((pos.y==8)||(pos.y==7))) //Si on appuie sur les boutons pauses
			{
				EtatTimer=!EtatTimer; //On inverse l'etat timer qui met en pause les decomptes
			}

			if((mouse.x>650)&&(mouse.x<850)&&(mouse.y>340)&&(mouse.y<400)) //Si on appuie sur save
			{
				save();
				printf("Succed\n");
			}

			if((mouse.x>650)&&(mouse.x<850)&&(mouse.y>250)&&(mouse.y<330)) //Si on appuie sur load
			{
				load();
				printf("Succed\n");
			}

			if(PartieLancee) //Si on clique quelque part 
			{
				//On vérifie quelle piece est selectionnee
				CheckPawn(pos,EtatJoueur);
				CheckTower(pos,EtatJoueur);
				CheckKnights(pos,EtatJoueur);
				CheckBishop(pos,EtatJoueur);
				CheckQueen(pos,EtatJoueur);
				CheckKing(pos,EtatJoueur);
			}

			break;

		case Clavier:

			switch (caractereClavier())
			{
			case 'Q': // Pour sortir quelque peu proprement du programme
			case 'q':
					libereDonneesImageRGB(&grid); // On libere la structure image,
						// c'est plus propre, meme si on va sortir du programme juste apres
					termineBoucleEvenements();
					break;
			case 'P':
			case 'p':
					menu = false;
					break;

			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
				if (alternCommande == false)
				{
					commande = recupereCommandeTapee(caractereClavier(), &tableau_commande, 0);
				}
				if (alternCommande == true)
				{
					commande2 = recupereCommandeTapee(caractereClavier(), &tableau_commande2, 0);
					
				}
				break;

			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
				if (alternCommande == false)
				{
					commande = recupereCommandeTapee(caractereClavier(), &tableau_commande, 1);
					printf("commande format chessgrid: %c %d\n", commande.x, commande.y);
				}

				if (alternCommande == true)
				{
					commande2 = recupereCommandeTapee(caractereClavier(), &tableau_commande2, 1);
					printf("commande2 format chessgrid: %c %d\n", commande2.x, commande2.y);
					
				}
				break;
			
			case 13:  //appuie sur entree
				alternCommande = !alternCommande; //change la valeur de alterncommande
		
			default:
				break;
		}
	}
}


