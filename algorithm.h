#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define INF 99999

typedef struct edge {
    int src;
    int dest;
    int weight;
} edge;

void FloydWarshall(int **graph, int v, FILE *outputfile);
void printSolutionFW(int **dist, int n, FILE *outputfile);

void Dijkstra(int **graph, int n, FILE *outputfile);
void dijkstraSingleSourceD(int **graph, int src, int n, int **weightMatrix);
int minDistanceD(int dist[], bool sptSet[], int n);
void printSolutionD(int **dist, int n, FILE *outputfile);


void Johnson(int **graph, int n, int edges, FILE *outputfile);
void BellmanFord(int **newmatrix, int source, int h[], edge e[], int edges, FILE *outputfile,
                    bool *breakingPoint);
void DijkstraJ(int **graph, int n, FILE *outputfile);
void dijkstraSingleSourceJ(int **graph, int src, int n, int **weightMatrix);
int minDistanceJ(int dist[], bool sptSet[], int n);
void printSolutionJ(int **dist, int n, FILE *outputfile);

void createAdjMatrix(int **graph, int v[], int n, int newEdge);

#endif