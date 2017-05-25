#ifndef _LECTURE_H
#define _LECTURE_H

int cherche_res(char* nom);
/*
 * Permet de recuper la postion de "nom" dans le tableau d'addresses
 * renvoi -1 si echec
 */
 
void init_chaine(char tmp[MAXBUF]);
/*Initialise une chaine à '\0' pour toutes ses valeures
*/
int lecture(char *cheminFichierCode, instruction *memoire);//principale
void lire_ligne(char ligne[MAXBUF], int fichier);
/* Enregistre une ligne de fichier dans ligne*/
int research(char* chaine,char c);
/* Renvoie la premiere occurence du caractère c dans chaine 
 * renvoir -1 si echec */
int stockage(char* ligne, int num_ligne); //principale
int verification(char* mot, int num_mot,int num_ligne); //principale
int verif_res(char* ligne,int num_ligne);
/* verifie les resultats */

#endif
