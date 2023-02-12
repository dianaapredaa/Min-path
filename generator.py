import random

def random_adjacency_list(V, E):

    matrix = []

    for i in range(E):
        
        row = [random.randint(0, V - 1), random.randint(0, V-1), random.randint(-99, 99)]

        matrix.insert(len(matrix), row)
    return matrix



V = random.randint(5, 100)
E = random.randint(5, 100)

matrix = random_adjacency_list(V, E)

print(str(V) + " " + str(E))
for row in matrix:
    print(*row)