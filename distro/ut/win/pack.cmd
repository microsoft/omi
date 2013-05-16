@ECHO OFF

REM =================Enable COLOR SETTING===========================
SETLOCAL EnableDelayedExpansion
for /F "tokens=1,2 delims=#" %%a in ('"prompt #$H#$E# & echo on & for %%b in (1) do rem"') do (
  set "DEL=%%a"

)

REM ======================WINOMI directory==========================
SET DESTDIR=%SDXROOT%\admin\wmi
SET WINOMIROOT=%DESTDIR%\winomi
IF NOT EXIST %WINOMIROOT% (goto :MISSWINOMI) ELSE (goto :CONTINUE)

:MISSWINOMI
echo(
call :ColorText 0c "Following directory does exists"
echo ^  %SDXROOT%\admin\WMI\WINOMI
GOTO :DONE


:CONTINUE

if not [%1]==[] (
    SET DESTDIR=%1
)
IF NOT EXIST %DESTDIR% (goto :USAGE)

PUSHD %cd%
CD %WINOMIROOT%

REM ======================DELETE all build logs==========================
DEL /S /F /Q build*.log >nul 2>&1
DEL /S /F /Q build*.trc >nul 2>&1
DEL /S /F /Q build*.prf >nul 2>&1

ZIP -r %DESTDIR%\winomi.zip *.* >nul 2>&1

IF %errorlevel% == 0 (
    echo(
    call :ColorText 0a " Packed"
    call :ColorText 0a " WINOMI"
    call :ColorText 0a " At"
    echo ^ %DESTDIR%\winomi.zip
    echo(
)
COPY /Y %WINOMIROOT%\ut\win\*.sh %DESTDIR%\ >nul 2>&1
POPD
GOTO :DONE

:USAGE
echo.
echo Usage: %0 [TargetDir]
echo ^  TargetDir specifies the location of the zip file
ECHO.
goto :DONE

REM =============Function - Outputs text in color=========

:ColorText
echo off
<nul set /p ".=%DEL%" > "%~2"
findstr /v /a:%1 /R "^$" "%~2" nul
del "%~2" > nul 2>&1
goto :DONE

:DONE