@ECHO OFF

REM USAGE: winomi_test.cmd [releaseshare]

SET TEST_ROOT=%SystemDrive%\winomi
SET BINPATH=%TEST_ROOT%
SET TESTBINPATH=%BINPATH%\tests\bin
SET TESTDIR=%BINPATH%\tests
SET LOGDIR=%CD%
SET LOGFILENAME=%LOGDIR%\test.log

ECHO Current Directory: %LOGDIR% >%LOGFILENAME%  2>&1

REM Workaround test failure around test_pal.cpp:TmpName function
IF NOT EXIST C:\temp (
    mkdir C:\temp
)

REM ======================Check Unit Test ROOT directory=============
IF NOT EXIST %BINPATH%\omiserver.exe (
    echo Please check the configuration. Omiserver.exe does not exist under %TEST_ROOT%    >> %LOGFILENAME%  2>&1
    GOTO :ERROR
)

REM ======================RUN UNIT TESTs============================
CALL TASKKILL /IM omiserver.exe     > %LOGDIR%\omiserver.log  2>&1
CALL start %BINPATH%\omiserver.exe    >> %LOGDIR%\omiserver.log  2>&1

REM NITS.exe needs to load test DLLs from current directory
CD /D %TESTBINPATH%
CALL nits -reset -file:%BINPATH%\tests\nitsargs.txt >> %LOGFILENAME%  2>&1
if ERRORLEVEL 1 (goto :FAILURE)

goto :SUCCESS

REM =================DONE with UNIT TESTs============================

:ERROR
ECHO Usage: %0 [RELEASESHARE]    >> %LOGFILENAME%  2>&1
SET EXITCODE=1
goto DONE

:FAILURE
ECHO Unit test failed.    >> %LOGFILENAME%  2>&1
SET EXITCODE=1
goto DONE

:SUCCESS
echo ####################    >> %LOGFILENAME%  2>&1
echo #_ALL TESTS PASSED_#    >> %LOGFILENAME%  2>&1
echo ####################    >> %LOGFILENAME%  2>&1

SET EXITCODE=0

:DONE
CALL TASKKILL /IM omiserver.exe    >> %LOGFILENAME%  2>&1
EXIT %EXITCODE%
