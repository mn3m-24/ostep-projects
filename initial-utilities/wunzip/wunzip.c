#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void wunzip(FILE *stream) {
  // reading 5bytes by 5bytes
  char buf[5];
  while (fread(buf, sizeof(buf), 1, stream)) {
    // interpreting first 4 bytes as int
    uint32_t cnt;
    memcpy(&cnt, buf, sizeof cnt);
    // writing the char cnt times to the stdout stream
    for (int i = 0; i < cnt; ++i) {
      fputc(buf[4], stdout);
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fputs("wunzip: file1 [file2 ...]\n", stdout);
    return EXIT_FAILURE;
  }
  for (int i = 1; i < argc; ++i) {
    FILE *fp = fopen(argv[i], "r");
    if (fp == NULL) {
      return EXIT_FAILURE;
    }
    wunzip(fp);
    fclose(fp);
  }
  return EXIT_SUCCESS;
}
