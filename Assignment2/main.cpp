#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int countData;

typedef struct Data {
    int startTime;
    int executeTime;
    int priority;
} Data;

typedef struct SumFIFO {
    int allExecuteTime;
    int allWaitTime;
} SumFIFO;

typedef struct Queue {
    Data element;
    Queue* link;
} Queue;

typedef struct HeapData: Data{
    int lastTime;
} HeapData;

typedef struct Heap {
    HeapData* heapArr;
    int numOfData;
} Heap;

typedef struct PriorityData {
    int waitTime;
    int executeTime;
    int numOfPriority;
} PriorityData;

Queue* originalDataQueue;
SumFIFO sumFIFO;
int dataLen;


void readFile() {
    printf("입력파일 이름? ");
    char* FILENAME = (char*)malloc(sizeof(char) * 100);
    scanf("%s", FILENAME);

    FILE* fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("Wrong Input : %s\n", FILENAME);
        return;
    }
    fscanf(fp, "%d", &dataLen);

    originalDataQueue = (Queue*)malloc(sizeof(Queue));
    originalDataQueue->link = NULL;
    Queue* queuePtr = originalDataQueue;
    for (int i = 0; i < dataLen; i++) {
        fscanf(fp, "%d %d %d", &queuePtr->element.startTime, &queuePtr->element.executeTime,
            &queuePtr->element.priority);

        queuePtr->link = (Queue*)malloc(sizeof(Queue));
        queuePtr = queuePtr->link;
        queuePtr->link = NULL;
    }

    fclose(fp);
    free(FILENAME);
}

void FIFOScheduling() {
    int time = originalDataQueue->element.startTime;
    Queue fifoPtr = *originalDataQueue;

    for (int start_time = time; fifoPtr.link != NULL; ++time) {
        if (fifoPtr.element.executeTime == 0) {
            sumFIFO.allWaitTime += start_time - fifoPtr.element.startTime;
            sumFIFO.allExecuteTime += time - fifoPtr.element.startTime;

            fifoPtr = *fifoPtr.link;
            start_time = time;
        }
        fifoPtr.element.executeTime--;
    }


    printf("FIFO Scheduling의 실행 결과:\n작업수 = %d, 종료시간 = %d, 평균 실행시간 = %.2lf, 평균 대기시간 = %.2lf\n", dataLen, time - 1,
        (double)sumFIFO.allExecuteTime / dataLen,
        (double)sumFIFO.allWaitTime / dataLen);
}

Heap* HeapInit() {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->numOfData = 0;
    heap->heapArr = (HeapData*)malloc(sizeof(HeapData) * (long long)pow(2, log2(dataLen) + 2));

    return heap;
}

/** 1 : a 0 : b */
int HeapCmp(Data heapDataA, Data heapDataB) {
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

void HeapInsert(Heap** root, Data heapData) {
    int insertIdx = (*root)->numOfData + 1;
    while (insertIdx != 1) {
        if (HeapCmp(heapData, (*root)->heapArr[insertIdx / 2])) {
            (*root)->heapArr[insertIdx] = (*root)->heapArr[insertIdx / 2];
            insertIdx /= 2;
        }
        else {
            break;
        }
    }

    (*root)->heapArr[insertIdx].executeTime = heapData.executeTime;
    (*root)->heapArr[insertIdx].priority = heapData.priority;
    (*root)->heapArr[insertIdx].startTime = heapData.startTime;
    (*root)->heapArr[insertIdx].lastTime = heapData.startTime;
    (*root)->numOfData += 1;
}

int GetPriorityChildIdx(Heap* root, int parentIdx) {
    if (parentIdx * 2 > root->numOfData) {
        return 0;
    }
    else if (parentIdx * 2 == root->numOfData) {
        return parentIdx * 2;
    }
    else {
        if (HeapCmp(root->heapArr[parentIdx * 2], root->heapArr[parentIdx * 2 + 1])) {
            return parentIdx * 2;
        }
        else {
            return parentIdx * 2 + 1;
        }
    }
}

void HeapDelete(Heap** root) {
    HeapData deleteData = (*root)->heapArr[1];
    HeapData lastData = (*root)->heapArr[(*root)->numOfData];

    int parentIdx = 1;
    int childIdx;
    while (childIdx = GetPriorityChildIdx(*root, parentIdx)) {
        if (HeapCmp((*root)->heapArr[childIdx], lastData)) {
            (*root)->heapArr[parentIdx] = (*root)->heapArr[childIdx];
            parentIdx = childIdx;
        }
        else {
            break;
        }
    }

    (*root)->heapArr[parentIdx] = lastData;
    (*root)->numOfData -= 1;
}


void PriorityQueue() {
    //    PriorityData *priorityData = (PriorityData *) malloc(sizeof(PriorityData) * (dataLen + 1));
    PriorityData priorityData[11] = { {0, 0, 0}, };
    Heap* heap = HeapInit();
    Queue originalPtr = *originalDataQueue;
   


    int time = originalDataQueue->element.startTime;
    HeapInsert(&heap, originalPtr.element);
    originalPtr = *originalPtr.link;

    int prevRootNodeStartTime = heap->heapArr[1].startTime;
    for (; heap->numOfData != 0; ++time, --(heap->heapArr[1].executeTime)) {
        if (heap->heapArr[1].executeTime == 0) {
            priorityData[heap->heapArr[1].priority].numOfPriority += 1;
            priorityData[0].executeTime += time - heap->heapArr[1].startTime;
            HeapDelete(&heap);
            if (prevRootNodeStartTime != heap->heapArr[1].startTime) {
                priorityData[heap->heapArr[1].priority].waitTime += time - heap->heapArr[1].lastTime;
                prevRootNodeStartTime = heap->heapArr[1].startTime;
            }
        }
        if (originalPtr.link != NULL) {
            if (originalPtr.element.startTime == time) {
                if (HeapCmp(originalPtr.element, (Data)heap->heapArr[1])) {
                    heap->heapArr[1].lastTime = time;
                }
                HeapInsert(&heap, originalPtr.element);
                originalPtr = *originalPtr.link;
            }
            if (prevRootNodeStartTime != heap->heapArr[1].startTime) {
                priorityData[heap->heapArr[1].priority].waitTime += time - heap->heapArr[1].lastTime;
                prevRootNodeStartTime = heap->heapArr[1].startTime;
            }
        }
        
        
    }

    printf("작업수 = %d, 종료시간 = %d, 평균 실행시간 = %.2lf\n", dataLen, time - 1, (double)priorityData[0].executeTime / dataLen);
    for (int i = 10; i > 0; i--) {
        if (!priorityData[i].numOfPriority) {
            continue;
        }
        printf("%5d %5d %.2lf\n", i, priorityData[i].numOfPriority,
            (double)priorityData[i].waitTime / priorityData[i].numOfPriority);
    }
}

int main() {
    readFile();
    FIFOScheduling();
    PriorityQueue();
    return 0;
}
