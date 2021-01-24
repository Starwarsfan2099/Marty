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

char file_extention[10];
char file_name[20];
char out_file_name[20];
int entrys = 0;

int allinfo_callback(void *data, int argc, char **argv, char **azColName){
	int i;
	struct json_object *jobj;

	printf("Entry %d:\n", entrys);

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

	entrys++;
	printf("\n");
	return 0;
}

int set_out_file_name(char *name){
	if (strlen(name) <= 19){
		sprintf(out_file_name, "%s", name);
		return(1);
	} else {
		printf("[-] File name too long.\n\n");
		return(0);
	}
}

int write_allinfo_callback(void *data, int argc, char **argv, char **azColName){
	int i;
	struct json_object *jobj;
	FILE *out_file;

	// printf("[*] Writing to file: %s\n", out_file_name);

	out_file = fopen(out_file_name, "a");

	if (out_file == NULL) {
        printf("[-] Error wriitng to output file.");
        exit(1);
    }

	fprintf(out_file, "Entry %d:\n", entrys);

	for(i = 0; i<argc; i++){
		if(!argv[i]){
			fprintf(out_file, "%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		} else {
			if(strstr(argv[i], "{") != NULL) {
				jobj = json_tokener_parse(argv[i]);
				fprintf(out_file, "%s:\n%s\n",azColName[i], \
					json_object_to_json_string_ext(jobj, \
					JSON_C_TO_STRING_SPACED | \
					JSON_C_TO_STRING_PRETTY));
			} else {
				fprintf(out_file, "%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
			}
		}
	}

	entrys++;
	fprintf(out_file, "\n");
	fclose(out_file);
	return 0;
}

int textfiles_callback(void *data, int argc, char **argv, char **azColName){
	int i;
	struct json_object *jobj;
	char *modified_time = "";

	for(i = 0; i<argc; i++){
		if(!argv[i]){
			// Pass, it's a NULL cell
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
			// Pass, it's a NULL cell
		} else {
			// Get application start time
			if (strcmp(azColName[i], "StartTime") == 0){
				start_time = argv[i];
			}
			// Last modified time
			if (strcmp(azColName[i], "LastModifiedTime") == 0){
				modified_time = argv[i];
			}
			// Decode JSON data from the payload here
			if(strstr(argv[i], "{") != NULL) {
				jobj = json_tokener_parse(argv[i]);
				json_object *tmp;
				// Program Name
				if (json_object_object_get_ex(jobj, "appDisplayName", &tmp)) {
					program_name = json_object_get_string(tmp);
					found_program = 1;
				}
				// Text displayed in the title of the window for the app
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

int set_extention(char *extention){
	if (strlen(extention) <= 9){
		sprintf(file_extention, "%s", extention);
		return(1);
	} else {
		printf("[-] File extention too long.\n\n");
		return(0);
	}
}

int set_file_name(char *name){
	if (strlen(file_name) <= 19){
		sprintf(file_name, "%s", name);
		return(1);
	} else {
		printf("[-] File name too long.\n\n");
		return(0);
	}
}

int extention_callback(void *data, int argc, char **argv, char **azColName){
	int i;
	int found_program = 0;
	struct json_object *jobj;
	char *modified_time = "";
	char *start_time = "";
	char *app_activity_id = "";
	const char *path = "";
	const char *file_title = "";

	for(i = 0; i<argc; i++){
		if(!argv[i]){
			// Pass, it's a NULL cell
		} else {
			if (strcmp(azColName[i], "LastModifiedTime") == 0){
				modified_time = argv[i];
			}
			if (strcmp(azColName[i], "StartTime") == 0){
				start_time = argv[i];
			}
			if (strcmp(azColName[i], "AppActivityId") == 0){
				if(strstr(argv[i], file_extention) != NULL) {
					app_activity_id = argv[i];
					found_program = 1;
				}
			}
			
			if (strcmp(azColName[i], "AppId") == 0){
				if(strstr(argv[i], file_extention) != NULL) {
					const char *start_pattern = "crossplatform\"},{\"application\":\"";
					const char *end_pattern = "\",\"platform\":\"";
					char main_string [strlen(argv[i]) + 1];
					sprintf(main_string, "%s", argv[i]);
					path = find_substring(main_string, start_pattern, end_pattern);
				}
			}
			
			if(strstr(argv[i], "{") != NULL) {
				jobj = json_tokener_parse(argv[i]);
				json_object *tmp;
				if (json_object_object_get_ex(jobj, "displayText", &tmp)) {
					if(strstr(argv[i], file_extention) != NULL) {
						file_title = json_object_get_string(tmp );
						json_object_object_get_ex(jobj, "description", &tmp);
						if (tmp != NULL){
							path = json_object_get_string(tmp);
						}
						found_program = 2;
					}
				}
			}
        }
	}

	if (found_program == 2){
		printf("[+] File Name: %s\n", file_title);
		printf("[*] Path: %s\n", path);
		printf("[*] Modified Time: %s\n", epoch_to_datetime(modified_time));
		printf("[*] Start time: %s\n\n", epoch_to_datetime(start_time));
		found_program = 0;
	}

	if (found_program == 1){
		printf("[+] AppActivityId: %s\n", app_activity_id);
		printf("[*] Modified Time: %s\n", epoch_to_datetime(modified_time));
		printf("[*] Start time: %s\n\n", epoch_to_datetime(start_time));
		found_program = 0;
	}
	
	return 0;
}

int file_name_callback(void *data, int argc, char **argv, char **azColName){
	int i;
	int found_program = 0;
	struct json_object *jobj;
	char *modified_time = "";
	char *start_time = "";
	char *app_activity_id = "";
	const char *path = "";
	const char *file_title = "";

	for(i = 0; i<argc; i++){
		if(!argv[i]){
			// Pass, it's a NULL cell
		} else {
			if (strcmp(azColName[i], "LastModifiedTime") == 0){
				modified_time = argv[i];
				// printf("ModifyTime: %s (%s)\n", modified_time, epoch_to_datetime(modified_time));

			}
			if (strcmp(azColName[i], "StartTime") == 0){
				start_time = argv[i];
				// printf("StartTime: %s (%s)\n", start_time, epoch_to_datetime(start_time));
			}
			if (strcmp(azColName[i], "AppActivityId") == 0){
				if(strstr(argv[i], file_name) != NULL) {
					app_activity_id = argv[i];
					found_program = 1;
				}
			}
			
			if (strcmp(azColName[i], "AppId") == 0){
				if(strstr(argv[i], file_name) != NULL) {
					const char *start_pattern = "crossplatform\"},{\"application\":\"";
					const char *end_pattern = "\",\"platform\":\"";
					char main_string [strlen(argv[i]) + 1];
					sprintf(main_string, "%s", argv[i]);
					path = find_substring(main_string, start_pattern, end_pattern);
				}
			}
			
			if(strstr(argv[i], "{") != NULL) {
				jobj = json_tokener_parse(argv[i]);
				json_object *tmp;
				if (json_object_object_get_ex(jobj, "displayText", &tmp)) {
					if(strstr(argv[i], file_name) != NULL) {
						file_title = json_object_get_string(tmp );
						json_object_object_get_ex(jobj, "description", &tmp);
						if (tmp != NULL){
							path = json_object_get_string(tmp);
						}
						found_program = 2;
					}
				}
			}
        }
	}

	if (found_program == 2){
		printf("[+] File Name: %s\n", file_title);
		printf("[*] Path: %s\n", path);
		printf("[*] Modified Time: %s\n", epoch_to_datetime(modified_time));
		printf("[*] Start time: %s\n\n", epoch_to_datetime(start_time));
		found_program = 0;
	}

	if (found_program == 1){
		printf("[+] AppActivityId: %s\n", app_activity_id);
		printf("[*] Modified Time: %s\n", epoch_to_datetime(modified_time));
		printf("[*] Start time: %s\n\n", epoch_to_datetime(start_time));
		found_program = 0;
	}
	
	return 0;
}