#ifndef _PIPELINE_H
#define _PIPELINE_H
#include "analyseurS.h"
#include "sequentiel.h"
#include "ual.h"


//Prototypes des fonctions
void etatReg(instruction * code, char *OPCODE, int numInst, int state);
void avancement(int cp, int tab[5][5]);
int verifReg(instruction * code, char * OPCODE, int numInst);
void affiche(int tab[5][5]);
int pipeline(instruction * code, int cp);
void appel(instruction * code, char *OPCODE, int numInst);
int appelBNEZ(instruction * code, int numInst);
void init_mutex(int* mutex);

#endif
