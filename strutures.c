//variables globales 

instruction* Jeu_dinstruction;
instruction* code;
Resultat* addr;
int cycle;

//---------------------------------------------------

struct REGISTRE{
        int valeur;
        int etat;
        };
typedef struct REGISTRE registre;

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

//---------------------------------------------------

struct RESULTAT{
	int* valeur;
	char* nom;
	};
typedef struct RESULTAT resultat;
