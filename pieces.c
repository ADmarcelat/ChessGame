#include <stdio.h>
#include <stdlib.h> //Pour abs()
#include "coordonnee.h"
#include "GfxLib.h"
#include "BmpLib.h"
#include "ESLib.h"
#include "graphisme.h"
#include "pieces.h"


//Gestions des pions :

//White
ChessGrid WhitePawns[8];
ChessGrid WhiteTower[2];
ChessGrid WhiteKnight[2];
ChessGrid WhiteBishop[2];
ChessGrid WhiteQueen;
ChessGrid WhiteKing;

//Black
ChessGrid BlackPawns[8];
ChessGrid BlackTower[2];
ChessGrid BlackKnight[2];
ChessGrid BlackBishop[2];
ChessGrid BlackQueen;
ChessGrid BlackKing;

//Compteurs
int piecePawn=32; //nombre de pièces (permettant de savoir si on doit afficher les coups possibles ou non)
int clicPawn=0; //Selection ou non d'un pion

int clicTower=0; 
int pieceTower=32;

int clicKnight=0;
int pieceKnight=32;

int clicBishop=0; 
int pieceBishop=32;

int clicQueen=0; 
int pieceQueen=32;

int clicKing=0;
int pieceKing=0;




//Variable de verification de coup
bool VerifieCoup;

// Les fonctions :

void save() // permet de sauvegarder
{
	printf("Saving\n");
    FILE *fichier= fopen("last_save.dat","wb"); 
    if (fichier != NULL) 
    { 
        fwrite(WhitePawns,sizeof(ChessGrid),8,fichier);
		fwrite(BlackPawns,sizeof(ChessGrid),8,fichier);
		fwrite(WhiteTower,sizeof(ChessGrid),2,fichier);
		fwrite(BlackTower,sizeof(ChessGrid),2,fichier);
		fwrite(WhiteKnight,sizeof(ChessGrid),2,fichier);
		fwrite(BlackKnight,sizeof(ChessGrid),2,fichier); 
		fwrite(WhiteBishop,sizeof(ChessGrid),2,fichier);
		fwrite(BlackBishop,sizeof(ChessGrid),2,fichier);
		fwrite(&WhiteQueen,sizeof(ChessGrid),1,fichier);
		fwrite(&BlackQueen,sizeof(ChessGrid),1,fichier);
		fwrite(&WhiteKing,sizeof(ChessGrid),1,fichier);
		fwrite(&BlackKing,sizeof(ChessGrid),1,fichier);          
		fclose(fichier);
    } 
    else 
    { 
    puts("impossible d'ouvrir le fichier"); 
    }
}

void load() // permet de load la last_save
{
	printf("Loading\n");

    FILE *fichier= fopen("last_save.dat","rb"); 
    if (fichier != NULL) 
    { 
        fread(WhitePawns,sizeof(ChessGrid),8,fichier);
		fread(BlackPawns,sizeof(ChessGrid),8,fichier);
		fread(WhiteTower,sizeof(ChessGrid),2,fichier);
		fread(BlackTower,sizeof(ChessGrid),2,fichier);
		fread(WhiteKnight,sizeof(ChessGrid),2,fichier);
		fread(BlackKnight,sizeof(ChessGrid),2,fichier); 
		fread(WhiteBishop,sizeof(ChessGrid),2,fichier);
		fread(BlackBishop,sizeof(ChessGrid),2,fichier);
		fread(&WhiteQueen,sizeof(ChessGrid),1,fichier);
		fread(&BlackQueen,sizeof(ChessGrid),1,fichier);
		fread(&WhiteKing,sizeof(ChessGrid),1,fichier);
		fread(&BlackKing,sizeof(ChessGrid),1,fichier);   
		fclose(fichier);
    } 
    else 
    { 
    	 puts("impossible d'ouvrir le fichier"); 
    }
}


// Prend une case en entrée et renvoie ce qu'il y a sur la case
CheckCase caseValue(ChessGrid carreau)
{
	CheckCase pawn;
	pawn.index = 32;
	pawn.name = '0';
	pawn.color = '0';
	//Queen
	if(WhiteQueen.x == carreau.x && WhiteQueen.y == carreau.y)
	{
		pawn.name = 'q'; // q => queen
		pawn.color = 'w'; // w => White
		pawn.index = 0; 
	}
	if(BlackQueen.x == carreau.x && BlackQueen.y == carreau.y)
	{
		pawn.name = 'q';
		pawn.color = 'b'; // black
		pawn.index = 0; 
	}
	//King
	if(WhiteKing.x == carreau.x && WhiteKing.y == carreau.y)
	{
		pawn.name = 'k';
		pawn.color = 'w';
		pawn.index = 0; 
	}
	if(BlackKing.x == carreau.x && BlackKing.y == carreau.y)
	{
		pawn.name = 'k';
		pawn.color = 'b';
		pawn.index = 0; 
	}

	else
	{
		//Pion par 8
		for(int i =0;i<8;i++)
		{
			if(WhitePawns[i].x == carreau.x && WhitePawns[i].y == carreau.y)
			{
				pawn.name = 'p';
				pawn.color = 'w';
				pawn.index = i; 
			}

			if(BlackPawns[i].x == carreau.x && BlackPawns[i].y == carreau.y)
			{
				pawn.name = 'p';
				pawn.color = 'b';
				pawn.index = i; 
			}		
		}

		//Pion par 2
		for(int i=0;i<2;i++)
		{
			//Tower
			if(WhiteTower[i].x == carreau.x && WhiteTower[i].y == carreau.y)
			{
				pawn.name = 't';
				pawn.color = 'w';
				pawn.index = i; 
			}
			if(BlackTower[i].x == carreau.x && BlackTower[i].y == carreau.y)
			{
				pawn.name = 't';
				pawn.color = 'b';
				pawn.index = i; 
			}

			//Knight
			if(WhiteKnight[i].x == carreau.x && WhiteKnight[i].y == carreau.y)
			{
				pawn.name = 'c'; // c => cavalier
				pawn.color = 'w';
				pawn.index = i; 
			}
			if(BlackKnight[i].x == carreau.x && BlackKnight[i].y == carreau.y)
			{
				pawn.name = 'c';
				pawn.color = 'b';
				pawn.index = i; 
			}
			//Bishop
			if(WhiteBishop[i].x == carreau.x && WhiteBishop[i].y == carreau.y)
			{
				pawn.name = 'b';
				pawn.color = 'w';
				pawn.index = i; 
			}
			if(BlackBishop[i].x == carreau.x && BlackBishop[i].y == carreau.y)
			{
				pawn.name = 'b';
				pawn.color = 'b';
				pawn.index = i; 
			}
		}
	}
	return pawn;
}



//On affiche chacun des pions à leur place
void AffichePieces()
{
	//Initialisation des variables

	static DonneesImageRGB *pawn_white = NULL;
	static DonneesImageRGB *pawn_black = NULL;
	static DonneesImageRGB *tower_white = NULL;
	static DonneesImageRGB *tower_black = NULL;
	static DonneesImageRGB *knight_white = NULL;
	static DonneesImageRGB *knight_black = NULL;
	static DonneesImageRGB *bishop_white = NULL;
	static DonneesImageRGB *bishop_black = NULL;
	static DonneesImageRGB *queen_white = NULL;
	static DonneesImageRGB *queen_black= NULL;
	static DonneesImageRGB *king_white = NULL;
	static DonneesImageRGB *king_black = NULL;

	//Lecture des images

 	pawn_white=lisBMPRGB("images/pawn_white.bmp");
	pawn_black=lisBMPRGB("images/pawn_black.bmp");
	tower_white=lisBMPRGB("images/tower_white.bmp");
	tower_black=lisBMPRGB("images/tower_black.bmp");
	knight_white=lisBMPRGB("images/knight_white.bmp");
	knight_black=lisBMPRGB("images/knight_black.bmp");
	bishop_white=lisBMPRGB("images/bishop_white.bmp");
	bishop_black=lisBMPRGB("images/bishop_black.bmp");
	queen_white=lisBMPRGB("images/queen_white.bmp");
	queen_black=lisBMPRGB("images/queen_black.bmp");
	king_white=lisBMPRGB("images/king_white.bmp");
	king_black=lisBMPRGB("images/king_black.bmp");

 	
 	if 
	 (pawn_white != NULL &&
	  pawn_black != NULL && 
	  tower_white != NULL &&
	  tower_black != NULL &&
	  knight_white !=NULL &&
	  knight_black != NULL &&
	  bishop_white != NULL &&
	  bishop_black != NULL &&
	  queen_white != NULL &&
	  queen_black != NULL &&
	  king_white != NULL &&
	  king_black != NULL)
 	{
 		//On affiche chaque pion

		
		//Pions par 8
 		for(int i=0;i<8;i++)
 		{	
 			//Pion blanc
			PixGrid PosInitWhitePawns=PixelCoordonnee(WhitePawns[i]);
 			ecrisImageTransparence(PosInitWhitePawns.x+9,PosInitWhitePawns.y+1,pawn_white->largeurImage,pawn_white->hauteurImage,pawn_white->donneesRGB); //+8 en x et +2 en y pour le décalage due à la taille de l'image
 			//Pion noir
			PixGrid PosInitBlackPawns=PixelCoordonnee(BlackPawns[i]);
 			ecrisImageTransparence(PosInitBlackPawns.x+9,PosInitBlackPawns.y+1,pawn_black->largeurImage,pawn_black->hauteurImage,pawn_black->donneesRGB);
 		}
		//Pièces par 2
		for(int i=0;i<2;i++)
		{
			//Tour blanche
			PixGrid PosInitWhiteTower=PixelCoordonnee(WhiteTower[i]);
 			ecrisImageTransparence(PosInitWhiteTower.x+5,PosInitWhiteTower.y,tower_white->largeurImage,tower_white->hauteurImage,tower_white->donneesRGB);
			//Tour blanche
			PixGrid PosInitBlackTower=PixelCoordonnee(BlackTower[i]);
 			ecrisImageTransparence(PosInitBlackTower.x+5,PosInitBlackTower.y,tower_black->largeurImage,tower_black->hauteurImage,tower_black->donneesRGB);

			//Cavalier blanc
			PixGrid PosInitWhiteKnight=PixelCoordonnee(WhiteKnight[i]);
 			ecrisImageTransparence(PosInitWhiteKnight.x+4,PosInitWhiteKnight.y+3,knight_white->largeurImage,knight_white->hauteurImage,knight_white->donneesRGB);
			//Cavalier noir
			PixGrid PosInitBlackKnight=PixelCoordonnee(BlackKnight[i]);
 			ecrisImageTransparence(PosInitBlackKnight.x+4,PosInitBlackKnight.y+3,knight_black->largeurImage,knight_black->hauteurImage,knight_black->donneesRGB);

			//Fou blanc
			PixGrid PosInitWhiteBishop=PixelCoordonnee(WhiteBishop[i]);
 			ecrisImageTransparence(PosInitWhiteBishop.x+3,PosInitWhiteBishop.y+1,bishop_white->largeurImage,bishop_white->hauteurImage,bishop_white->donneesRGB);
			//Fou noir
			PixGrid PosInitBlackBishop=PixelCoordonnee(BlackBishop[i]);
 			ecrisImageTransparence(PosInitBlackBishop.x+3,PosInitBlackBishop.y+1,bishop_black->largeurImage,bishop_black->hauteurImage,bishop_black->donneesRGB);
		}
		//Pièces unitaires
		
		//Reine blanche
		PixGrid PosInitWhiteQueen=PixelCoordonnee(WhiteQueen);
 		ecrisImageTransparence(PosInitWhiteQueen.x+3,PosInitWhiteQueen.y,queen_white->largeurImage,queen_white->hauteurImage,queen_white->donneesRGB);
		//Reine noire
		PixGrid PosInitBlackQueen=PixelCoordonnee(BlackQueen);
 		ecrisImageTransparence(PosInitBlackQueen.x+3,PosInitBlackQueen.y,queen_black->largeurImage,queen_black->hauteurImage,queen_black->donneesRGB);
		
		//Roi blanc
		PixGrid PosInitWhiteKing=PixelCoordonnee(WhiteKing);
 		ecrisImageTransparence(PosInitWhiteKing.x+4,PosInitWhiteKing.y+3,king_white->largeurImage,king_white->hauteurImage,king_white->donneesRGB);
		//Roi blanc
		PixGrid PosInitBlackKing=PixelCoordonnee(BlackKing);
 		ecrisImageTransparence(PosInitBlackKing.x+4,PosInitBlackKing.y+3,king_black->largeurImage,king_black->hauteurImage,king_black->donneesRGB);
	 }
}





//Définit la position initiale de chaque pièce
void DefPositionInitPieces()
{
	for(int i=0;i<8;i++)
	{
		//Pion blanc
		WhitePawns[i].x='a'+i;
		WhitePawns[i].y=2;
		//Pion Noir
		BlackPawns[i].x='a'+i;
		BlackPawns[i].y=7;
	}

	//Tour blanche
	WhiteTower[1].x='h';
	WhiteTower[1].y=1;
	WhiteTower[0].x='a';
	WhiteTower[0].y=1;

	//Tour blanche
	BlackTower[1].x='h';
	BlackTower[1].y=8;
	BlackTower[0].x='a';
	BlackTower[0].y=8;

	//Cavalier blanc
	WhiteKnight[1].x='g';
	WhiteKnight[1].y=1;
	WhiteKnight[0].x='b';
	WhiteKnight[0].y=1;

	//Cavalier noir
	BlackKnight[1].x='g';
	BlackKnight[1].y=8;
	BlackKnight[0].x='b';
	BlackKnight[0].y=8;

	//Fou blanc
	WhiteBishop[1].x='f';
	WhiteBishop[1].y=1;
	WhiteBishop[0].x='c';
	WhiteBishop[0].y=1;

	//Fou noir
	BlackBishop[1].x='f';
	BlackBishop[1].y=8;
	BlackBishop[0].x='c';
	BlackBishop[0].y=8;

	
	//Reine blanche
	WhiteQueen.x='d';
	WhiteQueen.y=1;

	//Reine noire
	BlackQueen.x='d';
	BlackQueen.y=8;
	
	//Roi blanc
	WhiteKing.x='e';
	WhiteKing.y=1;

	//Roi noir
	BlackKing.x='e';
	BlackKing.y=8;
}

//Permet de tuer le pion se situant sur la case en entrée de la focntion
void killPiece(ChessGrid carreau)
{
	CheckCase valeur = caseValue(carreau);
	if(valeur.color == 'w') // White
	{
		switch (valeur.name)
		{
		case 'q':
			WhiteQueen.x ='a'; // on place le pion en {'a',10} qui est une case de kill
			WhiteQueen.y = 10;
			break;
		case 'k':
			WhiteKing.x ='a';
			WhiteKing.y =10;
			break;
		case 'p':
			WhitePawns[valeur.index].x='a';
			WhitePawns[valeur.index].y=10;
			break;
		case 't':
			WhiteTower[valeur.index].x='a';
			WhiteTower[valeur.index].y=10;
			break;
		case 'c':
			WhiteKnight[valeur.index].x='a';
			WhiteKnight[valeur.index].y=10;
			break;
		case 'b':
			WhiteBishop[valeur.index].x='a';
			WhiteBishop[valeur.index].y=10;
			break;
		}
	}
	if(valeur.color == 'b') // Black
	{
		switch (valeur.name)
		{
		case 'q':
			BlackQueen.x ='a';
			BlackQueen.y = 10;
			break;
		case 'k':
			BlackKing.x ='a';
			BlackKing.y =10;
			break;
		case 'p':
			BlackPawns[valeur.index].x='a';
			BlackPawns[valeur.index].y=10;
			break;
		case 't':
			BlackTower[valeur.index].x='a';
			BlackTower[valeur.index].y=10;
			break;
		case 'c':
			BlackKnight[valeur.index].x='a';
			BlackKnight[valeur.index].y=10;
			break;
		case 'b':
			BlackBishop[valeur.index].x='a';
			BlackBishop[valeur.index].y=10;
			break;
		}
	}
}




//--------------------------------------------------- PAWNS ----------------------------------------------


//On vérifie si l'utilisateur clique sur un pion, si oui lequel 
void CheckPawn(ChessGrid pos, bool EtatJoueur)
{

	//Si c'est aux blancs
	if(!EtatJoueur)
	{
		for(int i=0; i<8 ; i++)
		{	
			if((pos.x==WhitePawns[i].x)&&(pos.y==WhitePawns[i].y)) //Si on clique sur la position du pion
			{
				piecePawn=i; 
				clicPawn+=1;
			}
		}
		
	}
//------------------------
	//Si c'est aux noirs
	if(EtatJoueur)
	{
		for(int i=0; i<8 ; i++)
		{	
			if((pos.x==BlackPawns[i].x)&&(pos.y==BlackPawns[i].y)) //Si on clique sur la position du pion
			{
				piecePawn=i;
				clicPawn+=1; 
			}
		}
		
	}

	//Si on reclique
	if((clicPawn==2))
		{
			piecePawn=32; //On désaffiche les coups possible
			clicPawn=0; //Si on reclique on reset
		}
}


//Fonction affichage et déplacement des pawns 
bool Pawn(bool EtatJoueur)
{
	ChessGrid WhCarreauPawn = WhitePawns[piecePawn];
	ChessGrid BLCarreauPawn = BlackPawns[piecePawn];
	//-------------------------------------
	//Carreau blanc au dessus
	ChessGrid WhCarreauPawnUp = WhCarreauPawn;
	WhCarreauPawnUp.y+=1;
	//Carreau noir en dessous
	ChessGrid BLCarreauPawnDown = BLCarreauPawn;
	BLCarreauPawnDown.y-=1;

	//Carreau blanc diagonale
	ChessGrid WhCarreauPawnUpLeft = WhCarreauPawn;
	WhCarreauPawnUpLeft.x-=1;
	WhCarreauPawnUpLeft.y+=1;
	ChessGrid WhCarreauPawnUpRight = WhCarreauPawn;
	WhCarreauPawnUpRight.x+=1;
	WhCarreauPawnUpRight.y+=1;


	//Carreau noir diagonale
	ChessGrid BLCarreauPawnDownLeft = BLCarreauPawn;
	BLCarreauPawnDownLeft.x-=1;
	BLCarreauPawnDownLeft.y-=1;
	ChessGrid BLCarreauPawnDownRight = BLCarreauPawn;
	BLCarreauPawnDownRight.x+=1;
	BLCarreauPawnDownRight.y-=1;

	//-------------------------------------

	ChessGrid ChoosenCase = clicCase();

	//Affichage disponibilité déplacement white pawns


	if(!EtatJoueur)
	{
		if(piecePawn != 32 && caseValue(WhCarreauPawnUp).name == '0' ) // On vérifie qu'il n'y a pas de pièce au dessus
		{	
			caseVerte(WhCarreauPawnUp); // affiche la case en verte	
			WhCarreauPawnUp.y+=1;
			if((WhitePawns[piecePawn].y == 2)&&(caseValue(WhCarreauPawnUp).name == '0')) //On verifie si il y a une piece 2 case au dessus du pion au depart
			{
				caseVerte(WhCarreauPawnUp); //Si non, on affiche une case verte
			}
			
		}
		if (piecePawn != 32)
		{
			// Affiche en rouge la case d'une diagonale d'un pion que on peut manger
			// name != '0' c'est qu'il y a un pion
			if(caseValue(WhCarreauPawnUpRight).name != '0' && caseValue(WhCarreauPawnUpRight).name != 'k' && caseValue(WhCarreauPawnUpRight).color=='b') // On ne peut pas tuer le kill
			{
				caseRouge(WhCarreauPawnUpRight); // affiche la case en rouge
			}

			if(caseValue(WhCarreauPawnUpLeft).name != '0' && caseValue(WhCarreauPawnUpLeft).name != 'k' && caseValue(WhCarreauPawnUpLeft).color=='b')
			{
				caseRouge(WhCarreauPawnUpLeft);
			}

		}
	}
//-------------------------------------------------
	//Affichage disponibilité déplacement black pawns
	if(EtatJoueur)
	{
		if(piecePawn != 32 && caseValue(BLCarreauPawnDown).name == '0')
		{	
			
			caseVerte(BLCarreauPawnDown); //Afficher case verte
			BLCarreauPawnDown.y-=1;
			if((BlackPawns[piecePawn].y == 7) && caseValue(BLCarreauPawnDown).name=='0') //On regarde si il y a une pièce 2 cases en dessosu du pion de depart
			{
				
				caseVerte(BLCarreauPawnDown); // Si non, on y affiche une case verte
			}
			
		}

		if(piecePawn !=32)
		{
			// Affiche en rouge la case d'une diagonale
			if(caseValue(BLCarreauPawnDownRight).name != '0' && caseValue(BLCarreauPawnDownRight).name != 'k' && caseValue(BLCarreauPawnDownRight).color=='w') // on ne peut pas kill le king
			{
				caseRouge(BLCarreauPawnDownRight); // affiche la case en rouge
			}

			if(caseValue(BLCarreauPawnDownLeft).name != '0' && caseValue(BLCarreauPawnDownLeft).name != 'k' && caseValue(BLCarreauPawnDownLeft).color=='w')
			{
				caseRouge(BLCarreauPawnDownLeft);
			}
		}
	}
//----------------------------------------------

	//On verifie qu'on clique dans la grille
	if((ChoosenCase.x>=97)&&(ChoosenCase.x<=104)&&(ChoosenCase.y>=1)&&(ChoosenCase.y<=8))
	{
		//Déplacement white pawns
		if(!EtatJoueur)
		{
			//Si le pion est à sa place de départ on autorise un déplacement de 2 cases
			if((WhitePawns[piecePawn].y==2)&&caseValue(ChoosenCase).name=='0')
			{
				if((ChoosenCase.y==WhitePawns[piecePawn].y+2)&&(ChoosenCase.x==WhitePawns[piecePawn].x)) 
				{
				
					EtatJoueur=PlacePion(ChoosenCase, EtatJoueur);
				}
			}
			
			//Sinon on autorise un déplacement de 1 case
			if((ChoosenCase.y==WhitePawns[piecePawn].y+1)&&(ChoosenCase.x==WhitePawns[piecePawn].x)&&(caseValue(ChoosenCase).name == '0'))
			{
				EtatJoueur=PlacePion(ChoosenCase, EtatJoueur);
			}

			//Si il y a un pion sur la diagonale droite ou gauche on le kill et on prend sa place
			if((ChoosenCase.y==WhitePawns[piecePawn].y+1)&&((ChoosenCase.x==WhitePawns[piecePawn].x+1)||(ChoosenCase.x==WhitePawns[piecePawn].x-1))&&(caseValue(ChoosenCase).name != '0')&&(caseValue(ChoosenCase).name != 'k'))
			{
				killPiece(ChoosenCase);
				EtatJoueur=PlacePion(ChoosenCase, EtatJoueur);
			}
			
		}
//----------------------------------------
	//Déplacement black pawns
		if(EtatJoueur)
		{
			//Si le pion est à sa place de départ on autorise un déplacement de 2 cases
			if((BlackPawns[piecePawn].y==7)&& caseValue(ChoosenCase).name=='0')
			{
				if((ChoosenCase.y==BlackPawns[piecePawn].y-2)&&(ChoosenCase.x==BlackPawns[piecePawn].x)) 
				{
					
					EtatJoueur=PlacePion(ChoosenCase, EtatJoueur);
				}
			}
			
			//Sinon on autorise un déplacement de 1 case
			if((ChoosenCase.y==BlackPawns[piecePawn].y-1)&&(ChoosenCase.x==BlackPawns[piecePawn].x)&&(caseValue(ChoosenCase).name == '0'))
			{
				EtatJoueur=PlacePion(ChoosenCase, EtatJoueur);
			}

			//Si il y a un pion sur la diagonale droite ou gauche on le kill et on prend sa place
			if((ChoosenCase.y==BlackPawns[piecePawn].y-1)&&((ChoosenCase.x==BlackPawns[piecePawn].x+1)||(ChoosenCase.x==BlackPawns[piecePawn].x-1))&&(caseValue(ChoosenCase).name != '0')&&(caseValue(ChoosenCase).name != 'k'))
			{
				killPiece(ChoosenCase);
				EtatJoueur=PlacePion(ChoosenCase, EtatJoueur);
			}
			

		}

		
		
	}

	
return EtatJoueur; //Return de Etat joueur changé pour mettre à jour les timers
}


//---------------------------------------------------

//Place le pion selectionné à la case choisie
bool PlacePion(ChessGrid ChoosenCase, int EtatJoueur)
{
	//Si déplacement pion blanc
	if(!EtatJoueur)
	{
		WhitePawns[piecePawn].x=ChoosenCase.x; //On déplace en X
		WhitePawns[piecePawn].y=ChoosenCase.y; //On déplace en Y
		
	}
	//--------------------------

	//Si déplacement pion noir
	if(EtatJoueur)
	{
		BlackPawns[piecePawn].x=ChoosenCase.x; //On deplace en X
		BlackPawns[piecePawn].y=ChoosenCase.y; //On déplace en Y
		
	}


	piecePawn=32; //On déselectionne la piece choisie
	clicPawn=0; //On donc empeche l'affichage de coup disponible
	
EtatJoueur=!EtatJoueur; //C'est au tour de l'autre joueur

return EtatJoueur; 
}


//------------------------------------------ TOWERS ----------------------------------------





void CheckTower(ChessGrid pos, bool EtatJoueur)
{

	//Si c'est aux blancs
	if(!EtatJoueur)
	{
		for(int i=0; i<2 ; i++)
		{	
			if((pos.x==WhiteTower[i].x)&&(pos.y==WhiteTower[i].y)) //Si on clique sur la position de la tour
			{
				pieceTower=i; 
				clicTower+=1;
			}
		}
		
	}
//------------------------
	//Si c'est aux noirs
	if(EtatJoueur)
	{
		for(int i=0; i<2 ; i++)
		{	
			if((pos.x==BlackTower[i].x)&&(pos.y==BlackTower[i].y)) //Si on clique sur la position de la tour
			{
				pieceTower=i;
				clicTower+=1; 
			}
		}
		
	}

	//Si on reclique
	if(clicTower==2)
	{
		pieceTower=32; //On désaffiche les coups possible
		clicTower=0; //Si on reclique on reset
	}
}

//---------------
//Fonction affichage et déplacement des tower
bool Tower(bool EtatJoueur)
{
	ChessGrid WhCarreauTower = WhiteTower[pieceTower];
	ChessGrid BLCarreauTower = BlackTower[pieceTower]; 
	//-------------------------------------
	
	//Toutes les directions de déplacement towers wh
	ChessGrid WhCarreauTowerUp = WhCarreauTower;
	WhCarreauTowerUp.y+=1;
	ChessGrid WhCarreauTowerLeft = WhCarreauTower;
	WhCarreauTowerLeft.x-=1;
	ChessGrid WhCarreauTowerRight = WhCarreauTower;
	WhCarreauTowerRight.x+=1;
	ChessGrid WhCarreauTowerDown = WhCarreauTower;
	WhCarreauTowerDown.y-=1;

	//Toutes les directions de déplacement towers bl
	ChessGrid BLCarreauTowerUp = BLCarreauTower;
	BLCarreauTowerUp.y+=1;
	ChessGrid BLCarreauTowerLeft = BLCarreauTower;
	BLCarreauTowerLeft.x-=1;
	ChessGrid BLCarreauTowerRight = BLCarreauTower;
	BLCarreauTowerRight.x+=1;
	ChessGrid BLCarreauTowerDown = BLCarreauTower;
	BLCarreauTowerDown.y-=1;
	
	

	
	//-------------------------------------

	ChessGrid ChoosenCase = clicCase();
	
	//Affichage disponibilité déplacement white tower

	
	if(!EtatJoueur)
	{
		if((pieceTower != 32)&&(clicTower==1)) // On vérifie qu'il n'y a pas de pièce au dessus
		{	
			
			
				while((WhCarreauTowerUp.y<9)&&(caseValue(WhCarreauTowerUp).name == '0'))
				{
				caseVerte(WhCarreauTowerUp); // affiche les case en verte
				WhCarreauTowerUp.y+=1;
				}

				if(caseValue(WhCarreauTowerUp).name != '0')
				{
					
					if((caseValue(WhCarreauTowerUp).name != 'k')&&(caseValue(WhCarreauTowerUp).color == 'b'))
					{
						caseRouge(WhCarreauTowerUp);//Sinon on affiche en rouge la case
					}
				}

				while((WhCarreauTowerLeft.x>96)&&(caseValue(WhCarreauTowerLeft).name == '0'))
				{
				caseVerte(WhCarreauTowerLeft); // affiche les case en verte
				WhCarreauTowerLeft.x-=1;
				}

				if(caseValue(WhCarreauTowerLeft).name != '0')
				{
					if((caseValue(WhCarreauTowerLeft).name != 'k')&&(caseValue(WhCarreauTowerLeft).color == 'b')) //ON affiche pas lorsqu'un roi est mis en echec
					{
						caseRouge(WhCarreauTowerLeft); //Sinon on affiche en rouge la case
					}
				}

				while((WhCarreauTowerRight.x<105)&&(caseValue(WhCarreauTowerRight).name == '0'))
				{
				caseVerte(WhCarreauTowerRight); // affiche les case en verte
				WhCarreauTowerRight.x+=1;
				}

				if(caseValue(WhCarreauTowerRight).name != '0')
				{
					if((caseValue(WhCarreauTowerRight).name != 'k')&&(caseValue(WhCarreauTowerRight).color == 'b')) //ON affiche pas lorsqu'un roi est mis en echec
					{
						caseRouge(WhCarreauTowerRight); //Sinon on affiche en rouge la case
					}
				}

				while((WhCarreauTowerDown.y>1)&&(caseValue(WhCarreauTowerDown).name == '0'))
				{
				caseVerte(WhCarreauTowerDown); // affiche les case en verte
				WhCarreauTowerDown.y-=1;
				}

				if(caseValue(WhCarreauTowerDown).name != '0')
				{
					if((caseValue(WhCarreauTowerDown).name != 'k')&&(caseValue(WhCarreauTowerDown).color == 'b')) //ON affiche pas lorsqu'un roi est mis en echec
					{
						caseRouge(WhCarreauTowerDown); //Sinon on affiche en rouge la case
					}
				}
	
		}
		
	}
//-------------------------------------------------
	//Affichage disponibilité déplacement black tower
	if(EtatJoueur)
	{
		if((pieceTower != 32)&&(clicTower==1)) // On vérifie qu'il n'y a pas de pièce au dessus
		{	
			

			
				while((BLCarreauTowerUp.y<9)&&(caseValue(BLCarreauTowerUp).name == '0'))
				{
				caseVerte(BLCarreauTowerUp); // affiche la case en verte
				BLCarreauTowerUp.y+=1;
				}

					if(caseValue(BLCarreauTowerUp).name != '0')
				{
					if((caseValue(BLCarreauTowerUp).name != 'k')&&(caseValue(BLCarreauTowerUp).color == 'w'))
					{
						caseRouge(BLCarreauTowerUp);//Sinon on affiche en rouge la case
					}
				}

				

				while((BLCarreauTowerLeft.x>96)&&(caseValue(BLCarreauTowerLeft).name == '0'))
				{
			
				caseVerte(BLCarreauTowerLeft); // affiche la case en verte
				BLCarreauTowerLeft.x-=1;
				}

					if(caseValue(BLCarreauTowerLeft).name != '0')
				{
					if((caseValue(BLCarreauTowerLeft).name != 'k')&&(caseValue(BLCarreauTowerLeft).color == 'w'))
					{
						caseRouge(BLCarreauTowerLeft);//Sinon on affiche en rouge la case
					}
				}

				while((BLCarreauTowerRight.x<105)&&(caseValue(BLCarreauTowerRight).name == '0'))
				{
				
				caseVerte(BLCarreauTowerRight); // affiche la case en verte
				BLCarreauTowerRight.x+=1;
				}

					if(caseValue(BLCarreauTowerRight).name != '0')
				{
					if((caseValue(BLCarreauTowerRight).name != 'k')&&(caseValue(BLCarreauTowerRight).color == 'w'))
					{
						caseRouge(BLCarreauTowerRight);//Sinon on affiche en rouge la case
					}
				}

				while((BLCarreauTowerDown.y>1)&&(caseValue(BLCarreauTowerDown).name == '0'))
				{
				
				caseVerte(BLCarreauTowerDown); // affiche la case en verte
				BLCarreauTowerDown.y-=1;
				}
					//Si la case n'est
					if(caseValue(BLCarreauTowerDown).name != '0')
				{
					if((caseValue(BLCarreauTowerDown).name != 'k')&&(caseValue(BLCarreauTowerDown).color == 'w'))
					{
						caseRouge(BLCarreauTowerDown); 
					}
				}
		}
	}	
	
	
//On verifie qu'on clique dans la grille
	if((ChoosenCase.x>=97)&&(ChoosenCase.x<=104)&&(ChoosenCase.y>=1)&&(ChoosenCase.y<=8))
	{
		//Déplacement white tower
		if(!EtatJoueur)
		{
	//----Va vérifier si il n'y a pas de pieces entre la case et la tour
					if((ChoosenCase.y<WhiteTower[pieceTower].y)&&(ChoosenCase.y>=WhCarreauTowerDown.y))
					{
							VerifieCoup=1;
					}	

					if((ChoosenCase.y>WhiteTower[pieceTower].y)&&(ChoosenCase.y<=WhCarreauTowerUp.y))
					{
						
							VerifieCoup=1;
					}	

					if((ChoosenCase.x<WhiteTower[pieceTower].x)&&(ChoosenCase.x>=WhCarreauTowerLeft.x))
					{
							VerifieCoup=1;
					}	

					if((ChoosenCase.x>WhiteTower[pieceTower].x)&&(ChoosenCase.x<=WhCarreauTowerRight.x))
					{	
							VerifieCoup=1;
					}	


	//---------------------------------------
			
				if((ChoosenCase.y==WhiteTower[pieceTower].y)^(ChoosenCase.x==WhiteTower[pieceTower].x))  //Ou exclusif (Soit x soit y)
				{
				
					
					//On autorise à manger une piece noire sauf le roi
					if(caseValue(ChoosenCase).color=='b' && caseValue(ChoosenCase).name!='k' && VerifieCoup==1)
					{
						
						killPiece(ChoosenCase);
						EtatJoueur=PlaceTower(ChoosenCase, EtatJoueur);
					}

					//On autorise un déplacement sur une case vide
					if(caseValue(ChoosenCase).index==32 && VerifieCoup==1)
					{
						EtatJoueur=PlaceTower(ChoosenCase, EtatJoueur);
					}


				}
			
			
		
		}
//----------------------------------------
	//Déplacement black pawns
		if(EtatJoueur)
		{
					if((ChoosenCase.y==BlackTower[pieceTower].y)^(ChoosenCase.x==BlackTower[pieceTower].x))  //Ou exclusif (Soit x soit y)
				{

//----Va vérifier si il n'y a pas de pieces entre la case et la tour
					if((ChoosenCase.y<BlackTower[pieceTower].y)&&(ChoosenCase.y>=BLCarreauTowerDown.y))
					{
							VerifieCoup=1;
					}	

					if((ChoosenCase.y>BlackTower[pieceTower].y)&&(ChoosenCase.y<=BLCarreauTowerUp.y))
					{
						
							VerifieCoup=1;
					}	

					if((ChoosenCase.x<BlackTower[pieceTower].x)&&(ChoosenCase.x>=BLCarreauTowerLeft.x))
					{
							VerifieCoup=1;
					}	

					if((ChoosenCase.x>BlackTower[pieceTower].x)&&(ChoosenCase.x<=BLCarreauTowerRight.x))
					{	
							VerifieCoup=1;
					}	


//------------------------------------------
					//On autorise à manger une piece noire sauf le roi
					if(caseValue(ChoosenCase).color=='w' && caseValue(ChoosenCase).name!='k' && VerifieCoup==1)
					{
				
						killPiece(ChoosenCase);
						EtatJoueur=PlaceTower(ChoosenCase, EtatJoueur);
					}

					//On autorise un déplacement sur une case vide
					if(caseValue(ChoosenCase).index==32 && VerifieCoup==1)
					{
						EtatJoueur=PlaceTower(ChoosenCase, EtatJoueur);
					}


				}
		}		
	}
	
return EtatJoueur; //Return de Etat joueur changé pour mettre à jour les timers
}





//Place la tour selectionnée à la case choisie
bool PlaceTower(ChessGrid ChoosenCase, int EtatJoueur)
{

	//Si déplacement tour blanche
	if(!EtatJoueur)
	{
		WhiteTower[pieceTower].x=ChoosenCase.x; //On déplace en X
		WhiteTower[pieceTower].y=ChoosenCase.y; //On déplace en Y
		
	}
	//--------------------------

	//Si déplacement tour noire
	if(EtatJoueur)
	{
		BlackTower[pieceTower].x=ChoosenCase.x; //On deplace en X
		BlackTower[pieceTower].y=ChoosenCase.y; //On déplace en Y
		
	}

	VerifieCoup=0; //Reinitialise le coup
	pieceTower=32; //On déselectionne la piece choisie
	clicTower=0; //On donc empeche l'affichage de coup disponible
	
EtatJoueur=!EtatJoueur; //C'est au tour de l'autre joueur

return EtatJoueur; 
}
//-------------- KNIGHTS-----------------------------

void CheckKnights(ChessGrid pos, bool EtatJoueur)
{

	//Si c'est aux blancs
	if(!EtatJoueur)
	{
		for(int i=0; i<2 ; i++)
		{	
			if((pos.x==WhiteKnight[i].x)&&(pos.y==WhiteKnight[i].y)) //Si on clique sur la position de la tour
			{
				pieceKnight=i; 
				clicKnight+=1;
			}
		}
		
	}
//------------------------
	//Si c'est aux noirs
	if(EtatJoueur)
	{
		for(int i=0; i<2 ; i++)
		{	
			if((pos.x==BlackKnight[i].x)&&(pos.y==BlackKnight[i].y)) //Si on clique sur la position de la tour
			{
				pieceKnight=i;
				clicKnight+=1; 
			}
		}
		
	}

	//Si on reclique
	if(clicKnight==2)
	{
		pieceKnight=32; //On désaffiche les coups possible
		clicKnight=0; //Si on reclique on reset
	}
}

//Fonction affichage et déplacement des Knight
bool Knight(bool EtatJoueur)
{
	ChessGrid WhCarreauKnight = WhiteKnight[pieceKnight];
	ChessGrid BLCarreauKnight = BlackKnight[pieceKnight]; 
	//-------------------------------------
	
	//Toutes les directions de déplacement Knights wh

	//En avant
	ChessGrid WhCarreauKnightUpA = WhCarreauKnight;
	WhCarreauKnightUpA.y+=1;
	WhCarreauKnightUpA.x-=2;
	ChessGrid WhCarreauKnightUpB = WhCarreauKnight;
	WhCarreauKnightUpB.y+=2;
	WhCarreauKnightUpB.x-=1;
	ChessGrid WhCarreauKnightUpC = WhCarreauKnight;
	WhCarreauKnightUpC.y+=2;
	WhCarreauKnightUpC.x+=1;
	ChessGrid WhCarreauKnightUpD = WhCarreauKnight;
	WhCarreauKnightUpD.y+=1;
	WhCarreauKnightUpD.x+=2;
	//En arriere
	ChessGrid WhCarreauKnightDownA = WhCarreauKnight;
	WhCarreauKnightDownA.y-=1;
	WhCarreauKnightDownA.x-=2;
	ChessGrid WhCarreauKnightDownB = WhCarreauKnight;
	WhCarreauKnightDownB.y-=2;
	WhCarreauKnightDownB.x-=1;
	ChessGrid WhCarreauKnightDownC = WhCarreauKnight;
	WhCarreauKnightDownC.y-=2;
	WhCarreauKnightDownC.x+=1;
	ChessGrid WhCarreauKnightDownD = WhCarreauKnight;
	WhCarreauKnightDownD.y-=1;
	WhCarreauKnightDownD.x+=2;

	//Toutes les directions de déplacement Knights bl
	//En avant
	ChessGrid BLCarreauKnightUpA = BLCarreauKnight;
	BLCarreauKnightUpA.y+=1;
	BLCarreauKnightUpA.x-=2;
	ChessGrid BLCarreauKnightUpB = BLCarreauKnight;
	BLCarreauKnightUpB.y+=2;
	BLCarreauKnightUpB.x-=1;
	ChessGrid BLCarreauKnightUpC = BLCarreauKnight;
	BLCarreauKnightUpC.y+=2;
	BLCarreauKnightUpC.x+=1;
	ChessGrid BLCarreauKnightUpD = BLCarreauKnight;
	BLCarreauKnightUpD.y+=1;
	BLCarreauKnightUpD.x+=2;
	//En arriere
	ChessGrid BLCarreauKnightDownA = BLCarreauKnight;
	BLCarreauKnightDownA.y-=1;
	BLCarreauKnightDownA.x-=2;
	ChessGrid BLCarreauKnightDownB = BLCarreauKnight;
	BLCarreauKnightDownB.y-=2;
	BLCarreauKnightDownB.x-=1;
	ChessGrid BLCarreauKnightDownC = BLCarreauKnight;
	BLCarreauKnightDownC.y-=2;
	BLCarreauKnightDownC.x+=1;
	ChessGrid BLCarreauKnightDownD = BLCarreauKnight;
	BLCarreauKnightDownD.y-=1;
	BLCarreauKnightDownD.x+=2;
	
	

	
	//-------------------------------------

	ChessGrid ChoosenCase = clicCase();
	
	//Affichage disponibilité déplacement white Knight

	
	if(!EtatJoueur)
	{
		if((pieceKnight != 32)&&(clicKnight==1)) // On vérifie qu'il n'y a pas de pièce au dessus
		{	
			
	//Cas UP.A		
				if(((WhCarreauKnightUpA.y<9)&&(WhCarreauKnightUpA.x>96))&&(caseValue(WhCarreauKnightUpA).name == '0'))
				{
				caseVerte(WhCarreauKnightUpA); // affiche les case en verte
				}

				if(caseValue(WhCarreauKnightUpA).name != '0')
				{
					
					if((caseValue(WhCarreauKnightUpA).name != 'k')&&(caseValue(WhCarreauKnightUpA).color == 'b'))
					{
						caseRouge(WhCarreauKnightUpA);//Sinon on affiche en rouge la case
					}
				}
	//Cas UP.B
				if(((WhCarreauKnightUpB.y<9)&&(WhCarreauKnightUpB.x>96))&&(caseValue(WhCarreauKnightUpB).name == '0'))
				{
				caseVerte(WhCarreauKnightUpB); // affiche les case en verte
				}

				if(caseValue(WhCarreauKnightUpB).name != '0')
				{
					
					if((caseValue(WhCarreauKnightUpB).name != 'k')&&(caseValue(WhCarreauKnightUpB).color == 'b'))
					{
						caseRouge(WhCarreauKnightUpB);//Sinon on affiche en rouge la case
					}
				}
	//Cas UP.C
				if(((WhCarreauKnightUpC.y<9)&&(WhCarreauKnightUpC.x<105))&&(caseValue(WhCarreauKnightUpC).name == '0'))
				{
				caseVerte(WhCarreauKnightUpC); // affiche les case en verte
				}

				if(caseValue(WhCarreauKnightUpC).name != '0')
				{
					
					if((caseValue(WhCarreauKnightUpC).name != 'k')&&(caseValue(WhCarreauKnightUpC).color == 'b'))
					{
						caseRouge(WhCarreauKnightUpC);//Sinon on affiche en rouge la case
					}
				}
	//Cas UP.D
				if(((WhCarreauKnightUpD.y<9)&&(WhCarreauKnightUpD.x<105))&&(caseValue(WhCarreauKnightUpD).name == '0'))
				{
				caseVerte(WhCarreauKnightUpD); // affiche les case en verte
				}

				if(caseValue(WhCarreauKnightUpD).name != '0')
				{
					
					if((caseValue(WhCarreauKnightUpD).name != 'k')&&(caseValue(WhCarreauKnightUpD).color == 'b'))
					{
						caseRouge(WhCarreauKnightUpD);//Sinon on affiche en rouge la case
					}
				}
	//Cas DOWN.A
				if(((WhCarreauKnightDownA.y>0)&&(WhCarreauKnightDownA.x>96))&&(caseValue(WhCarreauKnightDownA).name == '0'))
				{
				caseVerte(WhCarreauKnightDownA); // affiche les case en verte
				}

				if(caseValue(WhCarreauKnightDownA).name != '0')
				{
					
					if((caseValue(WhCarreauKnightDownA).name != 'k')&&(caseValue(WhCarreauKnightDownA).color == 'b'))
					{
						caseRouge(WhCarreauKnightDownA);//Sinon on affiche en rouge la case
					}
				}
	//Cas DOWN.B
				if(((WhCarreauKnightDownB.y>0)&&(WhCarreauKnightDownB.x>96))&&(caseValue(WhCarreauKnightDownB).name == '0'))
				{
				caseVerte(WhCarreauKnightDownB); // affiche les case en verte
				}

				if(caseValue(WhCarreauKnightDownB).name != '0')
				{
					
					if((caseValue(WhCarreauKnightDownB).name != 'k')&&(caseValue(WhCarreauKnightDownB).color == 'b'))
					{
						caseRouge(WhCarreauKnightDownB);//Sinon on affiche en rouge la case
					}
				}
	//Cas DOWN.C
				if(((WhCarreauKnightDownC.y>0)&&(WhCarreauKnightDownC.x<105))&&(caseValue(WhCarreauKnightDownC).name == '0'))
				{
				caseVerte(WhCarreauKnightDownC); // affiche les case en verte
				}

				if(caseValue(WhCarreauKnightDownC).name != '0')
				{
					
					if((caseValue(WhCarreauKnightDownC).name != 'k')&&(caseValue(WhCarreauKnightDownC).color == 'b'))
					{
						caseRouge(WhCarreauKnightDownC);//Sinon on affiche en rouge la case
					}
				}
	//Cas DOWN.D
				if(((WhCarreauKnightDownD.y>0)&&(WhCarreauKnightDownD.x<105))&&(caseValue(WhCarreauKnightDownD).name == '0'))
				{
				caseVerte(WhCarreauKnightDownD); // affiche les case en verte
				}

				if(caseValue(WhCarreauKnightDownD).name != '0')
				{
					
					if((caseValue(WhCarreauKnightDownD).name != 'k')&&(caseValue(WhCarreauKnightDownD).color == 'b'))
					{
						caseRouge(WhCarreauKnightDownD);//Sinon on affiche en rouge la case
					}
				}



		}
		
	}
//-------------------------------------------------
	//Affichage disponibilité déplacement black Knight
	if(EtatJoueur)
	{
		if((pieceKnight != 32)&&(clicKnight==1)) // On vérifie qu'il n'y a pas de pièce au dessus
		{	
		
			//Cas UP.A		
				if(((BLCarreauKnightUpA.y<9)&&(BLCarreauKnightUpA.x>96))&&(caseValue(BLCarreauKnightUpA).name == '0'))
				{
				caseVerte(BLCarreauKnightUpA); // affiche les case en verte
				}

				if(caseValue(BLCarreauKnightUpA).name != '0')
				{
					
					if((caseValue(BLCarreauKnightUpA).name != 'k')&&(caseValue(BLCarreauKnightUpA).color == 'w'))
					{
						caseRouge(BLCarreauKnightUpA);//Sinon on affiche en rouge la case
					}
				}
	//Cas UP.B
				if(((BLCarreauKnightUpB.y<9)&&(BLCarreauKnightUpB.x>96))&&(caseValue(BLCarreauKnightUpB).name == '0'))
				{
				caseVerte(BLCarreauKnightUpB); // affiche les case en verte
				}

				if(caseValue(BLCarreauKnightUpB).name != '0')
				{
					
					if((caseValue(BLCarreauKnightUpB).name != 'k')&&(caseValue(BLCarreauKnightUpB).color == 'w'))
					{
						caseRouge(BLCarreauKnightUpB);//Sinon on affiche en rouge la case
					}
				}
	//Cas UP.C
				if(((BLCarreauKnightUpC.y<9)&&(BLCarreauKnightUpC.x<105))&&(caseValue(BLCarreauKnightUpC).name == '0'))
				{
				caseVerte(BLCarreauKnightUpC); // affiche les case en verte
				}

				if(caseValue(BLCarreauKnightUpC).name != '0')
				{
					
					if((caseValue(BLCarreauKnightUpC).name != 'k')&&(caseValue(BLCarreauKnightUpC).color == 'w'))
					{
						caseRouge(BLCarreauKnightUpC);//Sinon on affiche en rouge la case
					}
				}
	//Cas UP.D
				if(((BLCarreauKnightUpD.y<9)&&(BLCarreauKnightUpD.x<105))&&(caseValue(BLCarreauKnightUpD).name == '0'))
				{
				caseVerte(BLCarreauKnightUpD); // affiche les case en verte
				}

				if(caseValue(BLCarreauKnightUpD).name != '0')
				{
					
					if((caseValue(BLCarreauKnightUpD).name != 'k')&&(caseValue(BLCarreauKnightUpD).color == 'w'))
					{
						caseRouge(BLCarreauKnightUpD);//Sinon on affiche en rouge la case
					}
				}
	//Cas DOWN.A
				if(((BLCarreauKnightDownA.y>0)&&(BLCarreauKnightDownA.x>96))&&(caseValue(BLCarreauKnightDownA).name == '0'))
				{
				caseVerte(BLCarreauKnightDownA); // affiche les case en verte
				}

				if(caseValue(BLCarreauKnightDownA).name != '0')
				{
					
					if((caseValue(BLCarreauKnightDownA).name != 'k')&&(caseValue(BLCarreauKnightDownA).color == 'w'))
					{
						caseRouge(BLCarreauKnightDownA);//Sinon on affiche en rouge la case
					}
				}
	//Cas DOWN.B
				if(((BLCarreauKnightDownB.y>0)&&(BLCarreauKnightDownB.x>96))&&(caseValue(BLCarreauKnightDownB).name == '0'))
				{
				caseVerte(BLCarreauKnightDownB); // affiche les case en verte
				}

				if(caseValue(BLCarreauKnightDownB).name != '0')
				{
					
					if((caseValue(BLCarreauKnightDownB).name != 'k')&&(caseValue(BLCarreauKnightDownB).color == 'w'))
					{
						caseRouge(BLCarreauKnightDownB);//Sinon on affiche en rouge la case
					}
				}
	//Cas DOWN.C
				if(((BLCarreauKnightDownC.y>0)&&(BLCarreauKnightDownC.x<105))&&(caseValue(BLCarreauKnightDownC).name == '0'))
				{
				caseVerte(BLCarreauKnightDownC); // affiche les case en verte
				}

				if(caseValue(BLCarreauKnightDownC).name != '0')
				{
					
					if((caseValue(BLCarreauKnightDownC).name != 'k')&&(caseValue(BLCarreauKnightDownC).color == 'w'))
					{
						caseRouge(BLCarreauKnightDownC);//Sinon on affiche en rouge la case
					}
				}
	//Cas DOWN.D
				if(((BLCarreauKnightDownD.y>0)&&(BLCarreauKnightDownD.x>105))&&(caseValue(BLCarreauKnightDownD).name == '0'))
				{
				caseVerte(BLCarreauKnightDownD); // affiche les case en verte
				}

				if(caseValue(BLCarreauKnightDownD).name != '0')
				{
					
					if((caseValue(BLCarreauKnightDownD).name != 'k')&&(caseValue(BLCarreauKnightDownD).color == 'w'))
					{
						caseRouge(WhCarreauKnightDownD);//Sinon on affiche en rouge la case
					}
				}
			
		}
	}	
	
	
//On verifie qu'on clique dans la grille
	if((ChoosenCase.x>=97)&&(ChoosenCase.x<=104)&&(ChoosenCase.y>=1)&&(ChoosenCase.y<=8))
	{
		//Déplacement white Knight
		if(!EtatJoueur)
		{		
			//On va verifier si l'utilisateur peut se déplacer où il veut aller
		//En UP.A
				if((ChoosenCase.y==WhCarreauKnightUpA.y)&&(ChoosenCase.x==WhCarreauKnightUpA.x))  //Ou exclusif (Soit x soit y)
				{
					VerifieCoup=1;
	
				}
		//En UP.B
				if((ChoosenCase.y==WhCarreauKnightUpB.y)&&(ChoosenCase.x==WhCarreauKnightUpB.x))  //Ou exclusif (Soit x soit y)
				{
					VerifieCoup=1;
			
				}
		//En UP.C
				if((ChoosenCase.y==WhCarreauKnightUpC.y)&&(ChoosenCase.x==WhCarreauKnightUpC.x))  //Ou exclusif (Soit x soit y)
				{
					VerifieCoup=1;
					
				}
		//En UP.D
				if((ChoosenCase.y==WhCarreauKnightUpD.y)&&(ChoosenCase.x==WhCarreauKnightUpD.x))  //Ou exclusif (Soit x soit y)
				{
					VerifieCoup=1;
				}
		//En DOWN.A
				if((ChoosenCase.y==WhCarreauKnightDownA.y)&&(ChoosenCase.x==WhCarreauKnightDownA.x))  //Ou exclusif (Soit x soit y)
				{
					VerifieCoup=1;

				}
		//En DOWN.B
				if((ChoosenCase.y==WhCarreauKnightDownB.y)&&(ChoosenCase.x==WhCarreauKnightDownB.x))  //Ou exclusif (Soit x soit y)
				{
					VerifieCoup=1;
	
				}
		//En DOWN.C
				if((ChoosenCase.y==WhCarreauKnightDownC.y)&&(ChoosenCase.x==WhCarreauKnightDownC.x))  //Ou exclusif (Soit x soit y)
				{
					VerifieCoup=1;

				}
		//En DOWN.D
				if((ChoosenCase.y==WhCarreauKnightDownD.y)&&(ChoosenCase.x==WhCarreauKnightDownD.x))  //Ou exclusif (Soit x soit y)
				{
					VerifieCoup=1;
				}
		//----------------------------------------------------------
					//On autorise à manger une piece noire sauf le roi
					if(caseValue(ChoosenCase).color=='b' && caseValue(ChoosenCase).name!='k'&& (VerifieCoup==1))
					{
						killPiece(ChoosenCase);
						EtatJoueur=PlaceKnight(ChoosenCase, EtatJoueur);
					}

					
					//On autorise un déplacement sur une case vide
					if(caseValue(ChoosenCase).index==32 && VerifieCoup==1)
					{
						
						EtatJoueur=PlaceKnight(ChoosenCase, EtatJoueur);
					}


				}
		}
	
//----------------------------------------
	//Déplacement black pawns
		if(EtatJoueur)
		{

			//On va verifier si l'utilisateur peut se déplacer où il veut aller
		//En UP.A
				if((ChoosenCase.y==BLCarreauKnightUpA.y)&&(ChoosenCase.x==BLCarreauKnightUpA.x))  //Ou exclusif (Soit x soit y)
				{
					VerifieCoup=1;
	
				}
		//En UP.B
				if((ChoosenCase.y==BLCarreauKnightUpB.y)&&(ChoosenCase.x==BLCarreauKnightUpB.x))  //Ou exclusif (Soit x soit y)
				{
					VerifieCoup=1;
			
				}
		//En UP.C
				if((ChoosenCase.y==BLCarreauKnightUpC.y)&&(ChoosenCase.x==BLCarreauKnightUpC.x))  //Ou exclusif (Soit x soit y)
				{
					VerifieCoup=1;
					printf("BBB\n");
				}
		//En UP.D
				if((ChoosenCase.y==BLCarreauKnightUpD.y)&&(ChoosenCase.x==BLCarreauKnightUpD.x))  //Ou exclusif (Soit x soit y)
				{
					VerifieCoup=1;
				}
		//En DOWN.A
				if((ChoosenCase.y==BLCarreauKnightDownA.y)&&(ChoosenCase.x==BLCarreauKnightDownA.x))  //Ou exclusif (Soit x soit y)
				{
					VerifieCoup=1;

				}
		//En DOWN.B
				if((ChoosenCase.y==BLCarreauKnightDownB.y)&&(ChoosenCase.x==BLCarreauKnightDownB.x))  //Ou exclusif (Soit x soit y)
				{
					VerifieCoup=1;
	
				}
		//En DOWN.C
				if((ChoosenCase.y==BLCarreauKnightDownC.y)&&(ChoosenCase.x==BLCarreauKnightDownC.x))  //Ou exclusif (Soit x soit y)
				{
					VerifieCoup=1;

				}
		//En DOWN.D
				if((ChoosenCase.y==BLCarreauKnightDownD.y)&&(ChoosenCase.x==BLCarreauKnightDownD.x))  //Ou exclusif (Soit x soit y)
				{
					VerifieCoup=1;
				}
		//----------------------------------------------------------
					//On autorise à manger une piece noire sauf le roi
					if(caseValue(ChoosenCase).color=='w' && caseValue(ChoosenCase).name!='k'&& (VerifieCoup==1))
					{
						killPiece(ChoosenCase);
						EtatJoueur=PlaceKnight(ChoosenCase, EtatJoueur);
					}

					
					//On autorise un déplacement sur une case vide
					if(caseValue(ChoosenCase).index==32 && VerifieCoup==1)
					{
						
						EtatJoueur=PlaceKnight(ChoosenCase, EtatJoueur);
					}


				
				
	
		}
	
return EtatJoueur; //Return de Etat joueur changé pour mettre à jour les timers
}





//Place le cavalier selectionnée à la case choisie
bool PlaceKnight(ChessGrid ChoosenCase, int EtatJoueur)
{

	//Si déplacement cavalier blanche
	if(!EtatJoueur)
	{
		WhiteKnight[pieceKnight].x=ChoosenCase.x; //On déplace en X
		WhiteKnight[pieceKnight].y=ChoosenCase.y; //On déplace en Y
		
	}
	//--------------------------

	//Si déplacement tour noire
	if(EtatJoueur)
	{
		BlackKnight[pieceKnight].x=ChoosenCase.x; //On deplace en X
		BlackKnight[pieceKnight].y=ChoosenCase.y; //On déplace en Y
		
	}

	VerifieCoup=0; //Reinitialise le coup
	pieceKnight=32; //On déselectionne la piece choisie
	clicKnight=0; //On donc empeche l'affichage de coup disponible
	
EtatJoueur=!EtatJoueur; //C'est au tour de l'autre joueur

return EtatJoueur; 
}



//------------------------------ BISHOPS--------------------------





//On vérifie si on clique sur un fou
void CheckBishop(ChessGrid pos, bool EtatJoueur)
{



	//Si c'est aux blancs
	if(!EtatJoueur)
	{
		for(int i=0; i<2 ; i++)
		{	
			if((pos.x==WhiteBishop[i].x)&&(pos.y==WhiteBishop[i].y)) //Si on clique sur la position du fou
			{
				pieceBishop=i; 
				clicPawn=0;
				clicBishop+=1;
				
			}
		}
		
	}
//------------------------
	//Si c'est aux noirs
	if(EtatJoueur)
	{
		for(int i=0; i<2 ; i++)
		{	
			if((pos.x==BlackBishop[i].x)&&(pos.y==BlackBishop[i].y)) //Si on clique sur la position du fou
			{
				pieceBishop=i;
				clicBishop+=1; 
			}
		}
		
	}

	//Si on reclique
	if(clicBishop==2)
	{
		pieceBishop=32; //On désaffiche les coups possible
		clicBishop=0; //Si on reclique on reset
	}
}


bool Bishop(bool EtatJoueur)
{
	ChessGrid WhCarreauBishop = WhiteBishop[pieceBishop];
	ChessGrid BLCarreauBishop = BlackBishop[pieceBishop]; 
	//-------------------------------------
	
	//Toutes les directions Bishops wh
	ChessGrid WhCarreauBishopRightUp = WhCarreauBishop;
	WhCarreauBishopRightUp.y+=1;
	WhCarreauBishopRightUp.x+=1;
	ChessGrid WhCarreauBishopLeftUp = WhCarreauBishop;
	WhCarreauBishopLeftUp.y+=1;
	WhCarreauBishopLeftUp.x-=1;
	ChessGrid WhCarreauBishopRightDown = WhCarreauBishop;
	WhCarreauBishopRightDown.y-=1;
	WhCarreauBishopRightDown.x+=1;
	ChessGrid WhCarreauBishopLeftDown = WhCarreauBishop;
	WhCarreauBishopLeftDown.y-=1;
	WhCarreauBishopLeftDown.x-=1;
	

	//Toutes les directions Bishops bl
	ChessGrid BLCarreauBishopRightUp = BLCarreauBishop;
	BLCarreauBishopRightUp.y+=1;
	BLCarreauBishopRightUp.x+=1;
	ChessGrid BLCarreauBishopLeftUp = BLCarreauBishop;
	BLCarreauBishopLeftUp.y+=1;
	BLCarreauBishopLeftUp.x-=1;
	ChessGrid BLCarreauBishopRightDown = BLCarreauBishop;
	BLCarreauBishopRightDown.y-=1;
	BLCarreauBishopRightDown.x+=1;
	ChessGrid BLCarreauBishopLeftDown = BLCarreauBishop;
	BLCarreauBishopLeftDown.y-=1;
	BLCarreauBishopLeftDown.x-=1;
	
	

	
	//-------------------------------------

	ChessGrid ChoosenCase = clicCase();

	//Affichage disponibilité déplacement white Bishop

	if(!EtatJoueur)
	{	
			if((pieceBishop != 32)&&(clicBishop==1)) // On vérifie qu'il n'y a pas de pièce au dessus
			{	
				
					
					while((WhCarreauBishopRightUp.y<9)&&(caseValue(WhCarreauBishopRightUp).name == '0')&&(WhCarreauBishopRightUp.x<105))
					{
					
					caseVerte(WhCarreauBishopRightUp); // affiche les case en verte
					WhCarreauBishopRightUp.y+=1;
					WhCarreauBishopRightUp.x+=1;
					}

					if(caseValue(WhCarreauBishopRightUp).name != '0')
					{
						
						if((caseValue(WhCarreauBishopRightUp).name != 'k')&&(caseValue(WhCarreauBishopRightUp).color == 'b'))
						{
							caseRouge(WhCarreauBishopRightUp);//Sinon on affiche en rouge la case
						}
					}

					while((WhCarreauBishopLeftUp.x>96)&&(caseValue(WhCarreauBishopLeftUp).name == '0')&&(WhCarreauBishopLeftUp.y<9))
					{
					caseVerte(WhCarreauBishopLeftUp); // affiche les case en verte
					WhCarreauBishopLeftUp.y+=1;
					WhCarreauBishopLeftUp.x-=1;
					
					}

					if(caseValue(WhCarreauBishopLeftUp).name != '0')
					{
						if((caseValue(WhCarreauBishopLeftUp).name != 'k')&&(caseValue(WhCarreauBishopLeftUp).color == 'b')) //ON affiche pas lorsqu'un roi est mis en echec
						{
							caseRouge(WhCarreauBishopLeftUp); //Sinon on affiche en rouge la case
						}
					}

					while((WhCarreauBishopRightDown.x<105)&&(caseValue(WhCarreauBishopRightDown).name == '0')&&(WhCarreauBishopRightDown.y>0))
					{
					caseVerte(WhCarreauBishopRightDown); // affiche les case en verte
					WhCarreauBishopRightDown.y-=1;
					WhCarreauBishopRightDown.x+=1;
					}

					if(caseValue(WhCarreauBishopRightDown).name != '0')
					{
						if((caseValue(WhCarreauBishopRightDown).name != 'k')&&(caseValue(WhCarreauBishopRightDown).color == 'b')) //ON affiche pas lorsqu'un roi est mis en echec
						{
							caseRouge(WhCarreauBishopRightDown); //Sinon on affiche en rouge la case
						}
					}

					while((WhCarreauBishopLeftDown.y>0)&&(caseValue(WhCarreauBishopLeftDown).name == '0')&&(WhCarreauBishopLeftDown.x>96))
					{
					caseVerte(WhCarreauBishopLeftDown); // affiche les case en verte
					WhCarreauBishopLeftDown.y-=1;
					WhCarreauBishopLeftDown.x-=1;
					}

					if(caseValue(WhCarreauBishopLeftDown).name != '0')
					{
						if((caseValue(WhCarreauBishopLeftDown).name != 'k')&&(caseValue(WhCarreauBishopLeftDown).color == 'b')) //ON affiche pas lorsqu'un roi est mis en echec
						{
							caseRouge(WhCarreauBishopLeftDown); //Sinon on affiche en rouge la case
						}
					}
			}	
	}
//-------------------------------------------------
	//Affichage disponibilité déplacement black Bishop
	if(EtatJoueur)
	{
		if((pieceBishop != 32)&&(clicBishop==1)) // On vérifie qu'il n'y a pas de pièce au dessus
		{	
			while((BLCarreauBishopRightUp.y<9)&&(caseValue(BLCarreauBishopRightUp).name == '0')&&(BLCarreauBishopRightUp.x<105))
					{
					
					caseVerte(BLCarreauBishopRightUp); // affiche les case en verte
					BLCarreauBishopRightUp.y+=1;
					BLCarreauBishopRightUp.x+=1;
					}

					if(caseValue(BLCarreauBishopRightUp).name != '0')
					{
						
						if((caseValue(BLCarreauBishopRightUp).name != 'k')&&(caseValue(BLCarreauBishopRightUp).color == 'w'))
						{
							caseRouge(BLCarreauBishopRightUp);//Sinon on affiche en rouge la case
						}
					}

			while((BLCarreauBishopLeftUp.x>96)&&(caseValue(BLCarreauBishopLeftUp).name == '0')&&(BLCarreauBishopLeftUp.y<9))
					{
					caseVerte(BLCarreauBishopLeftUp); // affiche les case en verte
					BLCarreauBishopLeftUp.y+=1;
					BLCarreauBishopLeftUp.x-=1;
					
					}

					if(caseValue(BLCarreauBishopLeftUp).name != '0')
					{
						if((caseValue(BLCarreauBishopLeftUp).name != 'k')&&(caseValue(BLCarreauBishopLeftUp).color == 'w')) //ON affiche pas lorsqu'un roi est mis en echec
						{
							caseRouge(BLCarreauBishopLeftUp); //Sinon on affiche en rouge la case
						}
					}

					while((BLCarreauBishopRightDown.x<105)&&(caseValue(BLCarreauBishopRightDown).name == '0')&&(BLCarreauBishopRightDown.y>0))
					{
					caseVerte(BLCarreauBishopRightDown); // affiche les case en verte
					BLCarreauBishopRightDown.y-=1;
					BLCarreauBishopRightDown.x+=1;
					}

					if(caseValue(BLCarreauBishopRightDown).name != '0')
					{
						if((caseValue(BLCarreauBishopRightDown).name != 'k')&&(caseValue(BLCarreauBishopRightDown).color == 'w')) //ON affiche pas lorsqu'un roi est mis en echec
						{
							caseRouge(BLCarreauBishopRightDown); //Sinon on affiche en rouge la case
						}
					}

					while((BLCarreauBishopLeftDown.y>0)&&(caseValue(BLCarreauBishopLeftDown).name == '0')&&(BLCarreauBishopLeftDown.x>96))
					{
					caseVerte(BLCarreauBishopLeftDown); // affiche les case en verte
					BLCarreauBishopLeftDown.y-=1;
					BLCarreauBishopLeftDown.x-=1;
					}

					if(caseValue(BLCarreauBishopLeftDown).name != '0')
					{
						if((caseValue(BLCarreauBishopLeftDown).name != 'k')&&(caseValue(BLCarreauBishopLeftDown).color == 'w')) //ON affiche pas lorsqu'un roi est mis en echec
						{
							caseRouge(BLCarreauBishopLeftDown); //Si non on affiche en rouge la case
						}
					}

			
				
		}
	}	
	
	
//On verifie qu'on clique dans la grille
	if((ChoosenCase.x>=97)&&(ChoosenCase.x<=104)&&(ChoosenCase.y>=1)&&(ChoosenCase.y<=8)&&(clicBishop==1))
	{
		
		//Déplacement white bishop
		if(!EtatJoueur)
		{
			
	//----Va vérifier si il n'y a pas de pieces entre la case et le fou dans chaque direction

					//Valeur absolue de la différence car on se déplace en diagonale
					if((abs(ChoosenCase.x-WhiteBishop[pieceBishop].x) == abs(ChoosenCase.y-WhiteBishop[pieceBishop].y))) 
			{
				//On vérifie dans les 4 diagonales, en fct du clic
		//Diagonale Bas/gauche
				if((ChoosenCase.y<WhiteBishop[pieceBishop].y)&&(ChoosenCase.x<WhiteBishop[pieceBishop].x)&&((ChoosenCase.y>=WhCarreauBishopLeftDown.y)&&(ChoosenCase.x>=WhCarreauBishopLeftDown.x)))
				{
					
						VerifieCoup=1;	
				}	
		//Diagonale Bas/droite
				if((ChoosenCase.y<WhiteBishop[pieceBishop].y)&&(ChoosenCase.x>WhiteBishop[pieceBishop].x)&&((ChoosenCase.y>=WhCarreauBishopRightDown.y)&&(ChoosenCase.x<=WhCarreauBishopRightDown.x)))
				{
					
						VerifieCoup=1;
				}	
		//Diagonale Haut/gauche
				if((ChoosenCase.y>WhiteBishop[pieceBishop].y)&&(ChoosenCase.x<WhiteBishop[pieceBishop].x)&&((ChoosenCase.y<=WhCarreauBishopLeftUp.y)&&(ChoosenCase.x>=WhCarreauBishopLeftUp.x)))
				{
					
						VerifieCoup=1;
				}	
		//Diagonale Haut/droite
				if((ChoosenCase.y>WhiteBishop[pieceBishop].y)&&(ChoosenCase.x>WhiteBishop[pieceBishop].x)&&((ChoosenCase.y<=WhCarreauBishopRightUp.y)&&(ChoosenCase.x<=WhCarreauBishopRightUp.x)))
				{	
					
						VerifieCoup=1;		
				}

			}

	//---------------------------------------
			
							if(VerifieCoup==1) //On regarde si on veut aller en diagonale en verifiant la valeur absolue des différences
							{
								//On tue une pièce noire
								if(caseValue(ChoosenCase).color=='b' && caseValue(ChoosenCase).name!='k')
								{
									
									killPiece(ChoosenCase);
									EtatJoueur=PlaceBishop(ChoosenCase, EtatJoueur);
								}

								//On autorise un déplacement sur une case vide
								if(caseValue(ChoosenCase).index==32)
								{
									EtatJoueur=PlaceBishop(ChoosenCase, EtatJoueur);
								}
							} 
							
		
		}
	}
	
//----------------------------------------
	//Déplacement black bishop
		if(EtatJoueur)
		{
	
	//----Va vérifier si il n'y a pas de pieces entre la case et le fou dans chaque direction

				//Valeur aboslue de la difference car on se déplace en diagonale
				if((abs(ChoosenCase.x-BlackBishop[pieceBishop].x) == abs(ChoosenCase.y-BlackBishop[pieceBishop].y))) 
			{
				//On vérifie dans les 4 diagonales, en fct du clic
			
		//Diagonale Bas/gauche
				if((ChoosenCase.y<BlackBishop[pieceBishop].y)&&(ChoosenCase.x<BlackBishop[pieceBishop].x)&&((ChoosenCase.y>=BLCarreauBishopLeftDown.y)&&(ChoosenCase.x>=BLCarreauBishopLeftDown.x)))
				{
					
						VerifieCoup=1;	
				}	
		//Diagonale Bas/Droite
				if((ChoosenCase.y<BlackBishop[pieceBishop].y)&&(ChoosenCase.x>BlackBishop[pieceBishop].x)&&((ChoosenCase.y>=BLCarreauBishopRightDown.y)&&(ChoosenCase.x<=BLCarreauBishopRightDown.x)))
				{
					
						VerifieCoup=1;
				}	
		//Diagonale Haut/gauche
				if((ChoosenCase.y>BlackBishop[pieceBishop].y)&&(ChoosenCase.x<BlackBishop[pieceBishop].x)&&((ChoosenCase.y<=BLCarreauBishopLeftUp.y)&&(ChoosenCase.x>=BLCarreauBishopLeftUp.x)))
				{
					
						VerifieCoup=1;
				}	
		//Diagonale Haut/Droite
				if((ChoosenCase.y>BlackBishop[pieceBishop].y)&&(ChoosenCase.x>BlackBishop[pieceBishop].x)&&((ChoosenCase.y<=BLCarreauBishopRightUp.y)&&(ChoosenCase.x<=BLCarreauBishopRightUp.x)))
				{	
					
						VerifieCoup=1;		
				}

			}

				

	//---------------------------------------
			
		if(VerifieCoup==1) //On regarde si on veut aller en diagonale en verifiant la valeur absolu des différences
					{
						//On tue une piece blanche
						if(caseValue(ChoosenCase).color=='w' && caseValue(ChoosenCase).name!='k')
						{
									
							killPiece(ChoosenCase);
							EtatJoueur=PlaceBishop(ChoosenCase, EtatJoueur);
						}

						//On autorise un déplacement sur une case vide
						if(caseValue(ChoosenCase).index==32 && VerifieCoup ==1)
						{
									EtatJoueur=PlaceBishop(ChoosenCase, EtatJoueur);
						}
					} 

		}	
	
	
return EtatJoueur; //Return de Etat joueur changé pour mettre à jour les timers
}



//Place le fou selectionnée à la case choisie
bool PlaceBishop(ChessGrid ChoosenCase, int EtatJoueur)
{

	//Si déplacement fou blanc
	if(!EtatJoueur)
	{
		WhiteBishop[pieceBishop].x=ChoosenCase.x; //On déplace en X
		WhiteBishop[pieceBishop].y=ChoosenCase.y; //On déplace en Y
		
	}
	//--------------------------

	//Si déplacement fou blanc
	if(EtatJoueur)
	{
		BlackBishop[pieceBishop].x=ChoosenCase.x; //On deplace en X
		BlackBishop[pieceBishop].y=ChoosenCase.y; //On déplace en Y
		
	}

	
	pieceBishop=32; //On déselectionne la piece choisie
	
	VerifieCoup=0; //Reinitialise le coup
	clicBishop=0; //On donc empeche l'affichage de coup disponible
	
EtatJoueur=!EtatJoueur; //C'est au tour de l'autre joueur

return EtatJoueur; 
}

//-------------------------------------- QUEEN--------------------------------




//On vérifie si on clique sur une reine
void CheckQueen(ChessGrid pos, bool EtatJoueur)
{
	//Si c'est aux blancs
	if(!EtatJoueur)
	{
		
			if((pos.x==WhiteQueen.x)&&(pos.y==WhiteQueen.y)) //Si on clique sur la position de lreine
			{
				pieceQueen=0;
				clicQueen+=1;
				
			}
		
	}
//------------------------
	//Si c'est aux noirs
	if(EtatJoueur)
	{
		
			if((pos.x==BlackQueen.x)&&(pos.y==BlackQueen.y)) //Si on clique sur la position de la reine
			{
				pieceQueen=1;
				clicQueen+=1; 
				
			}
		
		
	}

	//Si on reclique
	if(clicQueen==2)
	{
		pieceQueen=32; //On désaffiche les coups possible
		clicQueen=0; //Si on reclique on reset
	}
}

bool Queen(bool EtatJoueur)
{
	ChessGrid WhCarreauQueen = WhiteQueen;
	ChessGrid BLCarreauQueen = BlackQueen; 
	//-------------------------------------
	
	//Toutes les directions Queen wh
	ChessGrid WhCarreauQueenRightUp = WhCarreauQueen;
	WhCarreauQueenRightUp.y+=1;
	WhCarreauQueenRightUp.x+=1;
	ChessGrid WhCarreauQueenLeftUp = WhCarreauQueen;
	WhCarreauQueenLeftUp.y+=1;
	WhCarreauQueenLeftUp.x-=1;
	ChessGrid WhCarreauQueenRightDown = WhCarreauQueen;
	WhCarreauQueenRightDown.y-=1;
	WhCarreauQueenRightDown.x+=1;
	ChessGrid WhCarreauQueenLeftDown = WhCarreauQueen;
	WhCarreauQueenLeftDown.y-=1;
	WhCarreauQueenLeftDown.x-=1;

	ChessGrid WhCarreauQueenUp= WhCarreauQueen;
	WhCarreauQueenUp.y+=1;
	ChessGrid WhCarreauQueenLeft= WhCarreauQueen;
	WhCarreauQueenLeft.x-=1;
	ChessGrid WhCarreauQueenRight= WhCarreauQueen;
	WhCarreauQueenRight.x+=1;
	ChessGrid WhCarreauQueenDown= WhCarreauQueen;
	WhCarreauQueenDown.y-=1;
	

	//Toutes les directions Queen bl
	ChessGrid BLCarreauQueenRightUp = BLCarreauQueen;
	BLCarreauQueenRightUp.y+=1;
	BLCarreauQueenRightUp.x+=1;
	ChessGrid BLCarreauQueenLeftUp = BLCarreauQueen;
	BLCarreauQueenLeftUp.y+=1;
	BLCarreauQueenLeftUp.x-=1;
	ChessGrid BLCarreauQueenRightDown = BLCarreauQueen;
	BLCarreauQueenRightDown.y-=1;
	BLCarreauQueenRightDown.x+=1;
	ChessGrid BLCarreauQueenLeftDown = BLCarreauQueen;
	BLCarreauQueenLeftDown.y-=1;
	BLCarreauQueenLeftDown.x-=1;

	ChessGrid BLCarreauQueenUp= BLCarreauQueen;
	BLCarreauQueenUp.y+=1;
	ChessGrid BLCarreauQueenLeft= BLCarreauQueen;
	BLCarreauQueenLeft.x-=1;
	ChessGrid BLCarreauQueenRight= BLCarreauQueen;
	BLCarreauQueenRight.x+=1;
	ChessGrid BLCarreauQueenDown= BLCarreauQueen;
	BLCarreauQueenDown.y-=1;
	
	
	

	
	//-------------------------------------

	ChessGrid ChoosenCase = clicCase();

	//Affichage disponibilité déplacement white Queen

	if(!EtatJoueur)
	{	
	VerifieCoup=0;
			if((pieceQueen ==0)&&(clicQueen==1)) // Si on a selectionné la reine blanche
			{	
				
				while((WhCarreauQueenUp.y<9)&&(caseValue(WhCarreauQueenUp).name == '0'))
				{
				caseVerte(WhCarreauQueenUp); // affiche les case en verte
				WhCarreauQueenUp.y+=1;
				}

				if(caseValue(WhCarreauQueenUp).name != '0')
				{
					
					if((caseValue(WhCarreauQueenUp).name != 'k')&&(caseValue(WhCarreauQueenUp).color == 'b'))
					{
						caseRouge(WhCarreauQueenUp);//Sinon on affiche en rouge la case
					}
				}

				while((WhCarreauQueenLeft.x>96)&&(caseValue(WhCarreauQueenLeft).name == '0'))
				{
				caseVerte(WhCarreauQueenLeft); // affiche les case en verte
				WhCarreauQueenLeft.x-=1;
				}

				if(caseValue(WhCarreauQueenLeft).name != '0')
				{
					if((caseValue(WhCarreauQueenLeft).name != 'k')&&(caseValue(WhCarreauQueenLeft).color == 'b')) //ON affiche pas lorsqu'un roi est mis en echec
					{
						caseRouge(WhCarreauQueenLeft); //Sinon on affiche en rouge la case
					}
				}
			
				while((WhCarreauQueenRight.x<105)&&(caseValue(WhCarreauQueenRight).name == '0'))
				{
				caseVerte(WhCarreauQueenRight); // affiche les case en verte
				WhCarreauQueenRight.x+=1;
				}

				if(caseValue(WhCarreauQueenRight).name != '0')
				{
					if((caseValue(WhCarreauQueenRight).name != 'k')&&(caseValue(WhCarreauQueenRight).color == 'b')) //ON affiche pas lorsqu'un roi est mis en echec
					{
						caseRouge(WhCarreauQueenRight); //Sinon on affiche en rouge la case
					}
				}
				
				while((WhCarreauQueenDown.y>1)&&(caseValue(WhCarreauQueenDown).name == '0'))
				{
				caseVerte(WhCarreauQueenDown); // affiche les case en verte
				WhCarreauQueenDown.y-=1;
				}

				if(caseValue(WhCarreauQueenDown).name != '0')
				{
					if((caseValue(WhCarreauQueenDown).name != 'k')&&(caseValue(WhCarreauQueenDown).color == 'b')) //ON affiche pas lorsqu'un roi est mis en echec
					{
						caseRouge(WhCarreauQueenDown); //Sinon on affiche en rouge la case
					}
				}

				while((WhCarreauQueenRightUp.y<9)&&(caseValue(WhCarreauQueenRightUp).name == '0')&&(WhCarreauQueenRightUp.x<105))
					{
					
					caseVerte(WhCarreauQueenRightUp); // affiche les case en verte
					WhCarreauQueenRightUp.y+=1;
					WhCarreauQueenRightUp.x+=1;
					}

					if(caseValue(WhCarreauQueenRightUp).name != '0')
					{
						
						if((caseValue(WhCarreauQueenRightUp).name != 'k')&&(caseValue(WhCarreauQueenRightUp).color == 'b'))
						{
							caseRouge(WhCarreauQueenRightUp);//Sinon on affiche en rouge la case
						}
					}

					while((WhCarreauQueenLeftUp.x>96)&&(caseValue(WhCarreauQueenLeftUp).name == '0')&&(WhCarreauQueenLeftUp.y<9))
					{
					caseVerte(WhCarreauQueenLeftUp); // affiche les case en verte
					WhCarreauQueenLeftUp.y+=1;
					WhCarreauQueenLeftUp.x-=1;
					
					}

					if(caseValue(WhCarreauQueenLeftUp).name != '0')
					{
						if((caseValue(WhCarreauQueenLeftUp).name != 'k')&&(caseValue(WhCarreauQueenLeftUp).color == 'b')) //ON affiche pas lorsqu'un roi est mis en echec
						{
							caseRouge(WhCarreauQueenLeftUp); //Sinon on affiche en rouge la case
						}
					}

					while((WhCarreauQueenRightDown.x<105)&&(caseValue(WhCarreauQueenRightDown).name == '0')&&(WhCarreauQueenRightDown.y>0))
					{
					caseVerte(WhCarreauQueenRightDown); // affiche les case en verte
					WhCarreauQueenRightDown.y-=1;
					WhCarreauQueenRightDown.x+=1;
					}

					if(caseValue(WhCarreauQueenRightDown).name != '0')
					{
						if((caseValue(WhCarreauQueenRightDown).name != 'k')&&(caseValue(WhCarreauQueenRightDown).color == 'b')) //ON affiche pas lorsqu'un roi est mis en echec
						{
							caseRouge(WhCarreauQueenRightDown); //Sinon on affiche en rouge la case
						}
					}

					while((WhCarreauQueenLeftDown.y>0)&&(caseValue(WhCarreauQueenLeftDown).name == '0')&&(WhCarreauQueenLeftDown.x>96))
					{
					caseVerte(WhCarreauQueenLeftDown); // affiche les case en verte
					WhCarreauQueenLeftDown.y-=1;
					WhCarreauQueenLeftDown.x-=1;
					}

					if(caseValue(WhCarreauQueenLeftDown).name != '0')
					{
						if((caseValue(WhCarreauQueenLeftDown).name != 'k')&&(caseValue(WhCarreauQueenLeftDown).color == 'b')) //ON affiche pas lorsqu'un roi est mis en echec
						{
							caseRouge(WhCarreauQueenLeftDown); //Sinon on affiche en rouge la case
						}
					}

				
			}	
	}
//-------------------------------------------------
	//Affichage disponibilité déplacement black Queen
	if(EtatJoueur)
	{
		
		if((pieceQueen ==1)&&(clicQueen==1)) // Si on a selectionné la reine noire
		{	

			//On va afficher les cases de déplacement possible
			while((BLCarreauQueenUp.y<9)&&(caseValue(BLCarreauQueenUp).name == '0')) // Au dessus
				{
				caseVerte(BLCarreauQueenUp); // affiche les cases en vert
				BLCarreauQueenUp.y+=1;
				}

				if(caseValue(BLCarreauQueenUp).name != '0')
				{
					
					if((caseValue(BLCarreauQueenUp).name != 'k')&&(caseValue(BLCarreauQueenUp).color == 'w')) 
					{
						caseRouge(BLCarreauQueenUp);//Sinon on affiche en rouge la case
					}
				}

			while((BLCarreauQueenLeft.x>96)&&(caseValue(BLCarreauQueenLeft).name == '0')) // A gauche
				{
				caseVerte(BLCarreauQueenLeft); // affiche les case en verte
				BLCarreauQueenLeft.x-=1;
				}

				if(caseValue(BLCarreauQueenLeft).name != '0')
				{
					if((caseValue(BLCarreauQueenLeft).name != 'k')&&(caseValue(BLCarreauQueenLeft).color == 'w')) //ON affiche pas lorsqu'un roi est mis en echec
					{
						caseRouge(BLCarreauQueenLeft); //Sinon on affiche en rouge la case
					}
				}
			
			while((BLCarreauQueenRight.x<105)&&(caseValue(BLCarreauQueenRight).name == '0')) // A droite
				{
				caseVerte(BLCarreauQueenRight); // affiche les case en verte
				BLCarreauQueenRight.x+=1;
				}

				if(caseValue(BLCarreauQueenRight).name != '0')
				{
					if((caseValue(BLCarreauQueenRight).name != 'k')&&(caseValue(BLCarreauQueenRight).color == 'w')) //ON affiche pas lorsqu'un roi est mis en echec
					{
						caseRouge(BLCarreauQueenRight); //Sinon on affiche en rouge la case
					}
				}
				
			while((BLCarreauQueenDown.y>1)&&(caseValue(BLCarreauQueenDown).name == '0')) //En bas
				{
				caseVerte(BLCarreauQueenDown); // affiche les cases en verte
				BLCarreauQueenDown.y-=1;
				}

				if(caseValue(BLCarreauQueenDown).name != '0')
				{
					if((caseValue(BLCarreauQueenDown).name != 'k')&&(caseValue(BLCarreauQueenDown).color == 'w')) //ON affiche pas lorsqu'un roi est mis en echec
					{
						caseRouge(BLCarreauQueenDown); //Sinon on affiche en rouge la case
					}
				}
		
			//Diagonale haut/droite
			while((BLCarreauQueenRightUp.y<9)&&(caseValue(BLCarreauQueenRightUp).name == '0')&&(BLCarreauQueenRightUp.x<105))
					{
					
					caseVerte(BLCarreauQueenRightUp); // affiche les case en verte
					BLCarreauQueenRightUp.y+=1;
					BLCarreauQueenRightUp.x+=1;
					}

					if(caseValue(BLCarreauQueenRightUp).name != '0')
					{
						
						if((caseValue(BLCarreauQueenRightUp).name != 'k')&&(caseValue(BLCarreauQueenRightUp).color == 'w'))
						{
							caseRouge(BLCarreauQueenRightUp);//Sinon on affiche en rouge la case
						}
					}
			//Diagonale Haut/gauche
			while((BLCarreauQueenLeftUp.x>96)&&(caseValue(BLCarreauQueenLeftUp).name == '0')&&(BLCarreauQueenLeftUp.y<9))
					{
					caseVerte(BLCarreauQueenLeftUp); // affiche les case en verte
					BLCarreauQueenLeftUp.y+=1;
					BLCarreauQueenLeftUp.x-=1;
					
					}

					if(caseValue(BLCarreauQueenLeftUp).name != '0')
					{
						if((caseValue(BLCarreauQueenLeftUp).name != 'k')&&(caseValue(BLCarreauQueenLeftUp).color == 'w')) //ON affiche pas lorsqu'un roi est mis en echec
						{
							caseRouge(BLCarreauQueenLeftUp); //Sinon on affiche en rouge la case
						}
					}
			//Diagonale Bas/Droite
			while((BLCarreauQueenRightDown.x<105)&&(caseValue(BLCarreauQueenRightDown).name == '0')&&(BLCarreauQueenRightDown.y>0))
					{
					caseVerte(BLCarreauQueenRightDown); // affiche les case en verte
					BLCarreauQueenRightDown.y-=1;
					BLCarreauQueenRightDown.x+=1;
					}

					if(caseValue(BLCarreauQueenRightDown).name != '0')
					{
						if((caseValue(BLCarreauQueenRightDown).name != 'k')&&(caseValue(BLCarreauQueenRightDown).color == 'w')) //ON affiche pas lorsqu'un roi est mis en echec
						{
							caseRouge(BLCarreauQueenRightDown); //Sinon on affiche en rouge la case
						}
					}
			//Diagonale Bas/Gauche
			while((BLCarreauQueenLeftDown.y>0)&&(caseValue(BLCarreauQueenLeftDown).name == '0')&&(BLCarreauQueenLeftDown.x>96))
					{
					caseVerte(BLCarreauQueenLeftDown); // affiche les case en verte
					BLCarreauQueenLeftDown.y-=1;
					BLCarreauQueenLeftDown.x-=1;
					}

					if(caseValue(BLCarreauQueenLeftDown).name != '0')
					{
						if((caseValue(BLCarreauQueenLeftDown).name != 'k')&&(caseValue(BLCarreauQueenLeftDown).color == 'w')) //ON affiche pas lorsqu'un roi est mis en echec
						{
							caseRouge(BLCarreauQueenLeftDown); //Sinon on affiche en rouge la case
						}
					}	
		}
	}	
	
	
//On verifie qu'on clique dans la grille
	if((ChoosenCase.x>=97)&&(ChoosenCase.x<=104)&&(ChoosenCase.y>=1)&&(ChoosenCase.y<=8)&&(clicQueen==1))
	{
		
		//Déplacement white queen
		if(!EtatJoueur)
		{
			if((ChoosenCase.x==WhiteQueen.x)^(ChoosenCase.y==WhiteQueen.y)) //Si on choisit un deplacement linéaire (Comme les tours)
			{
				//ON verifie dans les 4 directions, en fct du clic
				if((ChoosenCase.y<WhiteQueen.y)&&(ChoosenCase.y>=WhCarreauQueenDown.y)) 
					{
							VerifieCoup=1;
					}	

					if((ChoosenCase.y>WhiteQueen.y)&&(ChoosenCase.y<=WhCarreauQueenUp.y))
					{
						
							VerifieCoup=1;
					}	

					if((ChoosenCase.x<WhiteQueen.x)&&(ChoosenCase.x>=WhCarreauQueenLeft.x))
					{
						
							VerifieCoup=1;
					}	

					if((ChoosenCase.x>WhiteQueen.x)&&(ChoosenCase.x<=WhCarreauQueenRight.x))
					{	
						
							VerifieCoup=1;
					}	
			}

			if((abs(ChoosenCase.x-WhiteQueen.x) == abs(ChoosenCase.y-WhiteQueen.y))) //Si on choisit un déplacement type "fou"
			{
				//On vérifie dans les 4 diagonales, en fct du clic
				if((ChoosenCase.y<WhiteQueen.y)&&(ChoosenCase.x<WhiteQueen.x)&&((ChoosenCase.y>=WhCarreauQueenLeftDown.y)&&(ChoosenCase.x>=WhCarreauQueenLeftDown.x)))
				{
					
						VerifieCoup=1;	
				}	

				if((ChoosenCase.y<WhiteQueen.y)&&(ChoosenCase.x>WhiteQueen.x)&&((ChoosenCase.y>=WhCarreauQueenRightDown.y)&&(ChoosenCase.x<=WhCarreauQueenRightDown.x)))
				{
					
						VerifieCoup=1;
				}	

				if((ChoosenCase.y>WhiteQueen.y)&&(ChoosenCase.x<WhiteQueen.x)&&((ChoosenCase.y<=WhCarreauQueenLeftUp.y)&&(ChoosenCase.x>=WhCarreauQueenLeftUp.x)))
				{
					
						VerifieCoup=1;
				}	

				if((ChoosenCase.y>WhiteQueen.y)&&(ChoosenCase.x>WhiteQueen.x)&&((ChoosenCase.y<=WhCarreauQueenRightUp.y)&&(ChoosenCase.x<=WhCarreauQueenRightUp.x)))
				{	
					
						VerifieCoup=1;		
				}

			}

			//On tue une pièce noire
					if(caseValue(ChoosenCase).color=='b' && caseValue(ChoosenCase).name!='k'&&(VerifieCoup==1))
					{
									
						killPiece(ChoosenCase);
						EtatJoueur=PlaceQueen(ChoosenCase, EtatJoueur);
					}

			//On autorise un déplacement sur une case vide
					if(caseValue(ChoosenCase).index==32 && VerifieCoup ==1)
					{
						EtatJoueur=PlaceQueen(ChoosenCase, EtatJoueur);
					}


		}
		
	
//----------------------------------------
	//Déplacement black queen
		if(EtatJoueur)
		{
			if((ChoosenCase.x==BlackQueen.x)^(ChoosenCase.y==BlackQueen.y)) //Si on choisit un deplacement linéaire (Comme les tours)
			{
			//On verifie dans la direction en fonction du clic
				if((ChoosenCase.y<BlackQueen.y)&&(ChoosenCase.y>=BLCarreauQueenDown.y)) 
					{
							VerifieCoup=1;
					}	

					if((ChoosenCase.y>BlackQueen.y)&&(ChoosenCase.y<=BLCarreauQueenUp.y))
					{
							VerifieCoup=1;
					}	

					if((ChoosenCase.x<BlackQueen.x)&&(ChoosenCase.x>=BLCarreauQueenLeft.x))
					{
							VerifieCoup=1;
					}	

					if((ChoosenCase.x>BlackQueen.x)&&(ChoosenCase.x<=BLCarreauQueenRight.x))
					{	
							VerifieCoup=1;
					}	
			}

			if((abs(ChoosenCase.x-BlackQueen.x) == abs(ChoosenCase.y-BlackQueen.y))) //Si on choisit un déplacement type "fou"
			{
				//On vérifie dans les 4 diagonales en fonction du clique
				if((ChoosenCase.y<BlackQueen.y)&&(ChoosenCase.x<BlackQueen.x)&&((ChoosenCase.y>=BLCarreauQueenLeftDown.y)&&(ChoosenCase.x>=BLCarreauQueenLeftDown.x)))
				{
						VerifieCoup=1;	
				}	

				if((ChoosenCase.y<BlackQueen.y)&&(ChoosenCase.x>BlackQueen.x)&&((ChoosenCase.y>=BLCarreauQueenRightDown.y)&&(ChoosenCase.x<=BLCarreauQueenRightDown.x)))
				{
						VerifieCoup=1;
				}	

				if((ChoosenCase.y>BlackQueen.y)&&(ChoosenCase.x<BlackQueen.x)&&((ChoosenCase.y<=BLCarreauQueenLeftUp.y)&&(ChoosenCase.x>=BLCarreauQueenLeftUp.x)))
				{
						VerifieCoup=1;
				}	

				if((ChoosenCase.y>BlackQueen.y)&&(ChoosenCase.x>BlackQueen.x)&&((ChoosenCase.y<=BLCarreauQueenRightUp.y)&&(ChoosenCase.x<=BLCarreauQueenRightUp.x)))
				{	
						VerifieCoup=1;		
				}

			}

			//On tue une pièce noire si déplacement vérifie
					if(caseValue(ChoosenCase).color=='w' && caseValue(ChoosenCase).name!='k'&&(VerifieCoup==1))
					{
									
						killPiece(ChoosenCase);
						EtatJoueur=PlaceQueen(ChoosenCase, EtatJoueur);
					}

			//On autorise un déplacement sur une case vide si déplacement vérifié
					if(caseValue(ChoosenCase).index==32 && VerifieCoup ==1)
					{
						EtatJoueur=PlaceQueen(ChoosenCase, EtatJoueur);
					}
	
		}
	

	}
return EtatJoueur; //Return de Etat joueur changé pour mettre à jour les timers
}

//Place la reine selectionnée à la case choisie
bool PlaceQueen(ChessGrid ChoosenCase, int EtatJoueur)
{

	//Si déplacement tour blanche
	if(!EtatJoueur)
	{
		WhiteQueen.x=ChoosenCase.x; //On déplace en X
		WhiteQueen.y=ChoosenCase.y; //On déplace en Y
		
	}
	//--------------------------

	//Si déplacement tour noire
	if(EtatJoueur)
	{
		BlackQueen.x=ChoosenCase.x; //On deplace en X
		BlackQueen.y=ChoosenCase.y; //On déplace en Y
		
	}

	VerifieCoup=0; //Reinitialise le coup
	pieceQueen=32;
	clicQueen=0; //On donc empeche l'affichage de coup disponible
	
EtatJoueur=!EtatJoueur; //C'est au tour de l'autre joueur

return EtatJoueur; 
}

//----------------------------------KING----------------------------


void CheckKing(ChessGrid pos, bool EtatJoueur)
{
	//Si c'est aux blancs
	if(!EtatJoueur)
	{
		
			if((pos.x==WhiteKing.x)&&(pos.y==WhiteKing.y)) //Si on clique sur la position de lreine
			{
				pieceKing=0;
				clicKing+=1;
			
			}
		
	}
//------------------------
	//Si c'est aux noirs
	if(EtatJoueur)
	{
		
			if((pos.x==BlackKing.x)&&(pos.y==BlackKing.y)) //Si on clique sur la position de la reine
			{
				pieceKing=1;
				clicKing+=1; 
				
			}
		
		
	}

	//Si on reclique
	if(clicKing==2)
	{
		pieceKing=32; //On désaffiche les coups possible
		clicKing=0; //Si on reclique on reset
	}
}

bool King(bool EtatJoueur)
{
	ChessGrid WhCarreauKing = WhiteKing;
	ChessGrid BLCarreauKing = BlackKing; 
	//-------------------------------------
	
	//Toutes les directions King wh
	ChessGrid WhCarreauKingRightUp = WhCarreauKing;
	WhCarreauKingRightUp.y+=1;
	WhCarreauKingRightUp.x+=1;
	ChessGrid WhCarreauKingLeftUp = WhCarreauKing;
	WhCarreauKingLeftUp.y+=1;
	WhCarreauKingLeftUp.x-=1;
	ChessGrid WhCarreauKingRightDown = WhCarreauKing;
	WhCarreauKingRightDown.y-=1;
	WhCarreauKingRightDown.x+=1;
	ChessGrid WhCarreauKingLeftDown = WhCarreauKing;
	WhCarreauKingLeftDown.y-=1;
	WhCarreauKingLeftDown.x-=1;

	ChessGrid WhCarreauKingUp= WhCarreauKing;
	WhCarreauKingUp.y+=1;
	ChessGrid WhCarreauKingLeft= WhCarreauKing;
	WhCarreauKingLeft.x-=1;
	ChessGrid WhCarreauKingRight= WhCarreauKing;
	WhCarreauKingRight.x+=1;
	ChessGrid WhCarreauKingDown= WhCarreauKing;
	WhCarreauKingDown.y-=1;
	

	//Toutes les directions King bl
	ChessGrid BLCarreauKingRightUp = BLCarreauKing;
	BLCarreauKingRightUp.y+=1;
	BLCarreauKingRightUp.x+=1;
	ChessGrid BLCarreauKingLeftUp = BLCarreauKing;
	BLCarreauKingLeftUp.y+=1;
	BLCarreauKingLeftUp.x-=1;
	ChessGrid BLCarreauKingRightDown = BLCarreauKing;
	BLCarreauKingRightDown.y-=1;
	BLCarreauKingRightDown.x+=1;
	ChessGrid BLCarreauKingLeftDown = BLCarreauKing;
	BLCarreauKingLeftDown.y-=1;
	BLCarreauKingLeftDown.x-=1;

	ChessGrid BLCarreauKingUp= BLCarreauKing;
	BLCarreauKingUp.y+=1;
	ChessGrid BLCarreauKingLeft= BLCarreauKing;
	BLCarreauKingLeft.x-=1;
	ChessGrid BLCarreauKingRight= BLCarreauKing;
	BLCarreauKingRight.x+=1;
	ChessGrid BLCarreauKingDown= BLCarreauKing;
	BLCarreauKingDown.y-=1;
	
	
	

	
	//-------------------------------------

	ChessGrid ChoosenCase = clicCase();

	//Affichage disponibilité déplacement white King
VerifieCoup=0;
	if(!EtatJoueur)
	{
			if((pieceKing ==0)&&(clicKing==1)) // Si on a selectionné le roi blanche
			{	
				//En haut
				if((caseValue(WhCarreauKingUp).name == '0')&&(WhCarreauKingUp.y<9))
				{
					
					caseVerte(WhCarreauKingUp);
				}
				else if((caseValue(WhCarreauKingUp).name != 'k')&&(caseValue(WhCarreauKingUp).color == 'b'))
						{
						caseRouge(WhCarreauKingUp);//Sinon on affiche en rouge la case
						}

				//A droite
				if((caseValue(WhCarreauKingRight).name == '0')&&(WhCarreauKingRight.x<105))
				{
					
					caseVerte(WhCarreauKingRight);
				}
				else if((caseValue(WhCarreauKingRight).name != 'k')&&(caseValue(WhCarreauKingRight).color == 'b'))
						{
						caseRouge(WhCarreauKingRight);//Sinon on affiche en rouge la case
						}

				//En bas
				if((caseValue(WhCarreauKingDown).name == '0')&&(WhCarreauKingDown.y>0))
				{
					
					caseVerte(WhCarreauKingDown);
				}
				else if((caseValue(WhCarreauKingDown).name != 'k')&&(caseValue(WhCarreauKingUp).color == 'b'))
						{
						caseRouge(WhCarreauKingDown);//Sinon on affiche en rouge la case
						}
				//A gauche
				if((caseValue(WhCarreauKingLeft).name == '0')&&(WhCarreauKingLeft.x>96))
				{
					
					caseVerte(WhCarreauKingLeft);
				}
				else if((caseValue(WhCarreauKingLeft).name != 'k')&&(caseValue(WhCarreauKingLeft).color == 'b'))
						{
						caseRouge(WhCarreauKingLeft);//Sinon on affiche en rouge la case
						}

				//A En Haut/gauche
				if((caseValue(WhCarreauKingLeftUp).name == '0')&&(WhCarreauKingLeftUp.x>96  && WhCarreauKingLeftUp.y<9))
				{
					
					caseVerte(WhCarreauKingLeftUp);
				}
				else if((caseValue(WhCarreauKingLeftUp).name != 'k')&&(caseValue(WhCarreauKingLeftUp).color == 'b'))
						{
						caseRouge(WhCarreauKingLeftUp);//Sinon on affiche en rouge la case
						}

				//En Haut/droite
				if((caseValue(WhCarreauKingRightUp).name == '0')&&(WhCarreauKingRightUp.x<105 && WhCarreauKingRightUp.y<9))
				{
					
					caseVerte(WhCarreauKingRightUp);
				}
				else if((caseValue(WhCarreauKingRightUp).name != 'k')&&(caseValue(WhCarreauKingRightUp).color == 'b'))
						{
						caseRouge(WhCarreauKingRightUp);//Sinon on affiche en rouge la case
						}

				//En bas/Droite
				if((caseValue(WhCarreauKingRightDown).name == '0') &&(WhCarreauKingRightDown.x<105 && WhCarreauKingRightDown.y>0))
				{
					
					caseVerte(WhCarreauKingRightDown);
				}
				else if((caseValue(WhCarreauKingRightDown).name != 'k')&&(caseValue(WhCarreauKingRightDown).color == 'b'))
						{
						caseRouge(WhCarreauKingRightDown);//Sinon on affiche en rouge la case
						}

			//En bas/Gauche
				if((caseValue(WhCarreauKingLeftDown).name == '0') && (WhCarreauKingLeftDown.x>96) && (WhCarreauKingLeftDown.y>0))
				{
					caseVerte(WhCarreauKingLeftDown);
				}
				else if((caseValue(WhCarreauKingLeftDown).name != 'k')&&(caseValue(WhCarreauKingLeftDown).color == 'b'))
						{
						caseRouge(WhCarreauKingLeftDown);//Sinon on affiche en rouge la case
						}
				
			}		
	}
	
//-------------------------------------------------
	//Affichage disponibilité déplacement black King
	if(EtatJoueur)
	{
		
			if((pieceKing ==1)&&(clicKing==1)) // Si on a selectionné le roi noir
			{
				//En haut
				if((caseValue(BLCarreauKingUp).name == '0')&&(BLCarreauKingUp.y<9))
				{
					
					caseVerte(BLCarreauKingUp);
				}
				else if((caseValue(BLCarreauKingUp).name != 'k')&&(caseValue(BLCarreauKingUp).color == 'w'))
						{
						caseRouge(BLCarreauKingUp);//Sinon on affiche en rouge la case
						}

				//A droite
				if((caseValue(BLCarreauKingRight).name == '0')&&(BLCarreauKingRight.x<105))
				{
					
					caseVerte(BLCarreauKingRight);
				}
				else if((caseValue(BLCarreauKingRight).name != 'k')&&(caseValue(BLCarreauKingRight).color == 'w'))
						{
						caseRouge(BLCarreauKingRight);//Sinon on affiche en rouge la case
						}

				//En bas
				if((caseValue(BLCarreauKingDown).name == '0')&&(BLCarreauKingDown.y>0))
				{
					caseVerte(BLCarreauKingDown);
				}
				else if((caseValue(BLCarreauKingDown).name != 'k')&&(caseValue(BLCarreauKingUp).color == 'w'))
						{
						caseRouge(BLCarreauKingDown);//Sinon on affiche en rouge la case
						}
				//A gauche
				if((caseValue(BLCarreauKingLeft).name == '0')&&(BLCarreauKingLeft.x>96))
				{
					
					caseVerte(BLCarreauKingLeft);
				}
				else if((caseValue(BLCarreauKingLeft).name != 'k')&&(caseValue(BLCarreauKingLeft).color == 'w'))
						{
						caseRouge(BLCarreauKingLeft);//Sinon on affiche en rouge la case
						}

				//A En Haut/gauche
				if((caseValue(BLCarreauKingLeftUp).name == '0')&&(BLCarreauKingLeftUp.x>96  && BLCarreauKingLeftUp.y<9))
				{
					
					caseVerte(BLCarreauKingLeftUp);
				}
				else if((caseValue(BLCarreauKingLeftUp).name != 'k')&&(caseValue(BLCarreauKingLeftUp).color == 'w'))
						{
						caseRouge(BLCarreauKingLeftUp);//Sinon on affiche en rouge la case
						}

				//En Haut/droite
				if((caseValue(BLCarreauKingRightUp).name == '0')&&(BLCarreauKingRightUp.x<105 && BLCarreauKingRightUp.y<9))
				{
					caseVerte(BLCarreauKingRightUp);
				}
				else if((caseValue(BLCarreauKingRightUp).name != 'k')&&(caseValue(BLCarreauKingRightUp).color == 'w'))
						{
						caseRouge(BLCarreauKingRightUp);//Sinon on affiche en rouge la case
						}

				//En bas/Droite
				if((caseValue(BLCarreauKingRightDown).name == '0')&&(BLCarreauKingRightDown.x<105 && BLCarreauKingUp.y>0))
				{
					
					caseVerte(BLCarreauKingRightDown);
				}
				else if((caseValue(BLCarreauKingRightDown).name != 'k')&&(caseValue(BLCarreauKingRightDown).color == 'w'))
						{
						caseRouge(BLCarreauKingRightDown);//Sinon on affiche en rouge la case
						}

				//En bas/Gauche
				if((caseValue(BLCarreauKingLeftDown).name == '0') && (BLCarreauKingLeftDown.x>96) && (BLCarreauKingLeftDown.y>0))
				{
					
					caseVerte(BLCarreauKingLeftDown);
				}
				else if((caseValue(BLCarreauKingLeftDown).name != 'k')&&(caseValue(BLCarreauKingLeftDown).color == 'w'))
						{
						caseRouge(BLCarreauKingLeftDown);//Sinon on affiche en rouge la case
						}
			}
	}
		
//--------------------------------------------------------------		
//On verifie qu'on clique dans la grille
	if((ChoosenCase.x>=97)&&(ChoosenCase.x<=104)&&(ChoosenCase.y>=0)&&(ChoosenCase.y<=8)&&(clicKing==1))
	{
		

		//Déplacement white King
		if(!EtatJoueur)
		{
			//ON cherche a autorise un déplacement
				//Si a gauche
				if((ChoosenCase.x==WhCarreauKingLeft.x)&&((ChoosenCase.y==WhCarreauKingLeft.y)))
					{		
							VerifieCoup=1;
					}	
				//Si en haut
				if((ChoosenCase.x==WhCarreauKingUp.x)&&(ChoosenCase.y==WhCarreauKingUp.y))
					{		
							VerifieCoup=1;
					}	
				//Si a droite
				if((ChoosenCase.x==WhCarreauKingRight.x)&&(ChoosenCase.y==WhCarreauKingRight.y))
					{		
							VerifieCoup=1;
					}	
				//Si en bas
				if((ChoosenCase.x==WhCarreauKingDown.x)&&(ChoosenCase.y==WhCarreauKingDown.y))
					{		
							VerifieCoup=1;
					}
				//Si en bas/droite
				if((ChoosenCase.x==WhCarreauKingRightDown.x)&&(ChoosenCase.y==WhCarreauKingRightDown.y))
					{		
							VerifieCoup=1;
					}	
				//Si en bas/gauche
				if((ChoosenCase.x==WhCarreauKingLeftDown.x)&&(ChoosenCase.y==WhCarreauKingLeftDown.y))
					{		
							VerifieCoup=1;
					}
				//Si en haut/Gauche
				if((ChoosenCase.x==WhCarreauKingLeftUp.x)&&(ChoosenCase.y==WhCarreauKingLeftUp.y))
					{		
							
							VerifieCoup=1;
					}	
				//Si en haut/droite
				if((ChoosenCase.x==WhCarreauKingRightUp.x)&&(ChoosenCase.y==WhCarreauKingRightUp.y))
					{		
							
							VerifieCoup=1;
					}	
//----------------------------------------------------------
			//On tue une pièce noire
					if(caseValue(ChoosenCase).color=='b' && caseValue(ChoosenCase).name!='k'&& VerifieCoup==1)
					{
									
						killPiece(ChoosenCase);
						EtatJoueur=PlaceKing(ChoosenCase, EtatJoueur);
					}

			//On autorise un déplacement sur une case vide
					if(caseValue(ChoosenCase).index==32 &&  VerifieCoup==1 )
					{
						
						EtatJoueur=PlaceKing(ChoosenCase, EtatJoueur);
					}

		}
	
		
	
//----------------------------------------
	//Déplacement black King
		if(EtatJoueur)
		{
			//ON cherche a autorise un déplacement
				//Si a gauche
				if((ChoosenCase.x==BLCarreauKingLeft.x)&&((ChoosenCase.y==BLCarreauKingLeft.y)))
					{		
							VerifieCoup=1;
					}	
				//Si en haut
				if((ChoosenCase.x==BLCarreauKingUp.x)&&(ChoosenCase.y==BLCarreauKingUp.y))
					{		
							VerifieCoup=1;
					}	
				//Si a droite
				if((ChoosenCase.x==BLCarreauKingRight.x)&&(ChoosenCase.y==BLCarreauKingRight.y))
					{		
							VerifieCoup=1;
					}	
				//Si en bas
				if((ChoosenCase.x==BLCarreauKingDown.x)&&(ChoosenCase.y==BLCarreauKingDown.y))
					{		
							VerifieCoup=1;
					}
				//Si en bas/droite
				if((ChoosenCase.x==BLCarreauKingRightDown.x)&&(ChoosenCase.y==BLCarreauKingRightDown.y))
					{		
							VerifieCoup=1;
					}	
				//Si en bas/gauche
				if((ChoosenCase.x==BLCarreauKingLeftDown.x)&&(ChoosenCase.y==BLCarreauKingLeftDown.y))
					{		
							VerifieCoup=1;
					}
				//Si en haut/Gauche
				if((ChoosenCase.x==BLCarreauKingLeftUp.x)&&(ChoosenCase.y==BLCarreauKingLeftUp.y))
					{		
							
							VerifieCoup=1;
					}	
				//Si en haut/droite
				if((ChoosenCase.x==BLCarreauKingRightUp.x)&&(ChoosenCase.y==BLCarreauKingRightUp.y))
					{		
							
							VerifieCoup=1;
					}	
//----------------------------------------------------------
			//On tue une pièce blanche
					if(caseValue(ChoosenCase).color=='w' && caseValue(ChoosenCase).name!='k'&& VerifieCoup==1)
					{
									
						killPiece(ChoosenCase);
						EtatJoueur=PlaceKing(ChoosenCase, EtatJoueur);
					}

			//On autorise un déplacement sur une case vide
					if(caseValue(ChoosenCase).index==32 &&  VerifieCoup==1 )
					{
						
						EtatJoueur=PlaceKing(ChoosenCase, EtatJoueur);
					}
		}
	}
	
	
return EtatJoueur; //Return de Etat joueur changé pour mettre à jour les timers
}


//Place la reine selectionnée à la case choisie
bool PlaceKing(ChessGrid ChoosenCase, int EtatJoueur)
{

	//Si déplacement tour blanche
	if(!EtatJoueur)
	{
		WhiteKing.x=ChoosenCase.x; //On déplace en X
		WhiteKing.y=ChoosenCase.y; //On déplace en Y
		
	}
	//--------------------------

	//Si déplacement tour noire
	if(EtatJoueur)
	{
		BlackKing.x=ChoosenCase.x; //On deplace en X
		BlackKing.y=ChoosenCase.y; //On déplace en Y
		
	}

	VerifieCoup=0; //Reinitialise le coup
	pieceKing=32;
	clicKing=0; //On donc empeche l'affichage de coup disponible
	
EtatJoueur=!EtatJoueur; //C'est au tour de l'autre joueur

return EtatJoueur; 
}

