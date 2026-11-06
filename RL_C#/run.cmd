@echo off
setlocal
pushd "%~dp0"
set DOTNET_EXE=%LOCALAPPDATA%\Microsoft\dotnet\dotnet.exe
if not exist "%DOTNET_EXE%" set DOTNET_EXE=dotnet
"%DOTNET_EXE%" build RL_CSharp.csproj --nologo -v quiet
if errorlevel 1 (
    popd
    exit /b 1
)
bin\Debug\net8.0\RL_CSharp.exe %*
popd
