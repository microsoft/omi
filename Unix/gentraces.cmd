@ECHO OFF
pushd %cd%

echo Starting Traces Generator
echo gentraces.cmd FILE or SYSLOG or NOOP or ETW

if "%1"=="FILE" (
echo Generating traces for File Logging
sd edit %BASEDIR%\admin\wmi\winomi\base\oiwinomi.h
%_NTTREE%\winomi\oigenc %1 %BASEDIR%\admin\wmi\winomi\base\oi_traces.h %BASEDIR%\admin\wmi\winomi\base\oiwinomi.h
)

if "%1"=="SYSLOG" (
echo Generating traces for Syslog OMI-Linux
sd edit %BASEDIR%\admin\wmi\winomi\base\oiomi.h
%_NTTREE%\winomi\oigenc %1 %BASEDIR%\admin\wmi\winomi\base\oi_traces.h OMI LOG_NDELAY LOG_LOCAL1 %BASEDIR%\admin\wmi\winomi\base\oiomi.h
)

if "%1"=="NOOP" (
echo Generating no-op for Syslog and WinOMI
sd edit %BASEDIR%\admin\wmi\winomi\base\oiomi.h
%_NTTREE%\winomi\oigenc %1 %BASEDIR%\admin\wmi\winomi\base\oi_traces.h %BASEDIR%\admin\wmi\winomi\base\oiomi.h
sd edit %BASEDIR%\admin\wmi\winomi\base\oiwinomi.h
%_NTTREE%\winomi\oigenc %1 %BASEDIR%\admin\wmi\winomi\base\oi_traces.h %BASEDIR%\admin\wmi\winomi\base\oiwinomi.h
)

if "%1"=="ETW" (
echo Generating ETW traces for WinOMI
sd edit %BASEDIR%\admin\wmi\winomi\base\oiwinomi.h
sd edit %BASEDIR%\admin\wmi\winomi\server\omiserver.man
%_NTTREE%\winomi\oigenc ETW %BASEDIR%\admin\wmi\winomi\base\oi_traces.h omiserver {6266923D-F7C9-452A-9167-A73B33A61302} omiserver.exe %BASEDIR%\admin\wmi\winomi\base\oiwinomi.h %BASEDIR%\admin\wmi\winomi\server\omiserver.man
reformatmanifest -inplace %BASEDIR%\admin\wmi\winomi\server\omiserver.man
)

if "%1"=="" (
echo Generating default traces for WinOMI and OMI
sd edit %BASEDIR%\admin\wmi\winomi\base\oiwinomi.h
%_NTTREE%\winomi\oigenc FILE %BASEDIR%\admin\wmi\winomi\base\oi_traces.h %BASEDIR%\admin\wmi\winomi\base\oiwinomi.h
sd edit %BASEDIR%\admin\wmi\winomi\base\oiomi.h
%_NTTREE%\winomi\oigenc FILE %BASEDIR%\admin\wmi\winomi\base\oi_traces.h %BASEDIR%\admin\wmi\winomi\base\oiomi.h
)