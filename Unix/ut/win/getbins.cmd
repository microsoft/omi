@ECHO OFF

REM usage check - make sure user alias specified
if "%1"=="" (set INFO=echo && set SEXIT=1) else (set INFO=rem && set SEXIT=0)

%INFO% Usage: getbins user_alias [source_dir]
%INFO%            user_alias is user alias only - no domain

if "%SEXIT%"=="1" goto :EXIT

if not "%2"=="" goto :EXIT

IF EXIST %SYSTEMROOT%\system32\taskkill.exe (    
    %SYSTEMROOT%\system32\taskkill /F /im omiserver.exe
) ELSE (
    kill omiserver.exe
)

rem xcopy binaries from scratch to local directories
echo Copying WinOMI bins ...
xcopy /s/e/q/r/y/D \\scratch2\scratch\%1\bins\%PROCESSOR_ARCHITECTURE% .
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
echo ... test bins copied.

:EXIT 
