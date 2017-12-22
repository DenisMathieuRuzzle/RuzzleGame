#include "Grille.h"

char LettreAlea (){
    char c = ( rand() % ( ( 90 - 65 ) + 1) ) + 65;
 	return c;
}

int rand_a_b(int min, int max){

	return (int)(((double)rand() * (double)(max - min) / (double)RAND_MAX)) + min;
}

int Score_lettre(char c){
    int points[]={1,3,3,2,1,4,2,4,1,8,10,1,2,1,1,3,8,1,1,1,1,4,10,10,10,10};
     
    c=toupper(c);
    if(c<'A' || c>'Z')         
        return(0);
    return(points[c-'A']);
}

Plate* Creation_Plateau (int nbLigne, int nbColone){
	
	int i,j;
	Plate* b;
	Lettre** Grille = malloc((nbLigne)*sizeof(Lettre));
	for(i=0;i<nbColone;i++){
		Grille[i] = malloc((nbColone+1)*sizeof(Lettre));
	}
	b = malloc(sizeof(Plate));
	b->Grille = Grille;

	for(i=0;i<nbLigne;i++){
		for (j=0;j<nbColone;j++){
			Lettre l;
			l.c = LettreAlea();
			l.x = i;
			l.y = j;
			l.score = Score_lettre(l.c);
			l.bns = 0;
			Grille[i][j] = l;
		}
	}
	b->nbligne = nbLigne;
	b->nbcolone = nbColone;
	b->score = 0;
	b->scoreMax = 0;

	return b;
}

void Delete_Board(Plate* b){
	int i;

	for(i=0;i<b->nbcolone;i++){
		free(b->Grille[i]);
	}
	free(b->Grille);
	free(b);
}

void Afficher_Grille(Plate* b){
	int i,j;

	for(i=0;i<(b->nbligne);i++){
		for(j=0;j<(b->nbcolone);j++){
			printf(" %c", b->Grille[i][j].c);
		}
		printf("\n");
	}
}

Plate* Affectation_Bonus(Plate* b){

	int nbBonus = (int)(0.35*(b->nbligne*b->nbcolone));
	int i;

	for(i=0;i<nbBonus;i++){
		int l = rand_a_b(0,b->nbligne-1);
		int c = rand_a_b(0,b->nbcolone-1);
		b->Grille[l][c].bns = rand_a_b(2,5);
	}

	return b;
}

int Calcul_score(MotTrouver* listeMot, int taille_listeMot){

	int i,j,k,pts = 0;

	for(i=0;i<taille_listeMot;i++){
		for(j=0;j<listeMot[i].taille;j++){
			//ajout des point des lettres
			pts += listeMot[i].l[j].score;
			if(listeMot[i].l[j].bns == 2){
				//ajout lettre double
				pts += listeMot[i].l[j].score;
			}else if(listeMot[i].l[j].bns == 3){
				//ajout lettre triple
				pts += listeMot[i].l[j].score*2;
			}else if(listeMot[i].l[j].bns == 4){
				//ajout mot double
				for(k=0;k<listeMot[i].taille;k++){
					pts += listeMot[i].l[k].score;
				}
			}else if(listeMot[i].l[j].bns == 5){
				//ajout mot triple
				for(k=0;k<listeMot[i].taille;k++){
					pts += listeMot[i].l[k].score*2;
				}
			}
		}
	}

	for(i=0;i<taille_listeMot;i++){
		//Bonus de longueur du mot on ne vas pas plus loint car aucun mot francais ne dépasse 26 lettres
		if((listeMot[i].taille >=5)&&(listeMot[i].taille <=10)){
			pts += 5;
		}else if((listeMot[i].taille >=10)&&(listeMot[i].taille <=15)){
			pts += 10;
		}else if((listeMot[i].taille >=15)&&(listeMot[i].taille <=20)){
			pts += 15;
		}else if((listeMot[i].taille >=20)&&(listeMot[i].taille <=25)){
			pts += 20;
		}else if((listeMot[i].taille >=25)&&(listeMot[i].taille <=30)){
			pts += 25;
		}
	}

	return pts;
}

MotTrouver Ajout_Lettre_Mot(MotTrouver mot, Lettre le){

	mot.taille ++;
	mot.l = realloc(mot.l,((mot.taille)*sizeof(Lettre)));
	mot.l[mot.taille] = le;

	return mot;
}

int main(int argc, char** argv){

	srand(time(NULL));
	int nbLigne = 4;
	int nbColone = 4;

	Plate* board;
	printf("Chargement du plateau de Jeu\n");
	board = Creation_Plateau(nbLigne,nbColone);
	Afficher_Grille(board);
	board = Affectation_Bonus(board);

	printf("Chargement du Dictionnaire\n");
	FILE* fichier = NULL;
    char *mot = malloc(sizeof(char));
	char caracActuel;
	fichier = fopen("dico.txt", "r");

    arbre_t *a = creer_arbre();

	if(fichier != NULL){

        int cpt = 0;
        int sizeMot = 0;
        do{
            caracActuel = fgetc(fichier);
            sizeMot ++;
            if(caracActuel != '\n'){
                mot = realloc(mot,sizeMot);
                mot[sizeMot-1] = caracActuel;
            }else{
                cpt ++;

                ajouter_mot(a,mot);
                
                sizeMot = 0;
            }
            
        }while(caracActuel != EOF);
		
		fclose(fichier);

	}else{
		printf("Impossible d'ouvrir le fichier.\n");
	}

	printf("Recherche des solution de la grille\n");
	printf("Pour l'instant en commentaire\n");

	printf("Test\n");
	MotTrouver test;
	test.taille = 0;
	//test.l[0] = board->Grille[0][0];
	//test.l[1] = board->Grille[1][1];
	test = Ajout_Lettre_Mot(test,board->Grille[2][2]);
	printf("%c\n", test.l[0].c);

	Delete_Board(board);
}