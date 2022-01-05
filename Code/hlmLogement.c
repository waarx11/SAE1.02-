#include "hlm.h"

PileLog creevide(void)
{
    PileLog p;
    p->logement.numLogement=NULL;
    p->logement.typeLog=;
    p->logement.nbChambre=NULL;
    p->logement.surfaceLog=NULL;
    p->logement.prixLog=0;
    p->logement.dateAchat.jours=NULL;
    p->logement.dateAchat.mois=NULL;
    p->logement.dateAchat.annee=NULL;
    return p;
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
    fscanf(fLog, "%d %s %d %f %f", &m->logement.numLogement, &m->logement.typeLog, &m->logement.nbChambre, );   
    m->suivant=p;
    return m; 
}

void chargementDem(ListeDem l, FILE *fDem, int *nbD)
{

}

void affichageLog(PileLog p)
{
    if(p->logement==NULL)
        return;
    printf("%d %s %d %.2f %.2f\n", p->logement.numLogement, p->logement.typeLog, p->logement.nbChambre, p->logement.surfaceLog, p->logement.prixLog);
    affichageLog(p->suivant);
}

