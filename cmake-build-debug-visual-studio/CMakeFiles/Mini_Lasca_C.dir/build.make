# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\PayThePizzo\Sites\Mini-Lasca-C

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\PayThePizzo\Sites\Mini-Lasca-C\cmake-build-debug-visual-studio

# Include any dependencies generated for this target.
include CMakeFiles\Mini_Lasca_C.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\Mini_Lasca_C.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\Mini_Lasca_C.dir\flags.make

CMakeFiles\Mini_Lasca_C.dir\laska.c.obj: CMakeFiles\Mini_Lasca_C.dir\flags.make
CMakeFiles\Mini_Lasca_C.dir\laska.c.obj: ..\laska.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\PayThePizzo\Sites\Mini-Lasca-C\cmake-build-debug-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Mini_Lasca_C.dir/laska.c.obj"
	C:\PROGRA~2\MICROS~2\2019\PROFES~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\Mini_Lasca_C.dir\laska.c.obj /FdCMakeFiles\Mini_Lasca_C.dir\ /FS -c C:\Users\PayThePizzo\Sites\Mini-Lasca-C\laska.c
<<

CMakeFiles\Mini_Lasca_C.dir\laska.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Mini_Lasca_C.dir/laska.c.i"
	C:\PROGRA~2\MICROS~2\2019\PROFES~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe > CMakeFiles\Mini_Lasca_C.dir\laska.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\PayThePizzo\Sites\Mini-Lasca-C\laska.c
<<

CMakeFiles\Mini_Lasca_C.dir\laska.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Mini_Lasca_C.dir/laska.c.s"
	C:\PROGRA~2\MICROS~2\2019\PROFES~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\Mini_Lasca_C.dir\laska.c.s /c C:\Users\PayThePizzo\Sites\Mini-Lasca-C\laska.c
<<

CMakeFiles\Mini_Lasca_C.dir\main.c.obj: CMakeFiles\Mini_Lasca_C.dir\flags.make
CMakeFiles\Mini_Lasca_C.dir\main.c.obj: ..\main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\PayThePizzo\Sites\Mini-Lasca-C\cmake-build-debug-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Mini_Lasca_C.dir/main.c.obj"
	C:\PROGRA~2\MICROS~2\2019\PROFES~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\Mini_Lasca_C.dir\main.c.obj /FdCMakeFiles\Mini_Lasca_C.dir\ /FS -c C:\Users\PayThePizzo\Sites\Mini-Lasca-C\main.c
<<

CMakeFiles\Mini_Lasca_C.dir\main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Mini_Lasca_C.dir/main.c.i"
	C:\PROGRA~2\MICROS~2\2019\PROFES~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe > CMakeFiles\Mini_Lasca_C.dir\main.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\PayThePizzo\Sites\Mini-Lasca-C\main.c
<<

CMakeFiles\Mini_Lasca_C.dir\main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Mini_Lasca_C.dir/main.c.s"
	C:\PROGRA~2\MICROS~2\2019\PROFES~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\Mini_Lasca_C.dir\main.c.s /c C:\Users\PayThePizzo\Sites\Mini-Lasca-C\main.c
<<

# Object files for target Mini_Lasca_C
Mini_Lasca_C_OBJECTS = \
"CMakeFiles\Mini_Lasca_C.dir\laska.c.obj" \
"CMakeFiles\Mini_Lasca_C.dir\main.c.obj"

# External object files for target Mini_Lasca_C
Mini_Lasca_C_EXTERNAL_OBJECTS =

Mini_Lasca_C.exe: CMakeFiles\Mini_Lasca_C.dir\laska.c.obj
Mini_Lasca_C.exe: CMakeFiles\Mini_Lasca_C.dir\main.c.obj
Mini_Lasca_C.exe: CMakeFiles\Mini_Lasca_C.dir\build.make
Mini_Lasca_C.exe: CMakeFiles\Mini_Lasca_C.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\PayThePizzo\Sites\Mini-Lasca-C\cmake-build-debug-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable Mini_Lasca_C.exe"
	"C:\Program Files\JetBrains\CLion 2020.3\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\Mini_Lasca_C.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~2\2019\PROFES~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\Mini_Lasca_C.dir\objects1.rsp @<<
 /out:Mini_Lasca_C.exe /implib:Mini_Lasca_C.lib /pdb:C:\Users\PayThePizzo\Sites\Mini-Lasca-C\cmake-build-debug-visual-studio\Mini_Lasca_C.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\Mini_Lasca_C.dir\build: Mini_Lasca_C.exe

.PHONY : CMakeFiles\Mini_Lasca_C.dir\build

CMakeFiles\Mini_Lasca_C.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Mini_Lasca_C.dir\cmake_clean.cmake
.PHONY : CMakeFiles\Mini_Lasca_C.dir\clean

CMakeFiles\Mini_Lasca_C.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\PayThePizzo\Sites\Mini-Lasca-C C:\Users\PayThePizzo\Sites\Mini-Lasca-C C:\Users\PayThePizzo\Sites\Mini-Lasca-C\cmake-build-debug-visual-studio C:\Users\PayThePizzo\Sites\Mini-Lasca-C\cmake-build-debug-visual-studio C:\Users\PayThePizzo\Sites\Mini-Lasca-C\cmake-build-debug-visual-studio\CMakeFiles\Mini_Lasca_C.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\Mini_Lasca_C.dir\depend

