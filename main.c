#include "structure.h"
#include "sequentiel.h"
#include "pipeline.h"
#include "analyseurS.h"
#include "Interface.h"

int main(int argc, char *argv[])
{
	//~ code = malloc(100 *sizeof(instruction));
	//~ addr = malloc(25 *sizeof(resultat));
	//Pour reconnaître GTK+
    gtk_init(&argc,&argv);
    
    //Création des widgets
	affichage();

    //Affichage de la fenêtre
    gtk_widget_show_all(Fenetre);
    gtk_main();	
	//~ free(code);
	//~ free(addr);
	  if(addr!=NULL)
	{
	free(addr);
	}
    return EXIT_SUCCESS;
}
