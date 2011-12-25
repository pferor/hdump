/**
 * @file dump.h
 *
 * @brief Hexadecimal dump routine declaration
 */

#ifndef DUMP_H
#define DUMP_H


/* Public interface */
/**
 * @brief Makes an hexadecimal and ASCII dump of a file
 *
 * @param *input    Input stream
 * @param *output   Where to be displayed
 * @param file_size Size of the content
 * @param columns   Columns to display on
 *
 * @return 0 if everything OK, or otherwise
 *
 * @note Data is processed in chunks of (2 * @e columns) bytes
 */
int hex_dump(FILE *input,
             FILE *output,
             size_t file_size,
             int columns);


#endif /* ! DUMP_H */

