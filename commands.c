/****************************************************************

Name: commands.c

Description:
    All commands that can be ran on the database and makes calls
to the callbacks header. This file also includes the sql commands.

****************************************************************/

#include <stdio.h>
#include <sqlite3.h>
#include "callbacks.h"

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
		fprintf(stdout, "[+] Operation done successfully\n");
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
		fprintf(stdout, "[+] Operation done successfully\n");
		return(1);
	}
}