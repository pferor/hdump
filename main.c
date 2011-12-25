/**
 * @file main.c
 *
 * @brief Hexadecimal dump of a file
 */

/* System includes */
#include <stdio.h>  /* fprintf, fopen,... */
#include <stdlib.h> /* malloc, free,... */

/* Local includes */
#include "dump.h"


/* Optimal columns for representation; also the data is taken in
 * 'columns * 2' chunks. */
#define COLUMNS 8


/* prototypes */
/**
 * @brief Show usage of this file
 *
 * @param *stream Stream where to dump this usage data
 * @param *arg0   Program name
 */
void show_usage(FILE *stream,
                const char *arg0);


/**
 * @brief Opens a file and dumps the content of a file
 *
 * @return
 *  0 Everything is OK
 *  1 Argument error (just one argument needed)
 *  2 File error (cannot open file)
 *  3 Memory error (cannot allocate)
 */
int main(int argc, char *argv[])
{
  FILE *fp;
  size_t file_size;

  /* check arguments */
  if (argc != 2) {
    show_usage(stdout, argv[0]);
    return 1;
  }

  /* open the file */
  fp = fopen(argv[1], "rb");
  if (fp == NULL) {
    fprintf(stderr, "%s: %s: No such file or directory\n",
            argv[0],
            argv[1]);
    return 2;
  }

  /* obtain file size */
  fseek(fp, 0, SEEK_END);
  file_size = ftell(fp);
  rewind(fp);

  /* hexdump */
  if (hex_dump(fp, stdout, file_size, COLUMNS) != 0) {
    fprintf(stderr, "%s: No enough memory for execution\n", argv[0]);
    return 3;
  }

  /* close file */
  fclose(fp);

  return 0;
}


/**
 * @brief Shows usage of this application
 *
 * @param *stream Output where the usage is written
 */
void show_usage(FILE *stream, const char *arg0)
{
  fprintf(stream, "Usage: %s <file>\n", arg0);
}

