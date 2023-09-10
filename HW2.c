#include <stdio.h>

int find_max(int*, int);
void flip(int*, int);
int pancake_sort(int*, int*, int);

int main() {
    int pancakes[30] = {0}, flip_cnt[60] = {0};
    int index = 0, len = 0;

    while (1) {
        int num;
        if (scanf_s("%d", &num) == EOF) break;
        pancakes[index++] = num;
        len++;

        char nextChar = getchar();
        if (nextChar == '\n') {
            for (int i = 0; i < len; i++) {
                if (len - 1 == i) {
                    printf("%d", pancakes[i]);
                    break;
                }
                printf("%d ", pancakes[i]);
            }
            int flip_num = pancake_sort(pancakes, flip_cnt, len); //정렬하며 동시에 flip한 횟수 저장
            
            printf("("); // 정렬된 순서 출력
            for (int i = 0; i < len; i++) {
                if (i == len - 1) {
                    printf("%d", pancakes[i]);
                    break;
                }
                printf("%d ", pancakes[i]);
            }
            printf(")");

            for (int i = 0; i < flip_num; i++) printf("%d ", flip_cnt[i]);
            printf("0\n");

            index = 0;
            len = 0;
        }
    }
    return 0;
}

int find_max(int* pk, int len) { // 가장 큰 지름의 위치를 찾기
    int max_index = 0;
    for (int i = 0; i < len; i++) {
        if (pk[i] > pk[max_index]) max_index = i;
    }
    return max_index;
}

void flip(int* pk, int num) { // 0번째 인덱스부터 num번째까지 flip
    int temp, start = 0;
    while (start < num) {
        temp = pk[num];
        pk[num] = pk[start];
        pk[start] = temp;
        start++;
        num--;
    }
}

int pancake_sort(int* pk, int* flip_cnt, int len) {
    int max_index, cnt = 0;
    for (int i = len; i > 1; i--) { // 맨 밑에서부터 가장 큰 수를 찾아서 flip 하여 위로 보낸뒤 다시 flip하여 맨 아래로 보냄. 배열 길이를 1 감소시켜 맨 아래 정렬된 지름은 제외한 뒤 반복
        max_index = find_max(pk, i);
        if (max_index == i - 1) continue; // max_index가 이미 맨 아래 있다면 continue
        if (max_index != 0) { 
            flip(pk, max_index);
            flip_cnt[cnt++] = len - max_index; // filp_cnt에 몇 번째 인덱스에서 flip한지 저장
        }
        flip(pk, i - 1);
        flip_cnt[cnt++] = len + 1 - i;
    }
    return cnt;
}