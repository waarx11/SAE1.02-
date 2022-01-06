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
	fscanf(fLoca,"%s %s %s %d %f %d %d %d %d", m->loc.prenom, m->loc.prenom, m->loc.nationalite, m->loc.plafond, m->loc.revenu, m->loc.numlogement, m->loc.datedebutloca.annee, m->loc.datedebutloca.mois, m->loc.datedebutloca.jours);
	m->suiv = lc;
	return m;
}

Booleen EstVide (Files f)
{
	if (f.tete == NULL)
		return Vrai;
	return Faux;
}

// void Vider (Files *f)
// {
// 	while (!EstVide(*f))
// 		*f= Defiler(f);
// }

Files FileVide(void)
{
	Files f;
	f.tete = NULL;
	f.queue = NULL;
	return f;
}



FilesLoc AffichLocataire(FILE fLoca, Files f)
{
	MaillonLoc *m;
	m = f.tete;
	printf("\t\t\t\t -- Toutes les informations sur le locataire --\n");
	printf("+----------------------------------------------------------------------------------------------------+\n");
	printf("| Nom\t | Prénom\t | Nationalité\t | Plafond\t | Revenu\t | Numéro de logement | Date début location |\n");
	while (m != NULL)
	{
		printf("+----------------------------------------------------------------------------------------------------+\n");
		printf("| %s\t | %s\t | %s\t | %d\t | %.2f\t | %d\t | %d/%d/%d\n", m->loc.prenom, m->loc.prenom, m->loc.nationalite, m->loc.plafond, m->loc.revenu, m->loc.numlogement);
		printf("+----------------------------------------------------------------------------------------------------+\n");
		m = m->suiv;
	}
}

FilesLoc AffichLocatairePrecis(FILE fLoca, Files f)
{
	int numLoca;
	MaillonLoc *m;
	m = f.tete;
	printf("\t\t\t\t -- Toutes les informations sur le %d --\n", numLoca);
	printf("+----------------------------------------------------------------------------------------------------+\n");
	printf("| Nom\t | Prénom\t | Nationalité\t | Plafond\t | Revenu\t | Numéro de logement | Date début location |\n");
	printf("+----------------------------------------------------------------------------------------------------+\n");
	printf("| %s\t | %s\t | %s\t | %d\t | %.2f\t | %d\t | %d/%d/%d\n", m->loc.prenom, m->loc.prenom, m->loc.nationalite, m->loc.plafond, m->loc.revenu, m->loc.numlogement);
	printf("+----------------------------------------------------------------------------------------------------+\n");
}




