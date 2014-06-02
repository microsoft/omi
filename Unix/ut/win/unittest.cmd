@ECHO OFF
pushd %cd%


IF EXIST %SYSTEMROOT%\system32\taskkill.exe (
    SET FULLSKU=1
) ELSE (
    SET FULLSKU=0
)

REM =================Enable COLOR SETTING===========================
SETLOCAL EnableDelayedExpansion
for /F "tokens=1,2 delims=#" %%a in ('"prompt #$H#$E# & echo on & for %%b in (1) do rem"') do (
  set "DEL=%%a"
)


if not [%2]==[] (
    goto :ERROR
)

if not [%1]==[] (
    SET BINPATH=%1) ELSE (SET BINPATH=%_NTTREE%\WinOMI
)


REM ======================Check Unit Test ROOT directory=============
IF NOT EXIST %BINPATH%\omiserver.exe (
    if %FULLSKU% == 1 (goto :FULLSKU_MISSROOT) else (goto :CSS_MISSROOT)
)
goto :CONTINUE

:FULLSKU_MISSROOT
echo(
call :ColorText 0c "Please specify correct unit test root directory!"
echo(
GOTO :ERROR

:CSS_MISSROOT
echo Please specify correct unit test root directory!
GOTO :ERROR

:CONTINUE


IF NOT EXIST %SystemRoot%\system32\nits.exe (
	echo(
	call :ColorText 0c "Please run unittest_install.cmd!"
	echo(
	GOTO :ERROR
)

SET TESTBINPATH=%BINPATH%\tests\bin


REM ================================================================
REM ======================RUN UNIT TESTs============================

IF EXIST %SYSTEMROOT%\system32\taskkill.exe (    
    %SYSTEMROOT%\system32\taskkill /F /im omiserver.exe
) ELSE (
    kill omiserver.exe
)
cd %BINPATH%

copy MI_OMI.dll %TESTBINPATH%\
md %TESTBINPATH%\en-us
copy en-us\MI_OMI.dll.mui %TESTBINPATH%\en-us

start omiserver.exe --loglevel 3
cd %TESTBINPATH%

nits -file:..\nitsargs.txt
if ERRORLEVEL 1 (goto :FAILURE)

IF EXIST %SYSTEMROOT%\system32\taskkill.exe (    
    %SYSTEMROOT%\system32\taskkill /F /im omiserver.exe
) ELSE (
    kill omiserver.exe
)
popd %cd%
goto :SUCCESS

REM =================DONE with UNIT TESTs============================


:ERROR
echo(
echo Usage: %0 [UT ROOT DIR]
ECHO.
goto :DONE

:FAILURE
echo(
call :ColorText 0c "Test failed!"
goto :DONE

:SUCCESS

if %FULLSKU% == 1 (goto :FULLSKUSUCCESS) else (goto :CSSSUCCESS)

:FULLSKUSUCCESS
echo(
echo(
call :ColorText 0a ####################
echo(
call :ColorText 0a #_
call :ColorText 0a "ALL"
call :ColorText 0a " TESTS"
call :ColorText 0a " PASSED!"
call :ColorText 0a _#
echo(
call :ColorText 0a ####################
echo(
goto :DONE

:CSSSUCCESS
echo ####################
echo #_ALL TESTS PASSED_#
echo ####################
goto :DONE


REM =============Function - Outputs text in color=========

:ColorText
echo off
<nul set /p ".=%DEL%" > "%~2"
findstr /v /a:%1 /R "^$" "%~2" nul
del "%~2" > nul 2>&1
goto :DONE


:DONE
