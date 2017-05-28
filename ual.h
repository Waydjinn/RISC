#ifndef _UAL_H
#define _UAL_H

#include "structure.h"

//Prototypes des fonctions
int BNEZ(registre* a, int jump);
void ADD(registre* a, registre* b, registre* c);
void MULT(registre* a, registre* b, registre* c);
void LW(registre* val, resultat res, registre* a);
void SW(registre* val, resultat res, registre* a);
void SLT(registre* a, registre* b, registre* c);

#endif
