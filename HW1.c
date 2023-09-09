#include <stdio.h>

int main() {
    int s, Day = 1;

    while (scanf_s("%d", &s) != EOF) {
        int h1, m1, h2, m2, prev_h, prev_m, max_nap = 0, index = 0; //prev은 이전 시간의 스케줄이 끝난 시간을 저장하여 다음 스케줄 시작 시간이 입력 되었을때 시간차를 구하기 위해 사용
        int nap_start[100] = {0}, nap_duration[101] = {0}; //nap_start는 각 스케줄의 시간차를 구하면서 이전 스케줄이 끝난 시간, 즉 낮잠이 시작할 시간을 저장. nap_duration은 각 시간차를 분으로 환산하여 저장
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
                nap_duration[i] = ((h1 * 60) + m1) - ((prev_h * 60) + prev_m); // 분으로 환산하여 낮잠 시간에 저장
                (nap_duration[i] > max_nap) ? (max_nap = nap_duration[i], index = i) : 0; // 현재 계산한 시간차가 가장 크다면 max_nap에 저장
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