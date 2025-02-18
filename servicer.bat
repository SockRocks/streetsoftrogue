@echo off
set "a=%~1"
set "b=%a%\newMain.exe"
REM Sets the binary as a service and sets it to run on start up
sc create joke binpath= "%b%" start= auto
sc start joke