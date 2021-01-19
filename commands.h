/****************************************************************

Name: commands.h

Description:
    All commands that can be ran on the database and makes calls
to the callbacks header. This file also includes the sql commands.

****************************************************************/

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <stdio.h>
#include <sqlite3.h>

int command_allinfo(sqlite3 *db);
int command_textfiles(sqlite3 *db, char *argument);
int command_programs(sqlite3 *db, char *argument);
int command_get_database_path();
int command_extentions(sqlite3 *db, char *argument);
int command_file_name(sqlite3 *db, char *argument);

#endif