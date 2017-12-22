#ifndef _ARBRE_H_
#define _ARBRE_H_

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define NB_CARACTERE 26

typedef struct noeud{
	char lettre;
	struct noeud **fils;
} noeud_t;

typedef noeud_t arbre_t;

unsigned char2index(const char c);
noeud_t *creer_noeud(const char c);
arbre_t *creer_arbre();
noeud_t *creer_fils(noeud_t *n,const char c);
void ajouter_mot(arbre_t *a,const char *s);
void supprimer_sous_arbre(noeud_t *n);
void supprimer_arbre(arbre_t *a);
int trouver_mot(const arbre_t *a,const char *s);
//void afficherArbre(const arbre_t *a);
void ajoute_medor(arbre_t *a,const char *s);
void cherche_medor(const arbre_t *a,const char *s);

#endif		/* _Grille_H_*/