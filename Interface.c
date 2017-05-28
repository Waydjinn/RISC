#include "Interface.h"

instruction* code;
resultat* addr;
int cycle[2];
registre tabreg[NB_REG];

/* La fonction permet de retrouver les résultats des variables du code à émuler
 * et les concaténe avec le résultat des cycles. 
 */
char* affiche_res_addr(char *res)
{
	int i,j;
	i=0;
	j=0;
	while(strcmp(addr[i].nom,"FIN")!=0)
	{
		j=0;
		while(addr[i].valeur[j]!=-1)
		{
			char* resultats=malloc(100000*sizeof(char)); //On alloue une taille de 100 char pour l affichage du resultat
			if(j%5==0)
			{
				sprintf(resultats,"\n %s[%d]=%d",addr[i].nom,j,addr[i].valeur[j]);
			}
			else{
				sprintf(resultats," %s[%d]=%d",addr[i].nom,j,addr[i].valeur[j]);
			}
			res=strcat(res, resultats);
			free(resultats);
			j++;
		}
		i++;
		res=strcat(res," \n\n ");
	}
	return res;
}
/* Trouve le chemin du fichier à sauvegarder en prenant en compte le choix User.
 * La fonction va concaténer le chemin du fichier à émuler (sans le nom du fichier) 
 * avec le nom de sauvegarde que l'utilisateur aura renseigné. On ajoute aussi l'extension
 *  .txt.
 */
char* Nom_fichier_sauvegarde(const char *path,const char *nomsauvegarde,char *newpath)//trouve le chemin du fichier a sauvegarder en prenant en compte le choix User
{
	int res=0;
	int i= strlen(path);
	while(path[i]!= '/')
	{
		i--;
		res=i;
	}
	res +=1;
	newpath=calloc((strlen(path)+strlen(nomsauvegarde)),sizeof(char));
	newpath=strncpy(newpath,path,res); //On copie le chemin sans le nom du fichier a tester
	newpath=strcat(newpath,nomsauvegarde);//on concatene le chemin du dossier et le nom de la sauvegarde
	return newpath=strcat(newpath,".txt");
}

/* La fonction permet l'éxecution du mode séquentiel ainsi que d'afficher les résultats.
 * 
 */ 
void Mode_sequentiel()
{
	if(addr!=NULL)
	{
	free(addr);
	}
	cycle[0]=0;
	cycle[1]=0;
	
	GtkTextBuffer *ResBuff;
    ResBuff = gtk_text_view_get_buffer(GTK_TEXT_VIEW (ResZone));
    
	if(cheminFichier==NULL) //Si user n'a pas choisi de code a tester renvoyer erreur et on stop l'execution.
	{
		gtk_text_buffer_set_text(ResBuff,"Veuillez choisir un fichier à tester !",-1);	
		return;
	}
	
	char* resultats; // Variable nécessaire à la conversion d'un type int en char*
	code = malloc(100 *sizeof(instruction));
	addr = malloc(25 *sizeof(resultat));
	int res_analyse = lecture(cheminFichier,code); // On lance l annalyse et on stocke le resultat.
	
    if(res_analyse==1) //Si le code ne comporte pas d'erreur on lance l'éxécution
    {
		Sequentiel(code);
		resultats=calloc(100000,sizeof(char)); //On alloue de la memoire pour l affichage du resultat
		sprintf(resultats,"Resultat du mode séquentiel : \n\n votre programme s'est éxécuté en %d cycles \n\n",cycle[0]); //On convertit le nb de cycle en type chaine pour pouvoir l'afficher.
		resultats=affiche_res_addr(resultats);
		gtk_text_buffer_set_text(ResBuff,resultats,-1);
		free(resultats);
		cycle[1]=-1; // Pour que la fonction sauvegarde sache qu'on à utilisé le mode sequentiel
	}
	else
	{
		gtk_text_buffer_set_text(ResBuff,"Le fichier à tester n'est pas conforme.\n\n Veuillez vérifier votre code : \n -Jeu d'instructions non respecté !\n -Nombre de registre supérieur à 32 !",-1);
	}
    free(code);
}
/* La fonction permet l'éxecution du mode pipeline ainsi que d'afficher les résultats.
 */ 
void Mode_pipeline()
{	
	if(addr!=NULL)
	{
	free(addr);
	}
	cycle[0]=0;
	cycle[1]=0;
	
	GtkTextBuffer *ResBuff;
    ResBuff = gtk_text_view_get_buffer(GTK_TEXT_VIEW (ResZone));
    
	if(cheminFichier==NULL) //Si user n'a pas choisi de code a tester renvoyer erreur et on stop l'execution.
	{
		gtk_text_buffer_set_text(ResBuff,"Veuillez choisir un fichier à tester !",-1);	
		return;
	}
	
	char* resultats; // Variable nécessaire à la conversion d'un type int en char*
	code = malloc(100 *sizeof(instruction));
	addr = malloc(25 *sizeof(resultat));
	int res_analyse = lecture(cheminFichier,code); // On lance l annalyse et on stocke le resultat.
	
    if(res_analyse==1) //Si le code ne comporte pas d'erreur on lance l'éxécution
    {
		pipeline(code,0);
		resultats=calloc(100000,sizeof(char)); //On alloue de la memoire pour l affichage du resultat
		sprintf(resultats,"Resultat du mode pipeline : \n\n votre programme s'est éxécuté en %d cycles \n\n",cycle[1]); //On convertit le nb de cycle en type chaine pour pouvoir l'afficher.
		resultats=affiche_res_addr(resultats);
		gtk_text_buffer_set_text(ResBuff,resultats,-1);
		free(resultats);
		cycle[0]=-1; // Pour que la fonction sauvegarde sache qu'on à utilisé le mode pipeline 
	}
	else
	{
		gtk_text_buffer_set_text(ResBuff,"Le fichier à tester n'est pas conforme.\n\n Veuillez vérifier votre code : \n -Jeu d'instructions non respecté !\n -Nombre de registre supérieur à 32 !",-1);
	}
    free(code);
}
/* La fonction permet l'éxecution du mode séquentiel et pipeline ainsi que d'afficher les résultats.
 */ 
void Comparaison()
{
	if(addr!=NULL)
	{
	free(addr);
	}
	cycle[0]=0;
	cycle[1]=0;
	
	GtkTextBuffer *ResBuff;
    ResBuff = gtk_text_view_get_buffer(GTK_TEXT_VIEW (ResZone));
    
	if(cheminFichier==NULL) //Si user n'a pas choisi de code a tester renvoyer erreur et on stop l'execution.
	{
		gtk_text_buffer_set_text(ResBuff,"Veuillez choisir un fichier à tester !",-1);	
		return;
	}
	
	char* resultats; // Variable nécessaire à la conversion d'un type int en char*
	code = malloc(100 *sizeof(instruction));
	addr = malloc(25 *sizeof(resultat));
	int res_analyse = lecture(cheminFichier,code); // On lance l annalyse et on stocke le resultat.
	
	
    if(res_analyse==1) //Si le code ne comporte pas d'erreur on lance l'éxécution
    {	
		Sequentiel(code);
		pipeline(code,0);
		float acc = (float)cycle[0]/(float)cycle[1];
		resultats=calloc(100000,sizeof(char)); //On alloue de la memoire pour l affichage du resultat
		sprintf(resultats,"Resultat du mode séquentiel :\n\n votre programme s'est éxécuté en %d cycles \n\n Resultat du mode pipeline :\n\n votre programme s'est éxécuté en %d cycles\n\n Le rapport sequentiel/pipeline vaut : %f \n\n",cycle[0],cycle[1],acc); //On convertit le nb de cycle en type chaine pour pouvoir l'afficher.
		resultats=affiche_res_addr(resultats);
		gtk_text_buffer_set_text(ResBuff,resultats,-1);
		free(resultats);
	}
	else
	{
		gtk_text_buffer_set_text(ResBuff,"Le fichier à tester n'est pas conforme.\n\n Veuillez vérifier votre code : \n -Jeu d'instructions non respecté !\n -Nombre de registre supérieur à 32 !",-1);
	}
    free(code);
}

void choix_chemin()
{
	//Pour afficher le chemin du fichier
	GtkTextBuffer *PathBuff;
    PathBuff = gtk_text_view_get_buffer(GTK_TEXT_VIEW (FilePath));
    
    //Choix du fichier
	GtkWidget *dialog;
	dialog = gtk_file_chooser_dialog_new("Choisir le code à émuler", GTK_WINDOW(Fenetre),
				      GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
				      NULL);
	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
	{
		cheminFichier = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		gtk_text_buffer_set_text(PathBuff,cheminFichier,-1);
	}
	gtk_widget_destroy (dialog);
}

void sauvegarde_res(GtkButton *SaveButton,gpointer data)
{	
	GtkTextBuffer *ResBuff;
    ResBuff = gtk_text_view_get_buffer(GTK_TEXT_VIEW (ResZone));
    
    GtkEntry *Nom_sauvegarde =g_object_get_data(G_OBJECT(SaveButton),"Nom_sauvegarde");
	const char *Sauve=gtk_entry_get_text(Nom_sauvegarde);//On recupére le nom du fichier a sauvegarder.
	int taille = strlen(Sauve);
	if( cheminFichier==NULL || taille==0)//Si pas de chemin relatif au fichier alors il n y a pas eu de test donc pas de save
	{
		gtk_text_buffer_set_text(ResBuff,"Erreur sauvegarde : \n -Chemin non comforme \n -Aucun nom de sauvegarde entré",-1);
		return;
	}
	char *path_res='\0'; //Chemin de la sauvegarde
	
	path_res=Nom_fichier_sauvegarde(cheminFichier,Sauve,path_res);
	
	FILE* fichier = NULL;
 
    fichier = fopen(path_res, "w");
		
	char *res=calloc(100000,sizeof(char));
	res=affiche_res_addr(res);
	
    if (fichier != NULL)
    {
		if(cycle[0]>=0 && cycle[1]>=0)
		{	
			float acc = (float)cycle[0]/(float)cycle[1];
			fprintf(fichier,"Résultat de l'analyse en mode comparaison : \n Execution séquentiel : %d cycles \n Execution pipeline : %d cycle \n Rapport sequentiel/pipeline : %f ",cycle[0],cycle[1],acc);
			fprintf(fichier,"\n\n Résultats : \n\n %s",res);
			fclose(fichier);
			free(res);
			gtk_text_buffer_set_text(ResBuff,"Sauvegarde réussie.",-1);
			return;
		}
		else if(cycle[0]>=0 && cycle[1]==-1)
		{
			fprintf(fichier,"Résultat de l'analyse en mode séquentiel : \n Execution séquentiel : %d cycles",cycle[0]);
			fprintf(fichier,"\n\n Résultats : \n\n %s",res);
			fclose(fichier);
			gtk_text_buffer_set_text(ResBuff,"Sauvegarde réussie.",-1);	
			free(res);
			return;
		}else if(cycle[0]==-1 && cycle[1]>=0)
		{
			fprintf(fichier,"Résultat de l'analyse en mode pipeline : \n Execution pipeline : %d cycles",cycle[1]);
			fprintf(fichier,"\n\n Résultats : \n\n %s",res);
			fclose(fichier);
			gtk_text_buffer_set_text(ResBuff,"Sauvegarde réussie.",-1);
			free(res);
			return;
		}
		remove(path_res);
		fclose(fichier);
		gtk_text_buffer_set_text(ResBuff,"Aucun résultats à sauvegarder !",-1);
    }
		free(res);
}

void affichage()
{        
    //Création de la fenêtre
    Fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(Fenetre), "Emulateur processeur RISC");
    gtk_window_set_default_size(GTK_WINDOW(Fenetre), 640, 480);
        gtk_window_set_position (GTK_WINDOW (Fenetre), GTK_WIN_POS_CENTER);
        g_signal_connect(G_OBJECT(Fenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);
                
    //Création Table
    GtkWidget *Table;
    Table=gtk_table_new(14,4,TRUE);
    gtk_container_add (GTK_CONTAINER (Fenetre),GTK_WIDGET(Table));
    
    //Création scrollbar
    GtkWidget *scrollbar;
    scrollbar = gtk_scrolled_window_new(NULL,NULL);

    //Création du widget de sauvegarde
    GtkWidget *labelSauvegarde;
        GtkWidget *Nom_sauvegarde;
        labelSauvegarde=gtk_label_new("Nom sauvegarde :");
        Nom_sauvegarde=gtk_entry_new();
    
    //Création des boutons
    GtkWidget *OpenButton,*SequButton,*PipeButton,*CompButton,*SaveButton;
        OpenButton = gtk_button_new_from_stock(GTK_STOCK_OPEN);
        SequButton = gtk_button_new_with_label("Mode séquentiel");
        PipeButton = gtk_button_new_with_label("Mode pipeline");
        CompButton = gtk_button_new_with_label("Comparaison");
        SaveButton = gtk_button_new_from_stock(GTK_STOCK_SAVE);
        
        //Création zone de résultat
    GtkTextBuffer *ResBuff;
    ResZone = gtk_text_view_new();
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollbar),ResZone);        //Ajout scrollbar
    ResBuff = gtk_text_view_get_buffer(GTK_TEXT_VIEW (ResZone));
    gtk_text_buffer_set_text(ResBuff,"Zone des résultats",-1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(ResZone),FALSE);
    
    //Création chemin fichier
    GtkTextBuffer *PathBuff;
    FilePath = gtk_text_view_new();
    PathBuff = gtk_text_view_get_buffer(GTK_TEXT_VIEW (FilePath));
    gtk_text_buffer_set_text(PathBuff,"Sélectionnez votre code à émuler.",-1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(FilePath),FALSE);
        
    //Insertion des boutons
    gtk_table_attach(GTK_TABLE(Table), OpenButton,
    0, 1, 1, 2, GTK_EXPAND,GTK_EXPAND,0,0);
    
    gtk_table_attach(GTK_TABLE(Table), SequButton,
    0, 1, 5, 7, GTK_EXPAND,GTK_EXPAND,0,0);
    gtk_table_attach(GTK_TABLE(Table), PipeButton,
    0, 1, 6, 8, GTK_EXPAND,GTK_EXPAND,0,0);
    gtk_table_attach(GTK_TABLE(Table), CompButton,
    0, 1, 7, 9, GTK_EXPAND,GTK_EXPAND,0,0);
    
    gtk_table_attach(GTK_TABLE(Table), SaveButton,
    0, 1, 12, 13, GTK_EXPAND,GTK_EXPAND,0,0);
        gtk_table_attach(GTK_TABLE(Table), labelSauvegarde, 0, 1, 10, 11, GTK_EXPAND,GTK_EXPAND,0,0);
        gtk_table_attach(GTK_TABLE(Table), Nom_sauvegarde,0, 1, 11, 12, GTK_EXPAND,GTK_EXPAND,0,0);
        
        //Insertion de la zone de résultat
    gtk_table_attach(GTK_TABLE(Table), scrollbar,
    1, 4, 3, 13, GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,0,0);
    
    //Insertion chemin fichier
    gtk_table_attach(GTK_TABLE(Table), FilePath,
    1, 4, 1, 2, GTK_EXPAND | GTK_FILL,GTK_EXPAND,0,0);
    
        //Fonction des Boutons
        g_signal_connect (G_OBJECT (OpenButton), "clicked", G_CALLBACK (choix_chemin), NULL);
        g_signal_connect (G_OBJECT (SequButton), "clicked", G_CALLBACK (Mode_sequentiel), NULL);
        g_signal_connect (G_OBJECT (PipeButton), "clicked", G_CALLBACK (Mode_pipeline), NULL);
        g_signal_connect (G_OBJECT (CompButton), "clicked", G_CALLBACK (Comparaison), NULL);
        
        g_object_set_data(G_OBJECT(SaveButton),"Nom_sauvegarde",Nom_sauvegarde); //On fait passer le text entré dans la fonction save
        g_signal_connect (G_OBJECT (SaveButton), "clicked", G_CALLBACK (sauvegarde_res), NULL);        
}
