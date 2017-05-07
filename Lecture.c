#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include "structures.h"

#define MAXBUF 20
#define NB_REG 32

instruction* code;
registre R[NB_REG];
/*
	code[i]->OPcode = new_opcode(tmp);
	code[i]->r1 = reg1;
	code[i]->r2 = reg2;
	code[i]->r3 = reg3;
	code[i]->res = res;
	code[i]->jump = j;
 */

//Prototypes des fonctions
int lecture(char *cheminFichierCode, instruction *memoire);
int stockage(char* ligne, int num_ligne);
int verification(char* mot, int num_mot,int num_ligne);
void affiche_test(int nombre_lignes)
{
	printf("affichage instructions : \n");
	for(int i = 0;i< nombre_lignes;i++)
	{
		printf("#%d ",i);
		printf("%s ",code[i].OPcode);
		if(code[i].r1!= -1)
			printf("R%d ",code[i].r1);
		if(code[i].r2!= -1)
			printf("R%d ",code[i].r2);
		if(code[i].r3!= -1)
			printf("R%d ",code[i].r3);
		if(strcmp(code[i].res,"default")!= 0)
			printf("%s ",code[i].res);
		if(code[i].jump != 4)	
			printf("%d ",code[i].jump);
		printf("\n");
	}
}
void init_chaine(char tmp[MAXBUF])
{
	int i;
	for(i=0;i<MAXBUF;i++)
	{
		tmp[i] = '\0'; // \0 represente la fin d'une chaine
	}
}

resultat init_resultat()
{
	resultat res;
	res.valeur = 0;
	res.nom = "default";
	return res;
}

instruction init_instr()
{
	instruction instr;
	instr.OPcode = "\0";
	instr.r1 = -1;
	instr.r2 = -1;
	instr.r3 = -1;
	instr.res = "\0";
	instr.jump = 4;
	return instr;
}
//Main
int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("Erreur, chemin fichier non fourni en argument\n");
	}
	else
	{
		code = malloc(100 *sizeof(instruction));
		lecture(argv[1], code);
	}
    return 0;
}

/*Fonction lecture
 * Renvoie 1 si la lecture aboutie, sinon 0.
 * cheminFichierCode est le chemin jusqu'au fichier à lire.
 * memoire est un tableau d'instruction qu'on initialise en lisant
 * ligne par ligne le code fourni à la fonction.
 *
 * On va lire le code ligne par ligne et vérifier que chaque ligne
 * lue est correcte par rapport au jeu d'instruction en appellant
 * la fonction vérification qui contient le tableau jeu d'instruction
 * une foi la vérification effectué on enregistre grâce à la fonction
 * stockage dans le tableau d'instruction memoire.
 *
 * Si une erreur est détecté on envoie un message d'erreur et on vide le
 * tableau memoire.
 */
int lecture(char *cheminFichierCode, instruction *memoire){
	int fichier;
	int i = 0;
	int j = 0;
  char c = '0'; 
	char ligne[MAXBUF];
	fichier = open(cheminFichierCode,O_RDONLY);
    init_chaine(ligne); // init permet d'initiliser les char*
    while(read(fichier,&c,1))// read renvoi 0 en fin de fichier
    {                       // donc tant qu'on y est pas on lit le fichier
      while(c != '\n')      // tant qu'on reste dans une meme ligne
      {
        ligne[i] = c;     // on ajoute carac par carac à ligne
        read(fichier,&c,1);
        i++;
      }
    //  ## operations pour separer la ligne ##
      //~ printf("ligne %d : \n%s \n",j,ligne);
     if(!stockage(ligne,j))
		{
			//~ printf("Appelez les hendek \n");
			return 0;
		}
    //  ## on reinitialise pour passer a la ligne suivante##
      init_chaine(ligne);
      i = 0;
      j++;
    }
		close(fichier);
		affiche_test(j);
    return 1;
}

/* Fonction verification
 * Renvoie 1 si la vérification est bonne, sinon 0.
 *
 *
 *
 */
int verification(char* mot, int num_mot,int num_ligne){
	char cc[MAXBUF]; int tmp = 0 ;int i = 0;
	init_chaine(cc);
	if(num_mot == 0) // entree Opcode
	{   
		//~ printf("debug opcode : %s \n",mot);
		if(strcmp(mot,"ADD")==0||strcmp(mot,"SUB")==0||strcmp(mot,"LW")==0||strcmp(mot,"SW")==0||strcmp(mot,"MULT")==0||strcmp(mot,"SLT")==0||strcmp(mot,"BNEZ")==0)
		{
			code[num_ligne].OPcode=malloc(MAXBUF);
			strcpy(code[num_ligne].OPcode,mot);
			return 1;
		}
		
	}
	
	if(num_mot > 0 && num_mot < 4)
	{	// ADD, SUB, MULT et SLT
		//~ printf("debug %s l%d m%d \n",code[num_ligne].OPcode,num_ligne,num_mot);
		if(strcmp(code[num_ligne].OPcode,"ADD")==0 || strcmp(code[num_ligne].OPcode,"SUB")==0 || strcmp(code[num_ligne].OPcode,"MULT")==0 || strcmp(code[num_ligne].OPcode,"SLT")==0)
		{	//entree registres 
			//~ printf("debug mot : %s \n",mot);
			//~ printf("debug mot[3]:%c mot[0]:%c mot[1]:%c mot[2]:%c \n",mot[3],mot[0],mot[1],mot[2]);
			if(mot[3] == '\0')	
			  //~ printf("mot 3 == 0 \n");
			if(mot[3] == '\0' && mot[0] == 'R' && isdigit(mot[1]) && (isdigit(mot[2]) || mot[2] == '\0'))
			{
				cc[0] = mot[1]; 
				cc[1]= mot[2];
				tmp = atoi(cc);
				if(tmp < NB_REG)
				{
					//~ printf("debug YOLOSWAG \n");
					if(num_mot == 1)
						code[num_ligne].r1 = tmp;
					if(num_mot == 2)
						code[num_ligne].r2 = tmp;
					if(num_mot == 3)
						code[num_ligne].r3 = tmp;
					return 1;
				}
			}
		} // LW et SW
		if(strcmp(code[num_ligne].OPcode,"LW")==0 ||strcmp(code[num_ligne].OPcode,"SW")==0 )
		{
			if(num_mot == 1) // registre 1
			{
				if(mot[3] == '\0' && mot[0] == 'R' && isdigit(mot[1])&& (isdigit(mot[2]) || mot[2] =='\0'))
				{
					cc[0] = mot[1]; 
					cc[1]= mot[2];
					tmp = atoi(cc);
					if(tmp < NB_REG)
					{
						code[num_ligne].r1 = tmp;
						return 1;
					}
				}
			}
			if(num_mot == 2) //addresse
			{
				code[num_ligne].res = mot;
				return 1;
			}
		} // BNEZ
		if(strcmp(code[num_ligne].OPcode,"BNEZ")==0)
		{
			if(num_mot == 1) // registre 1
			{
				if(mot[3] == '\0' && mot[0] == 'R' && isdigit(mot[1]) && (isdigit(mot[2]) || mot[2] =='\0'))
				{
					cc[0] = mot[1]; 
					cc[1]= mot[2];
					tmp = atoi(cc);
					if(tmp < NB_REG)
					{
						code[num_ligne].r1 = tmp;
						return 1;
					}
				}
			}
			if(num_mot == 2) //saut
			{
				if(mot[0] == '-' ||isdigit(mot[0]))
				{
					i = 1; 
					while(mot[i] != '\0')
					{
						if(!isdigit(mot[i]))
							return 0;
						i++;
					}
					tmp = atoi(mot);
					if(tmp % 4 ==0)
					{
						code[num_ligne].jump = tmp;
						return 1;
					}
				}
			}
		}
	}
		
	return 0;
}

/* Fonction stockage
 * Renvoie 1 si l'instruction a bien été stockée, sinon 0
 *
 *
 *
 *
 */

int stockage(char* ligne, int num_ligne){
	  code[num_ligne] = init_instr();
	  char tmp[MAXBUF];
	  int k = 0;
	  int i = 0;  int num_mot = 0;
      init_chaine(tmp);
      while(ligne[k]!='\0')//on s arrette en fin de ligne
      {
        while(ligne[k] !=' ' && ligne[k]!= '\0') //double securitée
        {
          tmp[i] = ligne[k]; // on stock dans un tmp les caracs du mot en cours
          k++;  i++;         // De lecture
        }
        // on met le mot dans le champ de la structure voulue
        //~ printf("tmp : %s \n",tmp);
		if(!verification(tmp,num_mot,num_ligne))
		{
			printf("Code Seerk \n");
			return 0;
		}
        // on passe au "mot" suivant
        i = 0;
        k++; num_mot ++;
        init_chaine(tmp);
      }
      return 1;
}
