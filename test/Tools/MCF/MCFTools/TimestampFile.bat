@echo off
::using predefined helpers for parameter 1 (filename, pathname, extension) assumes first parameter is a filename
SET FFILE=%~n1%
SET FPATH=%~f1%
SET FEXT=%~x1%


set FTEMP=%DATE%
set FYEAR=%FTEMP:~-4%
set FDAY=%FTEMP:~-7,2%
set FMONTH=%FTEMP:~-10,2%

set FTEMP=%TIME%
set FHOUR=%FTEMP:~0,2%
set FHOUR=%FHOUR: =0%
set FMIN=%FTEMP:~3,2%
set FSEC=%FTEMP:~6,2%

set TIMESTAMP=%FYEAR%%FMONTH%%FDAY%_%FHOUR%h%FMIN%m%FSEC%s

@echo on

copy %1 %FFILE%_%TIMESTAMP%%FEXT%
copy %1 %FFILE%_latest%FEXT%

EXIT /B 0