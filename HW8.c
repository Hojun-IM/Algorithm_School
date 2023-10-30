#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>

long long** distInit(int n); // matrix to save distance info
int* curInit(int n); // tells where current health centers are
int read_curCenter(FILE* in, int* cur, int inter, int n); // reads current health center location
int read_intersection(FILE* in, long long** dist, int n); // reads input intersection info
int getLocation(long long** dist, int* cur, int inter, int healthCenter); // find a place to build a new health center
double stdDev(double* stddevs, double* distances, int possibleInter); // find standard deviation from intersections to the health centers
void distRelease(long long** dist, int n); // release distance matrix
void curRelease(int* cur); // release current health center array

int main() {
	FILE* in = fopen("input.txt", "r");

	int healthCenter, intersection;
	fscanf(in, "%d %d", &healthCenter, &intersection);
	if (healthCenter > 100 || intersection > 100) {
		printf("Invalid Input\n");
		return -1;
	}

	int inputCheck;
	int* curCenter = curInit(intersection);
	inputCheck = read_curCenter(in, curCenter, intersection, healthCenter);
	if (inputCheck != 1) return -1;

	long long** dist = distInit(intersection);
	inputCheck = read_intersection(in, dist, intersection);
	if (inputCheck != 1) return -1;

	printf("%d\n", getLocation(dist, curCenter, intersection, healthCenter));

	distRelease(dist, intersection);
	curRelease(curCenter);
	fclose(in);
	return 0;
}

long long** distInit(int n) {
	long long** arr = (long long**)malloc(sizeof(long long*) * n);
	for (int i = 0; i < n; i++) {
		arr[i] = (long long*)malloc(sizeof(long long) * n);
	}
	return arr;
}

int* curInit(int n) {
	int* arr = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		arr[i] = 0;
	}
	return arr;
}

int read_curCenter(FILE* in, int* cur, int inter, int n) { // save 1 to the index where the health centers already exist
	for (int i = 0; i < n; i++) {
		int a;
		fscanf(in, "%d", &a);
		if (a > inter || a < 0) {
			printf("Invalid Input\n");
			return -1;
		}
		cur[a - 1] = 1;
	}
	return 1;
}

int read_intersection(FILE* in, long long** dist, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) { // distance to itself
				dist[i][j] = 0;
				continue;
			}
			dist[i][j] = INT_MAX; // no direct path exists
		}
	}
	int a, b, c;
	while (fscanf(in, "%d %d %d", &a, &b, &c) != EOF) { // distance info (two-way)
		if (a > n || b > n) {
			printf("Invalid Input\n");
			return -1;
		}
		dist[a - 1][b - 1] = c;
		dist[b - 1][a - 1] = c;
	}
	return 1;
}

int getLocation(long long** dist, int* cur, int inter, int healthCenter) {
	for (int k = 0; k < inter; k++) { // Floyd-Warshall algorithm
		for (int i = 0; i < inter; i++) {
			for (int j = 0; j < inter; j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}

	double* stddevs = (double*)malloc(sizeof(double) * inter);
	for (int i = 0; i < inter; i++) {
		stddevs[i] = 0;
	}

	int possibleInter = inter - healthCenter - 1;
	for (int i = 0; i < possibleInter; i++) {
		if (cur[i] == 1) continue;
		cur[i] = 1;// get the intersection index for the potential new location

		double* distances = (double*)malloc(sizeof(double) * possibleInter); // saves distances from intersection to the nearest health center
		for (int j = 0; j < possibleInter; j++) {
			distances[j] = DBL_MAX;
		}

		int idx = 0;
		for (int j = 0; j < inter; j++) {// find minimum distance from each intersection to the nearest health center
			int minVal = INT_MAX;
			if (cur[j] == 1)continue;
			for (int k = 0; k < inter; k++) {
				if (cur[k] != 1)continue;
				if (minVal > dist[j][k]) minVal = dist[j][k];
			}
			distances[idx++] = minVal;
		}

		// store the standard deviation in the array
		stddevs[i] = stdDev(stddevs, distances, possibleInter);

		// free the dynamically allocated distances array
		free(distances);
		cur[i] = 0;
	}

	// find the intersection for a new health center by finding minimum standard deviation to the health center from each intersection
	int minDist = INT_MAX;
	int minInter = 0;
	for (int i = 0; i < inter; i++) {
		if (cur[i] == 1) continue;
		if (minDist > stddevs[i]) {
			minDist = stddevs[i];
			minInter = i + 1;
		}
	}

	free(stddevs);
	return minInter;
}

double stdDev(double* stddevs, double* distances, int possibleInter) {
	// Calculate standard deviation
	double mean = 0.0;
	for (int j = 0; j < possibleInter; j++) {
		mean += distances[j];
	}
	mean /= possibleInter;

	double stddev = 0.0;
	for (int j = 0; j < possibleInter; j++) {
		stddev += ((distances[j] - mean) * (distances[j] - mean));
	}
	stddev = sqrt((stddev / possibleInter));

	// store the standard deviation in the array
	return stddev;
}

void distRelease(long long** dist, int n) {
	for (int i = 0; i < n; i++) {
		free(dist[i]);
	}
	free(dist);
}

void curRelease(int* cur) {
	free(cur);
}