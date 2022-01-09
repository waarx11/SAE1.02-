#include "hlm.h"
#include <stdlib.h>

PileLog creevide(void)
{
    return NULL;
}

Booleen EstPileVide(PileLog p)
{
    if (p==NULL) 
        return Vrai;
    return Faux;
}

PileLog lireLogement(FILE *fLog, PileLog p)
{
    MaillonLog *m;
    m=(MaillonLog *)malloc(sizeof(MaillonLog));
    if(m==NULL)
    {
        printf("Problème malloc\n");
        exit(1);
    }
    fscanf(fLog, "%d %s %d %f %f %d %d %d", &m->logement.numLogement, m->logement.typeLog, &m->logement.nbChambre, &m->logement.surfaceLog, &m->logement.prixLog, &m->logement.dateAchat.jours, &m->logement.dateAchat.mois, &m->logement.dateAchat.annee);   
    m->suivant=p;
    return m; 
}

PileLog chargementLog(PileLog p, int *nbD, char *ficLog)
{
    FILE *fLog;
    fLog=fopen(ficLog,"r");
    if (fLog == NULL)
    {
        printf("Problème ouverture fichier Dem");
        return NULL;
    }
    fscanf(fLog, "%d", nbD);
    for(int i=0;i<*nbD;i++)
        p=lireLogement(fLog,p);
    fclose(fLog);
}

void affichageLog(PileLog p)
{
    if(p==NULL)
        return;
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("Le logment numero : %d", p->logement.numLogement);
    printf("Type : %s nbChambre : %d  nbSurface : %.2f  Prix : %.2f \n", p->logement.typeLog, p->logement.nbChambre, p->logement.surfaceLog, p->logement.prixLog);
    printf("Le %d/%d/%d\n\n", p->logement.dateAchat.jours, p->logement.dateAchat.mois, p->logement.dateAchat.annee);
    printf("-----------------------------------------------------------------------------------------------------\n\n");
    affichageLog(p->suivant);
}

PileLog empiler(PileLog p, int numLogement, char *typeLog, int nbChambre, float surfaceLog, float prixLog, char *jour, char *mois, char *annee)
{
    MaillonLog* m;
    m=(MaillonLog*) malloc (sizeof(MaillonLog));
    if (m==NULL)
    {
        printf("Problème de malloc");
        exit(1);
    }
    m->logement.numLogement=numLogement;
    strcpy(m->logement.typeLog,typeLog);
    m->logement.nbChambre=nbChambre;
    m->logement.surfaceLog=surfaceLog;
    m->logement.prixLog=prixLog;
    Date dateAchat
    m->suivant=p;
    return m;
}