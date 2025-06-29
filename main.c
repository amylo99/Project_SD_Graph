#include <stdio.h>
#include <stdlib.h>
#include "projet.h"

// Fonction principale

int main() {

        int nb_clients;
        int capacite_vehicule;

        // Lire le nombre de clients
        if (scanf("%d", &nb_clients) != 1) {
            printf("Erreur lecture nb_clients\n");
            exit(3);
        }
        // Lire la capacité du véhicule
        if (scanf("%d", &capacite_vehicule) != 1) {
            printf("Erreur lecture capacite_vehicule\n");
            exit(4);
        }

        int demande_client[nb_clients];
        demande_client[0] = 0;

        // Lire les demandes des clients
        for (int i = 1; i <= nb_clients; i++) {
            if (scanf("%d", &demande_client[i]) != 1) {
            printf("Erreur lecture demande_client\n");
            exit(5);
            }
        }

        double mat_distance[nb_clients + 1][nb_clients + 1];

        // Lire la matrice des distances
        for (int i = 0; i <= nb_clients; i++) {
            for (int j = 0; j <= nb_clients; j++) {
            if (scanf("%lf", &mat_distance[i][j]) != 1) {
                printf("Erreur lecture mat_distance\n");
                exit(6);
            }
            }
        }
        int *Tour = (int *)malloc(nb_clients * sizeof(int));
        int premier_client;
        premier_client = 1;

        // Calculer le tour géant
        tourGeant(nb_clients, mat_distance, Tour, premier_client);

        // Créer le graphe
        struct Graph *graph = createGraph(nb_clients);

        // Construire le graphe auxiliaire
        procedureSplit(Tour, capacite_vehicule, nb_clients, mat_distance,
                        demande_client, graph);
        // Appliquer l'algorithme de Bellman-Ford
        bellmanFord(graph, 0);

        // Libérer la mémoire
        liberation_memoire(nb_clients, graph, Tour);

        return 0;
}
