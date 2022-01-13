#include "hlm.h"

Logement lireLog(FILE *fe)
{
    Logement log;
    fscanf(fe, "%d %s %d %f %f %d %d %d", &log.numLogement, log.typeLog, &log.nbChambre, &log.surfaceLog, &log.prixLog, &log.dateAchat.jours, &log.dateAchat.mois, &log.dateAchat.annee);
    return log; 
}

int chargeLogement(char *nomFich, Logement *tLog[], int taillemax)
{
    int i=0;
    FILE *fe;
    Logement log;
    fe = fopen(nomFich,"r");
    if(fe == NULL)
    {
        printf("Problème ouverture fichier\n");
        return -1;
    }
    tLog[i]=(Logement*)realloc(tLog,sizeof(Logement));
    log=lireLog(fe);
    while(feof(fe)==0)
    {
        tLog[i]=(Logement*)malloc(sizeof(Logement));
        if (tLog[i] == NULL)
        {
            printf("Problème d'allocation de memoire (realloc)! \n");
            exit(1);
        }
        *tLog[i]=log;
        log=lireLog(fe);
        i++;
    }
    fclose(fe);
    return i;
}


void affichageLog(Logement *tLog[], int nb)
{
    for(int i=0;i<nb;i++)
        printf("Numero du logement : %d\n\nType du logement : %s\nLe logement possede %d chambre et une surface de %.2f metre carre\n\nLe prix du logement est de : %.2f\nLogement acheter le : %d/%d/%d", tLog[i]->numLogement, tLog[i]->typeLog, tLog[i]->nbChambre, tLog[i]->surfaceLog, tLog[i]->prixLog, tLog[i]->dateAchat.jours, tLog[i]->dateAchat.mois, tLog[i]->dateAchat.annee);
}

// int rechercheDico(Logement **tArt, int n, char *value)
// {
//     int deb=0,m,fin=n-1;
//     while(deb<=fin)
//     {
// 	m=(deb+fin)/2;
// 	if(strcmp(value,tArt[m]->tRef)<=0)
// 		fin=m-1;
// 	else
// 		deb=m+1;
//     }
//     return deb;
// }


// int supprime(Logement **tArt, int nbart)
// {
//     int pos;
//     char value[20];
//     printf("Saisir un ref a supprimer : ");
//     fgets(value,19,stdin);
//     value[strlen(value)-1]='\0';
//     pos = rechercheDico(tArt, nbart, value);
//     free(tArt[pos]);
//     for(int i = pos;i<nbart-1;i++)
//     {
//         tArt[i] = tArt[i+1];
//     }
//     nbart--;
//     return nbart;
// }







/*
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
    return p;
}

void affichageLogement(PileLog p)
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
    Date dateAchat;
    m->suivant=p;
    return m;
}*/
