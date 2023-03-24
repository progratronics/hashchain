#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include "variables.h"


int main() {
  int choice;
  HTable * maHashTable;
  HTable * maHashTableStrlen;
  HTable * maHashTableSumASCII;
  HTable * maHashTableASCII;
  HElement * element;
  HCell * TeteCellule;
  element=malloc(sizeof(HElement));
  TeteCellule=malloc(sizeof(HCell));
  HElement * elementR;
  int i, k, option;
  char key[10];
  const char * filepath = "rep.txt";
  int somme;

  while (1) {

    printf("\n\t\t\tMenu\n\n");

    printf("\t1. Créer une table de hachage\n");
    printf("\t2. Créer un élèment et l'afficher\n");
    printf("\t3. Créer une liste chainée et afficher les différents élèments qui la compose\n");
    printf("\t4. Manipulation de la table de hachage (ajout et recherche d'élèments)\n");
    printf("\t5. Observation sur les différentes méthodes de hachage\n");
    scanf("%d", & choice);
    switch (choice) {

    case 1:

      maHashTable = createHTable(10);
      printHTable(maHashTable);
      break;
      //---------------------------------------------------------------------------------------------------------
    case 2:

      printf("Veuillez rentrer les différents champs du nouveau élèment\n");
      element = createElement();
      printHElement(element);
      break;
      //---------------------------------------------------------------------------------------------------------
    case 3:

      printf("Veuillez rentrer le nombre d'élèment de votre liste chainée\n");
      scanf("%d", & k);
      
      for (i = 0; i < k; i++) {
        element = createElement();
        TeteCellule = enqueueHElement(TeteCellule, element);
      }
      printHEntry(TeteCellule);
      break;
      //---------------------------------------------------------------------------------------------------------
    case 4:

      maHashTable = createHTable(10);
      printf("Veuillez rentrer le nombre d'élèments à ajouter à la table de hachage\n");
      scanf("%d", & k);
      printf("Veuillez saisir %d élèments dans la table de hachage\n", k);
      for (i = 0; i < k; i++) {
        addHElement(maHashTable);
      }
      printHTable(maHashTable);

      printf("1 : Chercher un élèment dans la table de hachage\n");
      // printf("2 : Supprimer un élèment dans la table de hachage\n");
      printf("2 : Quitter\n");

      printf("Veuillez faire un choix entre les différentes options\n");
      scanf("%d", & option);
      switch (option) {
      case 1:
        printf("2 : Veuillez saisir la clé de l'élèment à chercher\n");
        scanf("%s", key);
        elementR = malloc(sizeof(HElement));
        elementR = getHElement(maHashTable, key);
        printHElement(elementR);
        break;
//      case 2:
//       printf("3 : Veuillez rentrer la clé de l'élèment à supprimer\n");
//        scanf("%s", key);

//        printHElement(elementR);
//        removeHElement(maHashTable, key);
//        printHTable(maHashTable);
//        break;

      default:
        break;
      }
      break;
      //---------------------------------------------------------------------------------------------------------
      case 5:
        printf("Choisir la méthode de hachage\n");
        printf("1 : Longueur de la clé\n");
        printf("2 : Code ASCII du premier caractère\n");
        printf("3 : La somme des codes ASCII de tout les caractères\n");
        scanf("%d", & choice);

        switch (choice) {
        case 1:
          maHashTableStrlen = createHTable(100);
          maHashTableStrlen = loadHTableStrlen(filepath);
          printHTableNew(maHashTableStrlen);
          
          somme = computeNbCollisions(maHashTableStrlen);
          printf("%d\n", somme);
          break;

        case 2:
          maHashTableASCII = createHTable(100);
          maHashTableASCII = loadHTableASCII(filepath);
          printHTableNew(maHashTableASCII);

          somme = computeNbCollisions(maHashTableASCII);
          printf("%d\n", somme);
          break;

        case 3:
          maHashTableSumASCII = createHTable(100);
          maHashTableSumASCII = loadHTableHashSumASCII(filepath);
          printHTableNew(maHashTableSumASCII);

          somme = computeNbCollisions(maHashTableSumASCII);
          printf("%d\n", somme);
          break;

        default:
          break;
        }
    }
  }
}
