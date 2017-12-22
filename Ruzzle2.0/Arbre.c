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