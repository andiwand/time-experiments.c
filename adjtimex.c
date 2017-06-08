#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/timex.h>

int main(int argc, char** argv) {
  char* prog = argv[0]; argv = argv + 1; argc--;
  if (argc == 0) {
    fprintf(stderr, "usage: %s\n", prog);
    return 1;
  }

  if (argc & 1) {
    printf("invalid arguments\n");
    return -1;
  }

  struct timex buf;
  memset(&buf, 0, sizeof(buf));

  for (int i = 0; i < argc; i += 2) {
    long value = strtol(argv[i + 1], NULL, 10);
    if (strcmp(argv[i], "offset") == 0) {
      buf.offset = value;
      buf.modes |= ADJ_OFFSET;
    } else if (strcmp(argv[i], "frequency") == 0) {
      buf.freq = value;
      buf.modes |= ADJ_FREQUENCY;
    } else {
      printf("invalid operation: %s\n", argv[i]);
      return -1;
    }
  }

  int result = adjtimex(&buf);
  if (result == -1) {
    printf("error\n");
    return -1;
  }

  printf("success %d\n", result);
  return 0;
}
