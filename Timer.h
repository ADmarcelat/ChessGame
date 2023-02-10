#ifndef TIMER_H
#define TIMER_H

//Structures

typedef struct
{ 
//Gestion temps blanc
    int  compteurWhite;    
	int  ValeurMinutesWhite;
	int  ValeurSecondesWhite;
	char ChaineMinutesWhite[255];
	char ChaineSecondesWhite[255];
  

//Gestion temps noir
    int  compteurBlack;
    int  ValeurMinutesBlack;
	int  ValeurSecondesBlack;
	char ChaineMinutesBlack[255];
	char ChaineSecondesBlack[255];

} GestionTime; //Coordonnee version grille d'echec

//Va gerer le décompte des secondes si le bouton temps est activé
GestionTime Decompte(bool EtatTimer, bool EtatJoueur, GestionTime GestionTemps);


//Transforme les int en char pour les afficher
GestionTime TransformCompteur(GestionTime GestionTemps);

//Affiche le temps restant sur l'interface
void AfficheTemps(GestionTime GestionTemps);



#endif
