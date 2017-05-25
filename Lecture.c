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

instruction* code;
resultat* addr;

//Prototypes des fonctions
int cherche_res(char* nom);
void init_chaine(char tmp[MAXBUF]);
int lecture(char *cheminFichierCode, instruction *memoire);//principale
void lire_ligne(char ligne[MAXBUF], int fichier);
int research(char* chaine,char c);
int stockage(char* ligne, int num_ligne); //principale
int verification(char* mot, int num_mot,int num_ligne); //principale
int verif_res(char* ligne,int num_ligne);

//Fonctions d'affichages pour tests, décommenter pour test individuels
//~ void affiche_res(int nombre_adr) 
//~ {
	//~ printf("affichage addr : \n");
	//~ for(int i = 0;i<=nombre_adr;i++)
	//~ {
		//~ printf("@%s = %d \n",addr[i].nom,addr[i].valeur[0]);
	//~ }
//~ }

//~ void affiche_inst(int nombre_lignes)
//~ {
	//~ printf("affichage instructions : \n");
	//~ for(int i = 0;i<= nombre_lignes;i++)
	//~ {
		//~ printf("#%d ",i);
		//~ printf("%s ",code[i].OPcode);
		//~ if(strcmp(code[i].OPcode,"ADD")==0 ||strcmp(code[i].OPcode,"MUL")==0||strcmp(code[i].OPcode,"SLT")==0)
			//~ printf("R%d,R%d,R%d ",code[i].r1,code[i].r2,code[i].r3);
		//~ if(strcmp(code[i].OPcode,"LW")==0)
			//~ printf("R%d,@%s[%d] ",code[i].r1,code[i].res.nom,code[i].r2);
		//~ if(strcmp(code[i].OPcode,"SW")==0)
			//~ printf("@%s[R%d],R%d ",code[i].res.nom,code[i].r2,code[i].r1);
		//~ if(strcmp(code[i].OPcode,"BNEZ")==0)
			//~ printf("R%d,%d",code[i].r1,code[i].jump);
		//~ printf("\n");
	//~ }
//~ }

//~ //Main
//~ int main(int argc, char *argv[])
//~ {
	//~ if(argc < 2)
	//~ {
		//~ printf("Erreur, chemin fichier non fourni en argument\n");
	//~ }
	//~ else
	//~ {
		//~ code = malloc(100 *sizeof(instruction));
		//~ addr = malloc(100 *sizeof(resultat));
		//~ lecture(argv[1], code);
		//~ free(code);free(addr);
	//~ }
    //~ return 0;
//~ }
int cherche_res(char* nom){
	int i = 0;
	while(addr[i].nom != NULL)
	{
		if(strcmp(addr[i].nom,nom)==0)
			return i;
		i++;
	}
	return -1;
}

void init_chaine(char tmp[MAXBUF]){
	int i;
	for(i=0;i<MAXBUF;i++)
	{
		tmp[i] = '\0'; // \0 represente la fin d'une chaine
	}
}

int lecture(char *cheminFichierCode, instruction *memoire){
	int fichier;
	int i = 0;
	int nbadr = 0; 	// variable utilisée pour les tests
	int j = 0;
	char c = '0'; 
	char ligne[MAXBUF];
	char next[MAXBUF]; init_chaine(next);
	fichier = open(cheminFichierCode,O_RDONLY);	
	lire_ligne(ligne,fichier);
	lire_ligne(next,fichier);
	while(strlen(next)!=0)
	{
		if(!verif_res(ligne,j))
		{
			//A DECOMMENTER POUR TEST
			//~ printf("ERREUR RESULTAT \n");
			return 0;
		}
		init_chaine(ligne);
		strcpy(ligne,next);
		lire_ligne(next,fichier);
		j++;
	}
	if(!verif_res(ligne,j))
			return 0;
	nbadr =  j;
////////////////////////////////////////////////////////////////////////
    c = '0'; j = 0;
    init_chaine(ligne); // init permet d'initiliser les char*
    while(read(fichier,&c,1))// read renvoi 0 en fin de fichier
    {                  
      i = 0;
      while(c != '\n')      // tant qu'on reste dans une meme ligne
      {
        ligne[i] = c;     // on ajoute carac par carac à ligne
        read(fichier,&c,1);
        i++;
      }
    //  ## operations pour separer la ligne ##
     if(!stockage(ligne,j))
		{
			// A DECOMMENTER POUR TEST
			//~ printf("Erreur Stockage \n");
			return 0;
		}
    //  ## on reinitialise pour passer a la ligne suivante##
      init_chaine(ligne);
      i = 0;
      j++;
    }
		code[j] = init_instr(); //opcode de fin
		code[j].OPcode = "END"; 
		close(fichier);
		// A DECOMMENTER POUR TEST 
		//~ affiche_res(nbadr);
		//~ affiche_inst(j);
    return 1;
}

void lire_ligne(char ligne[MAXBUF], int fichier){
	int i = 0;
	char c = '\n';
	init_chaine(ligne);
		read(fichier,&c,1);
		while(c != '\n')      // tant qu'on reste dans une meme ligne
      {
        ligne[i] = c;     // on ajoute carac par carac à ligne
        if(!read(fichier,&c,1))
			break;
        i++;
      }
}

int research(char* chaine,char c){
	for(int i =0;i<=strlen(chaine);i++)
	{
		if(chaine[i] == c)
			return i;
	}
	return -1;
}

int stockage(char* ligne, int num_ligne){
	  code[num_ligne] = init_instr();
	  char tmp[MAXBUF];
	  int k = 0;
	  int i = 0;  int num_mot = 0;
      init_chaine(tmp);
      while(ligne[k]!='\0')//on s arrette en fin de ligne
      {
        while(ligne[k] !=' ' && ligne[k] !=',' && ligne[k]!= '\0' ) //double securitée
        {
          tmp[i] = ligne[k]; // on stock dans un tmp les caracs du mot en cours
          k++;  i++;         // De lecture
        }
        // on met le mot dans le champ de la structure voulue
		if(!verification(tmp,num_mot,num_ligne))
		{
			// A DECOMMENTER POUR TESTS
			//~ printf("Erreur Verif \n");
			return 0;
		}
        // on passe au "mot" suivant
        i = 0;
        k++; num_mot ++;
        init_chaine(tmp);
      }
      return 1;
}

int verification(char* mot, int num_mot,int num_ligne){
	char cc[MAXBUF]; int tmp = 0 ;int i = 0;
	init_chaine(cc);
	if(num_mot == 0) // entree Opcode
	{   
		if(strcmp(mot,"ADD")==0||strcmp(mot,"LW")==0||strcmp(mot,"SW")==0||strcmp(mot,"MUL")==0||strcmp(mot,"SLT")==0||strcmp(mot,"BNEZ")==0)
		{
			code[num_ligne].OPcode=malloc(MAXBUF);
			strcpy(code[num_ligne].OPcode,mot);
			return 1;
		}
		
	}
	
	if(num_mot > 0 && num_mot < 4)
	{	
		// ADD, MUL et SLT
		if(strcmp(code[num_ligne].OPcode,"ADD")==0 ||strcmp(code[num_ligne].OPcode,"MUL")==0 || strcmp(code[num_ligne].OPcode,"SLT")==0)
		{	//entree registres 
			if(mot[3] == '\0' && mot[0] == 'R' && isdigit(mot[1]) && (isdigit(mot[2]) || mot[2] == '\0'))
			{
				cc[0] = mot[1]; 
				cc[1]= mot[2];
				tmp = atoi(cc);
				if(tmp <= NB_REG)
				{
					if(num_mot == 1)
						code[num_ligne].r1 = tmp;
					if(num_mot == 2)
						code[num_ligne].r2 = tmp;
					if(num_mot == 3)
						code[num_ligne].r3 = tmp;
					return 1;
				}
			}
		} // LW 
		if(strcmp(code[num_ligne].OPcode,"LW")==0)
		{
			if(num_mot == 1) // registre 1
			{
				if(mot[3] == '\0' && mot[0] == 'R' && isdigit(mot[1])&& (isdigit(mot[2]) || mot[2] =='\0'))
				{
					cc[0] = mot[1]; 
					cc[1]= mot[2];
					tmp = atoi(cc);
					if(tmp <= NB_REG)
					{
						code[num_ligne].r1 = tmp;
						return 1;
					}
				}
			}
			if(num_mot == 2) //addresse
			{
				if(mot[0]=='@' && isalpha(mot[1])) //une addresse est
				{								 //definie ainsi : @NOM[R_NUM_]
					for(int i=0;i<strlen(mot);i++) // on enleve le @ pour traiter le reste
						mot[i] = mot[i+1];
					int pos1 = research(mot,'['); //on recherche si y a des crochets 
					int pos2 = research(mot,']'); // dans le mot
					int dist = pos2 - pos1; //on verifie leur position
					if((pos1 == -1 || pos2 ==-1 || dist < 3 || dist > 4))
						return 0;	
					if(mot[pos1+1] !=  'R' || mot[pos2+1] != '\0')
						return 0;
					for(int h=2;h<dist;h++)
					{	
						if(!isdigit(mot[pos1+h])) //si un carac n'est pas un digit 
							return 0;
						cc[h-2] = mot[pos1+h];
					}
					tmp = atoi(cc);
					if(tmp>=NB_REG)
						return 0;
					code[num_ligne].r2 = tmp;
					for(i = pos2;i>=pos1;i--)
						mot[i] = '\0';
					int adr = 0;
					adr = cherche_res(mot); // on verifie que l'addresse a été définie avant
					if(adr == -1)
						return 0;
					code[num_ligne].res =addr[adr]; // on pointe vers cette addresse
					return 1;
				}
			}
			
		}
		if(strcmp(code[num_ligne].OPcode,"SW")==0)
		{
			if(num_mot == 1) //addresse
			{
				if(mot[0]=='@' && isalpha(mot[1]))  //cf LW
				{
					for(int i=0;i<strlen(mot);i++)
						mot[i] = mot[i+1];
					int pos1 = research(mot,'[');
					int pos2 = research(mot,']');
					int dist = pos2 - pos1;
					if((pos1 == -1 || pos2 ==-1 || dist < 3 || dist > 4))
						return 0;	
					if(mot[pos1+1] !=  'R' || mot[pos2+1] != '\0')
						return 0;
					for(int h=2;h<dist;h++)
					{
						if(!isdigit(mot[pos1+h]))
							return 0;
						cc[h-2] = mot[pos1+h];
					}
					tmp = atoi(cc);
					if(tmp>=NB_REG)
						return 0;
					code[num_ligne].r2 = tmp;
					for(i = pos2;i>=pos1;i--)
						mot[i] = '\0';
					int adr = 0;
					adr = cherche_res(mot);
					if(adr == -1)
						return 0;
					code[num_ligne].res =addr[adr];
					return 1;
				}
			}
			if(num_mot == 2) // registre 1
			{
				if(mot[3] == '\0' && mot[0] == 'R' && isdigit(mot[1])&& (isdigit(mot[2]) || mot[2] =='\0'))
				{
					cc[0] = mot[1]; 
					cc[1]= mot[2];
					tmp = atoi(cc);
					if(tmp <= NB_REG)
					{
						code[num_ligne].r1 = tmp;
						return 1;
					}
				}
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

int verif_res(char* ligne, int num_ligne){
	addr[num_ligne] = init_resultat();
	//verification sous forme  @X9Z = 999
	 int k = 0;int i =0;int num_mot = 0;
	 char tmp[MAXBUF];init_chaine(tmp);
	 while(ligne[k]!='\0' && ligne[k]!= '\n')//on s arrette en fin de ligne
      {
        while(ligne[k] !=' '&& ligne[k]!= '\0' ) //double securitée
        {
          tmp[i] = ligne[k]; // on stock dans un tmp les caracs du mot en cours
          k++;  i++;         // De lecture
        }
        // on met le mot dans le champ de la structure voulue
		if(num_mot > 2)
			return 0;
		if(num_mot == 0)
		{
			if(tmp[0] != '@'|| !isalpha(tmp[1]))
				return 0;
			for(i=0;i<strlen(tmp);i++)
				tmp[i] = tmp[i+1];
			strcpy(addr[num_ligne].nom,tmp);
		}
		if(num_mot == 1)
		{
			if(tmp[0] != '=')
				return 0;
		}
		if(num_mot == 2)
		{
			int j = 0;
			while(tmp[j] != '\0')
			{
				if(!isdigit(tmp[j]))
					return 0;
				addr[num_ligne].valeur[0] = atoi(tmp);
				j++;
			}
			
		}
        // on passe au "mot" suivant
        i = 0;
        k++; num_mot ++;
        init_chaine(tmp);
      }
	return 1;
}




