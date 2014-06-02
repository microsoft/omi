setlocal
SET OMIUTILMOF_DIR=%SDXROOT%\admin\wmi\winomi\omiutils\mofs
SET CIM226_DIR=%SDXROOT%\admin\wmi\WMIv2\CIM-2.26.0

REM run downlevel version if available
set converter=%_NTTREE%\WINIP\win7\Convert-MofToProvider.exe
if not exist %converter% (
    set converter=Convert-MofToProvider.exe
)
%converter% -ClassList DummyClass -ExtraClass OMI_DebugError -MofFile %OMIUTILMOF_DIR%\gen.mof -IncludePath %OMIUTILMOF_DIR% %CIM226_DIR% -SkipLocalize -OutPath %OMIUTILMOF_DIR%\gen
