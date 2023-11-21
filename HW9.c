#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

int readInput1(FILE* in);
void readInput2(FILE* in, Point* p, int frosh);
Point* initPoint(int frosh);
int comparePoints(const void* a, const void* b);
int CCW(Point* p, Point* q, Point* r);
void grahamScan(Point* points, int n, int* hull, int* hullSize);
double calculateConvexHullLength(Point* points, int n);

int main() {
    FILE* in = fopen("input.txt", "r");

    // read inputs
    int frosh = readInput1(in);
    if (frosh > 100 || frosh < 3) {
        printf("Invalid Input\n");
        return -1;
    }
    Point* p = initPoint(frosh);
    readInput2(in, p, frosh);

    // Calculate the convex hull length
    double convexHullLength = calculateConvexHullLength(p, frosh);

    // Calculate the distance from the first point to the origin (0, 0)
    double distanceToOrigin = hypot(p[0].x, p[0].y);

    // Calculate the result by adding the convex hull length and 2 times the distance to the origin
    double result = convexHullLength + 2 * distanceToOrigin;

    // Print the result with up to 2 decimal points
    printf("%.2f\n", result);
    
    free(p);
    fclose(in);
    return 0;
}

int readInput1(FILE* in) {
    int frosh;
    fscanf(in, "%d", &frosh);
    return frosh;
}

void readInput2(FILE* in, Point* p, int frosh) {
    for (int i = 0; i < frosh; i++) {
        fscanf(in, "%lf %lf", &p[i].x, &p[i].y);
    }
}

Point* initPoint(int frosh) {
    Point* p = (Point*)malloc(sizeof(Point) * frosh);
    return p;
}

int comparePoints(const void* a, const void* b) {
    Point* pA = (Point*)a;
    Point* pB = (Point*)b;

    // Calculate the angle of two points with respect to the base point (smallest y-coordinate)
    double angleA = atan2(pA->y, pA->x);
    double angleB = atan2(pB->y, pB->x);
    if (angleA < angleB) return -1;
    if (angleA > angleB) return 1;

    // If the angles are the same, compare distances to the base point
    double distanceA = pA->x * pA->x + pA->y * pA->y; // Euclidean distance considering base as 0,0
    double distanceB = pB->x * pB->x + pB->y * pB->y;
    if (distanceA < distanceB) return -1;
    if (distanceA > distanceB) return 1;

    return 0;
}

int CCW(Point* p, Point* q, Point* r) {
    // using outer product
    double val = (q->y - p->y) * (r->x - q->x) - (q->x - p->x) * (r->y - q->y);

    if (val > 0) return 1; // CW
    else if (val < 0) return -1; // CCW
    else return 0; // Equal
}

void grahamScan(Point* p, int n, int* hull, int* hullSize) {
    int base = 0; // lowest y-coordinate (and leftmost if tied)
    for (int i = 1; i < n; i++) {
        if (p[i].y < p[base].y || (p[i].y == p[base].y && p[i].x < p[base].x)) {
            base = i;
        }
    }

    // Sort the points by angles from the base point
    qsort(&p[0], n, sizeof(Point), comparePoints);

    // Initialize the convex hull with the first three points
    hull[0] = 0;
    hull[1] = 1;
    hull[2] = 2;
    *hullSize = 3;

    // Process the remaining points
    for (int i = 3; i < n; i++) {
        // Keep removing the last point from the hull stack while the orientation is not counterclockwise
        while (*hullSize > 1 && CCW(&p[hull[*hullSize - 2]], &p[hull[*hullSize - 1]], &p[i]) != -1) {
            (*hullSize)--;
        }

        // Add the current point to the hull
        hull[*hullSize] = i;
        (*hullSize)++;
    }
}

double calculateConvexHullLength(Point* p, int n) {
    // Allocate memory for the convex hull to use it as a stack
    int* hull = (int*)malloc(sizeof(int) * n);
    int hullSize;

    // Apply the Graham Scan algorithm to find the convex hull
    grahamScan(p, n, hull, &hullSize);

    // Calculate the length of the convex hull
    double length = 0.0;
    for (int i = 0; i < hullSize - 1; i++) {
        length += hypot(p[hull[i]].x - p[hull[i + 1]].x, p[hull[i]].y - p[hull[i + 1]].y);
    }
    // length from the last point to the first point
    length += hypot(p[hull[hullSize - 1]].x - p[hull[0]].x, p[hull[hullSize - 1]].y - p[hull[0]].y);

    // Free allocated memory
    free(hull);

    return length;
}