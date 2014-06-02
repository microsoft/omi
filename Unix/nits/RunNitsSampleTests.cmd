REM usage check - make sure the binary location is specified
if "%1"=="" (echo "ERROR: Specify binary location" && goto :Exit)

call nits -reset
call nits -uninstall
call del \windows\system32\nits*
call copy /y %1\nits* \Windows\system32\
call nits -install
if not %errorlevel% == 0 (echo "ERROR: Nits install failed" && goto :Exit)
call nits -trace -wtt:c:\winomi\results.wtl -target:nitssample.dll;nitssampleproduct.dll nitssample.dll

:Exit
