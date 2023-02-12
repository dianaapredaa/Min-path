CC = gcc
CFLAGS = -Wall -lm

build: Dijkstra Floyd-Warshall Johnson RunP3 RunP1 RunP2 RunBest

run-p3:
	./run_all.sh p3

run-p1:
	./run_all.sh p1

run-p2:
	./run_all.sh p2

run-best:
	./run_all.sh best

run-all:
	./run_all.sh p1
	./run_all.sh p2
	./run_all.sh p3
	./run_all.sh best

Dijkstra: dijkstra.c
	$(CC) dijkstra.c -c $(CFLAGS)

Floyd-Warshall: floyd-warshall.c
	$(CC) floyd-warshall.c -c $(CFLAGS)

Johnson: johnson.c
	$(CC) johnson.c -c $(CFLAGS)

RunP3:
	$(CC) johnson.c -o p3 $(CFLAGS)

RunP1:
	$(CC) floyd-warshall.c -o p1 $(CFLAGS)

RunP2:
	$(CC) dijkstra.c -o p2 $(CFLAGS)

RunBest:
	$(CC) floyd-warshall.c -o best $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o p1 p2 best