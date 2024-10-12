#include <stdio.h>
#include <stdbool.h>

const int ARRAY_MAX = 30;
const int DATA_MAX = 10;
const int NODE = 10;

typedef struct dq {
	int offset;
	int base;
	int value[30];
} DOUBLE_QUEUE;

void initializeDoubleQueue(DOUBLE_QUEUE* dq) {
	dq->offset = 0;
	dq->base = 0;
	for (size_t i = 0; i < 20; i++) dq->value[i] = NULL;
	return;
}

bool checkOverflow(int base, int offset) {
	if (offset - base + 1 > DATA_MAX) return false;
	return true;
}

bool pushFront(DOUBLE_QUEUE* dq, int value) {
	if (checkOverflow(dq->base, dq->offset)) return false;
	if (dq->offset + 1 == ARRAY_MAX) return false;
	dq->value[dq->base + dq->offset + 1] = value;
	return true;
}

bool pushBack(DOUBLE_QUEUE* dq, int value) {
	if (dq->offset -)
}

int popBack(DOUBLE_QUEUE* dq) {
	dq->offset--;
	return dq->value[dq->base + dq->offset+1];
}

int popFront(DOUBLE_QUEUE* dq) {
	dq->base++;
	return dq->value[dq->base - 1];
}

int main() {
	DOUBLE_QUEUE dq;
	initializeDoubleQueue(&dq);



	return 0;
}