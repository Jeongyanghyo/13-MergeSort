#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100

int sorted[SIZE];
int comparisonCount = 0, moveCount = 0;
int totalComparisons = 0, totalMoves = 0;
int isFirst = 0, rounds = 0;

// 정렬 요소들을 출력
void print_list(int list[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

// 정렬 요소들을 20개만 출력
void print_partial_list(int list[], int n) {
    for (int i = 0; i < n && i < 20; i++) {
        printf("%02d ", list[i]);
    }
    printf(". . . \n");
}

// 배열에 랜덤 숫자들을 삽입
void generateRandomNumbers(int data[]) {
    srand((unsigned int)time(0));
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % 1000;
    }
}

void merge(int list[], int left, int mid, int right) {
    int i, j, k, l;
    i = left; // 왼쪽 부분 배열의 시작
    j = mid + 1; //오른쪽 부분 배열의 시작
    k = left; //정렬된 배열의 시작

    //두 부분 배열을 비교하여 정렬된 배열에 삽입
    while (i <= mid && j <= right) {
        comparisonCount++; //비교횟수 증가
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++]; //왼쪽 배열의 요소가 같거나 작으면 삽입
        }
        else {
            sorted[k++] = list[j++]; //오른쪽 배열의 요소가 작으면 삽입
        }
        moveCount++; //이동 횟수 증가
    }
    //왼쪽 부분 배열의 나머지 요소들 삽입
    if (i > mid) {
        for (l = j; l <= right; l++) {
            sorted[k++] = list[l];
            moveCount++;
        }
    }
    //오른쪽 부분 배열의 나머지 요소들 삽입
    else {
        for (l = i; l <= mid; l++) {
            sorted[k++] = list[l];
            moveCount++;
        }
    }
    //정렬된 배열을 원래 배열에 복사
    for (l = left; l <= right; l++) {
        list[l] = sorted[l];
        moveCount++;
    }

    rounds++; //라운드 횟수 증가

    //특정 라운드마다 배열의 일부를 출력 (첫 번째부터 10단위로 출력)
    if (rounds % 10 == 0 && isFirst == 0) {
        for (int i = 0; i < 10; i++)
            printf("%3d ", list[i]);
        printf("| ");
        for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++)
            printf("%3d ", list[i]);
        printf("\n\n");
    }
}

//재귀적인 방법으로 mergesort구현
void doMergeSort(int list[], int left, int right) {
    int mid;
    if (left < right) {
        mid = (left + right) / 2; //리스트 절반으로 분할
        doMergeSort(list, left, mid); //리스트 정렬
        doMergeSort(list, mid + 1, right); //리스트 정렬
        merge(list, left, mid, right); //합병과정
    }
}

//보너스 코드
//반복적인 방법으로 mergesort구현
void iterativeMergeSort(int list[], int n) {
    int curr_size;  // 현재 부분 배열 크기
    int left_start; // 현재 부분 배열의 시작 인덱스

    //부분 배열을 1에서부터 2배씩 증가시키며 정렬
    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            //부분 배열 중간지점 계산
            int mid = left_start + curr_size - 1;
            //합병할 부분배열의 오른쪽 끝 부분을 게산
            int right_end = (left_start + 2 * curr_size - 1 < n - 1) ? left_start + 2 * curr_size - 1 : n - 1;

            //합병 과정
            merge(list, left_start, mid, right_end);
        }
    }
}

int main() {
    int array[SIZE];

    for (int i = 0; i < 20; i++) {
        generateRandomNumbers(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Merge Sort Run\n");
            iterativeMergeSort(array, SIZE);

            printf("Result\n");
            print_list(array, SIZE);
            isFirst++;
        }
        else {
            iterativeMergeSort(array, SIZE);
        }

        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
