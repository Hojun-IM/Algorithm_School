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
		average = (int)(floor(average / 10) * 10); // 1�� �ڸ��� 0�� �ƴҰ�� 10�� �ڸ��� ���߱� ���� ���� ����

		for (int i = 0; i < n; i++) { // �ᱹ ��հ� ���� ū ������ �̵��ؾ� �ϱ� ������ ��պ��� ū �������� ��� ����
			if ((double)money[i] > average) {
				sum += money[i] - average;
			}
		}
		if ((total % 100) / n < 10) sum -= (total % 100); // 1�� �ڸ��� 0���� ����� ������ 1�� �ڸ��� �����ߴٸ� �� ����ŭ ����
		printf("$%.2lf\n", (double)sum);
	}
	return 0;
}