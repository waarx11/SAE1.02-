#include "hlm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \file hlmLogement.c
 * \brief Ce fichier contiendra l'ensemble des fonction nécessaire au traitement des logement de la société
 * \author VERDIER Nathan, MUZARD Thomas
 * \date 14 janvier 2022
 * 
 * Dans cette partit du programme, nous utilisons des tableaux pour exploité au mieux toute les notions vue en cours
 * De plus, il était plus facile pour nous de faire les logement dans un tableau pour la simplicité du code
 * 
 * Ici, nous trions dans l'insertion du logement par numéro de logement
 */

/**
 * \brief Lit un logement dans le fichier
 * \param *fe : fichier des logements
 * \return Un tableau
 */
Logement lireLog(FILE *fe)
{
    Logement log;
    fscanf(fe, "%d %s %d %f %f %d %d %d ", &log.numLogement, log.typeLog, &log.nbChambre, &log.surfaceLog, &log.prixLog, &log.dateAchat.jours, &log.dateAchat.mois, &log.dateAchat.annee);
    fgets(log.dispo,5,fe);
    log.dispo[strlen(log.dispo)-1]='\0';
    return log;
}

/**
 * \brief Charge dans le table, les éléments du fichier
 * \param *fe : fichier logement
 * \param *nbLog nombre de logement
 * \return Un tableau
 */
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

/**
 * \brief Affiche les information des logements
 * \param Logement tLog[] : Emplacement dans le tableau des logements
 * \param nbLog nombre de logement
 */
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

/**
 * \brief Supprime un logement dans le tableau
 * \param Logement *tLog : Emplacement dans le tableau des logements
 * \param nbLog nombre de logement
 * \return la position de l'élément
 */
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

/**
 * \brief recherche dans le tableau, un numéro de logement 
 * \param Logement *tLog Emplacement dans le tableau des logement
 * \param nbLog nombre de logement
 * \value numéro de logement rechercher
 * \return la position logement rechercher
 */
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

/**
 * \brief Recherche si le numéro de logement existe ou non
 * \param Logement *tLog Emplacement dans le tableau des logements
 * \param value Numéro de logement
 * \param nbLog Nombre de logement
 * \return Vrai ou Faux
 */
Booleen numLogExiste(Logement *tLog, int value, int nbLog)
{
    for(int i=0;i<nbLog;i++)
        if (tLog[i].numLogement==value) 
            return Vrai;
    return Faux;
}

/**
 * \brief Insère un logement dans le tableau
 * \param Logement *tLog Emplacement dans le tableau des logements
 * \param *nbLog nombre de logements dans le tableau
 * \return Un tableau
 */
Logement* insertionLog(Logement *tLog, int *nbLog)
{
    int pos=0, value, numLog, nbChambre, jours, mois, an;
    float surf, achat;
    char type[5];
    Booleen existe;
    Logement *tRel;
    numLog=rand() %4999 +1;
    existe=numLogExiste(tLog,numLog, *nbLog);
    while (existe==Vrai)
    {
        numLog=rand() %4999 +1;
        existe=numLogExiste(tLog,numLog, *nbLog);
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
    pos = rechercheDico(tLog, *nbLog, numLog);
    tRel=(Logement*)realloc(tLog, sizeof(Logement)*(*nbLog+1));
    if (tRel==NULL) 
    {
        printf("Problème de reallocation de memoire");
        exit(1);
    }
    tLog=tRel;
    for(int i=*nbLog;i>pos;i--)
        tLog[i] = tLog[i-1];
    tLog[pos].numLogement=numLog;
    strcpy(tLog[pos].typeLog,type);
    tLog[pos].nbChambre=nbChambre;
    tLog[pos].surfaceLog=surf;
    tLog[pos].prixLog=achat;
    tLog[pos].dateAchat.jours=jours;
    tLog[pos].dateAchat.mois=mois;
    tLog[pos].dateAchat.annee=an;
    strcpy(tLog[pos].dispo,"Oui");
    (*nbLog)++;
    return tLog;
}

/**
 * \brief Affiche les logements disponible
 * \param Logement *tLog : Emplacement dans le tableau de logement
 * \param nbLog nombre de logement
 */
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

/**
 * \brief Sauvegarde dans le fichier logements les ajout et suppression d'un logements
 * \param Logement *tLog Tableau des logement
 * \param nbLog nombre de logements
 * \param *fe fichier des logements
 */
void sauvegardeLog(Logement tLog[], int nbLog, FILE *fe)
{
    for (int i=0; i<nbLog; i++)
        fprintf(fe, "%d %s %d %.2f %.2f %d %d %d %s\n", tLog[i].numLogement, tLog[i].typeLog, tLog[i].nbChambre, tLog[i].surfaceLog, tLog[i].prixLog, tLog[i].dateAchat.jours, tLog[i].dateAchat.mois, tLog[i].dateAchat.annee, tLog[i].dispo);
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
