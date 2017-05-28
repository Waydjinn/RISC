#ifndef _ANALYSEURS_H
#define _ANALYSEURS_H

#include "structure.h"

//Prototypes des fonctions
int lecture(char *cheminFichierCode, instruction *memoire);
int stockage(char* ligne, int num_ligne);
int verification(char* mot, int num_mot,int num_ligne);
int verif_res(char* ligne,int num_ligne);
void affiche_res(int nombre_adr);
void affiche_inst(int nombre_lignes);
int research(char* chaine,char c);
void lire_ligne(char ligne[MAXBUF], int fichier);
int cherche_res(char* nom);

#endif
