# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rak/Documents/Corium

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rak/Documents/Corium

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/rak/Documents/Corium/CMakeFiles /home/rak/Documents/Corium/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/rak/Documents/Corium/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Corium

# Build rule for target.
Corium: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Corium
.PHONY : Corium

# fast build rule for target.
Corium/fast:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/build
.PHONY : Corium/fast

src/anim.o: src/anim.cpp.o

.PHONY : src/anim.o

# target to build an object file
src/anim.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/anim.cpp.o
.PHONY : src/anim.cpp.o

src/anim.i: src/anim.cpp.i

.PHONY : src/anim.i

# target to preprocess a source file
src/anim.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/anim.cpp.i
.PHONY : src/anim.cpp.i

src/anim.s: src/anim.cpp.s

.PHONY : src/anim.s

# target to generate assembly for a file
src/anim.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/anim.cpp.s
.PHONY : src/anim.cpp.s

src/audio.o: src/audio.cpp.o

.PHONY : src/audio.o

# target to build an object file
src/audio.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/audio.cpp.o
.PHONY : src/audio.cpp.o

src/audio.i: src/audio.cpp.i

.PHONY : src/audio.i

# target to preprocess a source file
src/audio.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/audio.cpp.i
.PHONY : src/audio.cpp.i

src/audio.s: src/audio.cpp.s

.PHONY : src/audio.s

# target to generate assembly for a file
src/audio.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/audio.cpp.s
.PHONY : src/audio.cpp.s

src/game/entity/entity.o: src/game/entity/entity.cpp.o

.PHONY : src/game/entity/entity.o

# target to build an object file
src/game/entity/entity.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/entity/entity.cpp.o
.PHONY : src/game/entity/entity.cpp.o

src/game/entity/entity.i: src/game/entity/entity.cpp.i

.PHONY : src/game/entity/entity.i

# target to preprocess a source file
src/game/entity/entity.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/entity/entity.cpp.i
.PHONY : src/game/entity/entity.cpp.i

src/game/entity/entity.s: src/game/entity/entity.cpp.s

.PHONY : src/game/entity/entity.s

# target to generate assembly for a file
src/game/entity/entity.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/entity/entity.cpp.s
.PHONY : src/game/entity/entity.cpp.s

src/game/entity/player.o: src/game/entity/player.cpp.o

.PHONY : src/game/entity/player.o

# target to build an object file
src/game/entity/player.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/entity/player.cpp.o
.PHONY : src/game/entity/player.cpp.o

src/game/entity/player.i: src/game/entity/player.cpp.i

.PHONY : src/game/entity/player.i

# target to preprocess a source file
src/game/entity/player.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/entity/player.cpp.i
.PHONY : src/game/entity/player.cpp.i

src/game/entity/player.s: src/game/entity/player.cpp.s

.PHONY : src/game/entity/player.s

# target to generate assembly for a file
src/game/entity/player.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/entity/player.cpp.s
.PHONY : src/game/entity/player.cpp.s

src/game/game.o: src/game/game.cpp.o

.PHONY : src/game/game.o

# target to build an object file
src/game/game.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/game.cpp.o
.PHONY : src/game/game.cpp.o

src/game/game.i: src/game/game.cpp.i

.PHONY : src/game/game.i

# target to preprocess a source file
src/game/game.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/game.cpp.i
.PHONY : src/game/game.cpp.i

src/game/game.s: src/game/game.cpp.s

.PHONY : src/game/game.s

# target to generate assembly for a file
src/game/game.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/game.cpp.s
.PHONY : src/game/game.cpp.s

src/game/gameInput.o: src/game/gameInput.cpp.o

.PHONY : src/game/gameInput.o

# target to build an object file
src/game/gameInput.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/gameInput.cpp.o
.PHONY : src/game/gameInput.cpp.o

src/game/gameInput.i: src/game/gameInput.cpp.i

.PHONY : src/game/gameInput.i

# target to preprocess a source file
src/game/gameInput.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/gameInput.cpp.i
.PHONY : src/game/gameInput.cpp.i

src/game/gameInput.s: src/game/gameInput.cpp.s

.PHONY : src/game/gameInput.s

# target to generate assembly for a file
src/game/gameInput.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/gameInput.cpp.s
.PHONY : src/game/gameInput.cpp.s

src/game/gameRender.o: src/game/gameRender.cpp.o

.PHONY : src/game/gameRender.o

# target to build an object file
src/game/gameRender.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/gameRender.cpp.o
.PHONY : src/game/gameRender.cpp.o

src/game/gameRender.i: src/game/gameRender.cpp.i

.PHONY : src/game/gameRender.i

# target to preprocess a source file
src/game/gameRender.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/gameRender.cpp.i
.PHONY : src/game/gameRender.cpp.i

src/game/gameRender.s: src/game/gameRender.cpp.s

.PHONY : src/game/gameRender.s

# target to generate assembly for a file
src/game/gameRender.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/gameRender.cpp.s
.PHONY : src/game/gameRender.cpp.s

src/game/obj/camera.o: src/game/obj/camera.cpp.o

.PHONY : src/game/obj/camera.o

# target to build an object file
src/game/obj/camera.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/obj/camera.cpp.o
.PHONY : src/game/obj/camera.cpp.o

src/game/obj/camera.i: src/game/obj/camera.cpp.i

.PHONY : src/game/obj/camera.i

# target to preprocess a source file
src/game/obj/camera.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/obj/camera.cpp.i
.PHONY : src/game/obj/camera.cpp.i

src/game/obj/camera.s: src/game/obj/camera.cpp.s

.PHONY : src/game/obj/camera.s

# target to generate assembly for a file
src/game/obj/camera.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/obj/camera.cpp.s
.PHONY : src/game/obj/camera.cpp.s

src/game/obj/obj.o: src/game/obj/obj.cpp.o

.PHONY : src/game/obj/obj.o

# target to build an object file
src/game/obj/obj.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/obj/obj.cpp.o
.PHONY : src/game/obj/obj.cpp.o

src/game/obj/obj.i: src/game/obj/obj.cpp.i

.PHONY : src/game/obj/obj.i

# target to preprocess a source file
src/game/obj/obj.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/obj/obj.cpp.i
.PHONY : src/game/obj/obj.cpp.i

src/game/obj/obj.s: src/game/obj/obj.cpp.s

.PHONY : src/game/obj/obj.s

# target to generate assembly for a file
src/game/obj/obj.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/obj/obj.cpp.s
.PHONY : src/game/obj/obj.cpp.s

src/game/tick.o: src/game/tick.cpp.o

.PHONY : src/game/tick.o

# target to build an object file
src/game/tick.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/tick.cpp.o
.PHONY : src/game/tick.cpp.o

src/game/tick.i: src/game/tick.cpp.i

.PHONY : src/game/tick.i

# target to preprocess a source file
src/game/tick.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/tick.cpp.i
.PHONY : src/game/tick.cpp.i

src/game/tick.s: src/game/tick.cpp.s

.PHONY : src/game/tick.s

# target to generate assembly for a file
src/game/tick.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/tick.cpp.s
.PHONY : src/game/tick.cpp.s

src/game/world/map.o: src/game/world/map.cpp.o

.PHONY : src/game/world/map.o

# target to build an object file
src/game/world/map.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/world/map.cpp.o
.PHONY : src/game/world/map.cpp.o

src/game/world/map.i: src/game/world/map.cpp.i

.PHONY : src/game/world/map.i

# target to preprocess a source file
src/game/world/map.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/world/map.cpp.i
.PHONY : src/game/world/map.cpp.i

src/game/world/map.s: src/game/world/map.cpp.s

.PHONY : src/game/world/map.s

# target to generate assembly for a file
src/game/world/map.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/game/world/map.cpp.s
.PHONY : src/game/world/map.cpp.s

src/gui/gui.o: src/gui/gui.cpp.o

.PHONY : src/gui/gui.o

# target to build an object file
src/gui/gui.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/gui/gui.cpp.o
.PHONY : src/gui/gui.cpp.o

src/gui/gui.i: src/gui/gui.cpp.i

.PHONY : src/gui/gui.i

# target to preprocess a source file
src/gui/gui.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/gui/gui.cpp.i
.PHONY : src/gui/gui.cpp.i

src/gui/gui.s: src/gui/gui.cpp.s

.PHONY : src/gui/gui.s

# target to generate assembly for a file
src/gui/gui.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/gui/gui.cpp.s
.PHONY : src/gui/gui.cpp.s

src/input.o: src/input.cpp.o

.PHONY : src/input.o

# target to build an object file
src/input.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/input.cpp.o
.PHONY : src/input.cpp.o

src/input.i: src/input.cpp.i

.PHONY : src/input.i

# target to preprocess a source file
src/input.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/input.cpp.i
.PHONY : src/input.cpp.i

src/input.s: src/input.cpp.s

.PHONY : src/input.s

# target to generate assembly for a file
src/input.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/input.cpp.s
.PHONY : src/input.cpp.s

src/main.o: src/main.cpp.o

.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/mesh.o: src/mesh.cpp.o

.PHONY : src/mesh.o

# target to build an object file
src/mesh.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/mesh.cpp.o
.PHONY : src/mesh.cpp.o

src/mesh.i: src/mesh.cpp.i

.PHONY : src/mesh.i

# target to preprocess a source file
src/mesh.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/mesh.cpp.i
.PHONY : src/mesh.cpp.i

src/mesh.s: src/mesh.cpp.s

.PHONY : src/mesh.s

# target to generate assembly for a file
src/mesh.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/mesh.cpp.s
.PHONY : src/mesh.cpp.s

src/phys/phys.o: src/phys/phys.cpp.o

.PHONY : src/phys/phys.o

# target to build an object file
src/phys/phys.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/phys/phys.cpp.o
.PHONY : src/phys/phys.cpp.o

src/phys/phys.i: src/phys/phys.cpp.i

.PHONY : src/phys/phys.i

# target to preprocess a source file
src/phys/phys.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/phys/phys.cpp.i
.PHONY : src/phys/phys.cpp.i

src/phys/phys.s: src/phys/phys.cpp.s

.PHONY : src/phys/phys.s

# target to generate assembly for a file
src/phys/phys.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/phys/phys.cpp.s
.PHONY : src/phys/phys.cpp.s

src/phys/sys.o: src/phys/sys.cpp.o

.PHONY : src/phys/sys.o

# target to build an object file
src/phys/sys.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/phys/sys.cpp.o
.PHONY : src/phys/sys.cpp.o

src/phys/sys.i: src/phys/sys.cpp.i

.PHONY : src/phys/sys.i

# target to preprocess a source file
src/phys/sys.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/phys/sys.cpp.i
.PHONY : src/phys/sys.cpp.i

src/phys/sys.s: src/phys/sys.cpp.s

.PHONY : src/phys/sys.s

# target to generate assembly for a file
src/phys/sys.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/phys/sys.cpp.s
.PHONY : src/phys/sys.cpp.s

src/render/renderer.o: src/render/renderer.cpp.o

.PHONY : src/render/renderer.o

# target to build an object file
src/render/renderer.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/render/renderer.cpp.o
.PHONY : src/render/renderer.cpp.o

src/render/renderer.i: src/render/renderer.cpp.i

.PHONY : src/render/renderer.i

# target to preprocess a source file
src/render/renderer.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/render/renderer.cpp.i
.PHONY : src/render/renderer.cpp.i

src/render/renderer.s: src/render/renderer.cpp.s

.PHONY : src/render/renderer.s

# target to generate assembly for a file
src/render/renderer.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/render/renderer.cpp.s
.PHONY : src/render/renderer.cpp.s

src/render/shader/shader.o: src/render/shader/shader.cpp.o

.PHONY : src/render/shader/shader.o

# target to build an object file
src/render/shader/shader.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/render/shader/shader.cpp.o
.PHONY : src/render/shader/shader.cpp.o

src/render/shader/shader.i: src/render/shader/shader.cpp.i

.PHONY : src/render/shader/shader.i

# target to preprocess a source file
src/render/shader/shader.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/render/shader/shader.cpp.i
.PHONY : src/render/shader/shader.cpp.i

src/render/shader/shader.s: src/render/shader/shader.cpp.s

.PHONY : src/render/shader/shader.s

# target to generate assembly for a file
src/render/shader/shader.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/render/shader/shader.cpp.s
.PHONY : src/render/shader/shader.cpp.s

src/sprite.o: src/sprite.cpp.o

.PHONY : src/sprite.o

# target to build an object file
src/sprite.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/sprite.cpp.o
.PHONY : src/sprite.cpp.o

src/sprite.i: src/sprite.cpp.i

.PHONY : src/sprite.i

# target to preprocess a source file
src/sprite.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/sprite.cpp.i
.PHONY : src/sprite.cpp.i

src/sprite.s: src/sprite.cpp.s

.PHONY : src/sprite.s

# target to generate assembly for a file
src/sprite.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/sprite.cpp.s
.PHONY : src/sprite.cpp.s

src/texture.o: src/texture.cpp.o

.PHONY : src/texture.o

# target to build an object file
src/texture.cpp.o:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/texture.cpp.o
.PHONY : src/texture.cpp.o

src/texture.i: src/texture.cpp.i

.PHONY : src/texture.i

# target to preprocess a source file
src/texture.cpp.i:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/texture.cpp.i
.PHONY : src/texture.cpp.i

src/texture.s: src/texture.cpp.s

.PHONY : src/texture.s

# target to generate assembly for a file
src/texture.cpp.s:
	$(MAKE) -f CMakeFiles/Corium.dir/build.make CMakeFiles/Corium.dir/src/texture.cpp.s
.PHONY : src/texture.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... Corium"
	@echo "... edit_cache"
	@echo "... src/anim.o"
	@echo "... src/anim.i"
	@echo "... src/anim.s"
	@echo "... src/audio.o"
	@echo "... src/audio.i"
	@echo "... src/audio.s"
	@echo "... src/game/entity/entity.o"
	@echo "... src/game/entity/entity.i"
	@echo "... src/game/entity/entity.s"
	@echo "... src/game/entity/player.o"
	@echo "... src/game/entity/player.i"
	@echo "... src/game/entity/player.s"
	@echo "... src/game/game.o"
	@echo "... src/game/game.i"
	@echo "... src/game/game.s"
	@echo "... src/game/gameInput.o"
	@echo "... src/game/gameInput.i"
	@echo "... src/game/gameInput.s"
	@echo "... src/game/gameRender.o"
	@echo "... src/game/gameRender.i"
	@echo "... src/game/gameRender.s"
	@echo "... src/game/obj/camera.o"
	@echo "... src/game/obj/camera.i"
	@echo "... src/game/obj/camera.s"
	@echo "... src/game/obj/obj.o"
	@echo "... src/game/obj/obj.i"
	@echo "... src/game/obj/obj.s"
	@echo "... src/game/tick.o"
	@echo "... src/game/tick.i"
	@echo "... src/game/tick.s"
	@echo "... src/game/world/map.o"
	@echo "... src/game/world/map.i"
	@echo "... src/game/world/map.s"
	@echo "... src/gui/gui.o"
	@echo "... src/gui/gui.i"
	@echo "... src/gui/gui.s"
	@echo "... src/input.o"
	@echo "... src/input.i"
	@echo "... src/input.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/mesh.o"
	@echo "... src/mesh.i"
	@echo "... src/mesh.s"
	@echo "... src/phys/phys.o"
	@echo "... src/phys/phys.i"
	@echo "... src/phys/phys.s"
	@echo "... src/phys/sys.o"
	@echo "... src/phys/sys.i"
	@echo "... src/phys/sys.s"
	@echo "... src/render/renderer.o"
	@echo "... src/render/renderer.i"
	@echo "... src/render/renderer.s"
	@echo "... src/render/shader/shader.o"
	@echo "... src/render/shader/shader.i"
	@echo "... src/render/shader/shader.s"
	@echo "... src/sprite.o"
	@echo "... src/sprite.i"
	@echo "... src/sprite.s"
	@echo "... src/texture.o"
	@echo "... src/texture.i"
	@echo "... src/texture.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

