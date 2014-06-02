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

c:\debuggers\%PROCESSOR_ARCHITECTURE%\gflags.exe /p /enable nits.exe /full
c:\debuggers\%PROCESSOR_ARCHITECTURE%\gflags.exe /i nits.exe +hpa
c:\debuggers\%PROCESSOR_ARCHITECTURE%\gflags.exe /i nits.exe +ust
c:\debuggers\%PROCESSOR_ARCHITECTURE%\gflags.exe /i nits.exe /tracedb 30

c:\debuggers\%PROCESSOR_ARCHITECTURE%\gflags.exe /p /enable omiserver.exe /full
c:\debuggers\%PROCESSOR_ARCHITECTURE%\gflags.exe /i omiserver.exe +hpa
c:\debuggers\%PROCESSOR_ARCHITECTURE%\gflags.exe /i omiserver.exe +ust
c:\debuggers\%PROCESSOR_ARCHITECTURE%\gflags.exe /i omiserver.exe /tracedb 30

c:\debuggers\%PROCESSOR_ARCHITECTURE%\gflags.exe /p /enable omiclient.exe /full
c:\debuggers\%PROCESSOR_ARCHITECTURE%\gflags.exe /i omiclient.exe +hpa
c:\debuggers\%PROCESSOR_ARCHITECTURE%\gflags.exe /i omiclient.exe +ust
c:\debuggers\%PROCESSOR_ARCHITECTURE%\gflags.exe /i omiclient.exe /tracedb 30

goto :DONE

:ERROR
echo(
echo Usage: %0 [BINARY ROOT DIR]
ECHO.
goto :DONE

:DONE
