
//variables globales

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
