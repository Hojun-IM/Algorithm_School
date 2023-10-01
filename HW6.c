#include <stdio.h>

int matrix[100][10];
int dp[100][10];

int min(int, int, int);
void create_dp(int, int);
int min_path(int, int);
int minrow_idx(int, int, int);
void print_path(int, int, int);

int main() {
    int m, n;
    while (scanf_s("%d %d", &m, &n) != EOF) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                scanf_s("%d", &matrix[i][j]);
            }
        }
        create_dp(m, n);

        int minPath = min_path(m, n);
        int minRowIdx = minrow_idx(minPath, m, n);
        int currentRow = minRowIdx; // shows where the path tracking starts
        
        print_path(currentRow, m, n);
        printf("\n%d\n", minPath);
    }

    return 0;
}

void create_dp(int m, int n) {
    for (int i = 0; i < m; i++) { // last column filled with elements last column from matrix
        dp[i][n - 1] = matrix[i][n - 1];
    }

    for (int j = n - 2; j >= 0; j--) { // starting from the last column -1 and top row, find out which element among upper right, right, down right have minimun value.
        for (int i = 0; i < m; i++) {
            int direct = dp[i][j + 1];
            int up = dp[(i - 1 + m) % m][j + 1];
            int down = dp[(i + 1) % m][j + 1];

            dp[i][j] = matrix[i][j] + min(direct, up, down); // add the minimun value to the one left and save it in the dp table
        }
    }
}

int min_path(int m, int n) { // starting from the top, find the min value from the first column which indicates the min weight across the table
    int minPath = dp[0][0];
    for (int i = 1; i < m; i++) {
        if (dp[i][0] < minPath) minPath = dp[i][0];
    }
    return minPath;
}

int minrow_idx(int minPath, int m, int n) { // find the index of minPath
    int minRowIndex = 0;
    for (int i = 0; i < m; i++) {
        if (dp[i][0] == minPath) {
            minRowIndex = i;
            return minRowIndex;
        }
    }
}

void print_path(int currentRow, int m, int n) { // from the currentRow, track the path with min value
    for (int j = 0; j < n; j++) {
        printf("%d ", matrix[currentRow][j]);

        int direct = dp[currentRow][j + 1]; // same 3 options from the current row
        int up = dp[(currentRow - 1 + m) % m][j + 1];
        int down = dp[(currentRow + 1) % m][j + 1];

        int next = min(direct, up, down); // find min value from 3 options which eventually indicates the next path it should take
        if (next == direct) currentRow = currentRow;
        else if (next == up) currentRow = (currentRow - 1 + m) % m;
        else currentRow = (currentRow + 1) % m;
    }
}

int min(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}