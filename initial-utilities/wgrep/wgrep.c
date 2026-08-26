#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void wgrep_stream(FILE *stream, const char *pattern) {
  char *line = NULL;
  size_t len = 0;
  size_t pattern_len = strlen(pattern);
  // getting each line of texts
  while (getline(&line, &len, stream) != -1) {
    // searching for match by iterating sequentially
    size_t line_len = strlen(line);
    // ignoring this line if the pattern is larger than it
    if (pattern_len > line_len) {
      continue;
    }

    for (int i = 0; i < line_len - pattern_len + 1; ++i) {
      bool match = true;
      for (int j = 0; j < pattern_len; ++j) {
        if (pattern[j] != line[j + i]) {
          match = false;
          break;
        }
      }
      if (!match) {
        continue;
      }
      fputs(line, stdout);
      break;
    }
  }
  // free the getline allocation
  free(line);
}

void wgrep(const char *path, const char *pattern) {
  if (path == NULL) {
    wgrep_stream(stdin, pattern);
    return;
  }
  // opening file
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    fputs("wgrep: cannot open file\n", stdout);
    exit(EXIT_FAILURE);
  }
  // using opend file as the stream
  wgrep_stream(fp, pattern);
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    fputs("wgrep: searchterm [file ...]\n", stdout);
    exit(EXIT_FAILURE);
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
