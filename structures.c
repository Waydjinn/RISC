// defines

#define NB_REG 32
//variables globales

instruction* code;
Resultat* addr;

int cycle[2];

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
//Constructeurs 
instruction init_instr()
{
	instruction instr;
	instr.OPcode = "\0";
	instr.r1 = -1;
	instr.r2 = -1;
	instr.r3 = -1;
	instr.res = init_resultat();
	instr.jump = 4;
	return instr;
}

resultat init_resultat() //initialisation resultats
{
	resultat res;
	res.valeur = malloc(10 * sizeof(int));
	res.valeur[0] = 0;
	res.nom = malloc(MAXBUF);
	init_chaine(res.nom);
	return res;
}



