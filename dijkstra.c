/* Dijkstra Algorithm
Source: https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/ */
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "algorithm.h"
#include "utils.c"
#define INF 99999

void printSolutionD(int **dist, int n, FILE *outputfile)
{
    fprintf (outputfile, "Dijkstra output: \n");
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

/* A utility function to find the vertex with minimum distance value, from
 the set of vertices not yet included in shortest path tree */
int minDistanceD(int dist[], bool sptSet[], int n)
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
void dijkstraSingleSourceD(int **graph, int src, int n, int **weightMatrix)
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
        int u = minDistanceD(dist, sptSet, n);

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

void Dijkstra(int **graph, int n, FILE *outputfile)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(graph[i][j] < 0) {
                fprintf(outputfile, "Dijkstra algorithm : \n");
                fprintf(outputfile, "Dijkstra only works on pozitive weights \n");

                return;
            }
        }
    }

    /* dist[][] contains the shortest distances between every pair of vertices */
    int **weightMatrix;
    
    /* alloc matrix */
    weightMatrix = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        weightMatrix[i] = (int *)calloc(n, sizeof(int)); 
    }

    /* Pick all vertices as source once */ 
    for (int i = 0; i < n; i++) {
        dijkstraSingleSourceD(graph, i, n, weightMatrix);
    }
    
    printSolutionD(weightMatrix, n, outputfile);
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
    Dijkstra(graph, vertex, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    end = clock();
    double duration = ((double)end - start)/CLOCKS_PER_SEC;

    printf("%lf\n", duration);

    return 0;
}
