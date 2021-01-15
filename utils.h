/****************************************************************

Name: utils.h

Description:
    Utilites and other stuff used to make life easier.

****************************************************************/

#include <stdbool.h>

#ifndef UTILS_H_
#define UTILS_H_

bool file_exists (char *filename);
char *epoch_to_datetime(char * epoch_time);

#endif