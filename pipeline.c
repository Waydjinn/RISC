#include "pipeline.h"

//##################Pipeline#################

instruction* code;
resultat* addr;
int cycle[2];
registre tabreg[NB_REG];

//Prototypes des fonctions
void etatReg(instruction * code, char *OPCODE, int numInst, int state);
void avancement(int numLigne, int tab[5][5]);
int verifReg(instruction * code, char * OPCODE, int numInst);
void affiche(int tab[5][5]);
int pipeline(instruction * code, int cp);
void appel(instruction * code, char *OPCODE, int numInst);
int finition(int tab[5][5]);
void init_mutex(int* mutex);


/* La fonction etatReg permet de modifier l'état des registres
 * correspondant à l'instruction qui vient de finir ou de commencer dans
 * le pipeline. On met l'état des regsitre à 0 quand ils sont libre et 
 * 1 quand ils sont occupés
 * Le paramètre code vient de pipeline et est la variable globale code 
 * le tableau d'instruction, le paramètre OPCODE vient de pipeline est 
 * représente le type de l'instruction qui demande de modifier l'état des registre,
 * le paramètre numInst vient de pipeline et permet de connaitre l'instruction
 * à traité (ici on traite les registres de cette instruction) et le paramètre
 * state représente l'état dans lequel on souhaite mettre le pipeline.
 */ 
void etatReg(instruction * code, char *OPCODE, int numInst, int state)
{
	//printf("flag\n");
	if((strcmp(OPCODE, "ADD") == 0)||(strcmp(OPCODE, "MULT") == 0)||(strcmp(OPCODE, "SLT") == 0)){
		tabreg[code[numInst].r1].etat = state;
		tabreg[code[numInst].r2].etat = state;
		tabreg[code[numInst].r3].etat = state;
	}
	if((strcmp(OPCODE, "SW") == 0)||(strcmp(OPCODE, "LW") == 0)){
		tabreg[code[numInst].r1].etat = state;
		tabreg[code[numInst].r2].etat = state;
	}
	if(strcmp(OPCODE, "BNEZ") == 0){
		tabreg[code[numInst].r1].etat = state;
	}
}

/* La fonction avancement permet remettre la ligne du tableau d'avancement
 * du pipeline d'une instruction terminé à -1
 * Elle est utilisée dans la fonction pipeline
 * Cette fonction est nécessaire pour le bon déroulement des vérifications
 * et des appels d'UAL dans le fonction pipeline
 * On utilise donc le paramètre cp fourni par le pipeline afin de déterminer
 * là ligne à réinitialisé et le paramètre tab[5][5] fourni par pipeline qui 
 * est le tableau d'avancement du pipeline
 */ 
void avancement(int numLigne, int tab[5][5])
{
	int i;
	for(i = 1; i < 5; i++)
		{
            tab[numLigne][i] = -1;
		}
}

/* Cette fonction à été crée pour facilité l'appel des fonction UAL et rendre le code
 * plus lisible en évitant de multiples boucle if, elle est utilisés dans la fonction pipeline
 * On appel donc la fonction UAL correspondant au paramètre OPCODE
 * et avec les registre qu'on obtient grâce aux paramètres code et numInst
 */ 
void appel(instruction * code, char *OPCODE, int numInst)
{
	if(strcmp(OPCODE, "ADD") == 0)
	{
		ADD(&tabreg[code[numInst].r1],&tabreg[code[numInst].r2],&tabreg[code[numInst].r3]);
	}
	if(strcmp(OPCODE, "MULT") == 0)
	{
		MULT(&tabreg[code[numInst].r1],&tabreg[code[numInst].r2],&tabreg[code[numInst].r3]);
	}
	if(strcmp(OPCODE, "SLT") == 0)
	{
		SLT(&tabreg[code[numInst].r1],&tabreg[code[numInst].r2],&tabreg[code[numInst].r3]);
	}
	if(strcmp(OPCODE, "LW") == 0)
	{
		LW(&tabreg[code[numInst].r2],code[numInst].res,&tabreg[code[numInst].r1]);
	}
	if(strcmp(OPCODE, "SW") == 0)
	{
		SW(&tabreg[code[numInst].r2],code[numInst].res,&tabreg[code[numInst].r1]);
	}
}

/* Cette fonction permet de vérifier si les registres sont disponibles 
 * pour l'instruction qui en a besoin elle renvoie 1 si les registres
 * sont disponibles et 0 dans le cas contraire.
 * Elle est utilisée par la fonction pipeline.
 * On récupère donc le tableau d'instruction code pour pouvoir vérfier 
 * les registre de la bonne instruction grace au paramètre numInst qui 
 * représente l'instruction qui nécessite la vérification, enfin le 
 * paramètre OPCODE permet de connaitre le type de l'instruction
 */ 
int verifReg(instruction * code, char * OPCODE, int numInst)
{
	if((strcmp(OPCODE, "ADD") == 0)||(strcmp(OPCODE, "MULT") == 0)||(strcmp(OPCODE, "SLT") == 0)){
		if(tabreg[code[numInst].r1].etat == 0 && tabreg[code[numInst].r2].etat == 0 && tabreg[code[numInst].r3].etat == 0)
		{
			return 1;
		}else return 0;
	}
	else if((strcmp(OPCODE, "SW") == 0)||(strcmp(OPCODE, "LW") == 0)){
		if(tabreg[code[numInst].r1].etat == 0 && tabreg[code[numInst].r2].etat == 0)
		{
			return 1;
		}else return 0;
	}
	else if(strcmp(OPCODE, "BNEZ") == 0){
		if(tabreg[code[numInst].r1].etat == 0)
		{
			return 1;
		}else return 0;
	}
	else
	{
		return 0;
	}
}

/* Cette fonction à été utilisé dans les phases de test pour vérifier
 * que l'avancement dans le tableau qui représente l'avancement du 
 * pipeline à chaque cycle s'effectu correctement. Elle sert à afficher
 * ce tableau d'avancement du pipeline
 * Cette fonction est utilisée dans la fonction pipeline
 */ 
void affiche_Pipeline(int tab[5][5])                                     
{
        int i,j;
        for (i=0;i<5;i++)
        {
                for(j=0;j<5;j++)
                {
                        printf(" tab[i][j] = %d ",tab[i][j]);
                }
                printf("\n");
        }
}
// Fonction pour passer les modulo negatif en modulo positif
//~ int mod(int a, int b)
//~ {
    //~ int r = a % b;
    //~ if (r >= 0){
		//~ return r;
	//~ }
	//~ return (r+b);
//~ }

//Cette fonction sert a initialiser les tableaux de booleen present dans la fonction pipeline 
void init_mutex(int* mutex)
{
	int i;
		for (i = 0; i < 5; i++)
	{
		mutex[i]=1;
	}
}

//Fonction qui execute et fais avancer les instruction présente dans le pipeline 
int finition(int tab[5][5])
{
	int i,cpt =0;
	int exec[5];
	init_mutex(exec);
	//printf("finition start \n");
	while ( tab[0][1] != -1 || tab[1][1] != -1 || tab[2][1] != -1 || tab[3][1] != -1 || tab[4][1] != -1 )
	{
		//affiche_Pipeline(tab);
		//printf("finition cycle + = %d \n",cpt);
		for (i=0;i<5;i++)
				{
					
					if(tab[i][4] == tab[i][1] && tab[i][4] != -1)
						{
							etatReg(code, code[tab[i][1]].OPcode,tab[i][1], 0);
							avancement(i,tab);
							tab[i][0] =1;
							exec[i]=1;
						}
					if(tab[i][2] == tab[i][1] && exec[i]==1 && tab[i][2] != -1)
						{
							appel(code,code[tab[i][1]].OPcode,tab[i][1]);
							exec[i]=0;
						}
					if( tab[i][1] != -1)
						{
							tab[i][tab[i][0]]= tab[i][1];
							tab[i][0]++;
						}
				}
				cpt++;
	}
	return cpt-1;
}

	
/* La fonction pipeline doit être initialement appellée avec une valeur de 0 pour le cp
 * le cp sera appelé à être modifier lors de l'apparition d'un BNEZ qui demande un retour
 * en arrière ou un saut en avant dans le code on appellera alors la fonction pipeline avec
 * le cp correspondant au saut du BNEZ.
 * 
 * Cette fonction récupère les instructions à exécuter (toutes les instructions font 4 cycle 
 * dans le pipeline) et à chaque foi qu'une instruction à fait ses 4 cycles elle est exécutée,
 * elle incrémente la variable globale cycle à chaque cycle effectué et se sert du tableau de registre
 * global tabreg et elle récupère les instructions dans la variable globale code
 */ 
int pipeline(instruction * code, int cp)
{
    int bool = 1;
    int mutex[5];
    int exec[5];
    int i,j;
    int pipeTab[5][5]; //Tableau qui représente l'avancement du pipeline
	//Initialisation du pipeline à -1
    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5; j++)
        {
            if(j == 0 )
            {
				pipeTab[i][j] = 1; 
            }
            else
            {
				pipeTab[i][j] = -1;
			}
		}
	}
	//initialisation des tableaux de bool
    init_mutex(mutex);
    init_mutex(exec);
   // printf("le cp est egale a %d\n",cp);
    while (strcmp(code[cp].OPcode, "END") != 0) //END représente la fin du code
    {
        if(strcmp(code[cp].OPcode, "BNEZ") != 0)//BNEZ est un cas spéciale a traiter
        {
			//affiche_Pipeline(pipeTab); 
			//printf("Instruction %d\n", cp);
			for (i=0;i<5;i++)
				{
					if(pipeTab[i][1] == -1 && bool ==1 )//on regarde si on peut charger une instruction dans le pipeline 
						{
							if(verifReg(code, code[cp].OPcode, cp) == 1)//on verifie si les registre de l'instruction qui va être chargé sont disponible 
								{
									pipeTab[i][1] = cp;
									pipeTab[i][0]++;
									bool =0;
									mutex[i]=0;
									etatReg(code, code[cp].OPcode, cp, 1);//on change l'etat des registres
								}
								else
								{
									bool = 0;//on bloque les autres chargements on attend que l'instruction se termine 
									cp --;
								}
						}
					if(pipeTab[i][4] == pipeTab[i][1] && pipeTab[i][4] != -1) // si une instruction est arrivé au bout du pipeline on reinitialise la ligne du pipeline et on libère les registres
						{
							etatReg(code, code[pipeTab[i][1]].OPcode,pipeTab[i][1], 0);
							avancement(i,pipeTab);
							pipeTab[i][0] =1;
							exec[i]=1;
						}
					if(pipeTab[i][2] == pipeTab[i][1] && exec[i]==1 && pipeTab[i][2] != -1) // L'instruction arrive la deuxieme case du pipeline qui correspond a l'execution de l'instruction dans notre cas 
						{
							appel(code,code[pipeTab[i][1]].OPcode,pipeTab[i][1]);
							exec[i]=0;
						}
					if( mutex[i]==1 && pipeTab[i][1] != -1)// l'instruction avance dans le pipeline 
						{
							pipeTab[i][pipeTab[i][0]]= pipeTab[i][1];
							pipeTab[i][0]++;
						}
				}
			bool = 1;
			init_mutex(mutex);;
            cycle[1] ++;
            cp ++;
           }
				else 
           {
				//printf(" Appel BNEZ PRE FINITION \n");  // Lors de l'appel du BNEZ on stop les chargements 
                cycle[1] =cycle[1]+finition(pipeTab)+4; // on execute les instructions au dessus du BNEZ en ajoutant le temps d'execution du BNEZ
                cp += BNEZ(&tabreg[code[cp].r1],code[cp].jump); 
                //printf(" Appel BNEZ POST FINITION \n");
                return pipeline(code,cp); // On réappel un pipeline avec le nouveau CP
           }        
       }
	cycle[1] =cycle[1]+finition(pipeTab);// on attend que toute les instructions se terminent .
	return 0;    
}

