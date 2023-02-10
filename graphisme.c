#include <stdlib.h>
#include <stdio.h>
#include "GfxLib.h"
#include "BmpLib.h"
#include "ESLib.h"
#include "graphisme.h"
#include "coordonnee.h"


//Fonction servants au graphisme ou aux animations



// Convertit largeur*hauteur pixels de la forme bleu, vert, rouge en entiers opacite, rouge, vert, bleu little endian
static int *BVR2ARVBT(int largeur, int hauteur, const unsigned char *donnees) {
    const unsigned char *ptrDonnees;
    unsigned char *pixels = (unsigned char*)malloc(largeur*hauteur*sizeof(int));
    unsigned char *ptrPixel;
    int index;
    ptrPixel = pixels;
    ptrDonnees = donnees;
    for
            (index = largeur*hauteur; index != 0; --index) /* On parcourt tous les
														pixels de l'image */
    {
        ptrPixel[0] = ptrDonnees[0];
        ptrPixel[1] = ptrDonnees[1];
        ptrPixel[2] = ptrDonnees[2];
        ptrPixel[3] = ptrDonnees[0]==1 && ptrDonnees[1]==0 && ptrDonnees[2]==0 ? 0:0x0FF;
       	//La couleur bleu "1" est en transparence
       	ptrDonnees += 3; /* On passe a la premiere composante du pixel suivant */
        ptrPixel += 4; /* On passe au pixel suivant */
    }
    return (int*)pixels;
}

static int *Green (int largeur, int hauteur, const unsigned char *donnees) {
	const unsigned char *ptrDonnees;
	unsigned char *pixels = (unsigned char*)malloc(largeur*hauteur*sizeof(int));
	unsigned char *ptrPixel;
	int index;
	ptrPixel = pixels;
	ptrDonnees = donnees;
	for (index = largeur*hauteur; index != 0; --index) /* On parcourt tous les pixels de l'image */
	{
		ptrPixel[0] = ptrDonnees[0];
		ptrPixel[1] = ptrDonnees[1];
		ptrPixel[2] = ptrDonnees[2];
		ptrPixel[3] = ptrDonnees[0]==0 && ptrDonnees[1]==255 && ptrDonnees[2]==0 ? 90:0x0FF;
		ptrDonnees += 3; /* On passe a la premiere composante du pixel suivant */
		ptrPixel += 4; /* On passe au pixel suivant */
	}
	return (int*)pixels;
	free(pixels);

}

static int *Red (int largeur, int hauteur, const unsigned char *donnees) {
	const unsigned char *ptrDonnees;
	unsigned char *pixels = (unsigned char*)malloc(largeur*hauteur*sizeof(int));
	unsigned char *ptrPixel;
	int index;
	ptrPixel = pixels;
	ptrDonnees = donnees;
	for (index = largeur*hauteur; index != 0; --index) /* On parcourt tous les pixels de l'image */
	{
		ptrPixel[0] = ptrDonnees[0];
		ptrPixel[1] = ptrDonnees[1];
		ptrPixel[2] = ptrDonnees[2];
		ptrPixel[3] = ptrDonnees[0]==0 && ptrDonnees[1]==0 && ptrDonnees[2]==255 ? 90:0x0FF;
		ptrDonnees += 3; /* On passe a la premiere composante du pixel suivant */
		ptrPixel += 4; /* On passe au pixel suivant */
	}
	return (int*)pixels;
	free(pixels);

}

// Ecris dans la fenetre une image BVR couvrant largeur*hauteur et demarrant en (x, y) */
void ecrisImageTransparence(int x, int y, int largeur, int hauteur, const unsigned char *donnees)
{
    int *pixels = BVR2ARVBT(largeur, hauteur, donnees);
    ecrisImageARVB(x, y, largeur, hauteur, pixels);
    free(pixels);
}

void GreenCase(int x, int y, int largeur, int hauteur, const unsigned char *donnees){
	int *pixels = Green(largeur, hauteur, donnees);
	ecrisImageARVB(x, y, largeur, hauteur, pixels);
	free(pixels);
}
	
void RedCase(int x, int y, int largeur, int hauteur, const unsigned char *donnees){
	int *pixels = Red(largeur, hauteur, donnees);
	ecrisImageARVB(x, y, largeur, hauteur, pixels);
	free(pixels);
}


//Prend en entré un carreau est colore la case en vert semi-transparent
void caseVerte(ChessGrid carreau)
{
	static DonneesImageRGB *caseVert = NULL; 
	caseVert = lisBMPRGB("images/caseVert.bmp"); //lis l'image attention le bmp en 24 bit
	if (caseVert != NULL){
		GreenCase(PixelCoordonnee(carreau).x+3, PixelCoordonnee(carreau).y, caseTaille, caseTaille, caseVert->donneesRGB);
	}
}

//Prend en entré un carreau est colore la case en vert semi-transparent
void caseRouge(ChessGrid carreau)
{
	static DonneesImageRGB *caseRouge = NULL; 
	caseRouge = lisBMPRGB("images/caseRouge.bmp"); //lis l'image attention le bmp en 24 bit
	if (caseRouge != NULL){
		RedCase(PixelCoordonnee(carreau).x+3, PixelCoordonnee(carreau).y, caseTaille, caseTaille, caseRouge->donneesRGB);
	}
}

// Affiche le menu
void afficheMenu()
{
	epaisseurDeTrait(3);
	couleurCourante(120,120,255);
	rectangle(170, 150, 650, 450);

	couleurCourante(120,120,255);
	afficheChaine("CHESS ISEN", 25, 330, 500);

	couleurCourante(255,255,255);
	afficheChaine("MENU", 20, 390, 375);

	afficheChaine("press < P > to play", 20, 300, 300);
	afficheChaine("press < Q > to quit", 20, 300, 245);

}