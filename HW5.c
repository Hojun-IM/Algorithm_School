#include <stdio.h>
#include <string.h>

long long dp[1001][101]; //[m+1][n+1] 크기의 배열 (빈 문자도 카운트)
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
	int m = strlen(s); // 주어진 문자열 길이
	int n = strlen(t); // 목표 문자열 길이

	for (int i = 0; i <= m; i++) {
		dp[i][0] = 1; // 목표 문자열이 빈 문자열이면 주어진 문자로 각 목표 문자열의 문자 만드는 방법 1가지
	}
	// s와 t가 같다면 주어진 s로 t를 만들거나 안 만들거나 2가지 방법 존재
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (s[i - 1] == t[j - 1]) { // s와 t가 같을 경우 s로 t를 만드는경우 + 안 만드는 경우
				dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]; 
			}
			else {
				dp[i][j] = dp[i - 1][j];
			}
		}
	}
	return dp[m][n];
}