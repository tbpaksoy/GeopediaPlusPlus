@echo off
setlocal enabledelayedexpansion

REM --- include paths ---

set INC1=..\src
set INC2=C:\CPP Libs\poly2tri
set INC3=C:\CPP Libs\Clipper2\Clipper2Lib\include
set INC4=C:\CPP Libs\glfw-3.3.8\glfw-3.3.8\include
set INC5=C:\CPP Libs\glew-2.1.0-win32\glew-2.1.0\include
set INC6=C:\CPP Libs\glm

set GLFW=-L"C:\CPP Libs\glfw-3.3.8.bin.WIN64\lib-mingw-w64" -lglfw3
set GLEW=-L"C:\CPP Libs\glew-2.1.0-win32\glew-2.1.0\bin\Release\x64" -lglew32

if not exist obj mkdir obj

for /r "%INC2%\poly2tri" %%f in (*.cc) do (
    echo Compiling %%f
    clang++ -std=c++17 -g -c -I"%INC2%" "%%f" -o "obj\%%~nf.o"
)

REM --- scan files recursively ---

for /r ..\src %%f in (*.cpp) do (
        echo Compiling %%f
        clang++ -std=c++17 -g -c -I"%INC1%" -I"%INC2%" -I"%INC3%" -I"%INC4%" -I"%INC5%" -I"%INC6%" %%f -o "obj\%%~nf.o"
)

REM --- create library ---
clang++ -std=c++17 -g -I"%INC1%" -I"%INC2%" -I"%INC3%" -I"%INC4%" -I"%INC5%" -I"%INC6%" -shared -o ..\libgpp.dll obj\*.o %GLFW% -lopengl32 %GLEW% -lmingw32 -lmingwex -lgdi32
endlocal