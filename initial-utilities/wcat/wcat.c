#include <stdio.h>
#include <stdlib.h>

void cat_file(char *path) {
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    fputs("wcat: cannot open file\n", stdout);
    exit(EXIT_FAILURE);
  }
  const size_t buf_size = 4096;
  char buf[buf_size]; // scratch buffer
  while (fgets(buf, buf_size, fp) != NULL) {
    fputs(buf, stdout);
  }
  fclose(fp);
}

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; ++i) {
    cat_file(argv[i]);
  }
  return EXIT_SUCCESS;
}
