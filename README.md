# Marty
It's time to go back... In the Windows timeline.

This is a **VERY** Alpha program for pulling data and timestamps from the Windows timeline. 
Binary's of the most recent stable pre-release are provided compiled for Windows, Linux, and MacOS.
`libsqlite3-dev`, `libssl-dev`, and `json-c` are required for building. Database is hash verified after use automatically.


```
        [*] Marty Verion 0.1 - Alpha
"It's time to go back... in the Windows Timeline."


Marty is a Windows Timeline Analysis Program.

Commands:
        showallinfo                             Print all information in the database.
        showfilename NAME                       Print all files found with NAME in the title.
        showprograms                            Print all programs executed by the user found in the database.
        showextentions EXTENTION                Print all files found with the EXTENTION.

Options:
        -l                                      Sort by the last modification time.
        -s                                      Sort by the last application or editior start time.

Windows Commands:
        showdatabasepath                        Print the path to the timeline database if on Windows.

To find databases:
        marty.exe showdatabasepath

Usage:
./marty "Database-Path" Command

Eamples:
./marty "ActivitiesCache.db" showtextfiles -l
./marty "ActivitiesCache.db" showextentions .docx -s

```
