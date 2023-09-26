#include <stdio.h>
#include <stdlib.h>

typedef struct elephant {
	int id;
	int size;
	int iq;
} Elephant;

int compare(void const* a, void const* b);
int ans[1000][1000]; // subsequence ����

int main() {
	Elephant e;
	Elephant eArr[1000];
	int id = 1;
	int n = 0;

	while (scanf_s("%d", &e.size) != EOF) {
		if (e.size != 0) {
			scanf_s("%d", &e.iq);
		}
		if (e.size == 0 || e.iq == 0) {
			qsort(eArr, n, sizeof(Elephant), compare);

			int idx = n - 1; // ������� ã�� ������ subsequence�� ������ �ε���
			int eSize[1000] = { 0 }; // ans �迭�� �� ���� ũ�� (subsequence�� ����) ����

			for (int i = n - 2; i >= 0; i--) { // �������� �̵��ϸ� subsequence ã��
				ans[i][eSize[i]] = i; // ���� �ε��� i�� subsequence�� �߰�
				eSize[i]++; // �ϳ��� �߰������Ƿ� ũ�� 1 ����

				for (int j = i + 1; j < n; j++) { // i �������� �����ϴ� subsequence ã��
					if (eSize[i] < 1 + eSize[j] && (eArr[i].size < eArr[j].size) && (eArr[i].iq > eArr[j].iq)) {
						// ���� �����ִ� subsequence�� ���̰� �� ������ ª�ƾ� ��
						// �� ª�ٸ� ���� ��� i�� ���� ��� j���� �����Դ� ���� ������ ���ƾ� ��
						for (int k = 0; k < eSize[j]; k++) { // �� ������ �����Ѵٸ� j�� �ִ� subsequence�� i�� �ڷ� ����, �� ����Ǿ� �ִ� subsequence�� ������
							ans[i][eSize[i] + k] = ans[j][k];
						}
						eSize[i] += eSize[j]; // ������ ���̸�ŭ ���̿� �߰�
					}
				}

				if (eSize[idx] < eSize[i]) // ���� ã�� ������ subsequence�� ���Ͽ� ���̰� ���� ū �ε��� idx�� ����
					idx = i;
			}

			printf("%d\n", eSize[idx]);
			for (int i = 0; i < eSize[idx]; i++) {
				printf("%d\n", eArr[ans[idx][i]].id);
			}
			id = 1;
			n = 0;
			continue;
		}
		e.id = id;
		eArr[n++] = e;
		id++;
	}
	return 0;
}

int compare(void const* a, void const* b) { //������ ���� ������, �����԰� ���ٸ� ����ť�� ���� ������
	Elephant* ea = (Elephant*)a;
	Elephant* eb = (Elephant*)b;
	if (ea->size < eb->size || (ea->size == eb->size && ea->iq > eb->iq)) return -1;
	return 1;
}