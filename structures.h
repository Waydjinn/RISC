#ifndef _STRUCTURES_H
#define _STRUCTURES_H


//#################Structures#################


struct REGISTRE{
        int valeur;
        int etat;
        };
typedef struct REGISTRE registre;

//---------------------------------------------------

struct RESULTAT{
	int* valeur;
	char* nom;
	};
typedef struct RESULTAT resultat;

//---------------------------------------------------

struct INSTRUCTION{
	char* OPcode;
	registre r1;
	registre r2;
	registre r3;
	resultat res;
	int jump;
	};
typedef struct INSTRUCTION instruction;

//##################Globales#################

extern instruction* Jeu_dinstruction;
extern instruction* code;
extern resultat* addr;
extern  int cycle;

#endif
