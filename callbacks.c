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
#include "utils.h"

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
	char *modified_time = "";

	for(i = 0; i<argc; i++){
		if(!argv[i]){
			// printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		} else {
			if (strcmp(azColName[i], "LastModifiedTime") == 0){
				modified_time = argv[i];
			}
			if(strstr(argv[i], "{") != NULL) {
				jobj = json_tokener_parse(argv[i]);
				json_object *tmp;
				if (json_object_object_get_ex(jobj, "displayText", &tmp)) {
					if(strstr(argv[i], ".txt") != NULL) {
						printf("[+] Name: %s\n", json_object_get_string(tmp));
						json_object_object_get_ex(jobj, "description", &tmp);
						printf("[*] Path: %s\n[*] Modified Time: %s\n\n", json_object_get_string(tmp), epoch_to_datetime(modified_time));
					}
				}
			}
        }
	}
	
	return 0;
}

int programs_callback(void *data, int argc, char **argv, char **azColName){
	int i;
	int found_program = 0;
	struct json_object *jobj;
	char *start_time = "";
	char *modified_time = "";
	const char *program_name = "";
	const char *display_text = "";
	
	for(i = 0; i<argc; i++){
		if(!argv[i]){
			// printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		} else {
			if (strcmp(azColName[i], "StartTime") == 0){
				start_time = argv[i];
			}
			if (strcmp(azColName[i], "LastModifiedTime") == 0){
				modified_time = argv[i];
			}
			if(strstr(argv[i], "{") != NULL) {
				jobj = json_tokener_parse(argv[i]);
				json_object *tmp;
				if (json_object_object_get_ex(jobj, "appDisplayName", &tmp)) {
					program_name = json_object_get_string(tmp);
					found_program = 1;
				}
				if (json_object_object_get_ex(jobj, "displayText", &tmp)) {
					display_text = json_object_get_string(tmp);
					found_program = 1;
				}
			}
        }
	}

	if (found_program != 0) {
		printf("[*] Program: %s\n[*] Display Text: %s\n[*] Start Time: %s (Epoch: %s)\n[*] Last Modified Time: %s (Epoch %s)\n\n", \
		program_name, display_text, epoch_to_datetime(start_time), start_time, epoch_to_datetime(modified_time), modified_time);
	}
	
	return 0;
}