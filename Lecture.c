#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "structures.h"

#define MAXBUF 1024

int lecture(char *cheminFichierCode, instruction memoire);

int main(int argc, char *argv[])
{
	int fs;
	int res;
	int k = 0;
	int l = 0;
	char tempCode;
	char tempParam;
	char opcode[MAXBUF];
	char oprande[MAXBUF];

	if(argc < 2)
	{
		printf("Erreur, chemin fichier non fourni en argument\n");
	}
	else
	{
		fs = open(argv[1], O_RDONLY);
		if(fs == -1)
		{
			printf("Le fichier est introuvable\n");
			exit(0);
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
	}
	
	close(fs);
    return 0;
}
