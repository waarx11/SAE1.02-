#include "hlm.h"

Locataire lireLocataire(FILE *fLoca)
{
 	Locataire loc;
 	fscanf(fLoca,"%d %s %s %s %d %f %d %d %d %d ", &loc.numloca ,loc.prenom, loc.nom, loc.nationalite, &loc.plafond, &loc.revenu, &loc.numlogement, &loc.datedebutloca.annee, &loc.datedebutloca.mois, &loc.datedebutloca.jours);
	fscanf(fLoca,"%d", &loc.nbNumTel);
	for (int i = 0; i<loc.nbNumTel ; i++)
	{
		loc.numTel = (Tel*)malloc(sizeof(Tel));
		fscanf(fLoca,"%s %s",loc.numTel->libelle, loc.numTel->num);
	}
	return loc;
}


Files chargementLoc (Files f, char *fic2)
{
	Locataire loc;
	FILE *fLoca;
	fLoca=fopen(fic2,"r");
	if (fLoca == NULL)
    {
        printf("Problème ouverture fichier Loc");
        return NULL;
    }

    loc = lireLocataire(fLoca);
    while(feof(fLoca) == 0)
    {

    	 f = Enfillercharge(f, loc);
    	loc = lireLocataire(fLoca);
    }
    fclose(fLoca);
	return f;
}

Files Enfillercharge (Files f, Locataire loca)
{
	MaillonLoc *m;
	m = (MaillonLoc *)malloc(sizeof(MaillonLoc));
	if (m == NULL)
	{
		printf("Problème de malloc \n");
		exit(1);
	}
    m->loc = loca;
    if (EstVide(f))
    {
    	m->suiv = m;
    	return m;
    }
	m->suiv = f->suiv;
	f->suiv = m;
    return m;
}

Booleen EstVide (Files f)
{
	if (f == NULL)
		return Vrai;
	return Faux;
}

Files FileVide(void)
{
	return NULL;
}

Files EnfillerLoca (Files f,int numloca, char prenom[], char nom[], char nationalite[], int plafond, float revenu, int numloge)
{
	MaillonLoc *m;
	int jours, mois, an, h, min, s, numLoc, nbNum;
	char libelle[31], numTel[16];
	m = (MaillonLoc *)malloc(sizeof(MaillonLoc));
	if (m == NULL)
	{
		printf("Problème de malloc");
		exit(1);
	}
	//Valeur aléatoire compris entre 0 et 5000
    srand(time(NULL));
    numLoc=rand() %5000;
    //date courant
    time_t now;
    struct tm *local = localtime(&now);
    h=local->tm_hour;
    min=local->tm_min;
    s=local->tm_sec;
    jours=local->tm_mday;
    mois=local->tm_mon+1;
    an=local->tm_year+1900;
	m->loc.numloca = numloca;
	strcpy(m->loc.prenom, prenom);
	strcpy(m->loc.nom, nom);
	strcpy(m->loc.nationalite, nationalite);
	m->loc.plafond = plafond;
	m->loc.revenu = revenu;
	m->loc.numlogement = numloge;
	m->loc.datedebutloca.annee = an;
	m->loc.datedebutloca.mois = mois;
	m->loc.datedebutloca.jours = jours;
	printf("Combien de numero de telephone posseder vous : ");
    scanf("%d%*c", &nbNum);
    m->loc.nbNumTel=nbNum;
    for (int i=0; i<nbNum; i++) 
    {
        m->loc.numTel=(Tel*)malloc(sizeof(Tel));
        fgets(libelle, 30, stdin);
        libelle[strlen(libelle)-1]='\0';
        strcpy(m->loc.numTel->libelle,libelle);
        fgets(numTel, 15, stdin);
        numTel[strlen(numTel)-1]='\0';
        strcpy(m->loc.numTel->num,numTel);
    }
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

Files defiler(Files f)//Supprime le premier élément d'une file
{
    MaillonLoc *tmp;
    if (EstVide(f))
        return NULL;
    if (f==f->suiv) //Si il y a 1 seule élément
    {
        free(f);
        return NULL;
    }
    tmp=f->suiv;
    f->suiv=tmp->suiv;//Saute un maillon
    free(tmp);
    return f;
}

void RechLoca (Files f, int numlocataire)
{
	if (numlocataire > f->loc.numloca)
		return;
	printf("test \n ");
	if (numlocataire = f->loc.numloca)
		AffichLocatairePrecis(f);
	else
		RechLoca(f->suiv, numlocataire);
}

void AffichLocataire(Files f)
{
	if (f == NULL)
		return;
	printf("+---------------------------------------------------------------------------------------------------------------------------+\n");
	printf("| %s\t | %s\t | %s\t | %d\t | %.2f\t | %d\t\t | %d/%d/%d \n", f->loc.prenom, f->loc.nom, f->loc.nationalite, f->loc.plafond, f->loc.revenu, f->loc.numlogement, f->loc.datedebutloca.jours, f->loc.datedebutloca.mois, f->loc.datedebutloca.annee);
	printf("+---------------------------------------------------------------------------------------------------------------------------+\n");
	AffichLocataire(f->suiv);
}

void AffichLocatairePrecis(Files f)
{
	printf("\t\t\t\t -- Toutes les informations sur le %d --\n", f->loc.numloca);
	printf("+-------------------------------------------------------------------------------------------------------------------------+\n");
	printf("| Nom\t | Prénom\t | Nationalité\t | Plafond\t | Revenu\t | Numéro de logement | Date début location |\n");
	printf("+-------------------------------------------------------------------------------------------------------------------------+\n");
	printf("| %s\t | %s\t | %s\t | %d\t | %.2f\t | %d\t\t | %d/%d/%d\n", f->loc.prenom, f->loc.nom, f->loc.nationalite, f->loc.plafond, f->loc.revenu, f->loc.numlogement, f->loc.datedebutloca.jours, f->loc.datedebutloca.mois, f->loc.datedebutloca.annee);
	printf("+-------------------------------------------------------------------------------------------------------------------------+\n");
}




