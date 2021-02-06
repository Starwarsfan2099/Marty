# Marty
It's time to go back... In the Windows timeline.

This is a **VERY** Alpha program for pulling data and timestamps from the Windows timeline. 
Binary's of the most recent stable pre-release are provided compiled for Windows, Linux, and MacOS.
`libsqlite3-dev`, `libssl-dev`, and `json-c` are required for building. 
Database is hash verified before and after use automatically for forensic verification.


```
        [*] Marty Verion 0.2 - Alpha
"It's time to go back... in the Windows Timeline."


Marty is a Windows Timeline Analysis Program.

Commands:
        showallinfo              [-s, -l]               Print all information in the database.
        writeallinfo   FILE      [-s, -l]               Write all information in the database to FILE.
        showfilenames  NAME      [-s, -l]               Print all files found with NAME in the title.
        showprograms             [-s, -l]               Print all programs executed by the user found in the database.
        showextentions EXTENTION [-s, -l]               Print all files found with the EXTENTION.
        showclipboard            [-l]                   Print all clipboard data in the database.

Options:
        -l                                              Sort by the last modification time.
        -s                                              Sort by the last application or editior start time.

Windows Commands:
        showdatabasepath                                Print the path to the timeline database if on Windows.

To find databases:
        marty.exe showdatabasepath

Usage:
./marty "Database-Path" Command

Eamples:
./marty "ActivitiesCache.db" showtextfiles -l
./marty "ActivitiesCache.db" showextentions .docx -s



```
