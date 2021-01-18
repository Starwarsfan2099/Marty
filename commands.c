/****************************************************************

Name: commands.c

Description:
    All commands that can be ran on the database and makes calls
to the callbacks header. This file also includes the sql commands.

****************************************************************/

#include <json.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sqlite3.h>
#if defined(__CYGWIN__) && !defined(_WIN32)
#include <windows.h>
#endif

#include "callbacks.h"
#include "tinydir.h"
#include "utils.h"

// On Windows, include a command to find the timeline databases.
#if defined(__CYGWIN__) && !defined(_WIN32)

int command_get_database_path() {
	char *profile_name;
	char dirpath[256];
	char newpath[256];
	tinydir_dir dir;

	// Get the current signed in username
	profile_name = getenv("USERNAME");
	printf("Profile Name: %s\n", profile_name);

	// Create the path to the catalog
	strcpy(dirpath, "C:\\Users\\");
	strcat(dirpath, profile_name);
	strcat(dirpath, "\\AppData\\Local\\ConnectedDevicesPlatform\\");

	printf("Timeline Path: %s\n\n", dirpath);

	// Use tinydir to get a list of directories in the timeline folder.
	tinydir_open(&dir, dirpath);

	while (dir.has_next)
	{
		tinydir_file file;
		tinydir_readfile(&dir, &file);

		if (file.is_dir) {
			strcpy(newpath, dirpath);
			strcat(newpath, file.name);
			strcat(newpath, "\\ActivitiesCache.db");
			if (file_exists(newpath) == 1) {
				printf("[+] Found Timeline Database at: %s\n", newpath);
			}
		}
		tinydir_next(&dir);
	}

	tinydir_close(&dir);
	return(0);
}

#endif

int command_allinfo(sqlite3 *db){
	char *sql;
	int rc;
	char *zErrMsg = 0;
	const char* data = "Callback function called";

	sql = "SELECT [O].[Id], [O].[AppId], [O].[PackageIdHash], [O].[AppActivityId], [O].[ActivityType], [O].[OperationType] AS [ActivityStatus], [O].[ParentActivityId], [O].[Tag], [O].[Group], [O].[MatchId], [O].[LastModifiedTime], [O].[ExpirationTime], [O].[Payload], [O].[Priority], [A].[IsLocalOnly], [O].[PlatformDeviceId], [O].[DdsDeviceId], [A].[CreatedInCloud], [O].[StartTime], [O].[EndTime], [O].[LastModifiedOnClient], 1 AS [IsInUploadQueue], [O].[GroupAppActivityId], [O].[ClipboardPayload], [O].[EnterpriseId], [O].[UserActionState], [O].[IsRead], [O].[OriginalPayload], [O].[OriginalLastModifiedOnClient], [O].[GroupItems], [O].[ETag] FROM   [ActivityOperation] AS [O]        LEFT OUTER JOIN [Activity] AS [A] ON [O].[Id] = [A].[Id] UNION SELECT [Id], [AppId], [PackageIdHash], [AppActivityId], [ActivityType], [ActivityStatus], [ParentActivityId], [Tag], [Group], [MatchId], [LastModifiedTime], [ExpirationTime], [Payload], [Priority], [IsLocalOnly], [PlatformDeviceId], [DdsDeviceId], [CreatedInCloud], [StartTime], [EndTime], [LastModifiedOnClient], 0 AS [IsInUploadQueue], [GroupAppActivityId], [ClipboardPayload], [EnterpriseId], [UserActionState], [IsRead], [OriginalPayload], [OriginalLastModifiedOnClient], [GroupItems], [ETag] FROM   [Activity] WHERE  [Id] NOT IN (SELECT [Id] FROM [ActivityOperation])";
	rc = sqlite3_exec(db, sql, allinfo_callback, (void*)data, &zErrMsg);

	if( rc != SQLITE_OK ) {
		fprintf(stderr, "\n[-] SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return(0);
	} else {
		fprintf(stdout, "[+] Operation completed successfully\n\n");
		return(1);
	}
}

int command_textfiles(sqlite3 *db, char *argument){
	char *sql;
	int rc;
	char *zErrMsg = 0;
	const char* data = "Callback function called";

	if ((strcmp(argument, "-s") == 0)) {
		printf("[*] Sorting by StartTime.\n");
		sql = "SELECT [O].[Id], [O].[AppId], [O].[PackageIdHash], [O].[AppActivityId], [O].[ActivityType], [O].[OperationType] AS [ActivityStatus], [O].[ParentActivityId], [O].[Tag], [O].[Group], [O].[MatchId], [O].[LastModifiedTime], [O].[ExpirationTime], [O].[Payload], [O].[Priority], [A].[IsLocalOnly], [O].[PlatformDeviceId], [O].[DdsDeviceId], [A].[CreatedInCloud], [O].[StartTime], [O].[EndTime], [O].[LastModifiedOnClient], 1 AS [IsInUploadQueue], [O].[GroupAppActivityId], [O].[ClipboardPayload], [O].[EnterpriseId], [O].[UserActionState], [O].[IsRead], [O].[OriginalPayload], [O].[OriginalLastModifiedOnClient], [O].[GroupItems], [O].[ETag] FROM   [ActivityOperation] AS [O]        LEFT OUTER JOIN [Activity] AS [A] ON [O].[Id] = [A].[Id] UNION SELECT [Id], [AppId], [PackageIdHash], [AppActivityId], [ActivityType], [ActivityStatus], [ParentActivityId], [Tag], [Group], [MatchId], [LastModifiedTime], [ExpirationTime], [Payload], [Priority], [IsLocalOnly], [PlatformDeviceId], [DdsDeviceId], [CreatedInCloud], [StartTime], [EndTime], [LastModifiedOnClient], 0 AS [IsInUploadQueue], [GroupAppActivityId], [ClipboardPayload], [EnterpriseId], [UserActionState], [IsRead], [OriginalPayload], [OriginalLastModifiedOnClient], [GroupItems], [ETag] FROM   [Activity] WHERE  [Id] NOT IN (SELECT [Id] FROM [ActivityOperation]) ORDER BY StartTime DESC";
	} else if ((strcmp(argument, "-l") == 0)) {
		printf("[*] Sorting by LastModifiedTime.\n");
		sql = "SELECT [O].[Id], [O].[AppId], [O].[PackageIdHash], [O].[AppActivityId], [O].[ActivityType], [O].[OperationType] AS [ActivityStatus], [O].[ParentActivityId], [O].[Tag], [O].[Group], [O].[MatchId], [O].[LastModifiedTime], [O].[ExpirationTime], [O].[Payload], [O].[Priority], [A].[IsLocalOnly], [O].[PlatformDeviceId], [O].[DdsDeviceId], [A].[CreatedInCloud], [O].[StartTime], [O].[EndTime], [O].[LastModifiedOnClient], 1 AS [IsInUploadQueue], [O].[GroupAppActivityId], [O].[ClipboardPayload], [O].[EnterpriseId], [O].[UserActionState], [O].[IsRead], [O].[OriginalPayload], [O].[OriginalLastModifiedOnClient], [O].[GroupItems], [O].[ETag] FROM   [ActivityOperation] AS [O]        LEFT OUTER JOIN [Activity] AS [A] ON [O].[Id] = [A].[Id] UNION SELECT [Id], [AppId], [PackageIdHash], [AppActivityId], [ActivityType], [ActivityStatus], [ParentActivityId], [Tag], [Group], [MatchId], [LastModifiedTime], [ExpirationTime], [Payload], [Priority], [IsLocalOnly], [PlatformDeviceId], [DdsDeviceId], [CreatedInCloud], [StartTime], [EndTime], [LastModifiedOnClient], 0 AS [IsInUploadQueue], [GroupAppActivityId], [ClipboardPayload], [EnterpriseId], [UserActionState], [IsRead], [OriginalPayload], [OriginalLastModifiedOnClient], [GroupItems], [ETag] FROM   [Activity] WHERE  [Id] NOT IN (SELECT [Id] FROM [ActivityOperation]) ORDER BY LastModifiedTime DESC";
	} else {
		sql = "SELECT [O].[Id], [O].[AppId], [O].[PackageIdHash], [O].[AppActivityId], [O].[ActivityType], [O].[OperationType] AS [ActivityStatus], [O].[ParentActivityId], [O].[Tag], [O].[Group], [O].[MatchId], [O].[LastModifiedTime], [O].[ExpirationTime], [O].[Payload], [O].[Priority], [A].[IsLocalOnly], [O].[PlatformDeviceId], [O].[DdsDeviceId], [A].[CreatedInCloud], [O].[StartTime], [O].[EndTime], [O].[LastModifiedOnClient], 1 AS [IsInUploadQueue], [O].[GroupAppActivityId], [O].[ClipboardPayload], [O].[EnterpriseId], [O].[UserActionState], [O].[IsRead], [O].[OriginalPayload], [O].[OriginalLastModifiedOnClient], [O].[GroupItems], [O].[ETag] FROM   [ActivityOperation] AS [O]        LEFT OUTER JOIN [Activity] AS [A] ON [O].[Id] = [A].[Id] UNION SELECT [Id], [AppId], [PackageIdHash], [AppActivityId], [ActivityType], [ActivityStatus], [ParentActivityId], [Tag], [Group], [MatchId], [LastModifiedTime], [ExpirationTime], [Payload], [Priority], [IsLocalOnly], [PlatformDeviceId], [DdsDeviceId], [CreatedInCloud], [StartTime], [EndTime], [LastModifiedOnClient], 0 AS [IsInUploadQueue], [GroupAppActivityId], [ClipboardPayload], [EnterpriseId], [UserActionState], [IsRead], [OriginalPayload], [OriginalLastModifiedOnClient], [GroupItems], [ETag] FROM   [Activity] WHERE  [Id] NOT IN (SELECT [Id] FROM [ActivityOperation])";
	}	rc = sqlite3_exec(db, sql, textfiles_callback, (void*)data, &zErrMsg);

	if( rc != SQLITE_OK ) {
		fprintf(stderr, "\n[-] SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return(0);
	} else {
		fprintf(stdout, "\n[+] Operation completed successfully\n\n");
		return(1);
	}
}

int command_programs(sqlite3 *db, char *argument){
	char *sql;
	int rc;
	char *zErrMsg = 0;
	const char* data = "Callback function called";

	if ((strcmp(argument, "-s") == 0)) {
		printf("[*] Sorting by StartTime.\n");
		sql = "SELECT [O].[Id], [O].[AppId], [O].[PackageIdHash], [O].[AppActivityId], [O].[ActivityType], [O].[OperationType] AS [ActivityStatus], [O].[ParentActivityId], [O].[Tag], [O].[Group], [O].[MatchId], [O].[LastModifiedTime], [O].[ExpirationTime], [O].[Payload], [O].[Priority], [A].[IsLocalOnly], [O].[PlatformDeviceId], [O].[DdsDeviceId], [A].[CreatedInCloud], [O].[StartTime], [O].[EndTime], [O].[LastModifiedOnClient], 1 AS [IsInUploadQueue], [O].[GroupAppActivityId], [O].[ClipboardPayload], [O].[EnterpriseId], [O].[UserActionState], [O].[IsRead], [O].[OriginalPayload], [O].[OriginalLastModifiedOnClient], [O].[GroupItems], [O].[ETag] FROM   [ActivityOperation] AS [O]        LEFT OUTER JOIN [Activity] AS [A] ON [O].[Id] = [A].[Id] UNION SELECT [Id], [AppId], [PackageIdHash], [AppActivityId], [ActivityType], [ActivityStatus], [ParentActivityId], [Tag], [Group], [MatchId], [LastModifiedTime], [ExpirationTime], [Payload], [Priority], [IsLocalOnly], [PlatformDeviceId], [DdsDeviceId], [CreatedInCloud], [StartTime], [EndTime], [LastModifiedOnClient], 0 AS [IsInUploadQueue], [GroupAppActivityId], [ClipboardPayload], [EnterpriseId], [UserActionState], [IsRead], [OriginalPayload], [OriginalLastModifiedOnClient], [GroupItems], [ETag] FROM   [Activity] WHERE  [Id] NOT IN (SELECT [Id] FROM [ActivityOperation]) ORDER BY StartTime DESC";
	} else if ((strcmp(argument, "-l") == 0)) {
		printf("[*] Sorting by LastModifiedTime.\n");
		sql = "SELECT [O].[Id], [O].[AppId], [O].[PackageIdHash], [O].[AppActivityId], [O].[ActivityType], [O].[OperationType] AS [ActivityStatus], [O].[ParentActivityId], [O].[Tag], [O].[Group], [O].[MatchId], [O].[LastModifiedTime], [O].[ExpirationTime], [O].[Payload], [O].[Priority], [A].[IsLocalOnly], [O].[PlatformDeviceId], [O].[DdsDeviceId], [A].[CreatedInCloud], [O].[StartTime], [O].[EndTime], [O].[LastModifiedOnClient], 1 AS [IsInUploadQueue], [O].[GroupAppActivityId], [O].[ClipboardPayload], [O].[EnterpriseId], [O].[UserActionState], [O].[IsRead], [O].[OriginalPayload], [O].[OriginalLastModifiedOnClient], [O].[GroupItems], [O].[ETag] FROM   [ActivityOperation] AS [O]        LEFT OUTER JOIN [Activity] AS [A] ON [O].[Id] = [A].[Id] UNION SELECT [Id], [AppId], [PackageIdHash], [AppActivityId], [ActivityType], [ActivityStatus], [ParentActivityId], [Tag], [Group], [MatchId], [LastModifiedTime], [ExpirationTime], [Payload], [Priority], [IsLocalOnly], [PlatformDeviceId], [DdsDeviceId], [CreatedInCloud], [StartTime], [EndTime], [LastModifiedOnClient], 0 AS [IsInUploadQueue], [GroupAppActivityId], [ClipboardPayload], [EnterpriseId], [UserActionState], [IsRead], [OriginalPayload], [OriginalLastModifiedOnClient], [GroupItems], [ETag] FROM   [Activity] WHERE  [Id] NOT IN (SELECT [Id] FROM [ActivityOperation]) ORDER BY LastModifiedTime DESC";
	} else {
		sql = "SELECT [O].[Id], [O].[AppId], [O].[PackageIdHash], [O].[AppActivityId], [O].[ActivityType], [O].[OperationType] AS [ActivityStatus], [O].[ParentActivityId], [O].[Tag], [O].[Group], [O].[MatchId], [O].[LastModifiedTime], [O].[ExpirationTime], [O].[Payload], [O].[Priority], [A].[IsLocalOnly], [O].[PlatformDeviceId], [O].[DdsDeviceId], [A].[CreatedInCloud], [O].[StartTime], [O].[EndTime], [O].[LastModifiedOnClient], 1 AS [IsInUploadQueue], [O].[GroupAppActivityId], [O].[ClipboardPayload], [O].[EnterpriseId], [O].[UserActionState], [O].[IsRead], [O].[OriginalPayload], [O].[OriginalLastModifiedOnClient], [O].[GroupItems], [O].[ETag] FROM   [ActivityOperation] AS [O]        LEFT OUTER JOIN [Activity] AS [A] ON [O].[Id] = [A].[Id] UNION SELECT [Id], [AppId], [PackageIdHash], [AppActivityId], [ActivityType], [ActivityStatus], [ParentActivityId], [Tag], [Group], [MatchId], [LastModifiedTime], [ExpirationTime], [Payload], [Priority], [IsLocalOnly], [PlatformDeviceId], [DdsDeviceId], [CreatedInCloud], [StartTime], [EndTime], [LastModifiedOnClient], 0 AS [IsInUploadQueue], [GroupAppActivityId], [ClipboardPayload], [EnterpriseId], [UserActionState], [IsRead], [OriginalPayload], [OriginalLastModifiedOnClient], [GroupItems], [ETag] FROM   [Activity] WHERE  [Id] NOT IN (SELECT [Id] FROM [ActivityOperation])";
	}
	rc = sqlite3_exec(db, sql, programs_callback, (void*)data, &zErrMsg);

	if( rc != SQLITE_OK ) {
		fprintf(stderr, "\n[-] SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return(0);
	} else {
		fprintf(stdout, "\n[+] Operation completed successfully\n\n");
		return(1);
	}
}