#include "Arbre.h"

// Cette fonction retourne
// 0 à 25 si c == 'a' à 'z'
// 26 si c == '\0' (ou autre chose)
unsigned char2index(const char c){
	char c_lower;
	if(isalpha(c)){
		c_lower = tolower(c); // convention : on met tout en minuscule
		return (c - 'a');
	}
	return NB_CARACTERE;
}

// Crée un noeud et remplit la lettre qu'il stocke
noeud_t *creer_noeud(const char c){
	noeud_t *n = (noeud_t *)malloc(sizeof(noeud_t));
	n->lettre = c;
	// calloc permet d'initialiser directement chaque n->fils[i] à NULL
	n->fils = (noeud_t **)calloc((NB_CARACTERE+1),sizeof(noeud_t *));
	return n;
}

arbre_t *creer_arbre(){
	return creer_noeud('\0');
}

// Créé un noeud fils (si besoin) correspondant à une lettre
noeud_t *creer_fils(noeud_t *n,const char c){
	unsigned idx = char2index(c);
	if (!n->fils[idx]){
		n->fils[idx] = creer_noeud(c); // nouveau fils
	}
	return n->fils[idx];
}

// Ajoute un mot dans l'arbre étant donné sa racine
void ajouter_mot(arbre_t *a,const char *s){
	unsigned i,idx_cur,n = strlen(s);
	noeud_t *noeud_cur = a;
	for(i=0;i<n;++i){
		idx_cur = char2index(s[i]);
		noeud_cur = creer_fils(noeud_cur,s[i]);
	}
	creer_fils(noeud_cur,'\0');
}

// Supprime tout le sous arbre à partir d'un noeud n
void supprimer_sous_arbre(noeud_t *n){
	unsigned i;
	for(i=0;i<=NB_CARACTERE;++i){
		if (n->fils[i]) supprimer_sous_arbre(n->fils[i]);
		free(n->fils[i]);
	}
	free(n->fils);
}

// Supprime un arbre étant donné sa racine
void supprimer_arbre(arbre_t *a){
	supprimer_sous_arbre(a);
}

// Recherche si un mot figure dans un dictionnaire
int trouver_mot(const arbre_t *a,const char *s){
	unsigned i,idx_cur,n = strlen(s);
	const noeud_t *noeud_cur = a;
	for(i=0;i<n;++i){
		idx_cur = char2index(s[i]);
		if(!noeud_cur->fils[idx_cur]) return 0;
		else noeud_cur = noeud_cur->fils[idx_cur];
	}
	return 1;
}
/*
void afficherArbre(const arbre_t *a){
	printf("bla\n");
	const noeud_t *noeud_cur = a;
	int i=0;
	noeud_cur = noeud_cur->fils[i];
	while( i<15 ){
		printf("bla\n");

		char cur_c = noeud_cur->lettre;
		printf("%c\n|",cur_c );
		int j = 0;
		while(noeud_cur->fils[j] != NULL){
			char fils_c = noeud_cur->fils[j]->lettre; 
			printf("%c\n|",fils_c );
			j++;
		}
		noeud_cur = noeud_cur->fils[i];
		i++;
	}
}*/

void ajoute_medor(arbre_t *a,const char *s){
	printf("ajoute le mot %s",s);
	ajouter_mot(a,s);
}


void cherche_medor(const arbre_t *a,const char *s){
	int trouve = trouver_mot(a,s);
	printf("est ce que le dictionnaire contient %s ? %i\n",s,trouve);
}

/*int main(int argc, char** argv){

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
                printf("%s\n", mot);
                ajouter_mot(a,mot);
                
                sizeMot = 0;
            }
            
        }while((caracActuel != EOF)&&(cpt <=1));
		
		fclose(fichier);

	}else{
		printf("Impossible d'ouvrir le fichier.\n");
	}

	char* test = "tapissa";
	printf("Le mot %s est il dans le dictionaire : %d\n",test, trouver_mot(a,test));

	return 0;
}*/