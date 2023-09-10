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
            int flip_num = pancake_sort(pancakes, flip_cnt, len); //�����ϸ� ���ÿ� flip�� Ƚ�� ����
            
            printf("("); // ���ĵ� ���� ���
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

int find_max(int* pk, int len) { // ���� ū ������ ��ġ�� ã��
    int max_index = 0;
    for (int i = 0; i < len; i++) {
        if (pk[i] > pk[max_index]) max_index = i;
    }
    return max_index;
}

void flip(int* pk, int num) { // 0��° �ε������� num��°���� flip
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
    for (int i = len; i > 1; i--) { // �� �ؿ������� ���� ū ���� ã�Ƽ� flip �Ͽ� ���� ������ �ٽ� flip�Ͽ� �� �Ʒ��� ����. �迭 ���̸� 1 ���ҽ��� �� �Ʒ� ���ĵ� ������ ������ �� �ݺ�
        max_index = find_max(pk, i);
        if (max_index == i - 1) continue; // max_index�� �̹� �� �Ʒ� �ִٸ� continue
        if (max_index != 0) { 
            flip(pk, max_index);
            flip_cnt[cnt++] = len - max_index; // filp_cnt�� �� ��° �ε������� flip���� ����
        }
        flip(pk, i - 1);
        flip_cnt[cnt++] = len + 1 - i;
    }
    return cnt;
}