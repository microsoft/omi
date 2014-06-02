set SCRATCH_BINS=\\scratch2\scratch\%USERNAME%\bins\%_BuildArch%

rem copy the binaries
xcopy /s/y/e/q/D %_NTTREE%\WinOMI %SCRATCH_BINS%\WinOMI\
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
xcopy /s/y/e/q/D %_NTTREE%\Symbols.pri %SCRATCH_BINS%\Symbols.pri\
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
xcopy /y/q/D %_NTTREE%\nitsdll.dll %SCRATCH_BINS%\
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
xcopy /y/q/D %_NTTREE%\nitsinj.dll %SCRATCH_BINS%\
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
xcopy /y/q/D %_NTTREE%\nits.exe %SCRATCH_BINS%\
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
xcopy /y/q/D %_NTTREE%\nitssample.dll %SCRATCH_BINS%\
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
xcopy /y/q/D %_NTTREE%\nitssampleproduct.dll %SCRATCH_BINS%\
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
:EXIT