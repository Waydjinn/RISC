#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "structures.h"

#define MAXBUF 10
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
	FILE *fichier = NULL;
	int caract = 0;
	int i = 0;
	int j = 0;
	char tmp[MAXBUF];
	char *tempInstr[5][1];
	fichier = fopen(cheminFichierCode, "r");
	
	/*
	for( i = 0; i <= 5; i++){
		tempInstr[i][1] = "0";
	}*/
	
	if(fichier != NULL){
		printf("FAIRE POUR CHAQUE LIGNES DU FICHIER\n");
		while(caract != EOF){
			
			caract = fgetc(fichier);
			if(caract == ' ' || caract == '\n'){
				printf("ON INSERE : %s DANS TAB[%d][1]\n", tmp, j);
				tempInstr[j][1] = tmp;
				printf("ON LIT TAB[%d][1] : %s \n", j,  tempInstr[j][1]);
				j++;
				printf("\n");
				while(i != 0){
					tmp[i] = ' ';
					i--;
				}
			}else{
				tmp[i] = caract;
				i++;
			}
		}
		printf("ON LIT TAB[4][1] : %s \n", tempInstr[4][1]);
		//printf("ON LIT TAB[5][1] : %s \n", tempInstr[5][1]); // ???
	
		fclose(fichier);
	}else{
		printf("Impossible d'ouvrir le fichier\n");
	}
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
