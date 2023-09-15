#include <stdio.h>
#include <math.h>

int main() {
	int n, money[101] = {0}, total, sum;
	double average;

	while (scanf_s("%d", &n) != 0) {
		total = 0;
		sum = 0;
		for (int i = 0; i < n; i++) {
			scanf_s("%d", &money[i]);
			total += money[i];
		}
		average = (double)total / n;
		average = (int)(floor(average / 10) * 10); // 1의 자리가 0이 아닐경우 10의 자리로 맞추기 위해 수를 내림

		for (int i = 0; i < n; i++) { // 결국 평균값 보다 큰 값에서 이동해야 하기 때문에 평균보다 큰 값에서만 평균 빼기
			if ((double)money[i] > average) {
				sum += money[i] - average;
			}
		}
		if ((total % 100) / n < 10) sum -= (total % 100); // 1의 자리를 0으로 맞췄기 때문에 1의 자리가 존재했다면 그 값만큼 빼기
		printf("$%.2lf\n", (double)sum);
	}
	return 0;
}