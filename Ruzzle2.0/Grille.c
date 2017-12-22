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

void Ajout_Lettre_Mot(MotTrouver* mot[], int i, Lettre le){

	mot[i]->taille ++;
	printf("plop0\n");
	mot[i]->l = realloc(mot[i]->l,((mot[i]->taille)*sizeof(Lettre)));
	mot[i]->l[mot[i]->taille] = le;
}

void Ajout_mot_tableauMot(MotTrouver* listeMot[],MotTrouver* mot, int taille_listeMot){

	taille_listeMot++;
	printf("plop1\n");
	listeMot = realloc(listeMot,(taille_listeMot*sizeof(MotTrouver)));
	listeMot[taille_listeMot] = mot;
}

char* MotTrouver_To_String(MotTrouver* mot){
	char* tmp = malloc(mot->taille*sizeof(char));
	int i;
	for(i=0;i<mot->taille;i++){
		tmp[i] = mot->l[i].c;
	}
	return tmp;
}

void Concat_Tab_MotTouver(MotTrouver* listeMot1[], int taille1, MotTrouver* listeMot2[], int taille2){

	printf("plop2\n");
	listeMot1 = realloc(listeMot1,(taille1+taille2)*sizeof(MotTrouver));
	int i;

	for(i=taille1;i<=(taille1+taille2);i++){
		listeMot1[i] = listeMot2[i-taille1];
	}
}

void Resolve_Grille(arbre_t* a, Plate* b, MotTrouver* Rez[], int taille_Rez){

	int k,l;
	int taille2 = 0;

	for(k=0;k<b->nbligne;k++){
		for(l=0;l<b->nbcolone;l++){
			MotTrouver* mot[1];
			mot[0] = malloc(sizeof(MotTrouver));
			mot[0]->taille = 0;
			mot[0]->l = malloc(sizeof(Lettre));
			Ajout_Lettre_Mot(mot,0,b->Grille[k][l]);
			taille2 = Resolve_Grille_Partie_Recursive(mot,a,b,k,l);
			Concat_Tab_MotTouver(Rez,taille_Rez,mot,taille2);
		}

	}
}

/*
* 	Cette fonction créer 1 indice par possibilité de mot vérifié
*				C'est a dire que si les borne sont correct et que le mot 
*				est dans le dictionnaire alors on ajoute un indice au tableau
*	Ensuite on ajoute le Mot au tableau
*	Puis on relance la fonction en changeant i et j en fonction 
*				de la case ou on veut aller
*/
int Resolve_Grille_Partie_Recursive(MotTrouver* mot[], arbre_t* a, Plate* b, int i, int j){
	printf("plop0.1\n");
	int cpt = 0;
	//Case en dessous
	if(((i+1)>=0)&&((i+1)<=b->nbligne)){
		Ajout_Lettre_Mot(mot,cpt,b->Grille[i+1][j]);
		if(trouver_mot(a,MotTrouver_To_String(mot[0]))==1){
			Ajout_mot_tableauMot(mot,mot[cpt],cpt);
			cpt++;
			Resolve_Grille_Partie_Recursive(mot,a,b,i+1,j);
		}
	}
	//Case au dessus
	if(((i-1)>=0)&&((i-1)<=b->nbligne)){
		Ajout_Lettre_Mot(mot,cpt,b->Grille[i-1][j]);
		if(trouver_mot(a,MotTrouver_To_String(mot[0]))==1){
			Ajout_mot_tableauMot(mot,mot[cpt],cpt);
			cpt++;
			Resolve_Grille_Partie_Recursive(mot,a,b,i-1,j);
		}
	}
	//Case a droite
	if(((j+1)>=0)&&((j+1)<=b->nbcolone)){
		Ajout_Lettre_Mot(mot,cpt,b->Grille[i][j+1]);
		if(trouver_mot(a,MotTrouver_To_String(mot[0]))==1){
			Ajout_mot_tableauMot(mot,mot[cpt],cpt);
			cpt++;
			Resolve_Grille_Partie_Recursive(mot,a,b,i,j+1);
		}
	}
	//Case a gauche
	if(((j-1)>=0)&&((j-1)<=b->nbcolone)){
		Ajout_Lettre_Mot(mot,cpt,b->Grille[i][j-1]);
		if(trouver_mot(a,MotTrouver_To_String(mot[0]))==1){
			Ajout_mot_tableauMot(mot,mot[cpt],cpt);
			cpt++;
			Resolve_Grille_Partie_Recursive(mot,a,b,i,j-1);
		}
	}
	//Case en bas a droite
	if((((i+1)>=0)&&((i+1)<=b->nbligne))&&(((j+1)>=0)&&((j+1)<=b->nbcolone))){
		Ajout_Lettre_Mot(mot,cpt,b->Grille[i+1][j+1]);
		if(trouver_mot(a,MotTrouver_To_String(mot[0]))==1){
			Ajout_mot_tableauMot(mot,mot[cpt],cpt);
			cpt++;
			Resolve_Grille_Partie_Recursive(mot,a,b,i+1,j+1);
		}
	}
	//Case en bas a gauche
	if((((i+1)>=0)&&((i+1)<=b->nbligne))&&(((j-1)>=0)&&((j-1)<=b->nbcolone))){
		Ajout_Lettre_Mot(mot,cpt,b->Grille[i+1][j-1]);
		if(trouver_mot(a,MotTrouver_To_String(mot[0]))==1){
			Ajout_mot_tableauMot(mot,mot[cpt],cpt);
			cpt++;
			Resolve_Grille_Partie_Recursive(mot,a,b,i+1,j-1);
		}
	}
	//Case en haut a gauche
	if((((i-1)>=0)&&((i-1)<=b->nbligne))&&(((j-1)>=0)&&((j-1)<=b->nbcolone))){
		Ajout_Lettre_Mot(mot,cpt,b->Grille[i-1][j-1]);
		if(trouver_mot(a,MotTrouver_To_String(mot[0]))==1){
			Ajout_mot_tableauMot(mot,mot[cpt],cpt);
			cpt++;
			Resolve_Grille_Partie_Recursive(mot,a,b,i-1,j-1);
		}
	}
	//Case en haut a droite
	if((((i-1)>=0)&&((i-1)<=b->nbligne))&&(((j+1)>=0)&&((j+1)<=b->nbcolone))){
		Ajout_Lettre_Mot(mot,cpt,b->Grille[i-1][j+1]);
		if(trouver_mot(a,MotTrouver_To_String(mot[0]))==1){
			Ajout_mot_tableauMot(mot,mot[cpt],cpt);
			cpt++;
			Resolve_Grille_Partie_Recursive(mot,a,b,i-1,j+1);
		}
	}
	return cpt;
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
	MotTrouver* Rez[1];
	Rez[0] = malloc(sizeof(MotTrouver));
	Rez[0]->taille = 0;
	Rez[0]->l = malloc(sizeof(Lettre));
	Resolve_Grille(a,board,Rez,0);

	Delete_Board(board);
}