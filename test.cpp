#include <stdio.h>

#include "threadmanager.cpp"

unsigned int ctr = 0;

uint16_t oneHandler(uint16_t thseq, uint16_t thseqtemp) {
	THREAD_START;
	printf("Counter is %d\n", ctr);
	THREAD_BREAK;
	ctr++;
	THREAD_BREAK;
	ctr *= 2;
	THREAD_END;
}

uint16_t twoHandler(uint16_t thseq, uint16_t thseqtemp) {
	THREAD_START;
	printf("B - 0\n");
	THREAD_BREAK;
	printf("B - 1\n");
	THREAD_END;
}

int main() {
	ThreadManager threadManager;
	threadManager.addThread(oneHandler);
	threadManager.addThread(twoHandler);

	for(;;) threadManager.tick();
	return 0;
}
