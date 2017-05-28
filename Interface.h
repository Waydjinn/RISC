#ifndef _INTERFACE_H
#define _INTERFACE_H

#include "analyseurS.h"
#include "structure.h"
#include "sequentiel.h"
#include "pipeline.h"
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

//Fonctions de l'interface
void Mode_sequentiel();
void Mode_pipeline();
void Comparaison();
void choix_chemin();
char* Nom_fichier_sauvegarde(const char* path,const char* nomsauvegarde,char *newpath);
void sauvegarde_res(GtkButton *SaveButton,gpointer data);
void affichage();
char* affiche_res_addr(char* res);

//Widgets dynamiques de l'interface

GtkWidget *Fenetre;
GtkWidget *ResZone;
GtkWidget *FilePath;
char *cheminFichier;
int cycle[2];

#endif
