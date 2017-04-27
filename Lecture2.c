#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "structures.h"

#define MAXBUF 15
instruction *code;

//Prototypes des fonctions
int lecture(char *cheminFichierCode, instruction *memoire);
int stockage(instruction *memoire, resultat *adresses, char *oc, registre *op);
int verification(instruction *memoire, instruction *instr);

//Main
int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("Erreur, chemin fichier non fourni en argument\n");
	}
	else
	{
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
	int fs;
	int res = 1;
	int k = 0;
	int l = 0;
	char tempCode;
	char tempParam;
	char opcode[MAXBUF];
	char oprande[MAXBUF];
	char *tempInstr[6][1];
	/* avec tempInstr[0] = OPcode
	 *      tempInstr[1] = R1
	 *      tempInstr[2] = R2
	 *      tempInstr[3] = R3
	 *      tempInstr[4] = res
	 *      tempInstr[5] = jump
	 */
	 int i, j;
	 for(i = 0; i <= 6; i++){
		tempInstr[i][1] = "Nil";
	 }
	fs = open(cheminFichierCode, O_RDONLY);
	if(fs == -1)
	{
		printf("Le fichier est introuvable\n");
		return 0;
	}
	while(res != 0)
	{
		tempCode = '1'; //Initialisation de la variable pour éviter que la variable reste au dernier caractère lu
		while(tempCode != ' ' && res != 0) 
		{
			res = read(fs, &tempCode, 1); //On recopie la ligne caractère par caracère
			if(tempCode != ' '){
				opcode[k] = tempCode; //On stock le caractère lu dans un tableau de char
				k++; //Suivant du char*
				
			}
		}
		j = 0;
		printf("On met opcode : %s dans tmp[%d][1] \n", opcode, j);
		tempInstr[j][1] = opcode;
		j++;
		tempParam = '1';
		while(tempParam != '\n' && res != 0)
		{
			printf("tempParam = %c\n", tempParam);
				res = read(fs, &tempParam, 1);
				if(tempParam != ' '){	
					oprande[l] = tempParam;
					l++;
				}else{
					printf("On met oprande : %s dans tmp[%d][1] \n", oprande, j);
					tempInstr[j][1] = oprande;
					j++;
					for(l=0; l<= i; l++)
					{
						oprande[l] = ' ';
					}
					l = 0;
				}
		}
		printf("On met oprande : %s dans tmp[%d][1] \n", oprande, j);
		tempInstr[j][1] = oprande;
		j++;
		
		k = 0; 
		l = 0;
		printf("Début instruction\n");
		for (i = 0; i <= 4; i++){
			printf("case : %d, %s \n", i,  tempInstr[i][1]);
		}
		printf("Fin instruction\n");
	}
	
	close(fs);
    return 1;
}

/* Fonction verification
 * Renvoie 1 si la vérification est bonne, sinon 0.
 * 
 * 
 * 
 */ 
int verification(instruction *memoire, instruction * instr){
	
	return 1;
}

/* Fonction stockage
 * Renvoie 1 si l'instruction a bien été stockée, sinon 0
 * 
 * 
 * 
 * 
 */ 

int stockage(instruction *memoire, resultat *adresses, char *oc, registre *op){
	
	return 1;
}
