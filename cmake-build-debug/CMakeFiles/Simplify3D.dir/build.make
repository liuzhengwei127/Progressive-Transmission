# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\75667\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\191.6707.69\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\75667\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\191.6707.69\bin\cmake\win\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\75667\CLionProjects\Simplify3D

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\75667\CLionProjects\Simplify3D\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\Simplify3D.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\Simplify3D.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\Simplify3D.dir\flags.make

CMakeFiles\Simplify3D.dir\main.cpp.obj: CMakeFiles\Simplify3D.dir\flags.make
CMakeFiles\Simplify3D.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\75667\CLionProjects\Simplify3D\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Simplify3D.dir/main.cpp.obj"
	C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1414~1.264\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Simplify3D.dir\main.cpp.obj /FdCMakeFiles\Simplify3D.dir\ /FS -c C:\Users\75667\CLionProjects\Simplify3D\main.cpp
<<

CMakeFiles\Simplify3D.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Simplify3D.dir/main.cpp.i"
	C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1414~1.264\bin\Hostx86\x86\cl.exe > CMakeFiles\Simplify3D.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\75667\CLionProjects\Simplify3D\main.cpp
<<

CMakeFiles\Simplify3D.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Simplify3D.dir/main.cpp.s"
	C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1414~1.264\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Simplify3D.dir\main.cpp.s /c C:\Users\75667\CLionProjects\Simplify3D\main.cpp
<<

# Object files for target Simplify3D
Simplify3D_OBJECTS = \
"CMakeFiles\Simplify3D.dir\main.cpp.obj"

# External object files for target Simplify3D
Simplify3D_EXTERNAL_OBJECTS =

Simplify3D.exe: CMakeFiles\Simplify3D.dir\main.cpp.obj
Simplify3D.exe: CMakeFiles\Simplify3D.dir\build.make
Simplify3D.exe: CMakeFiles\Simplify3D.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\75667\CLionProjects\Simplify3D\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Simplify3D.exe"
	C:\Users\75667\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\191.6707.69\bin\cmake\win\bin\cmake.exe -E vs_link_exe --intdir=CMakeFiles\Simplify3D.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100171~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100171~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1414~1.264\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\Simplify3D.dir\objects1.rsp @<<
 /out:Simplify3D.exe /implib:Simplify3D.lib /pdb:C:\Users\75667\CLionProjects\Simplify3D\cmake-build-debug\Simplify3D.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\Simplify3D.dir\build: Simplify3D.exe

.PHONY : CMakeFiles\Simplify3D.dir\build

CMakeFiles\Simplify3D.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Simplify3D.dir\cmake_clean.cmake
.PHONY : CMakeFiles\Simplify3D.dir\clean

CMakeFiles\Simplify3D.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\75667\CLionProjects\Simplify3D C:\Users\75667\CLionProjects\Simplify3D C:\Users\75667\CLionProjects\Simplify3D\cmake-build-debug C:\Users\75667\CLionProjects\Simplify3D\cmake-build-debug C:\Users\75667\CLionProjects\Simplify3D\cmake-build-debug\CMakeFiles\Simplify3D.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\Simplify3D.dir\depend

