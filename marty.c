/****************************************************************

Name: marty.c

Description:
    Main Marty file. Checks if the database is present, checks 
command line args, and executes commands based off of them. 

****************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <unistd.h>

#include "callbacks.h"
#include "commands.h"


int help() {
	printf("\nMarty is a Windows Timeline Analysis Program.\n");
	printf("\nCommands:\nshowallinfo			Print all information in the database.\n");
	printf("showtextfiles			Print all text files found in the database.\n");
	printf("showprograms			Print all programs executed by the user found in the database.\n");
	printf("\n");
	return(1);
}

bool file_exists (char *filename) {
	if( access( filename, F_OK ) == 0 ) {
		return(1);
	} else {
		return(0);
	}
}

int main(int argc, char* argv[]) {
	sqlite3 *db;
	char *filename = argv[1];
	int rc;

	fprintf(stderr, "\n[*] Marty Verion 1.0 - Alpha\n");
	fprintf(stderr, "\"It's time to go back... in the Windows Timeline.\"\n\n");

	// Check for no arguments or arguments for a help menu
	if ((argc <= 2) || (strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)) {
		help();
		return(0);
	}
	
	// Check if the database file exists
	if (file_exists(filename) == 0) {
		fprintf(stderr, "[-] Can't open database: %s\n", argv[1]);
		return(0);
	}

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
	} else if (strcmp(argv[2], "showtextfiles") == 0) {
		command_textfiles(db);
	} else if (strcmp(argv[2], "showprograms") == 0) {
		command_programs(db);
	} else {
	}

	// Close database
	sqlite3_close(db);
	return 0;
}
