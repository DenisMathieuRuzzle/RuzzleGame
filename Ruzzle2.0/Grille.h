#ifndef _GRILLE_H_
#define _GRILLE_H_

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "Arbre.h"

typedef struct _lettre Lettre;
struct _lettre{
	char c;
	int x;
	int y;
	int score;
	int bns;
};

typedef struct _MotTrouver MotTrouver;
struct _MotTrouver{
	Lettre* l;
	int taille;
};

typedef struct _plate Plate;
struct _plate {
	Lettre** Grille;
	int nbligne;
	int nbcolone;
	int score;
	int scoreMax;
};

char LettreAlea ();
int rand_a_b(int a, int b);
int Score_lettre(char c);
Plate* Creation_Plateau (int nbLigne, int nbColone);
void Delete_Board(Plate* b);
void Afficher_Grille(Plate* b);
Plate* Affectation_Bonus(Plate* b);
int Calcul_score(MotTrouver* listeMot, int taille_listeMot);
void Ajout_Lettre_Mot(MotTrouver* mot[], int i, Lettre le);
void Ajout_mot_tableauMot(MotTrouver* listeMot[],MotTrouver* mot, int taille_listeMot);
char* MotTrouver_To_String(MotTrouver* mot);
void Concat_Tab_MotTouver(MotTrouver* listeMot1[], int taille1, MotTrouver* listeMot2[], int taille2);
void Resolve_Grille(arbre_t* a, Plate* b, MotTrouver* Rez[], int taille_Rez);
int Resolve_Grille_Partie_Recursive(MotTrouver* mot[], arbre_t* a, Plate* b, int i, int j);

#endif		/* _Grille_H_*/