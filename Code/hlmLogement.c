#include "hlm.h"

PileLog creevide(void)
{
    return NULL;
}

PileLog lireLogement(FILE *fLog, PileLog p)
{
    MaillonLog *m;
    m=(MaillonLog *)malloc(sizeof(MaillonLog));
    m->logement.dateDemande = (Date *) malloc(sizeof(Date));
    if(m==NULL || m->logement.dateAchat==NULL)
    {
        printf("Problème malloc\n");
        exit(1);
    }
    fscanf(fLog, "%d %s %d %f %f", &m->logement.numLogement, &m->logement.typeLog, &m->logement.nbChambre, );   m->suivant=p;
    return m; 
}

void affichage(Pile p)
{
    if(p->logement==NULL)
        return;
    printf("%d %s %d %.2f %.2f\n", p->logement.numLogement, p->logement.typeLog, p->logement.nbChambre, p->logement.surfaceLog, p->logement.prixLog);
    affichage(p->suivant)
}

