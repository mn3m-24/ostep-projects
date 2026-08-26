#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void wgrep_stream(FILE *stream, const char *pattern) {
  char *line = NULL; // line allocated to this buffer
  size_t cap = 0;    // the capacity of the buffer
  // getting each line of texts, passed by reference bc they'll be modified
  while (getline(&line, &cap, stream) != -1) {
    // searching for the search match text inside the line
    if (strstr(line, pattern) == NULL) {
      continue;
    }
    fputs(line, stdout);
  }
  // free the getline allocation
  free(line);
}

void wgrep(const char *path, const char *pattern) {
  if (path == NULL) {
    wgrep_stream(stdin, pattern);
    return;
  }
  // opening file stream
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    fputs("wgrep: cannot open file\n", stdout);
    exit(EXIT_FAILURE);
  }
  // using opend file as the stream
  wgrep_stream(fp, pattern);
  fclose(fp);
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    fputs("wgrep: searchterm [file ...]\n", stdout);
    return EXIT_FAILURE;
  }
  char *pattern = argv[1];
  if (argc == 2) {
    wgrep(NULL, pattern);
    return EXIT_SUCCESS;
  }
  for (int i = 2; i < argc; ++i) {
    char *path = argv[i];
    wgrep(path, pattern);
  }
  return EXIT_SUCCESS;
}
