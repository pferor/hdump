/**
 * @file dump.c
 *
 * @brief Hexadecimal dump implementation
 */

/* System includes */
#include <stdio.h>  /* fprintf, fread,... */
#include <stdlib.h> /* malloc, free,... */
#include <ctype.h>  /* isprint,... */

/* Local includes */
#include "dump.h"


/* Dump routine */
int hex_dump(FILE *input,
             FILE *output,
             size_t file_size,
             int columns)
{
  int i, nvals;
  size_t tsize;
  unsigned char ascii[2 * columns];
  unsigned char *buffer;

  nvals = 0;
  tsize = 0;
  while (tsize < file_size) {
    buffer = (unsigned char *) malloc((2 * columns) *
                                      sizeof(unsigned char));
    if (buffer == NULL) {
      return -1;
    }

    /* copy the file into the auxiliary buffer */
    fread(buffer, 1, 2 * columns, input);

    /* column number*/
    fprintf(output, "%08x  ", nvals);

    /* hex values */
    for (i = 0; i < 2 * columns; i++) {
      ascii[i] = buffer[i];

      /* print the value*/
      if (tsize >= file_size) {
        fprintf(output, "   ");
      } else {
        fprintf(output, "%02x ", buffer[i]);
        nvals++;
      }

      /* middle space */
      if (i == (columns - 1)) {
        fprintf(output, " ");
      }

      /* increase control size */
      tsize++;
    }

    free(buffer);

    fprintf(output, " ");

    /* ASCII values */
    fprintf(output, "|");
    for (i = 0; i < 2 * columns; i++) {
      /* stop if the end is reached*/
      if ((tsize - 2 * columns + i + 1) > file_size) {
        break;
      }

      /* show only printable characters */
      if (isprint(ascii[i])) {
        fprintf(output, "%c", ascii[i]);
      } else {
        fprintf(output, ".");
      }
    }
    fprintf(output, "|");

    /* end of row */
    fprintf(output, "\n");
  }

  /* print last address */
  fprintf(output, "%08x\n", nvals);

  return 0;
}

