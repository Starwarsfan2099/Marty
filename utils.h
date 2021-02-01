/****************************************************************

Name: utils.h

Description:
    Utilites and other stuff used to make life easier.

****************************************************************/

#include <stdbool.h>

#ifndef UTILS_H_
#define UTILS_H_

bool file_exists (char *filename);
char *epoch_to_datetime(char * input_time);
char *find_substring(const char *main_string, const char *start_pattern, const char *end_pattern);
char *md5_hash_file(char *filename);
int base_64_decode(const char* b64message, char** buffer, size_t* length);
void remove_all_chars(char* str, char c);

#endif