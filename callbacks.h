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


#endif