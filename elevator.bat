@echo off
REM Requests elevated privileges for servicer.bat file
powershell Start-Process -FilePath "servicer.bat" -Verb runAs