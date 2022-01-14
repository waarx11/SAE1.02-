#include "hlm.h"
#include <stdio.h>
#include <stdlib.h>

Logement lireLog(FILE *fe)
{
    Logement log;
    fscanf(fe, "%d %s %d %f %f %d %d %d ", &log.numLogement, log.typeLog, &log.nbChambre, &log.surfaceLog, &log.prixLog, &log.dateAchat.jours, &log.dateAchat.mois, &log.dateAchat.annee);
    fgets(log.dispo,5,fe);
    log.dispo[strlen(log.dispo)-1]='\0';
    return log;
}

Logement* chargeLogement(FILE *fe, int *nbLog)
{
    Logement* log;
    fscanf(fe,"%d", nbLog);
    log = (Logement *) malloc(sizeof(Logement) * *nbLog);
    if (log == NULL)
    {
        printf("Problème d'allocation de memoire (malloc)! \n");
        exit(1);
    }
    for (int i=0;i<*nbLog;i++)
    {
        log[i]=lireLog(fe);
    }
    fclose(fe);
    return log;
}

void affichageLog(Logement tLog[], int nbLog)
{
    printf("Nombre de logement posséder : %d\n", nbLog);
    for(int i=0;i<nbLog;i++)
    {
        printf("-----------------------------------------------------------------------------------------------------\n\n");
        printf("Numero du logement : %d\n\nType de logement : %s\nNombre de chambre : %d\nPrix de la location : %.2f\nPrix de l'achat : %.2f\n\nDate de l'achat : %d/%d/%d\nLogement louer : %s\n\n", tLog[i].numLogement, tLog[i].typeLog, tLog[i].nbChambre, tLog[i].surfaceLog, tLog[i].prixLog, tLog[i].dateAchat.jours, tLog[i].dateAchat.mois, tLog[i].dateAchat.annee, tLog[i].dispo);
        printf("-----------------------------------------------------------------------------------------------------\n\n"); 
    }
}

int supprime(Logement *tLog, int nbLog)
{
    int pos, value;
    printf("Saisir Le numéro de logement a supprimer : ");
    scanf("%d",&value);
    pos = rechercheDico(tLog, nbLog, value);
    if (strcmp(tLog[pos].dispo,"Oui")==0)
    {
        for(int i = pos;i<nbLog-1;i++)
        {
            tLog[i] = tLog[i+1];
        }
        nbLog--;
        tLog=(Logement*)realloc(tLog, sizeof(Logement)-1);
    }
    else
        printf("Le logement est louer vous nous pouvez pas le vendre\n");
    return nbLog;
}

int rechercheDico(Logement *tLog, int nbLog, int value)
{
    int deb=0,m,fin=nbLog-1;
    while(deb<=fin)
    {
	m=(deb+fin)/2;
	if(value<=tLog[m].numLogement)
		fin=m-1;
	else
		deb=m+1;
    }
    return deb;
}

Booleen numLogExiste(Logement *tLog, int value, int nbLog)
{
    for(int i=0;i<nbLog;i++)
        if (tLog[i].numLogement==value) 
            return Vrai;
    return Faux;
}

int insertionLog(Logement *tLog, int nbLog)
{
    int pos, value, numLog;
    Booleen existe;
    numLog=rand() %5000;
    existe=numLogExiste(tLog,numLog, nbLog);
    while (existe==Vrai)
    {
        numLog=rand() %5000;
        existe=numLogExiste(tLog,numLog, nbLog);
    }
    printf("Saisir Le numéro de logement a supprimer : ");
    scanf("%d",&value);
    pos = rechercheDico(tLog, nbLog, value);
    if (strcmp(tLog[pos].dispo,"Oui")==0)
    {
        for(int i = pos;i<nbLog-1;i++)
        {
            tLog[i] = tLog[i+1];
        }
        nbLog--;
        tLog=(Logement*)realloc(tLog, sizeof(Logement)-1);
    }
    else
        printf("Le logement est louer vous nous pouvez pas le vendre\n");
    return nbLog;
}



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
