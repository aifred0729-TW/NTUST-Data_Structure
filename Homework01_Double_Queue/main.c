#include <stdio.h>
#include <stdbool.h>

const int ARRAY_MAX = 30;
const int DATA_MAX = 10;
const int NODE = 15;

typedef struct dq {
    int offset;
    int base;
    int value[30];
} DOUBLE_QUEUE;

void initializeDoubleQueue(DOUBLE_QUEUE* dq) {
    dq->offset = 0;
    dq->base = NODE;
    for (size_t i = 0; i < 30; i++) {
        dq->value[i] = NULL;
    }
    return;
}

// ========================================================

int getArrayStart(DOUBLE_QUEUE dq) {
    return dq.base;
}

int getArrayEnd(DOUBLE_QUEUE dq) {
    return dq.base + dq.offset;
}

int getDataSize(DOUBLE_QUEUE dq) {
    return dq.offset;
}

// ========================================================

bool checkBufferOverflow(DOUBLE_QUEUE dq) {
    if (getDataSize(dq) + 1 <= DATA_MAX) return false;
    printf("[!] Error, Data Overflow\n");
    return true;
}

void reAllocator(DOUBLE_QUEUE* dq) {
    printf("====  -----------  ====\n");
    printf("[+] Trigger reAllocator\n");
    printf("====  -----------  ====\n");
    for (size_t i = 0; i < getDataSize(*dq); i++) {
        dq->value[NODE + i] = dq->value[getArrayStart(*dq) + i];
    }
    dq->base = NODE;
    return;
}

void showQueueState(DOUBLE_QUEUE dq) {
    printf("========== Double Queue Data Structure ==========\n");
    printf("[+] Size : %d\n", getDataSize(dq));
    for (size_t i = 0; i < getDataSize(dq); i++) {
        printf("[+] Array Index %d : Data Index %d : Value %d\n", dq.base + i, i, dq.value[dq.base + i]);
    }
    printf("-------------------------------------------------\n");
    return;
}

// ========================================================

bool pushBack(DOUBLE_QUEUE* dq, int value) {
    if (checkBufferOverflow(*dq)) return false;
    if (getArrayEnd(*dq) + 1 >= ARRAY_MAX) reAllocator(dq);
    printf("[*] Push %d into queue back\n", value);
    dq->value[dq->base + dq->offset] = value;
    dq->offset++;
    return true;
}

bool pushFront(DOUBLE_QUEUE* dq, int value) {
    if (checkBufferOverflow(*dq)) return false;
    if (getArrayStart(*dq) -1 <= 0) reAllocator(dq);
    printf("[*] Push %d into queue front\n", value);
    dq->value[dq->base - 1] = value;
    dq->offset++;
    dq->base--;
    return true;
}

int popFront(DOUBLE_QUEUE* dq) {
    printf("[*] Get value from queue front\n");
    dq->base++;
    dq->offset--;
    return dq->value[dq->base - 1];
}

int popBack(DOUBLE_QUEUE* dq) {
    printf("[*] Get value from queue back\n");
    dq->offset--;
    return dq->value[dq->base + dq->offset];
}

// ========================================================

bool pushController(DOUBLE_QUEUE* dq, int value, bool isFront) {
    return isFront ? pushFront(dq, value) : pushBack(dq, value);
}

int popController(DOUBLE_QUEUE* dq, bool isFront) {
    if (isFront) return popFront(dq);
    return popBack(dq);
}

// ========================================================

int main() {
    DOUBLE_QUEUE dq;
    initializeDoubleQueue(&dq);
    
    // Test Normal Allocate

    for (size_t i = 1; i < 11; i++) {
        pushController(&dq, i, false);
    }

    // Test Over Allocate

    pushController(&dq, 123, false);

    showQueueState(dq);

    // Test pop value front and back

    int frontValue = popController(&dq, true);
    int backValue = popController(&dq, false);

    printf("[+] Value from Front : %d\n", frontValue);
    printf("[+] Value from Back : %d\n", backValue);

    showQueueState(dq);

    // Test push value into front and back

    pushController(&dq, 123, true);
    pushController(&dq, 456, false);

    showQueueState(dq);

    // Test reAllocator

    for (size_t i = 0; i < 6; i++) {
        popController(&dq, true);
    }

    for (size_t i = 0; i < 6; i++) {
        pushController(&dq, i, false);
    }

    showQueueState(dq);

    // Test other side

    for (size_t count = 0; count < 2; count++) {
        for (size_t i = 0; i < 10; i++) {
            popController(&dq, false);
        }

        for (size_t i = 0; i < 10; i++) {
            pushController(&dq, i, true);
        }
    }

    showQueueState(dq);

    return 0;
}
