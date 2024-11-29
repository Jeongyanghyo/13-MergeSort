#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100

int sorted[SIZE];
int comparisonCount = 0, moveCount = 0;
int totalComparisons = 0, totalMoves = 0;
int isFirst = 0, rounds = 0;

// ���� ��ҵ��� ���
void print_list(int list[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

// ���� ��ҵ��� 20���� ���
void print_partial_list(int list[], int n) {
    for (int i = 0; i < n && i < 20; i++) {
        printf("%02d ", list[i]);
    }
    printf(". . . \n");
}

// �迭�� ���� ���ڵ��� ����
void generateRandomNumbers(int data[]) {
    srand((unsigned int)time(0));
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % 1000;
    }
}

void merge(int list[], int left, int mid, int right) {
    int i, j, k, l;
    i = left; // ���� �κ� �迭�� ����
    j = mid + 1; //������ �κ� �迭�� ����
    k = left; //���ĵ� �迭�� ����

    //�� �κ� �迭�� ���Ͽ� ���ĵ� �迭�� ����
    while (i <= mid && j <= right) {
        comparisonCount++; //��Ƚ�� ����
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++]; //���� �迭�� ��Ұ� ���ų� ������ ����
        }
        else {
            sorted[k++] = list[j++]; //������ �迭�� ��Ұ� ������ ����
        }
        moveCount++; //�̵� Ƚ�� ����
    }
    //���� �κ� �迭�� ������ ��ҵ� ����
    if (i > mid) {
        for (l = j; l <= right; l++) {
            sorted[k++] = list[l];
            moveCount++;
        }
    }
    //������ �κ� �迭�� ������ ��ҵ� ����
    else {
        for (l = i; l <= mid; l++) {
            sorted[k++] = list[l];
            moveCount++;
        }
    }
    //���ĵ� �迭�� ���� �迭�� ����
    for (l = left; l <= right; l++) {
        list[l] = sorted[l];
        moveCount++;
    }

    rounds++; //���� Ƚ�� ����

    //Ư�� ���帶�� �迭�� �Ϻθ� ��� (ù ��°���� 10������ ���)
    if (rounds % 10 == 0 && isFirst == 0) {
        for (int i = 0; i < 10; i++)
            printf("%3d ", list[i]);
        printf("| ");
        for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++)
            printf("%3d ", list[i]);
        printf("\n\n");
    }
}

//������� ������� mergesort����
void doMergeSort(int list[], int left, int right) {
    int mid;
    if (left < right) {
        mid = (left + right) / 2; //����Ʈ �������� ����
        doMergeSort(list, left, mid); //����Ʈ ����
        doMergeSort(list, mid + 1, right); //����Ʈ ����
        merge(list, left, mid, right); //�պ�����
    }
}

//���ʽ� �ڵ�
//�ݺ����� ������� mergesort����
void iterativeMergeSort(int list[], int n) {
    int curr_size;  // ���� �κ� �迭 ũ��
    int left_start; // ���� �κ� �迭�� ���� �ε���

    //�κ� �迭�� 1�������� 2�辿 ������Ű�� ����
    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            //�κ� �迭 �߰����� ���
            int mid = left_start + curr_size - 1;
            //�պ��� �κй迭�� ������ �� �κ��� �Ի�
            int right_end = (left_start + 2 * curr_size - 1 < n - 1) ? left_start + 2 * curr_size - 1 : n - 1;

            //�պ� ����
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
