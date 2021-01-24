/****************************************************************

Name: callbacks.h

Description:
    Callbacks that receive the data from the sql queries. This 
does the brunt of the processing and output.

****************************************************************/

#ifndef CALLBACKS_H_
#define CALLBACKS_H_

int allinfo_callback(void *data, int argc, char **argv, char **azColName);
int textfiles_callback(void *data, int argc, char **argv, char **azColName);
int programs_callback(void *data, int argc, char **argv, char **azColName);
int extention_callback(void *data, int argc, char **argv, char **azColName);
int file_name_callback(void *data, int argc, char **argv, char **azColName);
int write_allinfo_callback(void *data, int argc, char **argv, char **azColName);

int set_out_file_name(char *name);
int set_extention(char *extention);
int set_file_name(char *extention);

#endif