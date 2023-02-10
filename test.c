#include <stdlib.h>
#include <stdio.h>
#include "coordonnee.h"

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
    int Sumx=bordureEpaisseur+8;
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




// Initialise la matrice de la grille en mémoire dynamique
// avec la position initiale des pions
char** iniMatGrid() 
{ 
    int size = 8;
    char** mat = (char **) malloc(sizeof(char*)*size);
    if(mat!=NULL) 
    { 
        for(int i=0;i<size;i+=1)
        { 
            mat[i]=(char*) malloc(sizeof(char)*size);
            if (mat[i] == NULL){puts("Memory not allocated");} 
            else { 
                for(int j=0;j<size;j+=1) 
                { 
                    switch (i)
                    {
                    case 0:
                        switch (j)
                        {
                        case 0: case 7:
                            mat[i][j]='t'; // t => tour noire 
                            break;
                        case 1: case 6:
                            mat[i][j]='c'; // c => cavalier noir
                            break;
                        case 2: case 5:
                            mat[i][j]='f'; // f => fou noir
                            break;
                        case 3:
                            mat[i][j]='q'; // q => reine noire (qween)
                            break;
                        case 4:
                            mat[i][j]='k'; // k => roi noir (king)
                            break;
                        }
                        break;

                    case 1:
                        mat[i][j]='p'; // p => pion noir
                        break;
                    case 6:
                        mat[i][j]='P'; // P => pion blanc
                        break;

                    case 7:
                        switch (j)
                        {
                        case 0: case 7:
                            mat[i][j]='T'; // T => tour blanche 
                            break;
                        case 1: case 6:
                            mat[i][j]='C'; // C => cavalier blanc
                            break;
                        
                        case 2: case 5:
                            mat[i][j]='F'; // F => fou blanc
                            break;
                        case 3:
                            mat[i][j]='Q'; // Q => reine blanche (qween)
                            break;
                        case 4:
                            mat[i][j]='K'; // K => roi blanc (king)
                            break;
                        }
                        break;
                    default :
                        mat[i][j]='0'; // 0 => la case est vide
                        break;
                    }
                }

            } 
        } 
    } else {puts("Memory not allocated");} 
    return mat; 
}

void arrayMat(int size,char** mat) 
{ 
    for(int i=0;i<size;i++) 
    { 
        for(int j=0;j<size;j++){
            printf("%c ",mat[i][j]);
        }
        printf("\n"); 
    } 

}

void freeMat(char** mat) 
{ 
    for(int i;i<8;i++) 
        free(mat[i]); 
}



// Renvoie la valeur des coordonnee d'une case
char matCoordonnee(ChessGrid carreau,char** mat)
{
    int i = 8-(carreau.y); // car on commence à partir de 1 dans les coordonnée des échecs
    int j = 7-(carreau.x - 97);
    return mat[j][i];
}

// Renvoie les coordonnees d'une valeur
ChessGrid* valMatCoordonnee(char val,char** mat){
    static ChessGrid L[7]; // Initie la liste de chessgrid (7=0+7)
    int k=0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(mat[i][j] == val){ 
                L[k].x=j+'a';
                L[k].y=i;
                k++;
            }
        }
    }
    return L;
}

int main(int argc, char **argv){
    char **mat=iniMatGrid();
    arrayMat(8,iniMatGrid());
    ChessGrid carreau = valMatCoordonnee('t',mat)[0];
    printf("case: %c%d\n",carreau.x,carreau.y);
    printf("val %c\n",matCoordonnee(carreau,mat));
   
    return 0;
}