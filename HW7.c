#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// coordinate with its vertex num
typedef struct coordinate {
	int vnum;
	double x;
	double y;
} Cor;

// two connected vertices with its weight 
typedef struct edge {
	int node[2];
	double distance;
} Edge;

Cor* initCor(int n); // memory allocation for Cor
Edge* initEdge(int n); // memory allocation for Edge
void read_input(FILE* in, Cor* c, int n); // reads input from a file
void find_edge(Cor* c, Edge* e, int n); // calculate every possible edges from all the vertices
int compare(const void* a, const void* b); // sort by distance

double kruskal(Edge* e, int* set, int n);
int get_parent(int* parent, int n); // find parent node
void unionParent(int* set, int a, int b); // sets the parent node as minimum nodes
int find(int* set, int a, int b); // find out if vertices are already part of the subtree

int main() {
	FILE* in = fopen("input.txt", "r");
	if (in == NULL) {
		printf("Failed to open!");
		return -1;
	}

	int n;
	while (fscanf(in, "%d", &n) != EOF) {
		Cor* c = initCor(n);
		Edge* e = initEdge(n * (n - 1) / 2); // n*(n-1)/2 for every possible edge for n vertices

		read_input(in, c, n);

		find_edge(c, e, n);

		qsort(e, n * (n - 1) / 2, sizeof(Edge), compare);

		// saves root node of vertices
		int* set = (int*)malloc(sizeof(int) * n);
		for (int i = 0; i < n; i++) { // initialize as it points itself
			set[i] = i;
		}

		printf("%.2f\n", kruskal(e, set, (n * (n - 1) / 2)));

		free(c);
		free(e);
		free(set);
	}
	fclose(in);
	return 0;
}

Cor* initCor(int n) {
	Cor* c = (Cor*)malloc(sizeof(Cor) * n);
	if (c == NULL) {
		printf("Failed to allocate memory!\n");
		return NULL;
	}
	return c;
}

Edge* initEdge(int n) {
	Edge* e = (Edge*)malloc(sizeof(Edge) * n);
	if (e == NULL) {
		printf("Failed to allocate memory!\n");
		return NULL;
	}
	return e;
}

void read_input(FILE* in, Cor* c, int n) {
	for (int i = 0; i < n; i++) {
		c[i].vnum = i;
		fscanf(in, "%lf %lf", &c[i].x, &c[i].y);
	}
}

void find_edge(Cor* c, Edge* e, int n) {
	int idx = 0;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			e[idx].node[0] = c[i].vnum;
			e[idx].node[1] = c[j].vnum;
			e[idx].distance = sqrt(pow((c[j].x - c[i].x), 2) + pow((c[j].y - c[i].y), 2)); // calculating a slope
			idx++;
		}
	}
}

int compare(const void* a, const void* b) {
	Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;

    if (edgeA->distance < edgeB->distance) return -1;
    if (edgeA->distance > edgeB->distance) return 1;
    return 0;
}

double kruskal(Edge* e, int* set, int n) {
	double sum = 0.0;
	for (int i = 0; i < n; i++) {
		if (!find(set, e[i].node[0], e[i].node[1])) { // if func find is not true, which means vertex e[i].node[0] and e[i].node[1]'s edge is not part of a calculating weight subtree add its weight to the sum
			sum += e[i].distance;
			unionParent(set, e[i].node[0], e[i].node[1]); // then change its root node to the smaller root node
		}
	}
	return sum;
}

int get_parent(int* set, int num) { // as it goes through the root node for each vertex, find and return the smallest vertex which is the parent
	if (set[num] == num) return num;
	return set[num] = get_parent(set, set[num]);
}

void unionParent(int* set, int a, int b) {
	a = get_parent(set, a);
	b = get_parent(set, b);
	if (a < b) set[b] = a; // compare root node for two vertices and save its root as smaller one
	else set[a] = b;
}

int find(int* set, int a, int b) {
	a = get_parent(set, a);
	b = get_parent(set, b);
	if (a == b) return 1; // if they share the same parent, return true
	else return 0;
}