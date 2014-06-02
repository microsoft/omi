@ECHO OFF

REM usage check - make sure user alias specified
if "%1"=="" (set INFO=echo && set SEXIT=1) else (set INFO=rem && set SEXIT=0)

%INFO% Usage: getbins binaries_source
%INFO%            binaries_source is the source to copy bins from, for example: \\tsclient\d\buddy\fbl_srv_msp.binaries.x86fre

if "%SEXIT%"=="1" goto :EXIT

if not "%2"=="" goto :EXIT

IF EXIST %SYSTEMROOT%\system32\taskkill.exe (    
    %SYSTEMROOT%\system32\taskkill /F /im omiserver.exe
) ELSE (
    kill omiserver.exe
)
rem xcopy binaries from scratch to local directories
echo Copying WinOMI bins ...
xcopy /s/e/q/r/y/D %1\WinOMI .\WinOMI\
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
xcopy /s/e/q/r/y/D %1\Symbols.pri .\Symbols.pri\
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
xcopy /y/q/D %1\nitsdll.dll .
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
xcopy /y/q/D %1\nitsinj.dll .
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
xcopy /y/q/D %1\nits.exe .
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
xcopy /y/q/D %1\nitssample.dll .
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
xcopy /y/q/D %1\nitssampleproduct.dll .
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
echo ... test bins copied.

:EXIT 
