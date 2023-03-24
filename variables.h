// STRUCTURES

typedef struct {
    char * key;
    char * mail;
    unsigned int date; /* sous la forme AAAAMMJJ. ex: 20140319 */
}
HElement;

typedef struct HCell {
    HElement * element;
    struct HCell * next;
}
HCell;

typedef struct {
    HCell ** table;
    unsigned int size;
}
HTable;


//−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
// FONCTIONS

// Calcul d'une clé à partir de la longueur d'une chaîne de caractère
int hash(HElement * element) {
    int hash = strlen(element -> key);
    return hash - 1;
}

// Calcul d'une clé à partir du code ASCII du premier caractère de notre chaîne de caractère 
int hashASCII(HElement * element) {
    return element -> key[0];
}

// Calcul d'une clé à partir de la somme des codes ASCII qui compose la chaîne de caractère
int hashSommeASCII(HElement * element) {
    int i, somme = 0;

    for (i = 0; i < strlen(element -> key); i++) {
        somme += element -> key[i];
    }

    return somme;
}

// Création d'une table de hachage
HTable * createHTable(unsigned int size) {
    HTable * maHashtable = NULL;

    int i;
    if (size < 1) return NULL;

    if ((maHashtable = malloc(sizeof(HTable))) == NULL) {
        return NULL;
    }
    if ((maHashtable -> table = malloc(sizeof(HCell * ) * size)) == NULL) {
        return NULL;
    }
    for (i = 0; i < size; i++) {
        maHashtable -> table[i] = NULL;
    }

    maHashtable -> size = size;

    return maHashtable;
}

// Création d'un élèment composant les listes chainées
HElement * createElement() {
    HElement * element;
    element = malloc(sizeof(element));

    printf("Veuillez rentrer le login\n");
    element -> key = malloc(sizeof(char * ));
    scanf("%s", element -> key);

    printf("Veuillez rentrer l'email\n");
    element -> mail = malloc(sizeof(char * ));
    scanf("%s", element -> mail);

    printf("Veuillez rentrer la date de naissaince sous la forme AAAAMMJJ. ex: 20140319\n");
    scanf("%u", & element -> date);
    return element;
}

void printHElement(HElement * element) {
    if(element==NULL) 
  	printf("Cet élèment n'existe pas dans la liste chainée\n");
    else
   	printf("login : %s, email : %s, date : %u\n", element -> key, element -> mail, element -> date);
}

// Insérer un élèment en queue de liste 
HCell * enqueueHElement(HCell * TeteCellule, HElement * element) {

    HCell * tmp = TeteCellule;
    HCell * QueueCellule;
    QueueCellule = malloc(sizeof(HCell));
    QueueCellule -> element = element;
    QueueCellule -> next = NULL;

    if (TeteCellule -> element == NULL) {
        return QueueCellule;
    } else {
        while (tmp -> next != NULL)
            tmp = tmp -> next;
        tmp -> next = QueueCellule;
    }
    return TeteCellule;
}

// Afficher les élèments qui composent une liste chainée
void printHEntry(HCell * TeteCellule) {
    int i = 0;

    HCell * tmp = TeteCellule;
    if (tmp -> next == NULL) {
        printHElement(tmp -> element);
    } else {
        while (tmp -> next != NULL) {
            printHElement(tmp -> element);
            tmp = tmp -> next;
            i++;
        }
        printHElement(tmp -> element);
        i++;
        printf("Le nombre d'élèments dans la liste chainée est %d\n", i);
    }
}

// Afficher le nombre d'élèments qui composent une liste chainée 
void printHEntryNew(HCell * TeteCellule) {
    int i = 0;

    HCell * tmp = TeteCellule;
    if (tmp -> next == NULL) {
        printf("Contient 1 élèment\n");
    } else {
        while (tmp -> next != NULL) {
            tmp = tmp -> next;
            i++;
        }

        i++;
        printf("Contient %d élèments\n", i);
    }
}

// Ajout d'un élèment à une table de hachage
void addHElement(HTable * h_table) {
    HElement * element;
    element = createElement();
    int key = hash(element);

    if (h_table -> table[key] != NULL) {
        h_table -> table[key] = enqueueHElement(h_table -> table[key], element);
    } else {
        HCell * TeteCellule;
        TeteCellule = malloc(sizeof(HCell));
        TeteCellule = enqueueHElement(TeteCellule, element);
        h_table -> table[key] = TeteCellule;
    }
}

// Affichage de la table de hachage avec les élèments qui composent chaque case
void printHTable(HTable * maHashtable) {
    int i;
    for (i = 0; i < maHashtable -> size; i++) {
        if (maHashtable -> table[i] != NULL) {
            printf("%d): \n", i );
            printHEntry(maHashtable -> table[i]);
        } else {
            printf("%d): NULL\n", i );
        }
    }
}




// Affichage de la table de hachage avec le nombre d'élèments par case
void printHTableNew(HTable * maHashtable) {
    int i;
    for (i = 0; i < maHashtable -> size; i++) {
        if (maHashtable -> table[i] != NULL) {
            printf("%d): ", i);
            printHEntryNew(maHashtable -> table[i]);
        } else {
            printf("%d): NULL\n", i);
        }
    }
}




// Améliorer argument pas de pointeur en entrée
HElement * getHElement(HTable * h_table, char * key) {
    int i = 0;
    int keyC = strlen(key) - 1;
    if (h_table -> table[keyC] == NULL) { // Si la liste est vide on retourne NULL
        return NULL;
    } else { // On parcours la liste jusqu'à retrouver notre élèment sinon..
    	HCell * tmp=h_table -> table[keyC];
        while (tmp != NULL) {
            if (strcmp(tmp -> element -> key, key) != 0) {
                tmp = tmp -> next;
                i++;
                continue;
            } else {
                printf("L'élèment est dans la case %d et son indice dans la liste chainée correspondante à la case est %d\n", keyC, i + 1);
                return tmp -> element;
            }
        }
    }
    // Si on le retrouve pas on retourne NULL
    return NULL;
}



void removeHElement(HTable * h_table, char * key) {
    int i = 0;
    int keyC = strlen(key) - 1;

    if (h_table -> table[keyC] == NULL) { // Si la liste est vide on fait rien
        printf("La liste est vide\n");
    } else if (strcmp(h_table -> table[keyC] -> element -> key, key) == 0 && h_table -> table[keyC] -> next == NULL) { // Si le premier élèment est celui qu'on recherche on le supprime directement 
        printf("La liste ne contient que l'élèment en lui même\n");
        free(h_table -> table[keyC]);
        h_table -> table[keyC] = NULL;
    }

    // Si liste contient plus d'un élèment et le premier est celui qu'on cherche
    else if (strcmp(h_table -> table[keyC] -> element -> key, key) == 0 && h_table -> table[keyC] -> next != NULL) {

        HCell * tmp = h_table -> table[keyC];
        HCell * suiv = tmp -> next;
        free(tmp);
        tmp = NULL;
        h_table -> table[keyC] = suiv;
    }
    // Sinon on parcourt
    else {
        HCell * tmp = h_table -> table[keyC];
        HCell * prec;

        while (tmp -> next != NULL) {
            prec = tmp;
            tmp = tmp -> next;
            if (strcmp(tmp -> element -> key, key) == 0)
                break;
        }

        if (strcmp(tmp -> element -> key, key) == 0) {
            HCell * suiv = tmp -> next;
            free(tmp);
            tmp = NULL;
            prec -> next = suiv;
        }
    }
}


unsigned int computeNbCollisions(HTable * h_table) {
    int k = 0, i, somme = 0;
    for (i = 0; i < h_table -> size; i++) {
        HCell * tmp = h_table -> table[i];

        if (tmp == NULL) {} else {
            while (tmp != NULL) {
                k++;
                tmp = tmp -> next;
            }
            k--;
            somme += k;
            k = 0;
        }
    }
    return somme;
}


HTable * loadHTableStrlen(const char * filepath) {
    HTable * maHashTable;
    maHashTable = createHTable(100);
    // Accéder case dans table de hashage et mettre adresse d'une cellule maHashTable->table[key];

    int s = 0, i = 0, j = 0, k = 0, h = 0;
    char * key;
    char * mail;
    char * date;
    int dateC;

    FILE * file = fopen(filepath, "r");
    if (file != NULL) { // Tant qu'on arrive pas à la fin du fichier
        // On consomme les 5 premiers caractères dont on n'en a pas besoin
        for (i = 0; i < 5; i++)
            s = fgetc(file);
            
        for (i = 0; i < 10001; i++) { // Parcourir toutes les lignes du fichier
            // On crée un élèment pour chaque ligne de notre fichier
            HElement * element;
            element = malloc(sizeof(element));
            s = fgetc(file);
            k = 0; 
            key = malloc(10 * sizeof(char));
            
            // KEY
            while (s != 44) { // Tant qu'on rencontre pas de virgule
                key[k] = s;
                k++;
                s = fgetc(file);
            }

            element -> key = malloc(sizeof(char * ));
            strcpy(element -> key, key);
            free(key); // On libère l'espace pour la prochaine allocation

            s = fgetc(file); // Récupérer la virgule suivante
	    
	    // MAIL
            j = 0;
            mail = malloc(100 * sizeof(char));
            while (s != 44) {
                mail[j] = s;
                j++;
                s = fgetc(file);
            }

            element -> mail = malloc(sizeof(char * ));
            strcpy(element -> mail, mail);
            free(mail);

            s = fgetc(file);

	    // DATE DE NAISSANCE
            h = 0;
            date = malloc(100 * sizeof(char));
            while (s != 44 && s != '\n') {
                mail[h] = s;
                h++;
                s = fgetc(file);
            }
            dateC = atoi(date);
            element -> date = dateC;
            free(date);

            // On calcule l'indice de la case ou l'on va insérer l'élèment
            // On choisit parmi les trois fonctions de hachage qu'on a 
            int cle = hash(element);
            cle = cle % 100;
            
            // C'est là qu'on crée une cellule et qu'on met son adresse dans le tableau de hachage
            // Si la case n'est pas vide on insère directement notre élèment en queue de liste sans créer de nouvelle cellule	
            if (maHashTable -> table[cle] != NULL) {
                maHashTable -> table[cle] = enqueueHElement(maHashTable -> table[cle], element);
            }
            // Sinon on crée une nouvelle cellule et on insère l'élèment en tête de liste
            else {
                HCell * TeteCellule;
                TeteCellule = malloc(sizeof(HCell));
                TeteCellule = enqueueHElement(TeteCellule, element);
                maHashTable -> table[cle] = TeteCellule;
            }
        }
        printf("\n");
        // On ferme le fichier
        fclose(file);
    }
    // On retourne la table de hachage
    return maHashTable;
}

HTable * loadHTableASCII(const char * filepath) {
    HTable * maHashTable;
    maHashTable = createHTable(100);
    // Accéder case dans table de hashage et mettre adresse d'une cellule maHashTable->table[key];

    int s = 0, i = 0, j = 0, k = 0, h = 0;
    char * key;
    char * mail;
    char * date;
    int dateC;

    FILE * file = fopen(filepath, "r");
    if (file != NULL) { // Tant qu'on arrive pas à la fin du fichier
        // On consomme les 5 premiers caractères dont on n'en a pas besoin
        for (i = 0; i < 5; i++)
            s = fgetc(file);
            
        for (i = 0; i < 10001; i++) { // Parcourir toutes les lignes du fichier
            // On crée un élèment pour chaque ligne de notre fichier
            HElement * element;
            element = malloc(sizeof(element));
            s = fgetc(file);
            k = 0; 
            key = malloc(10 * sizeof(char));
            
            // KEY
            while (s != 44) { // Tant qu'on rencontre pas de virgule
                key[k] = s;
                k++;
                s = fgetc(file);
            }

            element -> key = malloc(sizeof(char * ));
            strcpy(element -> key, key);
            free(key); // On libère l'espace pour la prochaine allocation

            s = fgetc(file); // Récupérer la virgule suivante
	    
	    // MAIL
            j = 0;
            mail = malloc(100 * sizeof(char));
            while (s != 44) {
                mail[j] = s;
                j++;
                s = fgetc(file);
            }

            element -> mail = malloc(sizeof(char * ));
            strcpy(element -> mail, mail);
            free(mail);

            s = fgetc(file);

	    // DATE DE NAISSANCE
            h = 0;
            date = malloc(100 * sizeof(char));
            while (s != 44 && s != '\n') {
                mail[h] = s;
                h++;
                s = fgetc(file);
            }
            dateC = atoi(date);
            element -> date = dateC;
            free(date);

            // On calcule l'indice de la case ou l'on va insérer l'élèment
            // On choisit parmi les trois fonctions de hachage qu'on a 
            int cle = hashASCII(element);
            cle = cle % 100;
            
            // C'est là qu'on crée une cellule et qu'on met son adresse dans le tableau de hachage
            // Si la case n'est pas vide on insère directement notre élèment en queue de liste sans créer de nouvelle cellule	
            if (maHashTable -> table[cle] != NULL) {
                maHashTable -> table[cle] = enqueueHElement(maHashTable -> table[cle], element);
            }
            // Sinon on crée une nouvelle cellule et on insère l'élèment en tête de liste
            else {
                HCell * TeteCellule;
                TeteCellule = malloc(sizeof(HCell));
                TeteCellule = enqueueHElement(TeteCellule, element);
                maHashTable -> table[cle] = TeteCellule;
            }
        }
        printf("\n");
        // On ferme le fichier
        fclose(file);
    }
    // On retourne la table de hachage
    return maHashTable;
}

HTable * loadHTableHashSumASCII(const char * filepath) {
    HTable * maHashTable;
    maHashTable = createHTable(100);
    // Accéder case dans table de hashage et mettre adresse d'une cellule maHashTable->table[key];

    int s = 0, i = 0, j = 0, k = 0, h = 0;
    char * key;
    char * mail;
    char * date;
    int dateC;

    FILE * file = fopen(filepath, "r");
    if (file != NULL) { // Tant qu'on arrive pas à la fin du fichier
        // On consomme les 5 premiers caractères dont on n'en a pas besoin
        for (i = 0; i < 5; i++)
            s = fgetc(file);
            
        for (i = 0; i < 10001; i++) { // Parcourir toutes les lignes du fichier
            // On crée un élèment pour chaque ligne de notre fichier
            HElement * element;
            element = malloc(sizeof(element));
            s = fgetc(file);
            k = 0; 
            key = malloc(10 * sizeof(char));
            
            // KEY
            while (s != 44) { // Tant qu'on rencontre pas de virgule
                key[k] = s;
                k++;
                s = fgetc(file);
            }

            element -> key = malloc(sizeof(char * ));
            strcpy(element -> key, key);
            free(key); // On libère l'espace pour la prochaine allocation

            s = fgetc(file); // Récupérer la virgule suivante
	    
	    // MAIL
            j = 0;
            mail = malloc(100 * sizeof(char));
            while (s != 44) {
                mail[j] = s;
                j++;
                s = fgetc(file);
            }

            element -> mail = malloc(sizeof(char * ));
            strcpy(element -> mail, mail);
            free(mail);

            s = fgetc(file);

	    // DATE DE NAISSANCE
            h = 0;
            date = malloc(100 * sizeof(char));
            while (s != 44 && s != '\n') {
                mail[h] = s;
                h++;
                s = fgetc(file);
            }
            dateC = atoi(date);
            element -> date = dateC;
            free(date);

            // On calcule l'indice de la case ou l'on va insérer l'élèment
            // On choisit parmi les trois fonctions de hachage qu'on a 
            int cle = hashSommeASCII(element);
            cle = cle % 100;
            
            // C'est là qu'on crée une cellule et qu'on met son adresse dans le tableau de hachage
            // Si la case n'est pas vide on insère directement notre élèment en queue de liste sans créer de nouvelle cellule	
            if (maHashTable -> table[cle] != NULL) {
                maHashTable -> table[cle] = enqueueHElement(maHashTable -> table[cle], element);
            }
            // Sinon on crée une nouvelle cellule et on insère l'élèment en tête de liste
            else {
                HCell * TeteCellule;
                TeteCellule = malloc(sizeof(HCell));
                TeteCellule = enqueueHElement(TeteCellule, element);
                maHashTable -> table[cle] = TeteCellule;
            }
        }
        printf("\n");
        // On ferme le fichier
        fclose(file);
    }
    // On retourne la table de hachage
    return maHashTable;
}
