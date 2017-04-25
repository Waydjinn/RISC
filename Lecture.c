#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "structures.h"

#define MAXBUF 1024
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
	int res;
	int k = 0;
	int l = 0;
	char tempCode;
	char tempParam;
	char opcode[MAXBUF];
	char oprande[MAXBUF];

	
	fs = open(cheminFichierCode, O_RDONLY);
	if(fs == -1)
	{
		printf("Le fichier est introuvable\n");
		return 0;
	}
	while(res != 0)
	{
		tempCode = '1';
		while(tempCode != ' ' && res != 0) //On recopie la ligne caractère par caracère
		{
			res = read(fs, &tempCode, 1);
			opcode[k] = tempCode;
			k++;
		}
		tempParam = '1';
		while(tempParam != '\n' && res != 0)
		{
			res = read(fs, &tempParam, 1);
			oprande[l] = tempParam;
			l++;
		}
		k = 0;
		l = 0;
		printf("opcode : %s \n", opcode);
		printf("oprande : %s \n", oprande);
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
