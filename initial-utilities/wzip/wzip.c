#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fputs("wzip: file1 [file2 ...]\n", stdout);
    return EXIT_FAILURE;
  }
  int c;
  int last_c = EOF; // sentinal value for currently no processed chars
  uint32_t cnt = 0;
  // merging files into one string & performing Run-Length Encoding compression.
  for (int i = 1; i < argc; ++i) {
    char *path = argv[i];
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
      exit(EXIT_FAILURE);
    }
    while ((c = fgetc(fp)) != EOF) {
      if (last_c != EOF && c != last_c) {
        fwrite(&cnt, sizeof(int32_t), 1, stdout);
        char ch = last_c;
        fwrite(&ch, sizeof(char), 1, stdout);
        last_c = c;
        cnt = 1;
        continue;
      }
      if (last_c == EOF) {
        last_c = c;
      }
      cnt += 1;
    }
    fclose(fp);
  }
  // flushing remaining compressed runs that remain after finishing all files
  if (last_c != EOF) {
    fwrite(&cnt, sizeof(int32_t), 1, stdout);
    char ch = last_c;
    fwrite(&ch, sizeof(char), 1, stdout);
  }
  return EXIT_SUCCESS;
}
