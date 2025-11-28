@echo off
setlocal enabledelayedexpansion

REM --- include paths ---

set build_defs=

set INC1=..\src
set INC2=C:\CPP Libs\poly2tri
set INC3=C:\CPP Libs\Clipper2\Clipper2Lib\include
set INC4=C:\CPP Libs\glfw-3.3.8\glfw-3.3.8\include
set INC5=C:\CPP Libs\glew-2.1.0-win32\glew-2.1.0\include
set INC6=C:\CPP Libs\glm
set INC7=C:\CPP Libs\imgui-1.90.4
set INC8=C:\CPP Libs\simdjson\singleheader
set INC9=C:\CPP Libs\CXXGraph\include

set args=-I"%INC1%" -I"%INC2%" -I"%INC3%" -I"%INC4%" -I"%INC5%" -I"%INC6%" -I"%INC8%" -I"%INC9%"

set GLFW=-L"C:\CPP Libs\glfw-3.3.8.bin.WIN64\lib-mingw-w64" -lglfw3
set GLEW=-L"C:\CPP Libs\glew-2.1.0-win32\glew-2.1.0\bin\Release\x64" -lglew32

if not exist obj mkdir obj

for /r "%INC2%\poly2tri" %%f in (*.cc) do (
    echo Compiling %%f
    clang++ -std=c++17 -g -c -I"%INC2%" "%%f" -o "obj\%%~nf.o"
)

    clang++ -std=c++17 -g -c -I"%INC8%" "%INC8%\simdjson.cpp" -o "obj\simdjson.o"

if "%1"=="imgui" (
    set build_defs=%build_defs% -DIMGUI

    set args=!args! -I"%INC7%"

    for %%f in ("%INC7%\imgui.cpp" "%INC7%\imgui_draw.cpp" "%INC7%\imgui_tables.cpp" "%INC7%\imgui_widgets.cpp") do (
        echo Compiling %%f
        clang++ -std=c++17 -g -c %args% %%f -o "obj\%%~nf.o"
    )

    clang++ -std=c++17 -g -c -I"%INC7%" -I"%INC4%" "%INC7%\backends\imgui_impl_opengl3.cpp" -o "obj\imgui_impl_opengl3.o"
    clang++ -std=c++17 -g -c -I"%INC7%" -I"%INC4%" "%INC7%\backends\imgui_impl_glfw.cpp" -o "obj\imgui_impl_glfw.o"
)

REM --- scan files recursively ---

for /r ..\src %%f in (*.cpp) do (
        echo Compiling %%f
        clang++ -std=c++17 -g -c %args% !build_defs! %%f -o "obj\%%~nf.o"
)

REM --- create library ---
clang++ -std=c++17 -g %args% -shared -o ..\libgpp.dll obj\*.o %GLFW% -lopengl32 %GLEW% -lgdi32
endlocal