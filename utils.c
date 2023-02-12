#include "algorithm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 99999

void createAdjMatrix(int **graph, int v[], int n, int newEdge) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                graph[i][i] = 0;
            } else {
                graph[i][j] = INF;
            }
        }
    }
    
    for (int i = 0; i < newEdge; i = i + 3) {
        for (int j = 0; j < n; j++) {
            if (v[i] == j) {
                for (int k = 0; k < n; k++) {
                    if (v[i + 1] == k) {
                        graph[j][k] = v[i + 2];
                    } 
                }
            } 
        }
    }

}