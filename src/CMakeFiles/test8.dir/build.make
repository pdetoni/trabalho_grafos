# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/src"

# Include any dependencies generated for this target.
include CMakeFiles/test8.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test8.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test8.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test8.dir/flags.make

CMakeFiles/test8.dir/tests/test8.cpp.o: CMakeFiles/test8.dir/flags.make
CMakeFiles/test8.dir/tests/test8.cpp.o: /mnt/c/users/Peleão\ Prapão/documents/github/trabalho_grafos/tests/test8.cpp
CMakeFiles/test8.dir/tests/test8.cpp.o: CMakeFiles/test8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/src/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test8.dir/tests/test8.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test8.dir/tests/test8.cpp.o -MF CMakeFiles/test8.dir/tests/test8.cpp.o.d -o CMakeFiles/test8.dir/tests/test8.cpp.o -c "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/tests/test8.cpp"

CMakeFiles/test8.dir/tests/test8.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test8.dir/tests/test8.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/tests/test8.cpp" > CMakeFiles/test8.dir/tests/test8.cpp.i

CMakeFiles/test8.dir/tests/test8.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test8.dir/tests/test8.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/tests/test8.cpp" -o CMakeFiles/test8.dir/tests/test8.cpp.s

CMakeFiles/test8.dir/Grafo.cpp.o: CMakeFiles/test8.dir/flags.make
CMakeFiles/test8.dir/Grafo.cpp.o: Grafo.cpp
CMakeFiles/test8.dir/Grafo.cpp.o: CMakeFiles/test8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/src/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test8.dir/Grafo.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test8.dir/Grafo.cpp.o -MF CMakeFiles/test8.dir/Grafo.cpp.o.d -o CMakeFiles/test8.dir/Grafo.cpp.o -c "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/src/Grafo.cpp"

CMakeFiles/test8.dir/Grafo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test8.dir/Grafo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/src/Grafo.cpp" > CMakeFiles/test8.dir/Grafo.cpp.i

CMakeFiles/test8.dir/Grafo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test8.dir/Grafo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/src/Grafo.cpp" -o CMakeFiles/test8.dir/Grafo.cpp.s

CMakeFiles/test8.dir/GrafoLista.cpp.o: CMakeFiles/test8.dir/flags.make
CMakeFiles/test8.dir/GrafoLista.cpp.o: GrafoLista.cpp
CMakeFiles/test8.dir/GrafoLista.cpp.o: CMakeFiles/test8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/src/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/test8.dir/GrafoLista.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test8.dir/GrafoLista.cpp.o -MF CMakeFiles/test8.dir/GrafoLista.cpp.o.d -o CMakeFiles/test8.dir/GrafoLista.cpp.o -c "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/src/GrafoLista.cpp"

CMakeFiles/test8.dir/GrafoLista.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test8.dir/GrafoLista.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/src/GrafoLista.cpp" > CMakeFiles/test8.dir/GrafoLista.cpp.i

CMakeFiles/test8.dir/GrafoLista.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test8.dir/GrafoLista.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/src/GrafoLista.cpp" -o CMakeFiles/test8.dir/GrafoLista.cpp.s

CMakeFiles/test8.dir/GrafoMatriz.cpp.o: CMakeFiles/test8.dir/flags.make
CMakeFiles/test8.dir/GrafoMatriz.cpp.o: GrafoMatriz.cpp
CMakeFiles/test8.dir/GrafoMatriz.cpp.o: CMakeFiles/test8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/src/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/test8.dir/GrafoMatriz.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test8.dir/GrafoMatriz.cpp.o -MF CMakeFiles/test8.dir/GrafoMatriz.cpp.o.d -o CMakeFiles/test8.dir/GrafoMatriz.cpp.o -c "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/src/GrafoMatriz.cpp"

CMakeFiles/test8.dir/GrafoMatriz.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test8.dir/GrafoMatriz.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/src/GrafoMatriz.cpp" > CMakeFiles/test8.dir/GrafoMatriz.cpp.i

CMakeFiles/test8.dir/GrafoMatriz.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test8.dir/GrafoMatriz.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/src/GrafoMatriz.cpp" -o CMakeFiles/test8.dir/GrafoMatriz.cpp.s

# Object files for target test8
test8_OBJECTS = \
"CMakeFiles/test8.dir/tests/test8.cpp.o" \
"CMakeFiles/test8.dir/Grafo.cpp.o" \
"CMakeFiles/test8.dir/GrafoLista.cpp.o" \
"CMakeFiles/test8.dir/GrafoMatriz.cpp.o"

# External object files for target test8
test8_EXTERNAL_OBJECTS =

test8: CMakeFiles/test8.dir/tests/test8.cpp.o
test8: CMakeFiles/test8.dir/Grafo.cpp.o
test8: CMakeFiles/test8.dir/GrafoLista.cpp.o
test8: CMakeFiles/test8.dir/GrafoMatriz.cpp.o
test8: CMakeFiles/test8.dir/build.make
test8: CMakeFiles/test8.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/src/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable test8"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test8.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -E copy_directory /mnt/c/users/Peleão\ Prapão/documents/github/trabalho_grafos/entradas /mnt/c/users/Peleão\ Prapão/documents/github/trabalho_grafos/src/entradas

# Rule to build all files generated by this target.
CMakeFiles/test8.dir/build: test8
.PHONY : CMakeFiles/test8.dir/build

CMakeFiles/test8.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test8.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test8.dir/clean

CMakeFiles/test8.dir/depend:
	cd "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/src" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos" "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos" "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/src" "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/src" "/mnt/c/users/Peleão Prapão/documents/github/trabalho_grafos/src/CMakeFiles/test8.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/test8.dir/depend

