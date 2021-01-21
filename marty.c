/****************************************************************

Name: marty.c

Description:
    Main Marty file. Checks if the database is present, checks 
command line args, and executes commands based off of them. 

****************************************************************/

#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <unistd.h>

#include "callbacks.h"
#include "commands.h"
#include "utils.h"

// Print help information
int help() {
	printf("\nMarty is a Windows Timeline Analysis Program.\n");
	printf("\nCommands:\n");
	printf("\tshowallinfo				Print all information in the database.\n");
	printf("\tshowfilename NAME			Print all files found with NAME in the title.\n");
	printf("\tshowprograms				Print all programs executed by the user found in the database.\n");
	printf("\tshowextentions EXTENTION		Print all files found with the EXTENTION.\n");

	printf("\nOptions:\n");
	printf("\t-l					Sort by the last modification time.\n");
	printf("\t-s					Sort by the last application or editior start time.\n");

// Check to see if we are building on Windows, if we are, add functionality and commands.
#if defined(__CYGWIN__) && !defined(_WIN32)
	printf("\nWindows Commands:\n");
	printf("\tshowdatabasepath			Print the path to the timeline database if on Windows.\n\n");
	printf("To find databases:\n\tmarty.exe showdatabasepath\n");
#endif

	printf("\nUsage: \n./marty \"Database-Path\" Command\n");
	printf("\nEamples: \n./marty \"ActivitiesCache.db\" showtextfiles -l\n");
	printf("./marty \"ActivitiesCache.db\" showextentions .docx -s\n");

	printf("\n");
	return(1);
}

int main(int argc, char* argv[]) {
	sqlite3 *db;
	char *filename = argv[1];
	int rc;
	int len;
	char orig_hash[33];
	char later_hash[33];
	char *temp = "";

	fprintf(stderr, "\n\t[*] Marty Verion 1.0 - Alpha\n");
	fprintf(stderr, "\"It's time to go back... in the Windows Timeline.\"\n\n");

	// Check for no arguments or arguments for a help menu
	if ((argc <= 1) || (strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)) {
		help();
		return(0);
	}

#if defined(__CYGWIN__) && !defined(_WIN32)
	if (strcmp(argv[1], "showdatabasepath") == 0) {
		command_get_database_path();
		return(1);
	}
#endif
	
	// Check if the database file exists
	if (file_exists(filename) == 0) {
		fprintf(stderr, "[-] Can't open database: %s\n", argv[1]);
		return(0);
	}

	temp = md5_hash_file(filename);
	strncpy(orig_hash, temp, 32);
	orig_hash[32] = '\0';
	printf("[*] MD5 Hash: %s\n\n", orig_hash);

	// Open the database
	rc = sqlite3_open(filename, &db);

	if (rc) {
		fprintf(stderr, "[-] Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	} else {
		fprintf(stderr, "[+] Opened database successfully\n\n");
	}
	
	// Commands go here
	if (strcmp(argv[2], "showallinfo") == 0) {
		command_allinfo(db);
	} else if (strcmp(argv[2], "showfilename") == 0) {
		if (argc < 4) {
			help();
			return(0);
		}
		len = set_file_name(argv[3]);
		if (len == 0){
			return (0);
		}
		if (argc == 4) {
			command_file_name(db, "NULL");
		} else if (strcmp(argv[4], "-s") == 0) {
			command_file_name(db, "-s");
		} else if (strcmp(argv[4], "-l") == 0) {
			command_file_name(db, "-l");
		} else {
			help();
			return(0);
		}
		set_file_name("");
	} else if (strcmp(argv[2], "showprograms") == 0) {
		if (argc == 3) {
			command_programs(db, "NULL");
		} else if (strcmp(argv[3], "-s") == 0) {
			command_programs(db, "-s");
		} else if (strcmp(argv[3], "-l") == 0) {
			command_programs(db, "-l");
		} else {
			help();
			return(0);
		}
	} else if (strcmp(argv[2], "showextentions") == 0) {
		if (argc < 4) {
			help();
			return(0);
		}
		len = set_extention(argv[3]);
		if (len == 0){
			return (0);
		}
		if (argc == 4) {
			command_extentions(db, "NULL");
		} else if (strcmp(argv[4], "-s") == 0) {
			command_extentions(db, "-s");
		} else if (strcmp(argv[4], "-l") == 0) {
			command_extentions(db, "-l");
		} else {
			help();
			return(0);
		}
		set_extention("");
	} else {
		help();
	}

	// Close database
	sqlite3_close(db);

	temp = md5_hash_file(filename);
	strncpy(later_hash, temp, 32);
	later_hash[32] = '\0';
	if (strcmp(later_hash, orig_hash) == 0) {
		printf("[+] %s Unchanged (%s:%s)\n\n", filename, orig_hash, later_hash);
	} else {
		// We should NEVER get here 
		printf("[-] %s CHANGED (%s:%s)\n\n", filename, orig_hash, later_hash);
	}

	return 0;
}
