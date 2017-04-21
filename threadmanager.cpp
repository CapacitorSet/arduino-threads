#include <stdint.h>

#define MAX_THREADS_PER_MANAGER 255

#define THREAD_START if (thseq == thseqtemp) {
#define THREAD_BREAK } thseqtemp++; if(thseq == thseqtemp) {
#define THREAD_END } return thseqtemp;

class ThreadManager {
private:
	uint16_t seq[MAX_THREADS_PER_MANAGER];
	uint16_t thseq;
	uint16_t thseqtemp;

	// Array of threads (functions taking two uints and returning an uint)
	uint16_t (*threads[MAX_THREADS_PER_MANAGER])(uint16_t, uint16_t);
	// Amount of threads
	uint16_t threads_len;

public:
	ThreadManager(void) {
		threads_len = 0;
	}

	void addThread(uint16_t (*handler)(uint16_t, uint16_t)) {
		seq[threads_len] = 0;
		threads[threads_len] = handler;
		threads_len++;
	}

	void tick(void) {
		for (size_t i = 0; i < threads_len; i++) {
			thseq = seq[i];
			thseqtemp = 0;
			thseqtemp = threads[i](thseq, thseqtemp);
			seq[i]++;
			if (seq[i] > thseqtemp) seq[i] = 0;
		}
	}
};
