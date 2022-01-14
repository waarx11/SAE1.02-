#include "hlm.h"

#define TAILLE 15


/**
 *\ file  hlmLocataire.c
 *\ brief  Ce fichier contiendra toute les fonctions nécessaire a la transmission d'informations sur un ou plusieurs locataire 
 *\ autor  VERDIER Nathan, MUZARD Thomas
 *\ date 14 janvier 2020
 * 
 * Dans cette partie du code, nous avons choisie les Files pour exploité un peu toute les notions vue en cours
 * De plus on pensait judicieux des file pour un locataire, toutefois, nous avons rencontrer un problème au niveau des tries que nous avons comblé avec des tableaux de pointeurs
 * 
 * Pour le choix du trie utilisé dans cette partie, nous avons prie le tri par permutation facilitant la régulation de ce que l'on souhaite trier dans le teableau
 * De plus, même si ce n'est pas la plus optimiser, c'est un fonction qui reste tout à fait efficace, dans l'optimisation du chargement du programme et dans la vitesse a laquelle elle trie
 */


/**
 *\ brief Permet de lire un locataire dans le fichier
 *\ param *fLoca : fichier locataire
 *\ return Un locataire
 */
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

/**
 *\ brief Permet de charger dans la file, les informations du locataire renseigner dans le fichier
 *\ param Files f : C'est un pointeur d'un maillon qui pointe sur locataire
 *\ param *nbelem : permet de définir le nombre d'élément dans le fichier
 *\ param *fic2 : définir le nom du fichier lors de l'ouverture
 *\ return Une file
 */
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

/**
 *\ brief Fonction permettant de charger les locataire dans la file
 *\ param Files f : C'est un pointeur d'un maillon pointant sur un locataire
 *\ param Locataire loca : Structure des données de locataire
 *\ return Une file
 */
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

/**
 *\ brief Permet de déterminer si la file et vide ou non
 *\ param C'est un pointeur d'un maillon pointant sur un locataire
 *\return Un booleen c'est à dire Vrai ou Faux (1 ou 0)
 */
Booleen EstVide (Files f)
{
	if (f == NULL)
		return Vrai;
	return Faux;
}

/**
 *\ brief Initialisation de la file
 *\ return Une file (NULL)
 */
Files FileVide(void)
{
	return NULL;
}

/**
 * \brief Permet de déterminer si le numéro de locataire existe déja ou non
 * \param Files f, c'est un pointeur d'une maillon pointant sur un locataire
 * \param value Se sera ici le futur numéro de locataire lors d'un ajout locataire
 * \return Un booleen, c'est à dire vrai ou faux
 */
Booleen numExiste2(Files f, int value)
{
	Files tmp;
	if (EstVide(f))
	{
		return Faux;
	}

	if (f->suiv->loc.numloca == value)
		return Vrai;
	tmp=f->suiv;

	while(tmp!=f){
		tmp=tmp->suiv;
	if (value == f->loc.numloca)
		return Vrai;;
	}
	return Faux;
}

/**
 * \brief Cette fonction est utilisé pour ajouter un locataire dans la file
 * \param Files F : c'est un pointeur d'un maillon pointant sur un locataire
 * \param prenom[] chaine de caractère du prénom du locataire
 * \param nom[] chaine de caractère du nom du locataire
 * \param nationalite[] chaine de caractere de la nationalité du locataire
 * \param plafond entier définissant le plafond du locataire
 * \param revenu reel définissant le revenu annuel du locataire
 * \param numloge entier définissant le numéro de logement attribué au locataire
 * \param prixlog réel définissant le prix du logement attribué au locataire
 * \param nbNumTel entier nombre de numéro indiqué par le locataire
 * \param libelle[] chaine de caractère libellant le numéro de téléphone
 * \param numTel[] chaine de caractère du numéro de téléphone
 * \return Une file
 */
Files EnfillerLoca (Files f,int numloca, char prenom[], char nom[], char nationalite[], int plafond, float revenu, int numloge, float prixlog, int nbNumTel, char *libelle, char *numTel)
{
	MaillonLoc *m;
	int jours, mois, an, numLoc, nbNum, s;
	Booleen existe;
	m = (MaillonLoc *)malloc(sizeof(MaillonLoc));
	if (m == NULL)
	{
		printf("Problème de malloc");
		exit(1);
	}
	//Valeur aléatoire compris entre 0 et 5000
    srand(time(NULL));
    //date courant
    time_t now;
    time(&now);
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
	m->loc.prixLog = prixlog;
	m->loc.datedebutloca.annee = an;
	m->loc.datedebutloca.mois = mois;
	m->loc.datedebutloca.jours = jours;
    m->loc.nbNumTel=nbNum;
    m->loc.numTel = (Tel *) malloc(sizeof(Tel)*nbNum);
    for (int i=0; i<nbNum; i++) 
    {
        strcpy(m->loc.numTel->libelle,libelle);
        strcpy(m->loc.numTel->num,numTel);
    }
	m->suiv = NULL;
	if(EstVide(f))
	{
		m->suiv = m;
		return m;
	}
	m->suiv = f->suiv;
	f->suiv = m;
	return m;
}

/**
 * \brief Supprime le premier element d'une file
 * \param Files f : C'est un pointeur d'un maillon pointant sur un locataire
 * \return Une file
 */
Files defiler(Files f)
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
    free(tmp->loc.numTel);
    free(tmp);
    return f;
}

/**
 * \brief Supprime un élément de la file et modifie la taille du fichier
 * \param Files f : c'est un pointeur d'un maillon pointant sur un locataire
 * \param *nbL entier du nombre de locataire dans le fichier
 * \return Une file
 */
Files defiler2(Files f, int *nbL)

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
    free(tmp->loc.numTel);
    free(tmp);
    (*nbL)--;
    return f;
}

/**
 * \brief Supprime un locataire précis dans la file
 * \param Files f : c'est un pointeur d'une maillon pointant sur un locataire
 * \param numlocataire entier du locataire a supprimer dans la file
 * \return Une file
 */
Files defilerLocaPrecis (Files f, int numlocataire, int *log)
{
	Files tmp;
	if (EstVide(f))
	{
		return NULL;
	}

	if (f->suiv->loc.numloca == numlocataire)
	{
		defiler(f);
		return f;
	}
	tmp=f->suiv;

	while(tmp!=f){
		if (numlocataire < tmp->suiv->loc.numloca)
			return f;
		if (tmp->suiv->loc.numloca == numlocataire)
		{
			defiler(tmp);
			*log=tmp->suiv->loc.numlogement;
		}
		tmp=tmp->suiv;
	}
	if (numlocataire == f->loc.numloca)
	{
		defiler(f);
		*log=f->loc.numlogement;
	}
	return f;
}

/**
 * \brief Permet de sauvegarder les modifications dans le fichier
 * \param Files f : c'est un pointeur d'un maillon pointant sur un locataire
 * \param *fLoc Fichier locataire
 */
void sauvegardeLoc(Files f, FILE *fLoc)
{
    if (f == NULL)
        return;
    sauvegardeLoc(f->suiv, fLoc);
    fprintf(fLoc, "%d %s %s %s %d %f %d %f %d %d %d %d ", f->loc.numloca ,f->loc.prenom, f->loc.nom, f->loc.nationalite, f->loc.plafond, f->loc.revenu, f->loc.numlogement, f->loc.prixLog, f->loc.datedebutloca.jours, f->loc.datedebutloca.mois, f->loc.datedebutloca.annee, f->loc.nbNumTel);
    for (int i=0 ; i<f->loc.nbNumTel ; i++) 
    {
        fprintf(fLoc, "%s %s ", f->loc.numTel[i].libelle, f->loc.numTel[i].num);
    }
    fprintf(fLoc,"\n");
}

/**
 * \brief Supprime tout le contenue du fichier, pour réécrire les modifications
 * \param Files f : c'est un pointeur d'un maillon pointant sur un locataire
 * \param *nbL entier du nombre de locataire dans le fichier
 */
void suppressionAll2(Files f, int *nbL)
{
    if (f == NULL)
        return ;
    suppressionAll2(f->suiv, nbL);
   	defiler2(f, nbL);
    return;
}

/**
 * \brief Permet de vider l'ensemble de la file
 * \param Files *pf : c'est un pointeur sur une file d'un pointeur d'un maillon pointant sur un locataire
 * \return Une file
 */
Files ViderFile (Files *pf)
{
	while (!EstVide(*pf))
		*pf = defiler(*pf);
	return NULL;
}

/**
 * \brief Recherche d'un locataire dans la file et l'affiche
 * \param Files f : pointeur d'un maillon pointant sur un locataire
 * \param numlocataire entier du numéro de locataire à rechercher
 */
void RechLoca (Files f, int numlocataire)
{
	Files tmp=f->suiv;
	while(f!=tmp){
		if (numlocataire == tmp->loc.numloca)
		{
			AffichLocatairePrecis(tmp);
			return;
		}
		tmp=tmp->suiv;
	}
}

/**
 * \brief Affiche l'ensemble de la file des locataires
 * \param Files f : c'est un pointeur d'un maillon pointant sur un locataire
 */
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

/**
 * \brief Affiche un locataire dans la file
 * \param Files f : c'est un pointeur d'un maillon pointant sur un locataire
 */
void AffichLocatairePrecis(Files f)
{
	printf("\t -- Toutes les informations sur le n°%s %s --\n", f->loc.nom, f->loc.prenom);
	printf("+-------------------------------------------------------------------------------+\n");
	printf("> N°locataire %d \n> Nationalite : %s\n> Plafond : %d\n> Revenu : %.2f\n> N°logement : %d\n> Prix du logement : %.2f€/mois \n> Date d'arrivé au logement : %d/%d/%d\n", f->loc.numloca, f->loc.nationalite, f->loc.plafond, f->loc.revenu, f->loc.numlogement, f->loc.prixLog, f->loc.datedebutloca.jours, f->loc.datedebutloca.mois, f->loc.datedebutloca.annee);
}

/**
 * \brief Affiche les locataires dans le tableau de pointeur
 * \param Locataire *tloc[] tableau pointeur des locataires
 * \param nbtl nombre de locataire dans le tableau
 */
void AffichTab (Locataire *tloc[], int nbtl)
{
	int i;
	for ( i = 0 ; i < nbtl ; i++)
	{
		printf("+-------------------------------------------------------------------------------+\n");
		printf("> N°locataire : %d \n> Nom : %s \n> Prenom : %s\n> Nationalite : %s\n> Plafond : %d\n> Revenu : %.2f\n> N°logement : %d\n>  Prix du logement : %.2f€/mois \n> date d'arrivé au logement : %d/%d/%d\n", tloc[i]->numloca, tloc[i]->nom, tloc[i]->prenom, tloc[i]->nationalite, tloc[i]->plafond, tloc[i]->revenu, tloc[i]->numlogement, tloc[i]->prixLog, tloc[i]->datedebutloca.jours, tloc[i]->datedebutloca.mois, tloc[i]->datedebutloca.annee);

	}
}

/**
 * \brief copie les élément de la file dans un tableau de pointeur
 * \param Files f : c'est un pointeur d'un maillon pointant sur un locataire
 * \param Locataire *tloc[] tableau de pointeur des locataires
 * \param tmax taille max du tableau
 * \return la taille logique du tableau
 */
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
			tloc[i] = (Locataire *) realloc (tloc, nvtTaille * sizeof(Locataire));
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
			tloc[i]=(Locataire*)realloc(tloc, nvtTaille * sizeof(Locataire));
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

/**
 * \brief Vide le tableau de pointeur
 * \param Locataire *tloc[] : tableau de pointeur des locataires
 * \param nbtl taille logique du tableau
 */
void ViderTab (Locataire *tloc[], int nbtl)
{
	int i;
	for ( i = 0 ; i< nbtl ; i ++)
	{
		free(tloc[i]);
	}
}

/**
 * \brief Recherche le locataire payant le moins cher son logement
 * \param Locataire *tloc[] : tableau de pointeur des locataires
 * \param nbtl taille logique du tableau
 * \param i position de l'emplacement
 * \return l'emplacement de l'élément
 */
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

/**
 * \brief Recherche le locataire par son nom
 * \param Locataire *tloc[] : tableau de pointeur des locataires
 * \param nbtl taille logique du tableau
 * \param i position de l'emplacement
 * \return l'emplacement de l'élément
 */
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


/**
 * \brief Recherche le locataire arriver en dernier dans son logement
 * \param Locataire *tloc[] : tableau de pointeur des locataires
 * \param nbtl taille logique du tableau
 * \param i position de l'emplacement
 * \return l'emplacement de l'élément
 */
int RechMinDate (Locataire *tloc[], int nbtl, int i)
{
	int date = i, j, k, l;
	for ( j = i+1 ; j < nbtl ; j ++)
	{
		if (tloc[j]->datedebutloca.annee < tloc[date]->datedebutloca.annee)
		{
			date = j;
			for ( k = i ; k < i ; k ++)
			{
				if (tloc[k]->datedebutloca.annee == tloc[date]->datedebutloca.annee)
				{
					if (tloc[k]->datedebutloca.mois < tloc[date]->datedebutloca.mois)
					{
						date = k;
			
						for ( l = i ; l < k ; l ++)
						{
							if(tloc[l]->datedebutloca.mois == tloc[date]->datedebutloca.mois)
							{
								if(tloc[l]->datedebutloca.jours < tloc[date]->datedebutloca.jours)
									date = l;
							}
						}
					}
						
				}
			}
		}
			
	}
	return date;
}

/**
 * \brief permute 2 emplacement dans le tableau
 * \param Locataire *tloc[] : tableau de pointeur des locataires
 * \param x première élément
 * \param y deuxième élément
 */
void Permute (Locataire *tloc[], int x, int y)
{
	Locataire *temp;
	temp = tloc[x];
	tloc[x] = tloc[y];
	tloc[y] = temp;
}

/**
 * \brief Trie le tableau 
 * \param Locataire *tloc[] : tableau de pointeur des locataires
 * \param nbtl taille logique du tableau
 */
void TriePermuteLoge (Locataire *tloc[], int nbtl)
{
	int i;
	for (i = 0 ; i < nbtl -1 ; i ++)
		Permute(tloc, i, RechMinPrixLoge(tloc, nbtl, i));
}

/**
 * \brief Trie le tableau 
 * \param Locataire *tloc[] : tableau de pointeur des locataires
 * \param nbtl taille logique du tableau
 */
void TriePermuteDate (Locataire *tloc[], int nbtl)
{
	int i;
	for (i = 0 ; i < nbtl -1 ; i ++)
		Permute(tloc, i, RechMinDate(tloc, nbtl, i));
}

/**
 * \brief Trie le tableau 
 * \param Locataire *tloc[] : tableau de pointeur des locataires
 * \param nbtl taille logique du tableau
 */
void TriePermuteNomLoca (Locataire *tloc[], int nbtl)
{
	int i;
	for (i = 0 ; i < nbtl -1 ; i ++)
		Permute(tloc, i, RechMinNomLoca(tloc, nbtl, i));
}
