::MCF.bat is designed to be a framework for automating a test pass.
::Variables set at the beginning of the file are used to run MCF, timestamp the
::generated report, generate an HTML report from the XML, and send the results 
::in an email (sending an email is commented out by default).

@echo off

::Data for XmlTransform. HTML filename used for sending email.
set LOGHTML=report.html

::Data for sendmail
set EMAIL=somebody@microsoft.com
set SUBJECT=Testing
set MAILXSL=compact.xslt
set MAILHTML=small_%LOGHTML%

::Data for MCF. LOGXML and LOGXSL are used to generate an HTML report
set MAP=map.xml
set LOGXSL=mcfreport.xslt
set LOGXML=report.xml
set APPEND=false

@echo on

::Run MCF to generate the report
call :mcf %*

::Make copies of the report with the current timestamp
call TimestampFile.bat %LOGXML%

::Create the html file
call XmlTransform.exe %LOGXML% %LOGXSL% %LOGHTML%

::Create a compacted html file for emailing
call XmlTransform.exe %LOGHTML% %MAILXSL% %MAILHTML%

::Send the email
::call sendmail.exe %LOGHTML% %SUBJECT% %EMAIL%

EXIT /B 0

:mcf
call mcf.exe /m:%MAP% /logxml:%LOGXML% /logxsl:%LOGXSL% /append:%APPEND%
set APPEND=true