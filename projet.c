#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projet.h"


// Fonction pour créer un nouveau maillon d'arc
/*
   * Données :
        succ : entier représentant le successeur.
        distance : double représentant la distance associée au maillon.
        tournee : pointeur vers une chaîne de caractères représentant la tournée.

   * Résultat :
        Retourne un pointeur vers une nouvelle structure maillon_succ initialisée avec les données fournies.

   * Locales :
        new : pointeur vers une structure maillon_succ utilisée pour allouer et initialiser un nouveau maillon.


*/
struct maillon_succ *createSucc(int succ, double distance, char *tournee) {
  struct maillon_succ *new =
      (struct maillon_succ *)malloc(sizeof(struct maillon_succ));
  new->succ = succ;
  new->distance = distance;
  new->tournee = (char *)malloc(strlen(tournee) + 1);
  strcpy(new->tournee, tournee);
  new->next = NULL;
  return new;
}

// Fonction pour créer un graphe avec n sommets
/*
    * Données :
        n : entier représentant le nombre de sommets dans le graphe.

    * Résultat :
        Retourne un pointeur vers une nouvelle structure Graph initialisée avec n sommets.

    * Locales :
        graph : pointeur vers une structure Graph utilisée pour allouer et initialiser un nouveau graphe.
        i : entier utilisé comme compteur pour initialiser les listes de successeurs des sommets.

*/
struct Graph *createGraph(int n) {
  struct Graph *graph = malloc(sizeof(struct Graph));
  graph->n = n;
  graph->liste_sommets = malloc(n * sizeof(struct maillon_succ));
  for (int i = 0; i <= n; i++) {
    graph->liste_sommets[i] = NULL;
  }
  return graph;
}

// procedure de calcul du tableau tour géant
/*
 * Données :

        MAT matrice d’entiers : matrice distance
        n  : entier : nombre de clients
        ID :entier : numéro du client avec lequel le tour commence

 * Résultat :

        T : tableau d’entiers : Tableau du tour géant

 * Locales :

        min :entier : distance minimale dans une ligne donnée
        min_j : entier : indice de la colonne de la distance minimale dans la ligne courante
        i : entier : indice de la ligne de la distance courante
        j : entier : indice de la colonne de la distance courante
        tot : entier : dimensions de la matrice M (matrice carrée )
        k : entier : indice du choix courant à faire pour l’insérer dans T
        p : entier : indice pour parcourir les lignes de la matrice M
        test : entier : indice pour parcourir les lignes de la matrice M
        M : matrice d’entiers : matrice distance
*/
void tourGeant(int n, const double MAT[n + 1][n + 1], int *T, int ID) {

  double M[n + 1][n + 1];
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      M[i][j] = MAT[i][j];
    }
  }
  double min = M[0][ID];
  int min_j = ID, i = ID, tot = n + 1;
  T[0] = ID;

  for (int p = 0; p < tot; p++) {
    M[p][0] = -1;
    M[p][ID] = -1;
  }
  i = min_j;
  min = M[i][0];
  int test = 0;
  while (min == -1 || min == 0) {
    test++;
    min = M[i][test];
    min_j = test;
  }
  for (int k = 1; k < tot - 1; k++) {
    for (int j = 0; j < tot; j++) {
      if (i != j && M[i][j] != -1 && M[i][j] < min) {
        min = M[i][j];
        min_j = j;
      }
    }

    T[k] = min_j;
    for (int p = 0; p < tot; p++) {
      M[p][min_j] = -1;
    }
    i = min_j;
    min = M[i][0];
    int test = 0;
    while (min == -1 || min == 0) {
      test++;
      min = M[i][test];
      min_j = test;
    }
  }
  printf("le tour géant est :\n");
  for (int i = 0; i < n; i++) {
    printf("%d|", T[i]);
  }
  printf("\n");
}

// Procédure pour convertir un nombre entier en chaîne de caractères
/*
    * Données :
        num : entier à convertir en chaîne de caractères.


    Résultat :
        str : pointeur vers une chaîne de caractères où stocker le résultat de la conversion.

    Locales :
        i : entier utilisé comme compteur pour remplir la chaîne de caractères.
        temp : entier temporaire utilisé pour compter le nombre de chiffres dans num.


*/
void convertir_en_str(int num, char *str) {
  int i = 0;
  if (num == 0) { // Cas où num est 0
    str[i] = '0';
    i++;
  } else { // compter le nombre de chiffres
    int temp = num;
    while (temp > 0) {
      temp = temp / 10;
      i++;
    }
    str[i] = '\0';
    while (num > 0) { // remplir la chaine de caractère
      i--;
      str[i] = (num % 10) + '0';
      num = num / 10;
    }
  }
}

// procedure SPLIT pour construire le graphe auxiliaire H
/*
 * Données :
            T:vecteur:d’entier: tour géant
            Q capacité des véhicules
            n nombre de clients
            M matrice distance
            q vecteur du nombre d’unités à livrer à chaque client
* Résultat :
            pondération : tableau de structure pond :  tableau qui contient la pondération des arcs
            head : vecteur d’entiers :tableau head de du graphe résultant
            succ : vecteur d’entiers : tableau succ du graph résultant
* Locales :
            cost coût courant
            load chargement courant
            i, j indices utilisés pour parcourir les clients de T
            k indice pour remplir le tableau pondération
            h indice pour parcourir le tableau head
            code_ascii c’est le code ascii du caractère de l’indice du client
*/
void procedureSplit(int *K, int Q, int n, double M[n + 1][n + 1], int *q,
                    struct Graph *graph) {
  int T[n + 1];
  T[0] = 0;
  for (int i = 1; i <= n; i++) {
    T[i] = K[i - 1];
  }

  double cost;
  int load, i, j, k;

  for (i = 1; i <= n; i++) {
    j = i;
    load = 0;
    do {
      load += q[T[j]];
      if (i == j) {
        cost = 2 * M[0][T[i]];
      } else {
        cost = cost - M[T[j - 1]][0] + M[T[j - 1]][T[j]] + M[T[j]][0];
      }
      if (load <= Q) {
        char tournee[1000] = "";
        for (k = i; k <= j; k++) {
          char str[10];
          convertir_en_str(T[k], str);
          strcat(tournee, str);
          if (k < j) { // Ajouter une virgule seulement entre les éléments
            strcat(tournee, ",");
          }
        }
        // creation du nouveau arc
        struct maillon_succ *new = createSucc(j, cost, tournee);
        // ajout de l'arc en tete de la liste du sommet i-1
        new->next = graph->liste_sommets[i - 1];
        graph->liste_sommets[i - 1] = new;
      }
      j++;
    } while (j <= n && load < Q);
  }
}

// procedure pour afficher les résultats de Bellman-Ford
/*
    * Données :
        n : entier représentant le nombre total de sommets dans le graphe.
        tournee : tableau de pointeurs vers des chaînes de caractères représentant les étapes de la tournée.
        pi : tableau de nombres flottants représentant les distances les plus courtes depuis le sommet source.
        pere : tableau d'entiers représentant les indices des prédécesseurs des sommets.

   * Résultat :
        Aucune valeur de retour (void). La fonction affiche simplement les résultats de l'algorithme de Bellman-Ford.

   * Locales :
        i : entier utilisé comme compteur pour parcourir les sommets et les résultats.
        Aucune autre variable locale explicite.

*/
void affichage_bellman(int n, char **tournee, double *pi, int *pere) {
  printf("Belleman : \n");
  printf("Sommet\tDistance depuis la source\tPredecesseur\tTournee\n");
  for (int i = 0; i <= n; i++) {
    if (tournee[i]) {
      printf("%d\t%.2f\t                         %d\t\t%s\n", i, pi[i], pere[i],
             tournee[i]);
    } else {
      printf("%d\t%.2f\t                         %d\t\tc'est la racine\n", i,
             pi[i], pere[i]);
    }
    if (i == n) {
      printf("le cout total est %lf \n ", pi[i]);
    }
  }
}

// procedure pour afficher la tournée optimale
/*
   * Données :
        n : entier représentant le nombre total d'étapes dans la tournée.
        r : entier représentant l'indice de l'étape de départ.
        tournee : tableau de pointeurs vers des chaînes de caractères représentant les étapes de la tournée.
        pere : tableau d'entiers représentant les indices des étapes précédentes dans la tournée optimale.

   * Résultat :
        Aucune valeur de retour (void). La fonction affiche simplement la tournée optimale.

   * Locales :
        i : entier utilisé comme compteur pour parcourir les étapes.
        nb_tournees : entier représentant le nombre total de tournées à effectuer.
        j : entier utilisé comme compteur pour remplir le tableau d'étapes.
        etapes : tableau de pointeurs vers des chaînes de caractères pour stocker les étapes de la tournée dans l'ordre inverse.


*/
void affichage_tournee_optimale(int n, int r, char **tournee, int *pere) {
  printf("\nTournée optimale : ");

  // Compter le nombre de tournées à faire
  int i = n;
  int nb_tournees = 0;
  while (i != r) {
    nb_tournees++;
    i = pere[i];
  }

  // Créer un tableau pour stocker les  tournées
  char *etapes[nb_tournees];
  i = n;
  int j = 0;
  while (i != r) {
    if (tournee[i] != NULL) {
      etapes[j] = tournee[i];
      j++;
    }
    i = pere[i];
  }

  // Afficher les tournées en ordre inverse
  printf("{");
  for (int j = nb_tournees - 1; j >= 0; j--) {
    printf("(%s)", etapes[j]);
  }
  printf("}");
  printf("\n");
}

// procedure de l'algorithme de Bellman-Ford avec affichage des prédécesseurs
/*
 * Données :
            graph: Le graphe sur lequel l'algorithme est exécuté.
            r: Le sommet source à partir duquel l'algorithme commence à calculer les distances les plus courtes.
 * Résultats :
            pi: Un tableau contenant les distances les plus courtes de la source r à chaque sommet du graphe.
            père: Un tableau contenant les prédécesseurs de chaque sommet sur le chemin le plus court de la source r.
            Tournée: Un tableau contenant les informations sur la tournée optimale pour chaque sommet.
 * Locales :
            n: Le nombre total de sommets dans le graphe.
            arc: Variable temporaire utilisée pour parcourir les listes d'adjacence et accéder aux arcs.
            x, y: Indices des sommets utilisés dans les boucles de l'algorithme.
            i: Variable de boucle utilisée pour itérer à travers les sommets du graphe.
*/
void bellmanFord(struct Graph *graph, int r) {
  int n = graph->n;
  double pi[n + 1];
  int pere[n + 1];
  char *tournee[n + 1];

  // Initializer π à l'infini et  Père à 0
  for (int i = 0; i <= n; i++) {
    pi[i] = INF;
    pere[i] = 0;
    tournee[i] = NULL;
  }
  pi[r] = 0;
  pere[r] = r;

  // Parcourir les successeurs de la racine
  struct maillon_succ *arc = graph->liste_sommets[r];
  while (arc != NULL) {
    int succ = arc->succ;
    pi[succ] = arc->distance;
    pere[succ] = r;
    tournee[succ] = arc->tournee;
    arc = arc->next;
  }

  // Relâcher les arêtes
  for (int i = 1; i <= n; i++) {
    for (int x = 0; x <= n; x++) {
      arc = graph->liste_sommets[x];
      while (arc != NULL) {
        int y = arc->succ;
        if (pi[x] + arc->distance < pi[y]) {
          pi[y] = pi[x] + arc->distance; // mettre à jour le tableau pi (tableau
                                         // de la distance)
          pere[y] = x;               // mettre à jour le tableau père
          tournee[y] = arc->tournee; // mettre à jour le tableau de la tournnée
        }
        arc = arc->next;
      }
    }
  }
  affichage_bellman(n, tournee, pi, pere);
  affichage_tournee_optimale(n, r, tournee, pere);
}

// procedure pour libérer la mémoire allouée dynamiquement
/*
    Données :
        nb_clients : entier représentant le nombre de clients.
        graph : pointeur vers une structure Graph contenant la liste des sommets.
        Tour : pointeur vers un tableau d'entiers représentant le tour géant.

    Résultat :
        Aucune valeur de retour (void). La fonction libère simplement la mémoire allouée dynamiquement.

    Locales :
        arc : pointeur vers un maillon de successeur courant dans la liste des successeurs.
        temp : pointeur temporaire pour libérer la mémoire.

*/
void liberation_memoire(int nb_clients, struct Graph *graph, int *Tour) {

  for (int i = 0; i <= nb_clients; i++) {
    struct maillon_succ *arc = graph->liste_sommets[i];
    while (arc) {
      struct maillon_succ *temp = arc;
      arc = arc->next;
      free(temp->tournee);
      free(temp);
    }
  }
  free(graph->liste_sommets);
  free(graph);
  free(Tour);
}
