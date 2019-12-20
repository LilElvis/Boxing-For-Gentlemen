@echo off
rem copy dependencies by D. Buckstein
set platform=%1
set config=%2
set src="%~dp0\ThirdParty\lib\OpenAL\%platform%\%config%\OpenAL32.dll"
set dst="%~dp0\bin\%platform%\%config%"
xcopy %src% %dst% /y
