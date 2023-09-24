#include <stdio.h>
#include <string.h>

// DECLARATION DES STRUCTURE
struct date {
    int jour;
    int mois;
    int anne;
};

struct tache {
    int id;
    char titre[100];
    char description[200];
    struct date dt;
    char status[25];
};

// SPECIAL VARIABLES TO CONTROLE TACHES
int maxTache = 100;
int tcount = 0;
int tacheSp_Id = 1;

// PETIT MENU AU DEMARRAGE
int petitMenu() {

    printf("===== Menu ====================== \n");
    printf("1 - Ajouter Une Taches \n");
    printf("2 - Exit => Terminee le Programme \n");
    printf("================================= \n");

    int ChoixPMenu;
    printf("Enter Votre Choix Du Menu :");
    scanf("%d", &ChoixPMenu);

    // UNE BOULE POUR QUE L'UTULISATEUR ENTRE UNE VALEUR CORRECT DU MENU
    while(ChoixPMenu > 2 || ChoixPMenu < 1) {
        printf("Enter Un Choix Correct Du Menu ( 1 ou 2 ) :");
        scanf("%d", &ChoixPMenu);
    }

    return ChoixPMenu;
}

// FONCTION POUR TESTEZ LA DATE SI VALID
int dateCheck(int jour, int mois, int anne) {

    if (anne < 2023 || anne > 2100)
        return -1;

    if (mois < 1 || mois > 12)
        return -1;

    if (jour < 1 || jour > 31)
        return -1;

    return 1;
}

// FONCTION POUR L'AJJOUT D'UN NOMBRE DES TACHE
void ajouterTache(struct tache nvT[]) {
    if (tcount < maxTache) {

        tcount++;

        nvT[tcount].id = tacheSp_Id++;

        printf("Entrer Le Titre De Votre Tache N°%d :", tcount);
        getchar();
        scanf("%[^\n]s", nvT[tcount].titre);

        printf("Entrer La Description De Votre Tache N°%d :", tcount);
        getchar();
        scanf("%[^\n]s", nvT[tcount].description);

        printf("Entrer Le deadline De Votre Tache N°%d :", tcount);
        scanf("%d/%d/%d", &nvT[tcount].dt.jour, &nvT[tcount].dt.mois, &nvT[tcount].dt.anne);

        while(dateCheck(nvT[tcount].dt.jour, nvT[tcount].dt.mois, nvT[tcount].dt.anne) == -1) {

            printf("Date Non Valid \n");
            printf("Entrer Le deadline De Votre Tache N°%d :", tcount);
            scanf("%d/%d/%d", &nvT[tcount].dt.jour, &nvT[tcount].dt.mois, &nvT[tcount].dt.anne);
            }

        printf("Entrer Le Status De Votre Tache N°%d (a realiser / en cours de realisation / finaliser ) :", tcount);
        getchar();
        scanf("%[^\n]s", nvT[tcount].status);

        while(strcmp(nvT[tcount].status, "a realiser")!= 0&& strcmp(nvT[tcount].status, "en cours de realisation")!= 0&& strcmp(nvT[tcount].status, "finaliser")!=0) {

            printf("Entrer Le Status De Votre Tache N°%d (a realiser / en cours de realisation / finaliser ) :", tcount);
            getchar();
            scanf("%[^\n]s",nvT[tcount].status);
            }

        printf("** La Tache a Ete Ajouter !\n");
        printf("********************* \n");

    }
    else {
        printf("Sorry ! Tache List Is Full :( \n");
    }
}

// FONCTION DE L'AFFICHAGE DES TOUTES LES TACHES
void afficherTache(struct tache nvT[], int tcount) {

    printf("==== Vos Taches ===================================================== \n");

    for (int bAf = 1; bAf <= tcount; bAf++) {

        printf("Id: %d \n", nvT[bAf].id);
        printf("Titre : %s \n", nvT[bAf].titre);
        printf("Description : %s \n", nvT[bAf].description);
        printf("Deadline : %d/%d/%d \n", nvT[bAf].dt.jour, nvT[bAf].dt.mois, nvT[bAf].dt.anne);
        printf("Status : %s \n", nvT[bAf].status);
        printf("===================================================================== \n");
        }
};

// FONCTION DE LA RECHERCHE DES TACHES PAR ID
int rechercheById(struct tache nvT[], int tcount) {

    int rechercheId;
    int idN_1 = -1;
    // int checkId = 0;

    printf("Enter L'Id De Votre Tache Pour Rechercher La :");
    scanf("%d", &rechercheId);

    for (int rId = 1; rId <= tcount; rId++) {

        if (rechercheId == nvT[rId].id) {
            printf("Tache Trouve ! \n");
            idN_1 = rId;
            //checkId++;
            break;
            }
        }
        /*if (checkId == 0 ) {
            printf("Tache Non Trouve ! \n");

            }*/

    return idN_1;
}

// FONCTION DE LA RECHERCHE DES TACHES PAR TITRE
int researcheByTitle(struct tache nvT[], int tcount) {

    char rechercheTr[100];
    int idN_2 = -1;
    //int checkTr = 0;

    printf("Enter Le Titre De Votre Tache Pour Rechercher La :");
    getchar();
    scanf("%[^\n]s", rechercheTr);

        for (int rTr = 1; rTr <= tcount; rTr++) {

            if (strcmp(rechercheTr, nvT[rTr].titre) == 0) {
                printf("Tache Trouve ! \n");
                idN_2 = rTr;
                //checkTr++;
                break;
                }
            }

        /*if (checkTr == 0 ) {
            printf("Tache Non Trouve ! \n");

            }*/

            return idN_2;
}

// FONCTION POUR L'AFFICHAGE DU RESULTAT DE LA RECHERCHE
void affichageSrResult(struct tache nvT[], int iNreturn) {

    printf("********* \n");

    printf("\n==== Votre Taches =================================================== \n");
    printf("Id: %d \n", nvT[iNreturn].id);
    printf("Titre : %s \n", nvT[iNreturn].titre);
    printf("Description : %s \n", nvT[iNreturn].description);
    printf("Deadline : %d/%d/%d \n", nvT[iNreturn].dt.jour, nvT[iNreturn].dt.mois, nvT[iNreturn].dt.anne);
    printf("Status : %s \n", nvT[iNreturn].status);
    printf("===================================================================== \n");
}

// FONCTION QUI CALCULE LA DATE RESTANTS POUR UNE TACHE
void dateRestant(struct tache nvT[], int tcount, int n) {

    // DATE ACTUEL
    struct date cDate;
    cDate.jour = 23;
    cDate.mois = 9;
    cDate.anne = 2023;

    for (int i = 1; i <= tcount; i++) {

        int joursRestants = 0;

        // SAVOIR SI LA DATE DU TACHE EST DANS LE FUTURE
        if (nvT[i].dt.anne > cDate.anne || (nvT[i].dt.anne == cDate.anne && nvT[i].dt.mois > cDate.mois) || ( nvT[i].dt.anne == cDate.anne && nvT[i].dt.mois == cDate.mois && nvT[i].dt.jour > cDate.jour)) {

            // CALCULER LE NOMBRE DE JOUR RESTANTS
            joursRestants = (nvT[i].dt.anne - cDate.anne) * 365 + (nvT[i].dt.mois - cDate.mois) * 30 + (nvT[i].dt.jour - cDate.jour);
        }

        // AFFFICHAGE DE RESULTAT
        if (n == 1)
            printf("Tache : %-15s, Jours restants  : %d\n", nvT[i].titre, joursRestants);
        else if (n == 2) {
            if (joursRestants <= 3) {
                printf("Tache : %-15s, Jours restants  : %d\n", nvT[i].titre, joursRestants);
            }
        }
    }
}

// FONCTION DE TRI ALPHABETIQUE
void triAlpha(struct tache nvT[]) {

    struct tache temp;

    for (int i = 0; i < tcount; i++) {

        for (int j = i + 1; j <= tcount; j++) {

            if (strcmp(nvT[j].titre, nvT[j - 1].titre) < 0){

                temp = nvT[j];
                nvT[j] = nvT[j - 1];
                nvT[j - 1] = temp;
            }
        }
    }
}

// FONCTION DE TRI DE DEADLINE
void triDeadline(struct tache nvT[]) {

    struct tache temp;

    for (int i = 0; i < tcount; i++) {

        for (int j = i + 1; j <= tcount; j++) {

           if (nvT[i].dt.anne > nvT[j].dt.anne) {
                        temp = nvT[i];
                        nvT[i] = nvT[j];
                        nvT[j] = temp;
                        }

                    else if (nvT[i].dt.anne == nvT[j].dt.anne) {

                        if (nvT[i].dt.mois > nvT[j].dt.mois) {
                            temp = nvT[i];
                            nvT[i] = nvT[j];
                            nvT[j] = temp;
                            }
                        else if (nvT[i].dt.mois == nvT[j].dt.mois) {

                            if (nvT[i].dt.jour > nvT[j].dt.jour) {
                                temp = nvT[i];
                                nvT[i] = nvT[j];
                                nvT[j] = temp;
                                }
                            }
                        }
            }
    }
}


int main() {

    // DECLARATION DE LA STRUCTURE TACHE ET CREONS UN NOUVEAUX TABLEAUX
    struct tache nvT[maxTache];
    //int iN_return;

    // AFFICHAGE D'UN PETIT MENU AU DEBUT
    int xResult = petitMenu();

    if (xResult == 1) {


        // LE NOMBRE DE TACHE QUE L'UTILISATEUR VEUT L'ENTRER
        int nTache;
        printf("\n************* \n");
        printf("Entrer Le Nombre Des Tache Que Vous Voulez Entrer :");
        scanf("%d", &nTache);

        while (nTache > 100 || nTache < 1) {

            printf("Nombre Non Valid\n");
            printf("Entrer Le Nombre Des Tache Que Vous Voulez Entrer :");
            scanf("%d", &nTache);
        }

        // UNE BOUCLE QUI NOUS AIDE A ENTREES LES VALEURS
        int by;
        for (by = 1; by <= nTache ; by++) {
            ajouterTache(nvT);
        }



        // DO WHILE POUR QUE LE MENU AFFICHE APRES LA FIN DE CHAQUE CHOIX
        int ChoixGMenu;
        do {

            // AFFICHAGE DU GRAND MENU
            printf("===== Menu ===================================================== \n");
            printf("1 - Ajouter Une Nouvelle Tache \n");
            printf("2 - Afficher Les Taches Existe \n");
            printf("3 - Recherche D'une Tache ( => Sous Menu ) \n");
            printf("4 - Modification des taches ( => Sous Menu ) \n");
            printf("5 - Statistique du programme  \n");
            printf("6 - Supprimer Une Tache  \n");
            printf("7 - Tri des taches  \n");
            printf("0 - Exit => Terminee le Programme \n");
            printf("================================================================ \n \n");

            printf("Enter Votre Choix Du Menu :");
            scanf("%d", &ChoixGMenu);


            // UNE BOULE POUR QUE L'UTULISATEUR ENTRE UNE VALEUR CORRECT DU MENU
            while(ChoixGMenu > 7 || ChoixGMenu < 0) {
                printf("Enter Un Choix Correct Du Menu ( 0 Jusqu'a 7 ) :");
                scanf("%d", &ChoixGMenu);
            }


            // AJOUTER UNE NOUVELLE TACHE
            if (ChoixGMenu == 1) {
                ajouterTache(nvT);
            }
            // AFFICHER LES TACHES STOCKES
            else if (ChoixGMenu == 2) {
                afficherTache(nvT, tcount);
            }
            // RECHERCHE D'UNE TACHE ( PAR ID & TITRE )
            else if (ChoixGMenu == 3) {

                int iNreturn;
                // SOUS MENU DE LA RECHERCHE D'UNE TACHE
                printf("===== Menu ====================== \n");
                printf("1 - Recherche D'une Tache Par Id \n");
                printf("2 - Recherche D'une Tache Par Titre \n");
                printf("3 - Return \n");
                printf("================================= \n");

                int choixRecherche;
                printf("Enter Votre Choix :");
                scanf("%d", &choixRecherche);

                // UNE BOULE POUR QUE L'UTULISATEUR ENTRE UNE VALEUR CORRECT DU MENU
                while(choixRecherche > 3 || choixRecherche < 1) {
                    printf("Enter Un Choix Correct Du Menu ( 1 Jusqu'a 3 ) :");
                    scanf("%d", &choixRecherche);
                    }

                // RECHERCHE D'UNE TACHE PAR ID
                if (choixRecherche == 1) {

                    iNreturn = rechercheById(nvT, tcount);
                    // affichageSrResult(nvT, iNreturn);
                    if (iNreturn != -1) {
                        affichageSrResult(nvT, iNreturn);
                        }
                    else{
                        printf("Tache Non Trouve ! \n");
                        }
                    }

                // RECHERCHE D'UNE TACHE PAR TITRE
                else if (choixRecherche == 2) {

                    iNreturn = researcheByTitle(nvT, tcount);
                    // affichageSrResult(nvT, iNreturn);

                    if (iNreturn != -1) {
                        affichageSrResult(nvT, iNreturn);
                        }
                    else{
                        printf("Tache Non Trouve ! \n");
                        }
                }

                // RETOUR AU MENU PRINCIPAL
                else if (choixRecherche == 3) {

                    printf("Retour Au Menu Principal \n");
                    }
            }
            // MODIFICATION D'UNE TACHE
            else if (ChoixGMenu == 4) {

                //int rId_Modf;

                // SOUS MENU DE MODIFICATION D'UNE TACHE
                printf("===== Menu ====================== \n");
                printf("1 - Modification La Description De La Tache \n");
                printf("2 - Modifier Le Status De La Tache \n");
                printf("3 - Modifier Le Deadline De La Tache \n");
                printf("4 - Return \n");
                printf("================================= \n");

                int choixModification;
                printf("Enter Votre Choix :");
                scanf("%d", &choixModification);

                // UNE BOULE POUR QUE L'UTULISATEUR ENTRE UNE VALEUR CORRECT DU MENU
                while(choixModification > 4 || choixModification < 1) {
                    printf("Enter Un Choix Correct Du Menu ( 1 Jusqu'a 4 ) :");
                    scanf("%d", &choixModification);
                    }

                // MODIFICATION DE LA DECRIPTION D'UNE TACHE
                if (choixModification == 1) {

                    int rId_modf = rechercheById(nvT, tcount);

                    if ( rId_modf == -1) {
                        printf("Tache Non Trouve !\n");
                    }
                    else {

                        printf("Entrer Votre Nouvelle Description Pour La Tache N° %d :", rId_modf);
                        getchar();
                        scanf("%[^\n]s", nvT[rId_modf].description);
                        printf("Description modifiée avec succès !\n");
                    }
                }

                // MODIFICATION DU STATUS D'UNE TACHE
                else if (choixModification == 2) {

                    int rId_modf = rechercheById(nvT, tcount);

                    if (rId_modf == -1) {
                        printf("Tache Non Trouve !\n");
                    }
                    else {
                       printf("Entrer Votre Nouveaux Status Pour La Tache N° %d :", rId_modf);
                        getchar();
                        scanf("%[^\n]s", nvT[rId_modf].status);

                        while(strcmp(nvT[rId_modf].status, "a realiser") != 0 && strcmp(nvT[rId_modf].status, "en cours de realisation") != 0 && strcmp(nvT[rId_modf].status, "finaliser")!=0) {
                            printf("Entrer Le Status De Votre Tache N°%d (a realiser / en cours de realisation / finaliser ) :", tcount);
                            getchar();
                            scanf("%[^\n]s",nvT[rId_modf].status);
                            }

                            printf("Statut modifié avec succès !\n");
                    }
                }

                // MODIFICATION DU  DEADLINE D'UNE TACHE
                else if (choixModification == 3) {

                    int rId_modf = rechercheById(nvT, tcount);

                    if (rId_modf == -1) {
                        printf("Tache Non Trouve !\n");
                    }
                    else {

                        printf("Entrer Votre Nouveaux deadline Pour La Tache N° %d :", rId_modf);
                        scanf("%d/%d/%d", &nvT[rId_modf].dt.jour, &nvT[rId_modf].dt.mois,   &nvT[rId_modf].dt.anne);

                        while(dateCheck(nvT[tcount].dt.jour, nvT[tcount].dt.mois, nvT[tcount].dt.anne) == -1) {

                            printf("Date Non Valid \n");
                            printf("Entrer Le deadline De Votre Tache N°%d :", tcount);
                            scanf("%d/%d/%d", &nvT[tcount].dt.jour, &nvT[tcount].dt.mois, &nvT[tcount].dt.anne);
                            }

                        printf("Deadline modifiée avec succès !\n");
                    }
                }

                // RETOUR AU MENU PRINCIPAL
                else if (choixModification == 4) {

                    printf("Retour Au Menu Principal \n");
                    }
            }

            else if (ChoixGMenu == 5) {

                // SOUS MENU DE STATISTIQUE D'UN PROGRAMME
                printf("===== Menu =========================================================== \n");
                printf("1 - Affichage Des Nombre Total Des Tache \n");
                printf("2 - Statistique Des Taches Completes & Incomplete \n");
                printf("3 - Affichage De Nombre Dejours Restants Jusqu'a Le delai de chaqu'une \n");
                printf("4 - Return \n");
                printf("====================================================================== \n");

                int choixStatistique;
                printf("Enter Votre Choix :");
                scanf("%d", &choixStatistique);

                // UNE BOULE POUR QUE L'UTULISATEUR ENTRE UNE VALEUR CORRECT DU MENU
                while(choixStatistique > 4 || choixStatistique < 1) {
                    printf("Enter Un Choix Correct Du Menu ( 1 Jusqu'a 4 ) :");
                    scanf("%d", &choixStatistique);
                }

                // AFFICHAGE DE NOMBRE DES TACHES CREER
                if (choixStatistique == 1) {

                    printf("=========================== \n");
                    printf("Total Des Taches Creer : %d\n", tcount);
                    printf("=========================== \n");
                }

                // AFFICHER LE NOMBRE DES TACHES COMPLET & INCOMPLETS
                else if (choixStatistique == 2) {

                    int Tcomplete = 0;
                    int Tincomplete = 0;

                    for (int q = 0; q <= tcount; q++) {

                        if ( strcmp(nvT[q].status, "a realiser") == 0) {
                            Tincomplete++;
                            }
                        else if ( strcmp(nvT[q].status, "en cours de realisation") == 0 ) {
                            Tincomplete++;
                            }
                        else if ( strcmp(nvT[q].status, "finaliser") == 0 ) {
                            Tcomplete++;
                            }
                        }

                        printf("=========================== \n");
                        printf("Taches Completes   : %d \n", Tcomplete);
                        printf("=========================== \n");
                        printf("Taches Incompletes : %d \n", Tincomplete);
                        printf("=========================== \n");

                }
                // AFFICHAGE DE NOMBRE DE JOURS RESTANTS JUSQU'A DELAI DE CHAQUE TACHE
                else if (choixStatistique == 3) {

                    dateRestant(nvT, tcount, 1);


                }
                // RETOUR AU MENU PRINCIPAL
                else if (choixStatistique == 4) {
                    printf("Retour Au Menu Principal \n");
                }
            }

            // SUPPRIMER UNE TACHE
            else if (ChoixGMenu == 6) {

                int e;
                int iS_return = rechercheById(nvT, tcount);

                if (iS_return != -1) {

                    for (e = iS_return; e < tcount; e++) {

                        nvT[e] = nvT[e + 1];
                    }

                    tcount--;
                    printf("Tache supprimee avec succes !\n");
                }
                else {
                    printf("Tache non trouvee et ne peut pas etre supprimee !\n");
                }


            }




            // TRIE D'UNE TACHES
            else if (ChoixGMenu == 7) {

                // SOUS MENU DE TRI D'UNE TACHE
                printf("===== Menu ====================== \n");
                printf("1 - Tri Par Ordre Alphabetique  \n");
                printf("2 - Tri Par Deadline \n");
                printf("3 - Les Taches Qui ont 3 jours ou moins dans le deadline \n");
                printf("4 - Return \n");
                printf("================================= \n");

                int choixTri;
                printf("Enter Votre Choix :");
                scanf("%d", &choixTri);

                // UNE BOULE POUR QUE L'UTULISATEUR ENTRE UNE VALEUR CORRECT DU MENU
                while(choixTri > 4 || choixTri < 1) {
                    printf("Enter Un Choix Correct Du Menu ( 1 Jusqu'a 4 ) :");
                    scanf("%d", &choixTri);
                    }

                // TRI PAR ORDRE ALPHABETIQUE
                if (choixTri == 1) {

                    triAlpha(nvT);
                    afficherTache(nvT, tcount);

                }

                // TRI PAR DEADLINE
                else if (choixTri == 2) {

                    triDeadline(nvT);
                    afficherTache(nvT, tcount);
                }

                else if (choixTri == 3) {

                    dateRestant(nvT, tcount, 2);
                }

                // RETOUR AU MENU PRINCIPAL
                else if (choixTri == 4) {
                    printf("Retour Au Menu Principal \n");
                }

            }










            } while (ChoixGMenu != 0);
            printf("Le Programme a ete arrete :( \n");

    }
    else if (xResult == 2) {

        printf("************* \n");
        printf("Programe a ete arrete");
    }



    return 0;
}
