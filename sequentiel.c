#include "sequentiel.h"

instruction* code;
resultat* addr;
int cycle[2];
registre tabreg[NB_REG];

//fonction pour initialiser les registres a 0
void init_reg(registre* reg)
{
	int i;
	for(i=0;i<NB_REG;i++)
	{
		reg[i].valeur=0;
		reg[i].etat=0;
	}
}
//Lit les instructions une par une , recupere l'op code et apelle la fonction UAL correspondante
void Sequentiel(instruction * Instruction)
{
	init_reg(tabreg);
	int cp=0;
	while (strcmp(Instruction[cp].OPcode, "END") != 0)
	{
		if(strcmp(Instruction[cp].OPcode, "ADD" ) == 0)
			{
				ADD(&tabreg[Instruction[cp].r1],&tabreg[Instruction[cp].r2],&tabreg[Instruction[cp].r3]);
				cycle[0] +=1;
				//printf("cp = %d  et OPcode = %s \n",cp,Instruction[cp].OPcode);
				cp++;
			}
		if(strcmp(Instruction[cp].OPcode, "MULT" ) == 0)
			{
				MULT(&tabreg[Instruction[cp].r1],&tabreg[Instruction[cp].r2],&tabreg[Instruction[cp].r3]);
				cycle[0] +=4;
				//printf("cp = %d  et OPcode = %s \n",cp,Instruction[cp].OPcode);
				cp++;
			}
		if(strcmp(Instruction[cp].OPcode, "LW" ) == 0)
			{
				LW(&tabreg[Instruction[cp].r2],Instruction[cp].res,&tabreg[Instruction[cp].r1]);
				cycle[0] +=2;
				//printf("cp = %d  et OPcode = %s \n",cp,Instruction[cp].OPcode);
				cp++;
			}
		if(strcmp(Instruction[cp].OPcode, "SW" ) == 0)
			{
				SW(&tabreg[Instruction[cp].r2],Instruction[cp].res,&tabreg[Instruction[cp].r1]);
				cycle[0] +=2;
				//printf("cp = %d  et OPcode = %s \n",cp,Instruction[cp].OPcode);
				cp++;
			}
		if(strcmp(Instruction[cp].OPcode, "SLT" ) == 0)
			{
				SLT(&tabreg[Instruction[cp].r1],&tabreg[Instruction[cp].r2],&tabreg[Instruction[cp].r3]);
				cycle[0] +=1;
				//printf("cp = %d  et OPcode = %s \n",cp,Instruction[cp].OPcode);
				cp++;
			}
		if(strcmp(Instruction[cp].OPcode, "BNEZ" ) == 0)
			{
				//printf("cp = %d  et OPcode = %s \n",cp,Instruction[cp].OPcode);
				cp += BNEZ(&tabreg[Instruction[cp].r1],Instruction[cp].jump);
				//printf("New cp = %d \n",cp);
				cycle[0]+=1;
			} 

	}
}

