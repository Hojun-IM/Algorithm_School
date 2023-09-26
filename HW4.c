#include <stdio.h>
#include <stdlib.h>

typedef struct elephant {
	int id;
	int size;
	int iq;
} Elephant;

int compare(void const* a, void const* b);
int ans[1000][1000]; // subsequence 저장

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

			int idx = n - 1; // 현재까지 찾은 최적의 subsequence의 마지막 인덱스
			int eSize[1000] = { 0 }; // ans 배열의 각 행의 크기 (subsequence의 길이) 저장

			for (int i = n - 2; i >= 0; i--) { // 역순으로 이동하며 subsequence 찾기
				ans[i][eSize[i]] = i; // 현재 인덱스 i를 subsequence에 추가
				eSize[i]++; // 하나를 추가했으므로 크기 1 증가

				for (int j = i + 1; j < n; j++) { // i 다음부터 시작하는 subsequence 찾기
					if (eSize[i] < 1 + eSize[j] && (eArr[i].size < eArr[j].size) && (eArr[i].iq > eArr[j].iq)) {
						// 현재 보고있는 subsequence의 길이가 그 전보다 짧아야 함
						// 더 짧다면 현재 요소 i가 다음 요소 j보다 몸무게는 낮고 지능은 높아야 함
						for (int k = 0; k < eSize[j]; k++) { // 위 조건을 만족한다면 j에 있는 subsequence를 i의 뒤로 복사, 즉 저장되어 있던 subsequence를 가져옴
							ans[i][eSize[i] + k] = ans[j][k];
						}
						eSize[i] += eSize[j]; // 가져온 길이만큼 길이에 추가
					}
				}

				if (eSize[idx] < eSize[i]) // 현재 찾은 최적의 subsequence와 비교하여 길이가 가장 큰 인덱스 idx에 저장
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

int compare(void const* a, void const* b) { //몸무게 작은 순서로, 몸무게가 같다면 아이큐가 낮은 순서로
	Elephant* ea = (Elephant*)a;
	Elephant* eb = (Elephant*)b;
	if (ea->size < eb->size || (ea->size == eb->size && ea->iq > eb->iq)) return -1;
	return 1;
}