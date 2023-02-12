/* Floyd-Warshall Algorithm 
Source: https://www.programiz.com/dsa/floyd-warshall-algorithm */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "algorithm.h"
#include "utils.c"
#define INF 99999

void printSolutionFW(int **dist, int n, FILE *outputfile)
{
    fprintf (outputfile, "Floy-Warshall output: \n");
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

void FloydWarshall(int **graph, int v, FILE *outputfile)
{
    /* dist[][] contains the shortest distances between every pair of vertices */
    int **dist;

    /* alloc matrix */
    dist = malloc(v * sizeof(int*));
    for (int i = 0; i < v; i++) {
        dist[i] = (int *)calloc(v, sizeof(int)); 
    }


    /* Initialize the solution matrix same as input graph matrix */
    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            dist[i][j] = graph[i][j];
    
    /* Add all vertices one by one to the set of intermediate vertices. */
    for (int k = 0; k < v; k++)
    {
        /* Pick all vertices as source once */
        for (int i = 0; i < v; i++)
        {
            /* Pick all vertices as destination for the above picked source */
            for (int j = 0; j < v; j++)
            {
                /* If vertex k is on the shortest path from i to j,
                then update the value of dist[i][j] */
                if (dist[i][k] != INF && dist[k][j] != INF)
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];

            }
        }
    }

    /* If distance of any vertex from itself
       becomes negative, then there is a negative
       weight cycle */
    for (int i = 0; i < v; i++) {
        if (dist[i][i] < 0) {
            fprintf(outputfile,"Floyd - Warshall algorithm : \n");
            fprintf(outputfile,"The graph has negative cycles \n");
            return;
        }
    }
    printSolutionFW(dist, v, outputfile);
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
    FloydWarshall(graph, vertex, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    end = clock();
    double duration = ((double)end - start)/CLOCKS_PER_SEC;

    printf("%lf\n", duration);

    return 0;
}
