xcopy /y/q/D \\tsclient\C\OMI\r2_r1.binaries.amd64chk\nitsdll.dll .
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
xcopy /y/q/D \\tsclient\C\OMI\r2_r1.binaries.amd64chk\nitsinj.dll .
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
xcopy /y/q/D \\tsclient\C\OMI\r2_r1.binaries.amd64chk\nits.exe .
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
xcopy /y/q/D \\tsclient\C\OMI\r2_r1.binaries.amd64chk\nitssample.dll .
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
xcopy /y/q/D \\tsclient\C\OMI\r2_r1.binaries.amd64chk\nitssampleproduct.dll .
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
xcopy /s/e/q/r/y/D \\tsclient\C\OMI\r2_r1.binaries.amd64chk\Symbols.pri\retail\dll .\dll\
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
xcopy /s/e/q/r/y/D \\tsclient\C\OMI\r2_r1.binaries.amd64chk\Symbols.pri\retail\exe .\exe\
if not %errorlevel% == 0 (echo "ERROR: Bin file copy failed." && goto :EXIT)
echo ... test bins copied.


nits -uninstall
del c:\Windows\system32\nits*
copy nits* c:\Windows\system32
nits -install

:EXIT 