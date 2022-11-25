// 학번 : 22112044    이름 : 변승우
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <cstring>

typedef struct Data {
    int startTime;
    int executeTime;
    int priority;
} Data;

typedef struct SumFIFO {
    int allExecuteTime;
    int allWaitTime;
} SumFIFO;

typedef struct HeapData : Data {
    int lastTime;
} HeapData;

typedef struct Heap {
    HeapData *heapArr;
    int numOfData;
} Heap;

typedef struct PriorityData {
    int waitTime;
    int executeTime;
    int numOfPriority;
} PriorityData;

int dataLen;
Data *originalData;

void readFile() {
    printf("입력파일 이름? ");
    char *FILENAME = (char *) malloc(sizeof(char) * 100);
    scanf("%s", FILENAME);

    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("Wrong Input : %s\n", FILENAME);
        return;
    }
    fscanf(fp, "%d", &dataLen);

    originalData = (Data *) malloc(sizeof(Data) * dataLen);

    for (int i = 0; i < dataLen; i++) {
        fscanf(fp, "%d %d %d", &originalData[i].startTime, &originalData[i].executeTime,
               &originalData[i].priority);
    }

    fclose(fp);
    free(FILENAME);
}

void FIFOScheduling() {
    int time = originalData[0].startTime;
    Data *fifoPtr = new Data[dataLen];
    memcpy(fifoPtr, originalData, sizeof(Data) * dataLen);
    SumFIFO sumFIFO = {0};
    int i = 0;
    for (int start_time = time; i < dataLen; ++time) {
        if (fifoPtr[i].executeTime == 0) {
            sumFIFO.allWaitTime += start_time - fifoPtr[i].startTime;
            sumFIFO.allExecuteTime += time - fifoPtr[i].startTime;
            start_time = time;
            ++i;
        }
        --fifoPtr[i].executeTime;
    }


    printf("FIFO Scheduling의 실행 결과:\n\t작업수 = %d, 종료시간 = %d, 평균 실행시간 = %.2lf, 평균 대기시간 = %.2lf\n", dataLen, time - 1,
           (double) sumFIFO.allExecuteTime / dataLen,
           (double) sumFIFO.allWaitTime / dataLen);

    delete[]fifoPtr;
}

Heap *HeapInit() {
    Heap *heap = new Heap;
    heap->numOfData = 0;
    heap->heapArr = new HeapData[dataLen];

    return heap;
}

/** 1 : a 0 : b */
int HeapCmp(const Data &heapDataA, const Data &heapDataB) {
    if (heapDataA.priority > heapDataB.priority) {
        return 1;
    }

    if (heapDataA.priority < heapDataB.priority) {
        return 0;
    }

    if (heapDataA.executeTime < heapDataB.executeTime) {
        return 1;
    }

    if (heapDataA.executeTime > heapDataB.executeTime) {
        return 0;
    }

    if (heapDataA.startTime < heapDataB.startTime) {
        return 1;
    }

    if (heapDataA.startTime > heapDataB.startTime) {
        return 0;
    }

    return 0;
}

void HeapInsert(Heap *(&root), Data heapData) {
    int insertIdx = root->numOfData + 1;
    while (insertIdx != 1) {
        if (HeapCmp(heapData, root->heapArr[insertIdx / 2])) {
            root->heapArr[insertIdx] = root->heapArr[insertIdx / 2];
            insertIdx /= 2;
        } else {
            break;
        }
    }

    root->heapArr[insertIdx].executeTime = heapData.executeTime;
    root->heapArr[insertIdx].priority = heapData.priority;
    root->heapArr[insertIdx].startTime = heapData.startTime;
    root->heapArr[insertIdx].lastTime = heapData.startTime;
    root->numOfData += 1;
}

int GetPriorityChildIdx(Heap *root, int parentIdx) {
    if (parentIdx * 2 > root->numOfData) {
        return 0;
    } else if (parentIdx * 2 == root->numOfData) {
        return parentIdx * 2;
    } else {
        if (HeapCmp(root->heapArr[parentIdx * 2], root->heapArr[parentIdx * 2 + 1])) {
            return parentIdx * 2;
        } else {
            return parentIdx * 2 + 1;
        }
    }
}

void HeapDelete(Heap *(&root)) {
    HeapData lastData = root->heapArr[root->numOfData];

    int parentIdx = 1;
    int childIdx;
    while ((childIdx = GetPriorityChildIdx(root, parentIdx))) {
        if (HeapCmp(root->heapArr[childIdx], lastData)) {
            root->heapArr[parentIdx] = root->heapArr[childIdx];
            parentIdx = childIdx;
        } else {
            break;
        }
    }

    root->heapArr[parentIdx] = lastData;
    root->numOfData -= 1;
}

void ChangeRootNodeHandler(Heap *(&heap), PriorityData *(&priorityData), const int &time, int &prevRootNodeStartTime) {
    if (prevRootNodeStartTime != heap->heapArr[1].startTime) {
        priorityData[heap->heapArr[1].priority].waitTime += time - heap->heapArr[1].lastTime;
        prevRootNodeStartTime = heap->heapArr[1].startTime;
    }
}

void PriorityScheduling() {
    PriorityData *priorityData = new PriorityData[11];
    memset(priorityData, 0, sizeof(PriorityData) * (11));

    Heap *heap = HeapInit();

    Data *dataPtr = originalData;

    int time = originalData[0].startTime;
    HeapInsert(heap, originalData[0]);

    int prevRootNodeStartTime = heap->heapArr[1].startTime;

    for (int i = 1; heap->numOfData != 0; ++time, --heap->heapArr[1].executeTime) {
        if (heap->heapArr[1].executeTime == 0) {
            priorityData[heap->heapArr[1].priority].numOfPriority += 1;
            priorityData[0].executeTime += time - heap->heapArr[1].startTime;
            HeapDelete(heap);
            ChangeRootNodeHandler(heap, priorityData, time, prevRootNodeStartTime);
        }
        if (i < dataLen) {
            if (dataPtr[i].startTime == time) {
                if (HeapCmp(dataPtr[i], (Data) heap->heapArr[1])) {
                    heap->heapArr[1].lastTime = time;
                }
                HeapInsert(heap, dataPtr[i]);
                i++;
            }
            ChangeRootNodeHandler(heap, priorityData, time, prevRootNodeStartTime);
        }

    }

    printf("\nPriority Scheduling의 실행 결과:\n");
    printf("\t작업수 = %d, 종료시간 = %d, 평균 실행시간 = %.2lf\n", dataLen, time - 1,
           (double) priorityData[0].executeTime / dataLen);
    for (int i = 10; i > 0; i--) {
        if (priorityData[i].numOfPriority == 0) {
            continue;
        }
        printf("\t우선순위 %-2d: %5d %10.2lf\n", i, priorityData[i].numOfPriority,
               (double) priorityData[i].waitTime / priorityData[i].numOfPriority);
    }

    delete heap;
    delete[]priorityData;
    delete dataPtr;
}

int main() {
    readFile();
    FIFOScheduling();
    PriorityScheduling();

    return 0;
}