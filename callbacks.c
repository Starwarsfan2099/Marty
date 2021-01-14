/****************************************************************

Name: callbacks.c

Description:
    Callbacks that receive the data from the sql queries. This 
does the brunt of the processing and output.

****************************************************************/

#include <json.h>
#include <stdio.h>
#include <string.h>
#include "callbacks.h"

int allinfo_callback(void *data, int argc, char **argv, char **azColName){
	int i;
	struct json_object *jobj;

	printf("%s: ", (const char*)data);

	for(i = 0; i<argc; i++){
		if(!argv[i]){
			printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		} else {
			if(strstr(argv[i], "{") != NULL) {
				jobj = json_tokener_parse(argv[i]);
				printf("%s:\n%s\n",azColName[i], \
					json_object_to_json_string_ext(jobj, \
					JSON_C_TO_STRING_SPACED | \
					JSON_C_TO_STRING_PRETTY));
			} else {
				printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
			}
		}
	}

	printf("\n");
	return 0;
}

int textfiles_callback(void *data, int argc, char **argv, char **azColName){
	int i;
	struct json_object *jobj;

	for(i = 0; i<argc; i++){
		if(!argv[i]){
			// printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		} else {
			if(strstr(argv[i], "{") != NULL) {
				jobj = json_tokener_parse(argv[i]);
				json_object *tmp;
				if (json_object_object_get_ex(jobj, "displayText", &tmp)) {
					if(strstr(argv[i], ".txt") != NULL) {
						printf("Name: %s\n", json_object_get_string(tmp));
						json_object_object_get_ex(jobj, "description", &tmp);
						printf("Path: %s\n\n", json_object_get_string(tmp));
					}
				}
			}
        }
	}
	
	return 0;
}

int programs_callback(void *data, int argc, char **argv, char **azColName){
	int i;
	struct json_object *jobj;

	for(i = 0; i<argc; i++){
		if(!argv[i]){
			// printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		} else {
			if(strstr(argv[i], "{") != NULL) {
				jobj = json_tokener_parse(argv[i]);
				json_object *tmp;
				if (json_object_object_get_ex(jobj, "appDisplayName", &tmp)) {
					printf("Program Name: %s\n", json_object_get_string(tmp));
				}
			}
        }
	}
	
	return 0;
}