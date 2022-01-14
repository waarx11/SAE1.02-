#include "hlm.h"

#define TAILLE 15

Locataire lireLocataire(FILE *fLoca)
{
 	Locataire loc;
 	fscanf(fLoca,"%d %s %s %s %d %f %d %f %d %d %d ", &loc.numloca ,loc.prenom, loc.nom, loc.nationalite, &loc.plafond, &loc.revenu, &loc.numlogement, &loc.prixLog, &loc.datedebutloca.annee, &loc.datedebutloca.mois, &loc.datedebutloca.jours);
	fscanf(fLoca,"%d", &loc.nbNumTel);
	loc.numTel = (Tel*)malloc(sizeof(Tel)*loc.nbNumTel);
	if (loc.numTel == NULL)
	{
		printf("Problème de malloc marche pas\n");
		exit(1);
	}
	for (int i = 0; i<loc.nbNumTel ; i++)
		fscanf(fLoca,"%s %s",loc.numTel[i].libelle, loc.numTel[i].num);
	return loc;
}

Files chargementLoc (Files f, int *nbelem, char *fic2)
{
	Locataire loc;
	FILE *fLoca;
	fLoca=fopen(fic2,"r");
	if (fLoca == NULL)
    {
        printf("Problème ouverture fichier Loc");
        return NULL;
    }
    fscanf(fLoca, "%d", nbelem);
    for (int i=0; i< *nbelem; i++)
    {
    	loc = lireLocataire(fLoca);
    	f = Enfillercharge(f, loc);
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

Files ViderFile (Files *pf)
{
	while (!EstVide(*pf))
		*pf = defiler(*pf);
	return NULL;
}

void RechLoca (Files f, int numlocataire)
{
	Files tmp=f->suiv;
	while(f!=tmp){
		if (numlocataire < tmp->loc.numloca)
			return;
		if (numlocataire == tmp->loc.numloca)
			AffichLocatairePrecis(tmp);
		tmp=tmp->suiv;
	}
	if (numlocataire == f->loc.numloca)
			AffichLocatairePrecis(f);
}

void AffichLocataire(Files f)
{
	Files tmp=f;
	tmp=tmp->suiv;
	while(f!=tmp)
	{
		printf("> n°locataire : %d \n> nom : %s \n> prenom : %s\n> nationalite : %s\n> plafond : %d\n> revenu : %.2f\n> n°logement : %d\n> Prix du logement : %.2f€/mois \n>date d'arrivé au logement : %d/%d/%d\n",tmp->loc.numloca, tmp->loc.prenom, tmp->loc.nom, tmp->loc.nationalite, tmp->loc.plafond, tmp->loc.revenu, tmp->loc.numlogement, tmp->loc.prixLog, tmp->loc.datedebutloca.jours, tmp->loc.datedebutloca.mois, tmp->loc.datedebutloca.annee);
		printf("n° Téléphone(s) : \n");
		for (int i=0; i<tmp->loc.nbNumTel; i++) 
        {
            printf("\t-> %s :  %s\n", tmp->loc.numTel[i].libelle, tmp->loc.numTel[i].num);
        }
        printf("\n");
		tmp=tmp->suiv;
	}
	printf("> N°locataire : %d \n> Nom : %s \n> Prenom : %s\n> Nationalite : %s\n> Plafond : %d\n> Revenu : %.2f\n> N°logement : %d\n>  Prix du logement : %.2f€/mois \n> date d'arrivé au logement : %d/%d/%d\n", f->loc.numloca ,f->loc.prenom, f->loc.nom, f->loc.nationalite, f->loc.plafond, f->loc.revenu, f->loc.numlogement, f->loc.prixLog, f->loc.datedebutloca.jours, f->loc.datedebutloca.mois, f->loc.datedebutloca.annee);
	printf("N° Téléphone(s) : \n");
	for (int i=0; i<f->loc.nbNumTel; i++) 
        {
            printf("\t-> %s :  %s\n", f->loc.numTel[i].libelle, f->loc.numTel[i].num);
        }
    printf("\n");
}

void AffichLocatairePrecis(Files f)
{
	printf("\t -- Toutes les informations sur le n°%s %s --\n", f->loc.nom, f->loc.prenom);
	printf("+-------------------------------------------------------------------------------+\n");
	printf("> N°locataire %d \n> Nationalite : %s\n> Plafond : %d\n> Revenu : %.2f\n> N°logement : %d\n> Prix du logement : %.2f€/mois \n> Date d'arrivé au logement : %d/%d/%d\n", f->loc.numloca, f->loc.nationalite, f->loc.plafond, f->loc.revenu, f->loc.numlogement, f->loc.prixLog, f->loc.datedebutloca.jours, f->loc.datedebutloca.mois, f->loc.datedebutloca.annee);
}

void AffichTab (Locataire *tloc[], int nbtl)
{
	int i;
	for ( i = 0 ; i < nbtl ; i++)
	{
		printf("+-------------------------------------------------------------------------------+\n");
		printf("> N°locataire : %d \n> Nom : %s \n> Prenom : %s\n> Nationalite : %s\n> Plafond : %d\n> Revenu : %.2f\n> N°logement : %d\n>  Prix du logement : %.2f€/mois \n> date d'arrivé au logement : %d/%d/%d\n", tloc[i]->numloca, tloc[i]->nom, tloc[i]->prenom, tloc[i]->nationalite, tloc[i]->plafond, tloc[i]->revenu, tloc[i]->numlogement, tloc[i]->prixLog, tloc[i]->datedebutloca.jours, tloc[i]->datedebutloca.mois, tloc[i]->datedebutloca.annee);

	}
}


int TransfertTab (Files f, Locataire *tloc[], int tmax)
{
	Locataire *nvt;
	int nvtTaille = tmax +5;
	Files tmp=f, temp;
	tmp = tmp->suiv;
	int i = 0;


	while(f != tmp)
	{
		tloc[i] = (Locataire *) malloc (sizeof(Locataire));
		if (tloc[i] == NULL)
		{
			printf("problème de malloc");
			exit(1);
		}

		if (tmax <= i)
		{
			nvt = (Locataire *) realloc (tloc, nvtTaille * sizeof(Locataire));
			if (nvt == NULL)
			{
				printf("probleme de realloc \n");
				exit(1);
			}
		}

		*tloc[i] = tmp->loc;
		temp = tmp->suiv;
		tmp = temp;
		i ++;
	}

	tloc[i] = (Locataire *) malloc (sizeof(Locataire));
		if (tloc[i] == NULL)
		{
			printf("problème de malloc");
			exit(1);
		}
	if (tmax == i)
		{
			tloc[i]=(Locataire*)realloc(tloc, sizeof(Locataire));
			tmax=+1;
			if (tloc[i] == NULL)
			{
				printf("problème de realloc n°2\n");
				exit(1);
			}
		}
	*tloc[i] = f->loc;
	temp = f->suiv;
	i ++;
	return i;
}

Files TransfertFiles (Files f, Locataire *tloc[], int nbtl)
{
	int i, j;
	// FileVide();

	for ( i = 0 ; i < nbtl; i ++)
	{
		f = Enfillercharge(f, *tloc[i]);
	}
}

Locataire ViderTab (Locataire *tloc[], int nbtl)
{
	int i;
	for ( i = nbtl+1 ; i< nbtl ; i --)
	{
		free(tloc[i]);
	}
}

int RechMinPrixLoge (Locataire *tloc[], int nbtl, int i)
{
	int prix = i, j;
	for (j = i+1 ; j < nbtl ; j ++)
	{
		if(tloc[j]->prixLog < tloc[prix]->prixLog)
			prix = j;
	}
	return prix;
}

int RechMinNomLoca (Locataire *tloc[], int nbtl, int i)
{
	int nom = i, j;
	for (j = i+1 ; j < nbtl ; j ++)
	{
		if(strcmp(tloc[j]->nom, tloc[nom]->nom) < 0 )
			nom = j;
	}
	return nom;
}



int RechMinDate (Locataire *tloc[], int nbtl, int i)
{
	int date = i, j, k, l;
	for ( j = i+1 ; j < nbtl ; j ++)
	{
		if (tloc[j]->datedebutloca.annee < tloc[date]->datedebutloca.annee)
			date = j;
	
			for ( k = i ; k < i ; k ++)
			{
				if (tloc[k]->datedebutloca.annee == tloc[date]->datedebutloca.annee)
					if (tloc[k]->datedebutloca.mois < tloc[date]->datedebutloca.mois)
						date = k;
			
						for ( l = i ; l < k ; l ++)
						{
							if(tloc[l]->datedebutloca.mois == tloc[date]->datedebutloca.mois)
								if(tloc[l]->datedebutloca.jours < tloc[date]->datedebutloca.jours)
									date = l;
						}
			}
	}
	return date;
}


int RechMinNumLoca (Locataire *tloc[], int nbtl, int i)
{
	int min = i, j;
	for (j = i+1 ; j < nbtl ; j ++)
	{
		if(tloc[j]->numloca < tloc[min]->numloca)
			min = j;
	}
	return min;
}

void Permute (Locataire *tloc[], int x, int y)
{
	Locataire *temp;
	temp = tloc[x];
	tloc[x] = tloc[y];
	tloc[y] = temp;
}

void TriePermuteLoge (Locataire *tloc[], int nbtl)
{
	int i;
	for (i = 0 ; i < nbtl -1 ; i ++)
		Permute(tloc, i, RechMinPrixLoge(tloc, nbtl, i));
}

void TriePermuteDate (Locataire *tloc[], int nbtl)
{
	int i;
	for (i = 0 ; i < nbtl -1 ; i ++)
		Permute(tloc, i, RechMinDate(tloc, nbtl, i));
}

void TriePermuteNumLoca (Locataire *tloc[], int nbtl)
{
	int i;
	for (i = 0 ; i < nbtl -1 ; i ++)
		Permute(tloc, i, RechMinPrixLoge(tloc, nbtl, i));
}

void TriePermuteNomLoca (Locataire *tloc[], int nbtl)
{
	int i;
	for (i = 0 ; i < nbtl -1 ; i ++)
		Permute(tloc, i, RechMinNomLoca(tloc, nbtl, i));
}
