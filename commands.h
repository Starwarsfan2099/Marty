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

#endif