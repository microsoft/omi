@ECHO OFF

REM USAGE: winunittest.cmd ReleaseShare

REM passed in parameters

SET RELEASEROOT=%1
SET NTTREEDIR=%RELEASEROOT%
SET BINPATH=%NTTREEDIR%\WinOMI
SET TESTBINPATH=%BINPATH%\tests\bin
SET TESTDIR=%BINPATH%\tests
SET LOGDIR=%CD%
SET LOGFILENAME=%LOGDIR%\config.log

ECHO Current Direcotry: %LOGDIR% >%LOGFILENAME% 2>&1

SET TEST_ROOT=%SystemDrive%\winomi

REM ======================Create test directory======================
IF NOT EXIST %TEST_ROOT% (
    mkdir %TEST_ROOT%
    goto INSTALL
)

rmdir /S /Q %TEST_ROOT%
mkdir %TEST_ROOT%

:INSTALL

REM ======================Check Unit Test ROOT directory=============
IF NOT EXIST %BINPATH%\omiserver.exe (
    echo Please correct the release share! It does not have nits.exe built  >>%LOGFILENAME% 2>&1
    GOTO :ERROR
)

Call nits -uninstall >>%LOGFILENAME% 2>&1

DEL %SYSTEMROOT%\system32\nits*

copy /y %NTTREEDIR%\nitsdll.dll %SYSTEMROOT%\system32\.   >>%LOGFILENAME% 2>&1
copy /y %NTTREEDIR%\nitsinj.dll %SYSTEMROOT%\system32\.   >>%LOGFILENAME% 2>&1
copy /y %NTTREEDIR%\nits.exe %SYSTEMROOT%\system32\.   >>%LOGFILENAME% 2>&1

IF NOT EXIST %SystemRoot%\system32\nits.exe (
    echo "Please run unittest_install.cmd!" >>%LOGFILENAME% 2>&1
    GOTO :ERROR
)

Call nits -install    >>%LOGFILENAME% 2>&1

CALL xcopy %BINPATH%  %TEST_ROOT% /E /Y    >>%LOGFILENAME% 2>&1
IF NOT EXIST %TEST_ROOT%\omiserver.exe (
GOTO :ERROR
)

SET TEST_ROOT_TESTBIN=%TEST_ROOT%\tests\bin
ECHO TEST_ROOT_TESTBIN: %TEST_ROOT_TESTBIN% >>%LOGFILENAME% 2>&1

COPY /Y %TEST_ROOT%\MI_OMI.dll %TEST_ROOT_TESTBIN%\
IF NOT EXIST %TEST_ROOT_TESTBIN%\en-us (
    MKDIR %TEST_ROOT_TESTBIN%\en-us
)
COPY /Y %TEST_ROOT%\en-us\MI_OMI.dll.mui %TEST_ROOT_TESTBIN%\en-us\

GOTO :SUCCESS

REM =================DONE with config============================

:ERROR
ECHO Usage: %0 [RELEASESHARE]    >>%LOGFILENAME% 2>&1
Call nits -uninstall    >>%LOGFILENAME% 2>&1
EXIT 1

:SUCCESS
echo ####################    >>%LOGFILENAME% 2>&1
echo #Configuration Done#    >>%LOGFILENAME% 2>&1
echo ####################    >>%LOGFILENAME% 2>&1
EXIT 0
