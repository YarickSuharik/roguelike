@echo off
setlocal
set DOTNET_EXE=%LOCALAPPDATA%\Microsoft\dotnet\dotnet.exe
if not exist "%DOTNET_EXE%" set DOTNET_EXE=dotnet
"%DOTNET_EXE%" build "%~dp0RL_CSharp.csproj" %*
