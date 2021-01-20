/****************************************************************

Name: utils.c

Description:
    Utilites and other stuff used to make life easier.

****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// Check to see if a file exists
int file_exists (char *filename) {
	if( access( filename, F_OK ) == 0 ) {
		return(1);
	} else {
		return(0);
	}
}

// Conversion for epoch time used in the timeline
char *epoch_to_datetime(char * input_time){
    time_t epoch_time = atoi(input_time);
    struct tm ts;
    static char modified_time[80];
    ts = *localtime(&epoch_time);
    strftime(modified_time, sizeof(modified_time), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
    return modified_time;
}

char *find_substring(const char *main_string, const char *start_pattern, const char *end_pattern){

    char *target = NULL;
    char *start, *end;

    if ((start = strstr(main_string, start_pattern))) {
        start += strlen(start_pattern);
        if ((end = strstr(start, end_pattern))) {
            target = (char *)malloc(end - start + 1);
            memcpy(target, start, end - start);
            target[end - start] = '\0';
        }
    }

    return(target);
}