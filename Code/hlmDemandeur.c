#include "hlm.h"

//Ce fichier s'occupe des demandes

Liste initliste(void)
{
    return NULL;
}

Liste lireMenage(FILE *fDem, Liste l)
{
    Maillon *m;
    m=(Maillon *)malloc(sizeof(Maillon));
    m->demandeurs.dateDemande = (Date *) malloc(sizeof(Date));
    if(m==NULL || m->demandeurs.dateDemande==NULL)
    {
        printf("Problème malloc");
        exit(1);
    }
    fscanf(fDem, "%d %d %d %f %s %d %d %d %d %d %d %d", &m->demandeurs.numDemande, &m->demandeurs.nbPoint, &m->demandeurs.nbPersonne, &m->demandeurs.ressourceAnnuel, m->demandeurs.nomDeFamille, &m->demandeurs.numTel, &m->demandeurs.dateDemande->jours, &m->demandeurs.dateDemande->mois, &m->demandeurs.dateDemande->annee, &m->demandeurs.dateDemande->heure, &m->demandeurs.dateDemande->minute, &m->demandeurs.dateDemande->seconde);
    m->suivant=l;
    return m; 
}

void chargementDem(Liste l, FILE *fDem, int *nbD)
{
    fscanf(fDem, "%d", nbD);
    for(int i=0;i<*nbD;i++)
        l=lireMenage(fDem,l);
}

void affichage(Liste l)
{
    if (l==NULL)
        return;
    printf("-----------------------------------------------------------------------------------------------------\n\n");
    printf("Numero de dossier : %d", l->demandeurs.numDemande);
    printf("%d %d %f %s %d", l->demandeurs.nbPoint, l->demandeurs.nbPersonne, l->demandeurs.ressourceAnnuel, l->demandeurs.nomDeFamille, l->demandeurs.numTel);
    printf("Le %d/%d/%d a %d:%d:%d", l->demandeurs.dateDemande->jours, l->demandeurs.dateDemande->mois, l->demandeurs.dateDemande->annee, l->demandeurs.dateDemande->heure, l->demandeurs.dateDemande->minute, l->demandeurs.dateDemande->seconde);
    printf("-----------------------------------------------------------------------------------------------------\n\n");
    affichage(l->suivant);
}

Liste insertionEnTeteDem(Liste l, int nbPoint, int nbPersonne, float ressourceAnnuel, char *nomDeFamille, int numTel)
{
    int jours, mois, an, h, min, s, numDemande;
    Maillon *m;
    m=(Maillon *)malloc(sizeof(Maillon));
    m->demandeurs.dateDemande = (Date *) malloc(sizeof(Date));
    if(m==NULL || m->demandeurs.dateDemande==NULL)
    {
        printf("Problème malloc");
        exit(1);
    }
    //Valeur aléatoire compris entre 0 et 5000
    srand(time(NULL));
    numDemande=rand() %5000;
    //date courant
    time_t now;
    struct tm *local = localtime(&now);
    h=local->tm_hour;
    min=local->tm_min;
    s=local->tm_sec;
    jours=local->tm_mday;
    mois=local->tm_mon+1;
    an=local->tm_year+1900;
    m->demandeurs.numDemande=numDemande+1;
    m->demandeurs.nbPoint=nbPoint;
    m->demandeurs.nbPersonne=nbPersonne;
    m->demandeurs.ressourceAnnuel=ressourceAnnuel;
    strcpy(m->demandeurs.nomDeFamille,nomDeFamille);
    m->demandeurs.numTel=numTel;
    m->demandeurs.dateDemande->jours=jours;
    m->demandeurs.dateDemande->mois=mois;
    m->demandeurs.dateDemande->annee=an;
    m->demandeurs.dateDemande->heure=h;
    m->demandeurs.dateDemande->minute=min;
    m->demandeurs.dateDemande->seconde=s;
    m->suivant=l;
    return m;
}

Liste insertionDem(Liste l, int nbPoint, int nbPersonne, float ressourceAnnuel, char *nomDeFamille, int numTel)
{
    if(l==NULL)
        return insertionEnTeteDem(l, nbPoint, nbPersonne, ressourceAnnuel, nomDeFamille, numTel);
    if (l->demandeurs.nbPoint<nbPoint) 
        return insertionEnTeteDem(l, nbPoint, nbPersonne, ressourceAnnuel, nomDeFamille, numTel);
    l->suivant=insertionDem(l->suivant, nbPoint, nbPersonne, ressourceAnnuel, nomDeFamille, numTel);
    return l;
}

