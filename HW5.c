#include <stdio.h>
#include <string.h>

long long dp[1001][101]; //[m+1][n+1] ũ���� �迭 (�� ���ڵ� ī��Ʈ)
int distinct(char* s, char* t);

int main() {
	int n;
	scanf_s("%d", &n);

	char s[1000], t[100];
	while (n--) {
		scanf_s("%s", s, sizeof(s));
		scanf_s("%s", t, sizeof(t));
		int seq = distinct(s, t);
		printf("%d\n", seq);
	}

	return 0;
}

int distinct(char* s, char* t) {
	int m = strlen(s); // �־��� ���ڿ� ����
	int n = strlen(t); // ��ǥ ���ڿ� ����

	for (int i = 0; i <= m; i++) {
		dp[i][0] = 1; // ��ǥ ���ڿ��� �� ���ڿ��̸� �־��� ���ڷ� �� ��ǥ ���ڿ��� ���� ����� ��� 1����
	}
	// s�� t�� ���ٸ� �־��� s�� t�� ����ų� �� ����ų� 2���� ��� ����
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (s[i - 1] == t[j - 1]) { // s�� t�� ���� ��� s�� t�� ����°�� + �� ����� ���
				dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]; 
			}
			else {
				dp[i][j] = dp[i - 1][j];
			}
		}
	}
	return dp[m][n];
}