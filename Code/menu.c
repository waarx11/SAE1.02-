#include "hlm.h"

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
	printf("| 4. Afficher les types de logement \t\t |\n");
	printf("| 5. Afficher les types de logement disponuble   |\n");
	printf("| 9. Retour \t\t\t\t\t |\n");
	printf("+------------------------------------------------+\n");
}

void affichChoixTrieLoca(void)
{
	printf("\t Comment souhaitez vous triez la liste : \n");
	printf("+------------------------------------------------+\n");
	printf("| 1. Le nom par ordre alphabétique \t\t |\n");
	printf("| 2. Par numéro de logement\t\t\t |\n");
	printf("| 3. En fonction du prix du logement\t \t |\n");
	printf("| 4. Ordre croissant d'arrivée au logement\t |\n");
	printf("| 5. Test affichage \t\t\t\t |\n");
	printf("| 9. Retour \t\t\t\t\t |\n");
	printf("+------------------------------------------------+\n");
}

void affichMenuLocataire(void)
{
	printf("\t Que voulez vous faire : \n");
	printf("+------------------------------------------------+\n");
	printf("| 1. Afficher la liste des locataires \t\t |\n");
	printf("| 2. Recherche d'un locataire \t\t\t |\n");
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
	int nbD, nbL, nbLog=5, choix;
	char ficDem[30] = "FichierDemLoge.txt";
	char ficLoc[30] = "FichierLoca.txt";
	char ficlog[30] = "FichierLoge.txt";

	ListeDem ld;
	Files lc;
	PileLog lg;
	Logement **tLog;

	ld = initliste();
	ld = chargementDem(ld, &nbD, ficDem);
	ld = expirationDem(ld, &nbD);

	// lc = FileVide();
	// lc = chargementLoc(lc, &nbL, ficLoc);

	nbLog = chargeLogement(ficlog, tLog, nbLog);


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
				MenuLocataire(lc);
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
	sauvegardeTout(ld, ficDem, nbD, lc, ficLoc);
}

void MenuLocataire(Files lc)
{
	int choixLoca, locataire;

	affichMenuLocataire();
	scanf("%d%*c", &choixLoca);

	while (choixLoca != 1 && choixLoca != 2 && choixLoca != 9)
	{
		printf("Choix doit être égale à 1, 2 ou 9. Retapez : ");
		scanf("%d%*c", &choixLoca);
	}

	 while (choixLoca != 9)
	 {
		switch (choixLoca)
		{
			case 1:
				MenuChoixTrie(lc);
			break;

			case 2:
				// Fonction recherche locataire
				printf("Saisir un numéro de locataire : \n");
				scanf("%d", &locataire);
				RechLoca(lc->suiv, locataire);
			break;
		}
		affichMenuLocataire();
		scanf("%d%*c", &choixLoca);

		while (choixLoca != 1 && choixLoca != 2 && choixLoca != 9)
		{
			printf("Choix doit être égale à 1, 2 ou 9. Retapez : ");
			scanf("%d%*c", &choixLoca);
		}
	 }
}

void MenuChoixTrie (Files lc)
{
	int choixTrie;

	affichChoixTrieLoca();
	scanf("%d%*c", &choixTrie);


	while (choixTrie != 1 && choixTrie != 2 && choixTrie != 3 && choixTrie !=4 && choixTrie != 5 && choixTrie != 9)
	{
		printf("Choix doit être égale à 1, 2, 3, 4, 5 ou 9. Retapez : ");
		scanf("%d%*c", &choixTrie);
	}

	 while (choixTrie != 9)
	 {
		switch (choixTrie)
		{
			case 1:
				//faire avant l'appel un printf de ce que va contenir le fichier ex : prix | nbChambre ....
				// Afficher en fonction du nom
			break;

			case 2:
				//faire avant l'appel un printf de ce que va contenir le fichier ex : prix | nbChambre ....
				// Afficher en fonction du numéro de locataire
			break;

			case 3:
				//faire avant l'appel un printf de ce que va contenir le fichier ex : prix | nbChambre ....
				// Afficher en fonction du prix du logement
			break;

			case 4:
				//faire avant l'appel un printf de ce que va contenir le fichier ex : prix | nbChambre ....
				// Afficher en fonction de la date d'arrivée au logement
			break;

			case 5:
				// Teste des fonctions d'affichage
				printf("\t -- Toutes les informations sur le locataire --\n");
				printf("+---------------------------------------------------------------------------------------+\n");
				AffichLocataire(lc);
			break;
		}
		affichChoixTrieLoca();
		scanf("%d%*c", &choixTrie);

		while (choixTrie != 1 && choixTrie != 2 && choixTrie != 3 && choixTrie !=4 && choixTrie != 5 && choixTrie != 9)
		{
			printf("Choix doit être égale à 1, 2, 3, 4, 5 ou 9. Retapez : ");
			scanf("%d%*c", &choixTrie);
		}
	 }
}

void MenuLogement (Logement *tLog[],int *nbLog)
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
				// Fonction d'ajout logement
			break;

			case 2:
				// Fonction suppression de logement
			break;

			case 3:
				affichageLog(tLog, *nbLog);
			break;

			case 4:
				// Fonction d'affichage des types des logements
			break;

			case 5:
				// Fonction d'affichage des logements disponiblent
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
	int choixDemLoge, rechDemandeur, suppDemandeur, numModif, nbPoint, nbPers, numTel;
	float revenu;
	char nomF[32], prenomD[32], nationa[4], passe;
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
				printf("Saisir sa nationalité (2 carac): \n");
				fgets(nationa,4,stdin);
				nationa[strlen(nationa)-1]='\0';
				if(strcmp(nationa,"FR\0")!=0) 
				{
					printf("La personne pocède t-il un passe (O pour oui) : ");
					scanf("%c%*c", &passe);
					if (passe == 'O' || passe == 'o')
					{
						ld=insertionDem(ld, nbPoint, nbPers, revenu, nomF, prenomD, nationa);
						printf("Insertion reussie!");
						(*nbD)++;
					}
					else
						printf("Insertion annule!");
				}
				else
				{
					ld=insertionDem(ld, nbPoint, nbPers, revenu, nomF, prenomD, nationa);
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

void sauvegardeTout(ListeDem ld, char *ficDem, int nbD, Files f, char *ficLoc)
{
	FILE *pf;
	pf=fopen(ficDem, "w");
	fprintf(pf,"%d\n",nbD);
	sauvegardeDem(ld, pf);
	suppressionAll(ld, &nbD);
	fclose(pf);
	// fL=fopen(ficLoc, "w");
	// sauvegardeLoc(f, fL);
	// fclose(fL);
}
