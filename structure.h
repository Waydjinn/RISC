#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <ctype.h>

//#################Structures#################

#define NB_REG 32
#define MAXBUF 20

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
	int r1;
	int r2;
	int r3;
	resultat res;
	int jump;
	};
typedef struct INSTRUCTION instruction;

//##################Globales#################

extern instruction* code;
extern resultat* addr;
extern  int cycle[2];
extern registre tabreg[NB_REG];

//Prototypes
void init_chaine(char tmp[MAXBUF]);
instruction init_instr();
resultat init_resultat();

#endif
