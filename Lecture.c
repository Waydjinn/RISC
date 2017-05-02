#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#include "structures.h"

#define MAXBUF 20
instruction *code;

//Prototypes des fonctions
int lecture(char *cheminFichierCode, instruction *memoire);
int stockage(instruction *memoire, resultat *adresses, char *oc, registre *op);
int verification(instruction *memoire, instruction *instr);
void init_chaine(char tmp[MAXBUF])
{
	int i;
	for(i=0;i<MAXBUF;i++)
	{
		tmp[i] = '\0'; // \0 represente la fin d'une chaine
	}
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
  int k = 0;
  char c = '0'; char carac = '0';
  char tmp[MAXBUF];
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
      printf("ligne %d : \n%s \n",j,ligne);
      k =0;i =0;
      init_chaine(tmp);
      while(ligne[k]!='\0')//on s arrette en fin de ligne
      {
        while(ligne[k] !=' ' && ligne[k]!= '\0') //double securitée
        {
          tmp[i] = ligne[k]; // on stock dans un tmp les caracs du mot en cours
          k++;               // De lecture
          i++;
        }
        // on met le mot dans le champ de la structure voulue
        printf("tmp : %s \n",tmp);


        // on passe au "mot" suivant
        i = 0;
        k++;
        init_chaine(tmp);
      }
    //  ## on reinitialise pour passer a la ligne suivante##
      init_chaine(ligne);
      i = 0;
      j++;
    }
		close(fichier);

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
