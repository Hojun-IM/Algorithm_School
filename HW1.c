#include <stdio.h>

int main() {
    int s, Day = 1;

    while (scanf_s("%d", &s) != EOF) {
        int h1, m1, h2, m2, prev_h, prev_m, max_nap = 0, index = 0; //prev�� ���� �ð��� �������� ���� �ð��� �����Ͽ� ���� ������ ���� �ð��� �Է� �Ǿ����� �ð����� ���ϱ� ���� ���
        int nap_start[100] = {0}, nap_duration[101] = {0}; //nap_start�� �� �������� �ð����� ���ϸ鼭 ���� �������� ���� �ð�, �� ������ ������ �ð��� ����. nap_duration�� �� �ð����� ������ ȯ���Ͽ� ����
        char schedule[256];

        if (s == 0) {
            Day++;
            continue;
        }
        if (s == 1) {
            scanf_s("%d:%d %d:%d %[^\n]", &h1, &m1, &h2, &m2, schedule, sizeof(schedule));
            printf("Day #%d: the longest nap starts at %02d:%02d and will last for 0 minutes.\n", Day, h2, m2);
            Day++;
            continue;
        }
        for (int i = 0; i < s; i++) {
            scanf_s("%d:%d %d:%d %[^\n]", &h1, &m1, &h2, &m2, schedule, sizeof(schedule));
            if (i != 0) {
                nap_duration[i] = ((h1 * 60) + m1) - ((prev_h * 60) + prev_m); // ������ ȯ���Ͽ� ���� �ð��� ����
                (nap_duration[i] > max_nap) ? (max_nap = nap_duration[i], index = i) : 0; // ���� ����� �ð����� ���� ũ�ٸ� max_nap�� ����
            }
            prev_h = h2;
            prev_m = m2;
            nap_start[i] = (h2 * 60) + m2;
        }
        if(max_nap / 60 == 0) printf("Day #%d: the longest nap starts at %02d:%02d and will last for %d minutes.\n", Day, nap_start[index - 1] / 60, nap_start[index - 1] % 60, max_nap % 60);
        else printf("Day #%d: the longest nap starts at %02d:%02d and will last for %d hours and %d minutes.\n", Day, nap_start[index - 1] / 60, nap_start[index - 1] % 60, max_nap / 60, max_nap % 60);
        Day++;
    }
    return 0;
}