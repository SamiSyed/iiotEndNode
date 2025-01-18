@echo off

:: Set the path to Python executable (optional, update if needed)
set PYTHON_PATH=python

:: Set the path to the Python script
set SCRIPT_PATH=cubeMX_CodeGen_Postrun.py

:: Print the paths for debugging
echo Running Python script using %PYTHON_PATH%
echo Script path: %SCRIPT_PATH%

:: Run the Python script
%PYTHON_PATH% %SCRIPT_PATH%

:: Check the exit code of the Python script
if %ERRORLEVEL% NEQ 0 (
    echo [Error] Failed to execute the Python script. Exit code: %ERRORLEVEL%
    pause
) else (
    echo [Success] Python script executed successfully.
    exit /b
)
