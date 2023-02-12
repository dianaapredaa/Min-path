/* Johnson Algorithm
Source: https://www.geeksforgeeks.org/johnsons-algorithm-for-all-pairs-shortest-paths-implementation/ */
/* Bellman-Ford Algorithm
Source:  https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/ */
#include "algorithm.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "algorithm.h"
#include "utils.c"
#define INF 99999

void printSolutionJ(int **dist, int n, FILE *outputfile)
{
    fprintf (outputfile, "Johnson output: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                fprintf(outputfile, "%7s", "INF");
            else
                fprintf (outputfile, "%7d", dist[i][j]);
        }
        fprintf(outputfile,"\n");
    }
}

void BellmanFord(int **matrix, int source, int dist[], edge edge[], int edges, FILE *outputfile,
                    bool *breakingPoint) {
    /* Initialize distances from source to the all other vertices as INF */ 
    for (int i = 0; i < source + 1; i++)
        dist[i] = INF;

    dist[source] = 0;

    /* Relax all edges |V| - 1 times. A simple shortest
       path from src to any other vertex can have at-most |V| - 1 edges */
    for (int i = 0; i < source; i++) {
        for (int j = 0; j < edges; j++) {
            int u = edge[j].src;
            int v = edge[j].dest;
            int weight = edge[j].weight;
            if(dist[u] != INF && weight != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    /* Check for negative-weight cycles. The above
       step guarantees shortest distances if graph doesn't
       contain negative weight cycle. If we get a shorter
       path, then there is a cycle. */
    for(int i = 0; i < edges; i++) {
        int u = edge[i].src;
        int v = edge[i].dest;
        int weight = edge[i].weight;
        if(dist[u] != INF && dist[u] + weight < dist[v]) {
            fprintf (outputfile, "Johnson output: \n");
            fprintf(outputfile, "Graph contains negative weight cycle\n");
            *breakingPoint = true;
            return;
        }
    }
  
    return;
}

/* A utility function to find the vertex with minimum distance value, from
 the set of vertices not yet included in shortest path tree */
int minDistanceJ(int dist[], bool sptSet[], int n)
{
    int min = INT_MAX;
    int min_index;
 
    for (int v = 0; v < n; v++)
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
 
    return min_index;
}

/* Function that implements Dijkstra's single source shortest path algorithm
   for a graph represented using adjacency matrix representation */
void dijkstraSingleSourceJ(int **graph, int src, int n, int **weightMatrix)
{
    /* dist[i] will hold the shortest distance from src to dest */
    int dist[n]; 

    /* sptSet[i] will be true if vertex i is included in shortest
       path tree or shortest distance from src to i is finalized */
    bool sptSet[n]; 

    /* Initialize all distances as INFINITE and stpSet[] as false */
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        sptSet[i] = false;
    }
 
    /* Distance of source vertex from itself is always 0 */
    dist[src] = 0;

    /* Find shortest path for all vertices */
    for (int count = 0; count < n - 1; count++) {
        /* Pick the minimum distance vertex from the set of vertices not
           yet processed. u is always equal to src in the first iteration */
        int u = minDistanceJ(dist, sptSet, n);

        /* Mark the picked vertex as processed */
        sptSet[u] = true;

        /* Update dist value of the adjacent vertices of the picked vertex */
        for (int v = 0; v < n; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INF
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];    
        }
    }

    /* neede in order to have the same output for all three algprithms */
    for (int j = 0; j < n; j++) 
        weightMatrix[src][j] = dist[j];
}


void DijkstraJ(int **graph, int n, FILE *outputfile)
{
    /* dist[][] contains the shortest distances between every pair of vertices */
    int **weightMatrix;
    
    /* alloc matrix */
    weightMatrix = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        weightMatrix[i] = (int *)calloc(n, sizeof(int)); 
    }

    /* Pick all vertices as source once */ 
    for (int i = 0; i < n; i++) {
        dijkstraSingleSourceJ(graph, i, n, weightMatrix);
    }

    printSolutionJ(weightMatrix, n, outputfile);
}


void Johnson(int **graph, int n, int edges, FILE *outputfile) {

    int **matrix;

    /* alloc matrix */
    matrix = malloc((n + 1) * sizeof(int*));
    for (int i = 0; i < n + 1; i++) {
        matrix[i] = (int *)calloc((n + 1), sizeof(int)); 
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = graph[i][j];

    for (int i = 0; i < n + 1; i++) {
        matrix[n][i] = 0;
        if (i != n) {
            matrix[i][n] = INF;
        }
    }

    edges = edges + n;


    /* We use Bellman-Ford algorithm calculating the shortest
       distances from the new node to all other vertices. */
    edge edge[edges];
    int k = 0;
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            if (matrix[i][j] != INF && i != j) {
                edge[k].src = i;
                edge[k].dest = j;
                edge[k].weight = matrix[i][j];
                k++;
            }
        }
    }

    int dist[n];
    bool breakingPoint = false;

    /* We apply Bellman-Ford for the new graph */
    BellmanFord(matrix, n, dist, edge, edges, outputfile, &breakingPoint);
    
    if (breakingPoint) {
        return;
    } 
    
    /* We go back to the original graph and reweight the edges */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] != INF)
                graph[i][j] = graph[i][j] + dist[i] - dist[j];
        }
    }

    /* We apply Dijkstra */
    DijkstraJ(graph, n, outputfile);

    return;  
}


int main(int argc, char *argv[]) {
///////////////// CHECKER /////////////////

    clock_t start, end;
    start = clock();

    int vertex;
    int edges;
    int v[1000];

    FILE *inputFile = fopen("test.in","rt");
    FILE *outputFile = fopen("test.out", "wt");

    fscanf(inputFile,"%d", &vertex);
    fscanf(inputFile,"%d", &edges);

    for (int i = 0; i < edges * 3; i++) {
        fscanf(inputFile, "%d", &v[i]);
    }
    
    int **graph;
    graph = malloc(vertex * sizeof(int*));
    for (int i = 0; i < vertex; i++) {
        graph[i] = (int *)calloc(vertex, sizeof(int)); 
    }
    
    createAdjMatrix(graph, v, vertex, edges * 3);
    Johnson(graph, vertex, edges, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    end = clock();
    double duration = ((double)end - start)/CLOCKS_PER_SEC;

    printf("%lf\n", duration);

    return 0;
}