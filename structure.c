// defines
#include "structure.h"

instruction* code;
resultat* addr;
int cycle[2];
registre tabreg[NB_REG];

void init_chaine(char tmp[MAXBUF])
{
	int i;
	for(i=0;i<MAXBUF;i++)
	{
		tmp[i] = '\0'; // \0 represente la fin d'une chaine
	}
}

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
	res.valeur = malloc(10000 * sizeof(int));
	res.valeur[0] = 0;
	res.valeur[1] = -1;
	res.nom = malloc(MAXBUF);
	init_chaine(res.nom);
	return res;
}

