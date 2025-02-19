@echo off
REM Sets the binary as a service and sets it to run on start up
sc create joke binpath= "%~dp0\newMain.exe" start= auto
sc start joke