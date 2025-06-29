#if ! defined (PROJET_H)
#define PROJET_H 1

#define INF 100000000

/**********************************************************************
 * IMPLANTATION
 *
 * Spécification de l'implantation
 *
 * Implantation de Tableau de listes chaînées (Graph)
 *
 * Les maillons sont alloués dynamiquement.
 * Le champ next du dernier maillon vaut (struct maillon_double*)0
 *
 * Le champ liste_sommets d'une liste pointe vers le premier maillon???
 * Le champ n est égal au nombre de maillons de la liste
 *
 * Des listes distinctes ont des maillons distincts (pas de maillon partagé).
 **********************************************************************/

// Structure pour représenter les maillons des arcs du graphe
struct maillon_succ {
  int succ;                  // Successeur
  double distance;           // Distance
  char *tournee;             // Tournée
  struct maillon_succ *next; // Pointeur vers le maillon suivant
};

// Structure pour représenter le graphe avec des listes d'adjacence
struct Graph {
  int n;                      // Nombre de sommets
  struct maillon_succ *
      *liste_sommets;         // Tableau de listes chainées  des successeurs
                              // correspondant à chaque sommets
                              // le dernier sommet du graph n'est pas inclut dans
                              // liste_sommets car il n'a pas de successeurs
};


/**********************************************************************
 * PROTOTYPES DES FONCTIONS
 **********************************************************************/

// Fonction pour créer un nouveau maillon d'arc
struct maillon_succ *createSucc(int succ, double distance, char *tournee);

// Fonction pour créer un graphe avec n sommets
struct Graph *createGraph(int n);

// procedure de calcul du tableau tour géant
extern void tourGeant(int n, const double MAT[n + 1][n + 1], int *T, int ID);

// Procédure pour convertir un nombre entier en chaîne de caractères
extern void convertir_en_str(int num, char *str);

// Fonction SPLIT pour construire le graphe auxiliaire H
extern void procedureSplit(int *K, int Q, int n, double M[n + 1][n + 1], int *q, struct Graph *graph);

// Fonction pour afficher les résultats de Bellman-Ford
extern void affichage_bellman(int n, char **tournee, double *pi, int *pere);

// Fonction pour afficher la tournée optimale
extern void affichage_tournee_optimale(int n, int r, char **tournee, int *pere);

// Fonction pour l'algorithme de Bellman-Ford avec affichage des prédécesseurs
extern void bellmanFord(struct Graph *graph, int r);

// Fonction pour libérer la mémoire allouée dynamiquement
extern void liberation_memoire(int nb_clients, struct Graph *graph, int *Tour);

#endif





