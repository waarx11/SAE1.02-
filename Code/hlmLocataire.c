#include "hlm.h"

Files lireLocataire(FILE *fLoca, Files lc)
{
	MaillonLoc *m;
	m=(MaillonLoc *)malloc(sizeof(MaillonLoc));
	if (m == NULL)
	{
		printf("Problème de malloc\n");
		exit(1);
	}
	fscanf(fLoca,"%d %s %s %s %d %f %d %d %d %d ", &m->loc.numloca ,m->loc.prenom, m->loc.nom, m->loc.nationalite, &m->loc.plafond, &m->loc.revenu, &m->loc.numlogement, &m->loc.datedebutloca.annee, &m->loc.datedebutloca.mois, &m->loc.datedebutloca.jours);
	fscanf(fLoca,"%d", &m->loc.nbNumTel);
	for (int i = 0; i<m->loc.nbNumTel ; i++)
	{
		m->loc.numTel = (Tel*)malloc(sizeof(Tel));
		fscanf(fLoca,"%s %s", m->loc.numTel->libelle, m->loc.numTel->num);
	}
	m->suiv = lc;
	return m;
}

Files chargementLoc(Files lc, char *fic2, int *nbL)
{
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
        lc=lireLocataire(fLoca,lc);
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
	return NULL;
}

Files Enfiler (Files f,int numloca, char prenom[], char nom[], char nationalite[], int plafond, float revenu, int numloge)
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

int RechDichoNumLoca (Files f, int numloca)
{
	MaillonLoc *m;
	int deb=0, milieu, fin=numloca-1;
	
	while(deb<=fin)
	{	
		milieu=(deb+fin)/2;

		if (numloca >= m->loc.numloca)
			deb = milieu+1;
		else
			fin = milieu-1;
	}
	return deb;
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
	int numloca;
	printf("\t\t\t\t -- Toutes les informations sur le %d --\n", numloca);
	printf("+-------------------------------------------------------------------------------------------------------------------------+\n");
	printf("| Nom\t | Prénom\t | Nationalité\t | Plafond\t | Revenu\t | Numéro de logement | Date début location |\n");
	printf("+-------------------------------------------------------------------------------------------------------------------------+\n");
	printf("| %s\t | %s\t | %s\t | %d\t | %.2f\t | %d\t\t | %d/%d/%d\n", f->loc.prenom, f->loc.nom, f->loc.nationalite, f->loc.plafond, f->loc.revenu, f->loc.numlogement, f->loc.datedebutloca.jours, f->loc.datedebutloca.mois, f->loc.datedebutloca.annee);
	printf("+-------------------------------------------------------------------------------------------------------------------------+\n");
}




