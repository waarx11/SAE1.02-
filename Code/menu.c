#include "hlm.h"
#include <stdlib.h>

#define TAILLE 100

void affichMenu(void)
{
	printf("\t Que voulez vous faire : \n");
	printf("+------------------------------------------------+\n");
	printf("| 1. Information sur Locataire \t\t\t |\n");
	printf("| 2. Logement \t\t\t\t\t |\n");
	printf("| 3. Demande de logement \t\t\t |\n");
	printf("| 9. Quitter \t\t\t\t\t |\n");
	printf("+------------------------------------------------+\n");
}

void affichMenuLogement(void)
{
	printf("\t Que voulez vous faire : \n");
	printf("+------------------------------------------------+\n");
	printf("| 1. Ajouter un logement  \t \t \t |\n");
	printf("| 2. Supprimer un logement \t\t\t |\n");
	printf("| 3. Afficher posséder par des HLM63 \t\t |\n");
	printf("| 4. Afficher les types de logement disponible\t |\n");
	printf("| 9. Retour \t\t\t\t\t |\n");
	printf("+------------------------------------------------+\n");
}

void affichChoixTrieLoca(void)
{
	printf("\t Comment souhaitez vous triez la liste : \n");
	printf("+------------------------------------------------+\n");
	printf("| 1. Le nom par ordre alphabétique \t\t |\n");
	printf("| 2. En fonction du prix du logement\t \t |\n");
	printf("| 3. Ordre croissant d'arrivée au logement\t |\n");
	printf("| 4. Affichage de la File sans modification\t |\n");
	printf("| 9. Retour \t\t\t\t\t |\n");
	printf("+------------------------------------------------+\n");
}

void affichMenuLocataire(void)
{
	printf("\t Que voulez vous faire : \n");
	printf("+------------------------------------------------+\n");
	printf("| 1. Afficher la liste des locataires \t\t |\n");
	printf("| 2. Recherche d'un locataire \t\t\t |\n");
	printf("| 3. Ajouter un locataire \t \t\t |\n");
	printf("| 4. Supprimer un locataire   \t\t\t |\n");
	printf("| 9. Retour \t\t\t\t\t |\n");
	printf("+------------------------------------------------+\n");
}

void affichMenuDemLog(void)
{
	printf("\t Que voulez vous faire : \n");
	printf("+------------------------------------------------+\n");
	printf("| 1. Enregistrer une demande \t\t\t |\n");
	printf("| 2. Modifier une demande\t\t\t |\n");
	printf("| 3. Supprimer une demande\t\t\t |\n");
	printf("| 4. Afficher toute les demandes\t\t |\n");
	printf("| 5. Rechercher un Demandeur par son num\t |\n");
	printf("| 9. Retour \t\t\t\t\t |\n");
	printf("+------------------------------------------------+\n");
}

void menu(void)
{
	int nbD, nbL, nbLog, choix;
	char ficDem[30] = "FichierDemLoge.don";
	char ficLoc[30] = "FichierLoca.don";
	char ficlog[30] = "FichierLoge.don";

	ListeDem ld;
	Files lc;
	// PileLog lg;
	Logement *tLog;
	FILE *fl;

	ld = initliste();
	ld = chargementDem(ld, &nbD, ficDem);
	ld = expirationDem(ld, &nbD);

	lc = FileVide();
	lc = chargementLoc(lc, &nbL, ficLoc);

    fl=fopen(ficlog, "rb");
    if(fl==NULL)
    {
        printf("Problème a l'ouverture du fichier logement");
        return;
    }
	tLog = chargeLogement(fl, &nbLog);

	affichMenu();
	scanf("%d%*c", &choix);

	while (choix != 1 && choix != 2 && choix != 3 && choix != 9)
	{
		printf("Choix doit être égale à 1, 2, 3 ou 9. Retapez : ");
		scanf("%d%*c", &choix);
	}

	 while (choix != 9)
	 {
		switch (choix)
		{
			case 1:
				lc = MenuLocataire(lc, &nbL, tLog, &nbLog, ld, &nbD);
			break;

			case 2:
				MenuLogement(tLog, &nbLog);
			break;

			case 3:
				ld=MenuDemLog(ld, &nbD);
			break;
		}

		affichMenu();
		scanf("%d%*c", &choix);

		while (choix != 1 && choix != 2 && choix != 3 && choix != 9)
		{
			printf("Choix doit être égale à 1, 2, 3 ou 9. Retapez : ");
			scanf("%d%*c", &choix);
		}
	 }
	ld = expirationDem(ld, &nbD);
	sauvegardeTout(ld, ficDem, nbD, nbL, lc, ficLoc, tLog, ficlog, nbLog);
}

Files MenuLocataire(Files lc, int *nbL, Logement tLog[], int *nbLog, ListeDem ld, int *nbD)
{
	int choixLoca, locataire, numLoc, existe2, value, i;

	affichMenuLocataire();
	scanf("%d%*c", &choixLoca);

	while (choixLoca != 1 && choixLoca != 2 && choixLoca != 3 && choixLoca != 4 && choixLoca != 9)
	{ 
		printf("Choix doit être égale à 1, 2, 3, 4 ou 9. Retapez : ");
		scanf("%d%*c", &choixLoca);
	}

	 while (choixLoca != 9)
	 {
		switch (choixLoca)
		{
			case 1:
				lc = MenuChoixTrie(lc, nbL);
			break;

			case 2:
				// Fonction recherche locataire
				printf("Saisir un numéro de locataire : \n");
				scanf("%d", &locataire);
				RechLoca(lc->suiv, locataire);
			break;

			case 3:
				// Fonction ajout de locataire
				numLoc=rand() %4999 + 1;
    			existe2=numExiste2(lc,numLoc);
				while (existe2 == Vrai)
				{
					numLoc=rand() % 4999 + 1;
					existe2=numExiste2(lc,numLoc);
				}
				printf("Saisir le numéro de logement que vous souhaitez attribué au locataire : \n");
				scanf("%d", &value);
				i = rechercheDico(tLog, *nbL, value);
				while (strcmp(tLog[i].dispo,"Non")==0)
				{
					printf("Le logement n'est pas disponible, ressaisissez un n°logement : \n");
					scanf("%d", &value);
					i = rechercheDico(tLog, *nbL, value);
				}
				EnfillerLoca(lc, numLoc, ld->demandeurs.nomDeFamille, ld->demandeurs.prenom, ld->demandeurs.nationalite, ld->demandeurs.nbPersonne, ld->demandeurs.revenueBrut, tLog[i].numLogement, tLog[i].prixLog, ld->demandeurs.nbNum, ld->demandeurs.numTel->libelle, ld->demandeurs.numTel->num);
				suppression(ld, ld->demandeurs.numDemande, nbD);
				strcpy(tLog[i].dispo,"Non");
			break;

			case 4:
				// Fonction suppression locataire
				printf("Saisir le numéro de locataire que vous souhaitez supprimer : \n");
				scanf("%d", &locataire);
				defilerLocaPrecis(lc, locataire);
			break;
		}
		affichMenuLocataire();
		scanf("%d%*c", &choixLoca);

		while (choixLoca != 1 && choixLoca != 2 && choixLoca != 3 && choixLoca != 4 && choixLoca != 9)
		{
			printf("Choix doit être égale à 1, 2, 3, 4 ou 9. Retapez : ");
			scanf("%d%*c", &choixLoca);
		}
	 }
	 return lc;
}

Files MenuChoixTrie (Files lc, int *nbL)
{
	int choixTrie, nbtl;
	Locataire *tloc[TAILLE];
	int tmax = TAILLE;
	nbtl = TransfertTab(lc, tloc, tmax);
	affichChoixTrieLoca();
	scanf("%d%*c", &choixTrie);


	while (choixTrie != 1 && choixTrie != 2 && choixTrie != 3 && choixTrie !=4 && choixTrie != 9)
	{
		printf("Choix doit être égale à 1, 2, 3, 4 ou 9. Retapez : ");
		scanf("%d%*c", &choixTrie);
	}

	 while (choixTrie != 9)
	 {
		switch (choixTrie)
		{
			case 1:
				//faire avant l'appel un printf de ce que va contenir le fichier ex : prix | nbChambre ....
				printf("\t -- Affichage des locataires triés en fonction du nom des locataires --\n");
				printf("+---------------------------------------------------------------------------------------+\n");
				TriePermuteNomLoca(tloc, nbtl);
				AffichTab(tloc, nbtl);
			break;

			case 2:
				//faire avant l'appel un printf de ce que va contenir le fichier ex : prix | nbChambre ....
				printf("\t -- Affichage des locataires triés en fonction du prix du logement --\n");
				printf("+---------------------------------------------------------------------------------------+\n");
				TriePermuteLoge(tloc, nbtl);
				AffichTab(tloc, nbtl);
			break;

			case 3:
				//faire avant l'appel un printf de ce que va contenir le fichier ex : prix | nbChambre ....
				printf("\t -- Affichage des locataires triés en fonction de l'arrivé au logement --\n");
				printf("+---------------------------------------------------------------------------------------+\n");
				TriePermuteDate(tloc, nbtl);
				AffichTab(tloc, nbtl);
			break;

			case 4:
				// Teste des fonctions d'affichage 
				printf("\t -- Toutes les informations sur le locataire --\n");
				printf("+---------------------------------------------------------------------------------------+\n");
				AffichLocataire(lc);
			break;
		}
		affichChoixTrieLoca();
		scanf("%d%*c", &choixTrie);

		while (choixTrie != 1 && choixTrie != 2 && choixTrie != 3 && choixTrie !=4 && choixTrie != 9)
		{
			printf("Choix doit être égale à 1, 2, 3, 4 ou 9. Retapez : ");
			scanf("%d%*c", &choixTrie);
		}
	 }
	 ViderTab(tloc, nbtl);
	 return lc;
}

void MenuLogement (Logement tLog[],int *nbLog)
{
	int choixLoge;

	affichMenuLogement();
	scanf("%d%*c", &choixLoge);

	while (choixLoge != 1 && choixLoge != 2 && choixLoge != 3 && choixLoge != 4 && choixLoge != 5 && choixLoge != 9)
	{
		printf("Choix doit être égale à 1, 2, 3, 4, 5 ou 9. Retapez : ");
		scanf("%d%*c", &choixLoge);
	}

	while (choixLoge != 9)
	{
		switch (choixLoge)
		{
			case 1:
				tLog=insertionLog(tLog, nbLog);
			break;

			case 2:
				*nbLog=supprime(tLog, *nbLog);
			break;

			case 3:
				affichageLog(tLog, *nbLog);
			break;

			case 4:
				affichageLogDispo(tLog, *nbLog);
			break;
		}
		affichMenuLogement();
		scanf("%d%*c", &choixLoge);

		while (choixLoge != 1 && choixLoge != 2 && choixLoge != 3 && choixLoge != 4 && choixLoge != 5 && choixLoge != 9)
		{
			printf("Choix doit être égale à 1, 2, 3, 4, 5 ou 9. Retapez : ");
			scanf("%d%*c", &choixLoge);
		}
	}
}

ListeDem MenuDemLog (ListeDem ld, int *nbD)
{
	int choixDemLoge, numDemande, rechDemandeur, suppDemandeur, numModif, nbPoint, nbPers, numTel;
	float revenu;
	char nomF[32], prenomD[32], nationa[4], passe;
	Booleen existe;
	affichMenuDemLog();
	scanf("%d%*c", &choixDemLoge);

	while (choixDemLoge != 1 && choixDemLoge != 2 && choixDemLoge != 3 && choixDemLoge != 4 && choixDemLoge != 5 && choixDemLoge != 6 && choixDemLoge != 9)
	{
		printf("Choix doit être égale à 1, 2, 3, 4, 5, 6 ou 9. Retapez : ");
		scanf("%d%*c", &choixDemLoge);
	}

	while (choixDemLoge != 9)
	{
		switch (choixDemLoge)
		{
			case 1:
				// Fonction d'enregistrer une demande
				printf("Saisir le nom de Famille : \n");
				fgets(nomF,32,stdin);
				nomF[strlen(nomF)-1]='\0';
				printf("Saisir le prénom : \n");
				fgets(prenomD,32,stdin);
				prenomD[strlen(prenomD)-1]='\0';
				printf("Pour rappel : \n");
				printf("Les personnes handicapees : 30 points\nLes personnes victimes de violences au sein du couple :15 points\nLes personnes hébergées ou logées temporairement : 15 points\nLes personnes sans aucun logement ou menacées dexpulsion sans relogement : 10 points\nLes personnes logées dans un logement insalubre ou dangereux : 8 points\n");
				printf("Saisir le nombre de point de l'individue : ");
				scanf("%d", &nbPoint);
				printf("Saisir le nombre d'indivu à charge : \n");
				scanf("%d",&nbPers);
				printf("Saisir le revenu brut de l'individu : \n");
				scanf("%f%*c", &revenu);
				numDemande=rand() %4999 + 1;
    			existe=numExiste(ld,numDemande);
				while (existe==Vrai)
				{
					numDemande=rand() % 4999 + 1;
					existe=numExiste(ld,numDemande);
				}
				printf("Saisir sa nationalité (2 carac): \n");
				fgets(nationa,4,stdin);
				nationa[strlen(nationa)-1]='\0';
				if(strcmp(nationa,"FR\0")!=0)
				{
					printf("La personne pocède t-il un passe (O pour oui) : ");
					scanf("%c%*c", &passe);
					if (passe == 'O' || passe == 'o')
					{
						ld=insertionDem(ld, numDemande, nbPoint, nbPers, revenu, nomF, prenomD, nationa);
						printf("Insertion reussie!");
						(*nbD)++;
					}
					else
						printf("Insertion annule!");
				}
				else
				{
					ld=insertionDem(ld, numDemande, nbPoint, nbPers, revenu, nomF, prenomD, nationa);
					printf("Insertion reussie!");
					(*nbD)++;
				}
			break;

			case 2:
				printf("Entrez le numero du Demandeur a modifier : ");
				scanf("%d",&numModif);
				ld=modification(ld, numModif);
			break;

			case 3:
				printf("Entrée le numero du Demandeur a supprimer : ");
				scanf("%d",&suppDemandeur);
				ld=suppression(ld, suppDemandeur, nbD);
			break;

			case 4:
				affichageDem(ld);
			break;

			case 5:
				printf("Entrée le numero du Demandeur rechercher : ");
				scanf("%d",&rechDemandeur);
				afficherUnDemandeur(ld, rechDemandeur);
			break;
		}
		affichMenuDemLog();
		scanf("%d%*c", &choixDemLoge);

		while (choixDemLoge != 1 && choixDemLoge != 2 && choixDemLoge != 3 && choixDemLoge != 4 && choixDemLoge != 5 && choixDemLoge != 6 && choixDemLoge != 9)
		{
			printf("Choix doit être égale à 1, 2, 3, 4, 5, 6 ou 9. Retapez : ");
			scanf("%d%*c", &choixDemLoge);
		}
	}
	ld = expirationDem(ld, nbD);
	return ld;
}

void sauvegardeTout(ListeDem ld, char *ficDem, int nbD, int nbL, Files lc, char *ficLoc, Logement *tLog, char *ficLog, int nbLog)
{
	FILE *pf;
	pf=fopen(ficDem, "w");
	fprintf(pf,"%d\n",nbD);
	sauvegardeDem(ld, pf);
	suppressionAll(ld, &nbD);
	fclose(pf);
	
	FILE *fL;
	fL=fopen(ficLoc, "w");
	sauvegardeLoc(lc, fL);
	suppressionAll2(lc, &nbL);
	fclose(fL);

	FILE *fLog;
	fLog=fopen(ficLog, "w");
	sauvegardeLog(tLog, nbLog, fLog);
	free(tLog);
	fclose(fL);
}
