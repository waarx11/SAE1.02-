#include "hlm.h"

FilesLoc lireLocataire(FILE *fLoca, FilesLoc lc)
{
	MaillonLoc *m;
	m=(MaillonLoc *)malloc(sizeof(MaillonLoc));
	if (m == NULL)
	{
		printf("Problème de malloc\n");
		exit(1);
	}
	fscanf(fLoca,"%s/%s/%s/%d/%f/%d/%d/%d/%d ", m->loc.prenom, m->loc.nom, m->loc.nationalite, m->loc.plafond, m->loc.revenu, m->loc.numlogement, m->loc.datedebutloca.annee, m->loc.datedebutloca.mois, m->loc.datedebutloca.jours);
	return m;
}

FilesLoc chargementLoc(FilesLoc lc, char *fic2, int *nbL)
{
	Files fc;
	FILE *fLoca;
	MaillonLoc *m;
	fLoca=fopen(fic2,"r");
	if (fLoca == NULL)
    {
        printf("Problème ouverture fichier Loc");
        return NULL;
    }
    fscanf(fLoca, "%d", nbL);
    for(int i=0;i<*nbL;i++)
        fc=lireLocataire(fLoca,fc);
	fclose(fLoca);
	return lc;
}

Booleen EstVide (Files f)
{
	if (f == NULL)
		return Vrai;
	return Faux;
}

Files FileVide(void)
{
	Files f;
	f == NULL;
	return f;
}

FilesLoc Enfiler (Files f, char prenom[], char nom[], char nationalite[], int plafond, float revenu, int numloge, int annee, int mois, int jour)
{
	MaillonLoc *m;
	m = (MaillonLoc *)malloc(sizeof(MaillonLoc));
	if (m == NULL)
	{
		printf("Problème de malloc");
		exit(1);
	}
	strcpy(m->loc.prenom, prenom);
	strcpy(m->loc.nom, nom);
	strcpy(m->loc.nationalite, nationalite);
	m->loc.plafond = plafond;
	m->loc.revenu = revenu;
	m->loc.numlogement = numloge;
	m->loc.datedebutloca.annee = annee;
	m->loc.datedebutloca.mois = mois;
	m->loc.datedebutloca.jours = jour;
	m->suiv = NULL;

	if(EstVide(f))
	{
		m->suiv = f->suiv;
		return m;
	}
	m->suiv = f->suiv;
	f->suiv = m;
	return m;
}

FilesLoc Defiler(Files f)
{
 MaillonLoc *tmp;
 if (EstVide(f))
 return NULL;
 if (f==f->suiv)
 {
 free(f);
 return NULL;
 }
 tmp=f->suiv;
 f->suiv=tmp->suiv;
 free(tmp);
 return f;
}

// FilesLoc RechLoca(char caract[])
// {
// 	MaillonLoc *m;
// 	while (m != NULL)
// 	{
		
// 		m = m->suiv;
// 	}
// }

// FilesLoc RechLoca(Files f)
// {
// 	MaillonLoc *m;
// 	m = f;
// 	while (m != NULL)
// 	{
		
// 		m = m->suiv;
// 	}
// }

FilesLoc AffichLocataire(Files f)
{
	MaillonLoc *m;
	m = f;
	printf("\t\t\t\t -- Toutes les informations sur le locataire --\n");
	printf("+----------------------------------------------------------------------------------------------------+\n");
	printf("| Nom\t | Prénom\t | Nationalité\t | Plafond\t | Revenu\t | Numéro de logement | Date début location |\n");
	while (m != NULL)
	{
		printf("+----------------------------------------------------------------------------------------------------+\n");
		printf("| %s\t | %s\t | %s\t | %d\t | %.2f\t | %d\t | %d/%d/%d\n", m->loc.prenom, m->loc.prenom, m->loc.nationalite, m->loc.plafond, m->loc.revenu, m->loc.numlogement, m->loc.datedebutloca.annee, m->loc.datedebutloca.mois, m->loc.datedebutloca.jours);
		printf("+----------------------------------------------------------------------------------------------------+\n");
		m = m->suiv;
	}
}

FilesLoc AffichLocatairePrecis(Files f)
{
	int numLoca;
	MaillonLoc *m;
	m = f;
	printf("\t\t\t\t -- Toutes les informations sur le %d --\n", numLoca);
	printf("+----------------------------------------------------------------------------------------------------+\n");
	printf("| Nom\t | Prénom\t | Nationalité\t | Plafond\t | Revenu\t | Numéro de logement | Date début location |\n");
	printf("+----------------------------------------------------------------------------------------------------+\n");
	printf("| %s\t | %s\t | %s\t | %d\t | %.2f\t | %d\t | %d/%d/%d\n", m->loc.prenom, m->loc.prenom, m->loc.nationalite, m->loc.plafond, m->loc.revenu, m->loc.numlogement, m->loc.datedebutloca.annee, m->loc.datedebutloca.mois, m->loc.datedebutloca.jours);
	printf("+----------------------------------------------------------------------------------------------------+\n");
}




