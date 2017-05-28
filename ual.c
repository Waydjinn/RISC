#include "ual.h"

instruction* code;
resultat* addr;
int cycle[2];
registre tabreg[NB_REG];

//On entre 3 registres, le resultat de l'addition des registres b et c devient la valeur du registre a
void ADD(registre* a, registre* b, registre* c)
{
	//printf("%d + %d = ",b->valeur,c->valeur);
	a->valeur = (b->valeur)+(c->valeur); 
	//printf("%d \n ",a->valeur);
}
//On entre 3 registres, le resultat de la multiplication des registres b et c devient la valeur du registre a
void MULT(registre* a, registre* b, registre* c)
{
	//printf("%d * %d = ",b->valeur,c->valeur);
        a->valeur = (b->valeur)*(c->valeur);
       // printf("%d \n ",a->valeur);

}
//On recupere la valeur dans le tableau res pour la donner au registre a 
void LW(registre* val, resultat res, registre* a)
{
	a->valeur = res.valeur[val->valeur];
	//printf("%d -> %d \n ",a->valeur,res.valeur[val->valeur]);
}
//on prend la valeur du registre a pour l'enregistrer dans le tableau de res on alloue dynamiquement sa case
void SW(registre* val, resultat res, registre* a)
{
	int i=0;
	while(strcmp(res.nom,addr[i].nom) != 0)
	{
		i++;
	}
	//~ addr[i].valeur[val->valeur] = malloc(sizeof(int));
	addr[i].valeur[val->valeur] = a->valeur;
	addr[i].valeur[(val->valeur)+1] = -1;
	//printf("val.valeur =%d res =%d et a  = %d  \n ",val->valeur,addr[i].valeur[val->valeur],a->valeur);
}
//on regarde si la valeur du registre b est plus petite que la valeur du registre a, si oui a prend la valeur 1 sinon il prend 0
void SLT(registre* a, registre* b, registre* c)
{
	if(b->valeur < c->valeur)
		{
			a->valeur = 1;
		}
	else a->valeur = 0;
	//printf (" %d < %d ",b->valeur , c->valeur);
}
//si la valeur du registre 1 est egale a 1 on retourne le jump/4 qui correspond au cp ou l'on doit avancer ou reculer 
int BNEZ(registre* a, int jump)
{

	if(a->valeur == 1)
	{	
		return jump/4;
	}
	
	else return 1;
	//printf( " R = %d  et jump= %d ",a->valeur,jump);
}

