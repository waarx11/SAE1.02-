#include "hlm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    Logement *tRel;
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
        tRel=(Logement*)realloc(tLog, sizeof(Logement) * nbLog);
        if (tRel==NULL) 
        {
            printf("Problème de reallocation de memoire");
            return nbLog+1;
        }
        else
            tLog=tRel;  
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
    int pos=0, value, numLog, nbChambre, jours, mois, an;
    float surf, achat;
    char type[5];
    Booleen existe;
    Logement *tRel;
    numLog=rand() %4999 +1;
    existe=numLogExiste(tLog,numLog, nbLog);
    while (existe==Vrai)
    {
        numLog=rand() %4999 +1;
        existe=numLogExiste(tLog,numLog, nbLog);
    }
    printf("Saisir le type du logement : ");
    fgets(type,4, stdin);
    type[strlen(type)-1]='\0';
    printf("Nombre de chambre : ");
    scanf("%d", &nbChambre);
    printf("La surface du logement : ");
    scanf("%f", &surf);
    printf("Le prix du logement a l'achat : ");
    scanf("%f", &achat);
    printf("La date de l'achat (dd mm yyyy): ");
    scanf("%d %d %d%*c", &jours, &mois, &an);
    pos = rechercheDico(tLog, nbLog, numLog);
    tRel=(Logement*)realloc(tLog, sizeof(Logement)*(nbLog+1));
    if (tRel==NULL) 
    {
        printf("Problème de reallocation de memoire");
        return nbLog;
    }
    tLog=tRel;
    free(tRel);
    for(int i=nbLog;i>=pos;i--)
        tLog[i+1] = tLog[i];
    tLog[pos].numLogement=numLog;
    strcpy(tLog[pos].typeLog,type);
    tLog[pos].nbChambre=nbChambre;
    tLog[pos].surfaceLog=surf;
    tLog[pos].prixLog=achat;
    tLog[pos].dateAchat.jours=jours;
    tLog[pos].dateAchat.mois=mois;
    tLog[pos].dateAchat.annee=an;
    strcpy(tLog[pos].dispo,"Oui");
    nbLog++;
    return nbLog;
}

void affichageParType(Logement tLog[], int nbLog)
{
    printf("Les logement disponible\n");
    for(int i=0;i<nbLog;i++)
    {
        if (strcmp(tLog[i].dispo,"Oui")==0)
        {
            printf("-----------------------------------------------------------------------------------------------------\n\n");
            printf("Numero du logement : %d\n\nType de logement : %s\nNombre de chambre : %d\nPrix de la location : %.2f\nPrix de l'achat : %.2f\n\nDate de l'achat : %d/%d/%d\nLogement louer : %s\n\n", tLog[i].numLogement, tLog[i].typeLog, tLog[i].nbChambre, tLog[i].surfaceLog, tLog[i].prixLog, tLog[i].dateAchat.jours, tLog[i].dateAchat.mois, tLog[i].dateAchat.annee, tLog[i].dispo);
            printf("-----------------------------------------------------------------------------------------------------\n\n"); 
        }
    }
}

void affichageLogDispo(Logement tLog[], int nbLog)
{
    printf("Les logement disponible\n");
    for(int i=0;i<nbLog;i++)
    {
        if (strcmp(tLog[i].dispo,"Oui")==0)
        {
            printf("-----------------------------------------------------------------------------------------------------\n\n");
            printf("Numero du logement : %d\n\nType de logement : %s\nNombre de chambre : %d\nPrix de la location : %.2f\nPrix de l'achat : %.2f\n\nDate de l'achat : %d/%d/%d\nLogement louer : %s\n\n", tLog[i].numLogement, tLog[i].typeLog, tLog[i].nbChambre, tLog[i].surfaceLog, tLog[i].prixLog, tLog[i].dateAchat.jours, tLog[i].dateAchat.mois, tLog[i].dateAchat.annee, tLog[i].dispo);
            printf("-----------------------------------------------------------------------------------------------------\n\n"); 
        }
    }
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
