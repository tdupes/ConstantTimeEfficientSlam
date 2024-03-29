#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "Slam.h"

void handler(int sig) {

  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);

}

int main(int argc, char* argv[]) {

	signal(SIGSEGV, handler);

	Slam slam;

	if(argc > 1) {

		int numFrames = atoi(argv[1]);
		slam.maxKeyFrames = (uint)numFrames;

	}

	slam.run();

}