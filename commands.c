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
#include <sqlite3.h>
#include "callbacks.h"

// On Windows, include a command to find the timeline databases.
#if defined(__CYGWIN__) && !defined(_WIN32)

int command_get_database_path(){
	char *profile_name;
	char filepath[80];
	FILE *catalog;

	// Get the current signed in username
	profile_name = getenv("USERNAME");
	printf("Profile Name: %s\n", profile_name);

	// Create the path to the catalog
	strcpy(filepath, "C:\\Users\\");
	strcat(filepath, profile_name);
	strcat(filepath, "\\AppData\\Local\\ConnectedDevicesPlatform\\CDPGlobalSettings.cdp");

	printf("Catalog File Path: %s\n\n", filepath);

	// Open the catalog file
 	if ((catalog = fopen(filepath, "r")) == NULL){
       printf("[-] Error opening catalog file");

       // Program exits if the file pointer returns NULL.
       return(1);
   	}

	printf("[+] Opened Catalog file.\n");

	fseek(catalog, 0, SEEK_END);
	long fsize = ftell(catalog);
	fseek(catalog, 0, SEEK_SET);

	char *catalog_contents = malloc(fsize + 1);
	fread(catalog_contents, 1, fsize, catalog);
	fclose(catalog);

	printf("[+] Catalog COntents:\n%s", catalog_contents);

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
		fprintf(stderr, "[-] SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return(0);
	} else {
		fprintf(stdout, "[+] Operation done successfully\n\n");
		return(1);
	}
}

int command_textfiles(sqlite3 *db){
	char *sql;
	int rc;
	char *zErrMsg = 0;
	const char* data = "Callback function called";

	sql = "SELECT [O].[Id], [O].[AppId], [O].[PackageIdHash], [O].[AppActivityId], [O].[ActivityType], [O].[OperationType] AS [ActivityStatus], [O].[ParentActivityId], [O].[Tag], [O].[Group], [O].[MatchId], [O].[LastModifiedTime], [O].[ExpirationTime], [O].[Payload], [O].[Priority], [A].[IsLocalOnly], [O].[PlatformDeviceId], [O].[DdsDeviceId], [A].[CreatedInCloud], [O].[StartTime], [O].[EndTime], [O].[LastModifiedOnClient], 1 AS [IsInUploadQueue], [O].[GroupAppActivityId], [O].[ClipboardPayload], [O].[EnterpriseId], [O].[UserActionState], [O].[IsRead], [O].[OriginalPayload], [O].[OriginalLastModifiedOnClient], [O].[GroupItems], [O].[ETag] FROM   [ActivityOperation] AS [O]        LEFT OUTER JOIN [Activity] AS [A] ON [O].[Id] = [A].[Id] UNION SELECT [Id], [AppId], [PackageIdHash], [AppActivityId], [ActivityType], [ActivityStatus], [ParentActivityId], [Tag], [Group], [MatchId], [LastModifiedTime], [ExpirationTime], [Payload], [Priority], [IsLocalOnly], [PlatformDeviceId], [DdsDeviceId], [CreatedInCloud], [StartTime], [EndTime], [LastModifiedOnClient], 0 AS [IsInUploadQueue], [GroupAppActivityId], [ClipboardPayload], [EnterpriseId], [UserActionState], [IsRead], [OriginalPayload], [OriginalLastModifiedOnClient], [GroupItems], [ETag] FROM   [Activity] WHERE  [Id] NOT IN (SELECT [Id] FROM [ActivityOperation])";
	rc = sqlite3_exec(db, sql, textfiles_callback, (void*)data, &zErrMsg);

	if( rc != SQLITE_OK ) {
		fprintf(stderr, "[-] SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return(0);
	} else {
		fprintf(stdout, "\n[+] Operation done successfully\n\n");
		return(1);
	}
}

int command_programs(sqlite3 *db){
	char *sql;
	int rc;
	char *zErrMsg = 0;
	const char* data = "Callback function called";

	sql = "SELECT [O].[Id], [O].[AppId], [O].[PackageIdHash], [O].[AppActivityId], [O].[ActivityType], [O].[OperationType] AS [ActivityStatus], [O].[ParentActivityId], [O].[Tag], [O].[Group], [O].[MatchId], [O].[LastModifiedTime], [O].[ExpirationTime], [O].[Payload], [O].[Priority], [A].[IsLocalOnly], [O].[PlatformDeviceId], [O].[DdsDeviceId], [A].[CreatedInCloud], [O].[StartTime], [O].[EndTime], [O].[LastModifiedOnClient], 1 AS [IsInUploadQueue], [O].[GroupAppActivityId], [O].[ClipboardPayload], [O].[EnterpriseId], [O].[UserActionState], [O].[IsRead], [O].[OriginalPayload], [O].[OriginalLastModifiedOnClient], [O].[GroupItems], [O].[ETag] FROM   [ActivityOperation] AS [O]        LEFT OUTER JOIN [Activity] AS [A] ON [O].[Id] = [A].[Id] UNION SELECT [Id], [AppId], [PackageIdHash], [AppActivityId], [ActivityType], [ActivityStatus], [ParentActivityId], [Tag], [Group], [MatchId], [LastModifiedTime], [ExpirationTime], [Payload], [Priority], [IsLocalOnly], [PlatformDeviceId], [DdsDeviceId], [CreatedInCloud], [StartTime], [EndTime], [LastModifiedOnClient], 0 AS [IsInUploadQueue], [GroupAppActivityId], [ClipboardPayload], [EnterpriseId], [UserActionState], [IsRead], [OriginalPayload], [OriginalLastModifiedOnClient], [GroupItems], [ETag] FROM   [Activity] WHERE  [Id] NOT IN (SELECT [Id] FROM [ActivityOperation])";
	rc = sqlite3_exec(db, sql, programs_callback, (void*)data, &zErrMsg);

	if( rc != SQLITE_OK ) {
		fprintf(stderr, "[-] SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return(0);
	} else {
		fprintf(stdout, "\n[+] Operation done successfully\n\n");
		return(1);
	}
}