@ECHO OFF
pushd %cd%

if not [%2]==[] (
    goto :ERROR
)

if not [%1]==[] (
    SET BINPATH=%1) ELSE (SET BINPATH=%_NTTREE%
)


REM ======================Check Unit Test ROOT directory=============

call nits -uninstall
DEL %SYSTEMROOT%\system32\nits*

copy /y %BINPATH%\nitsdll.dll %SYSTEMROOT%\system32\.
copy /y %BINPATH%\nitsinj.dll %SYSTEMROOT%\system32\.
copy /y %BINPATH%\nits.exe %SYSTEMROOT%\system32\.

call nits -install
if ERRORLEVEL 1 goto :ERROR

goto :DONE

:ERROR
echo(
echo Usage: %0 [BINARY ROOT DIR]
ECHO.
goto :DONE

:DONE
