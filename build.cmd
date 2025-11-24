@echo off
setlocal enabledelayedexpansion

REM --- check if build/build.cmd exists ---

cd build

if exist "build.cmd" (
        echo Running build\build.cmd
        call "build.cmd" %*
) else (
        echo Error: build\build.cmd not found.
        exit /b 1
)

cd ..

REM --- include paths ---
set includes[0]=C:\CPP Libs\poly2tri
set includes[1]=C:\CPP Libs\Clipper2\Clipper2Lib\include
set includes[2]=C:\CPP Libs\glfw-3.3.8\glfw-3.3.8\include
set includes[3]=C:\CPP Libs\glew-2.1.0-win32\glew-2.1.0\include
set includes[4]=C:\CPP Libs\glm

set GLFW=-L"C:\CPP Libs\glfw-3.3.8.bin.WIN64\lib-mingw-w64" -lglfw3
set GLEW=-L"C:\CPP Libs\glew-2.1.0-win32\glew-2.1.0\bin\Release\x64" -lglew32

set include_args=

for /l %%i in (0,1,4) do (
    set include_args=!include_args! -I"!includes[%%i]!"
)

echo Include arguments: !include_args!

REM --- Compile source files ---
for %%f in (*.cpp) do (
        set fname=%%~nf
    echo Compiling %%f -> !fname!.exe
        clang++ -g !include_args! %%f -o !fname!.exe !GLFW! -lopengl32 !GLEW! libgpp.dll

)