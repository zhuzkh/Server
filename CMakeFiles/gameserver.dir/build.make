# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /mnt/d/GitHub/Asio/Asio/Server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/GitHub/Asio/Asio/Server

# Include any dependencies generated for this target.
include CMakeFiles/gameserver.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gameserver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gameserver.dir/flags.make

CMakeFiles/gameserver.dir/AsioAcceptor.o: CMakeFiles/gameserver.dir/flags.make
CMakeFiles/gameserver.dir/AsioAcceptor.o: AsioAcceptor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gameserver.dir/AsioAcceptor.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameserver.dir/AsioAcceptor.o -c /mnt/d/GitHub/Asio/Asio/Server/AsioAcceptor.cpp

CMakeFiles/gameserver.dir/AsioAcceptor.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameserver.dir/AsioAcceptor.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/GitHub/Asio/Asio/Server/AsioAcceptor.cpp > CMakeFiles/gameserver.dir/AsioAcceptor.i

CMakeFiles/gameserver.dir/AsioAcceptor.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameserver.dir/AsioAcceptor.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/GitHub/Asio/Asio/Server/AsioAcceptor.cpp -o CMakeFiles/gameserver.dir/AsioAcceptor.s

CMakeFiles/gameserver.dir/AsioAcceptor.o.requires:

.PHONY : CMakeFiles/gameserver.dir/AsioAcceptor.o.requires

CMakeFiles/gameserver.dir/AsioAcceptor.o.provides: CMakeFiles/gameserver.dir/AsioAcceptor.o.requires
	$(MAKE) -f CMakeFiles/gameserver.dir/build.make CMakeFiles/gameserver.dir/AsioAcceptor.o.provides.build
.PHONY : CMakeFiles/gameserver.dir/AsioAcceptor.o.provides

CMakeFiles/gameserver.dir/AsioAcceptor.o.provides.build: CMakeFiles/gameserver.dir/AsioAcceptor.o


CMakeFiles/gameserver.dir/AsioSocket.o: CMakeFiles/gameserver.dir/flags.make
CMakeFiles/gameserver.dir/AsioSocket.o: AsioSocket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/gameserver.dir/AsioSocket.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameserver.dir/AsioSocket.o -c /mnt/d/GitHub/Asio/Asio/Server/AsioSocket.cpp

CMakeFiles/gameserver.dir/AsioSocket.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameserver.dir/AsioSocket.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/GitHub/Asio/Asio/Server/AsioSocket.cpp > CMakeFiles/gameserver.dir/AsioSocket.i

CMakeFiles/gameserver.dir/AsioSocket.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameserver.dir/AsioSocket.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/GitHub/Asio/Asio/Server/AsioSocket.cpp -o CMakeFiles/gameserver.dir/AsioSocket.s

CMakeFiles/gameserver.dir/AsioSocket.o.requires:

.PHONY : CMakeFiles/gameserver.dir/AsioSocket.o.requires

CMakeFiles/gameserver.dir/AsioSocket.o.provides: CMakeFiles/gameserver.dir/AsioSocket.o.requires
	$(MAKE) -f CMakeFiles/gameserver.dir/build.make CMakeFiles/gameserver.dir/AsioSocket.o.provides.build
.PHONY : CMakeFiles/gameserver.dir/AsioSocket.o.provides

CMakeFiles/gameserver.dir/AsioSocket.o.provides.build: CMakeFiles/gameserver.dir/AsioSocket.o


CMakeFiles/gameserver.dir/Logger.o: CMakeFiles/gameserver.dir/flags.make
CMakeFiles/gameserver.dir/Logger.o: Logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/gameserver.dir/Logger.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameserver.dir/Logger.o -c /mnt/d/GitHub/Asio/Asio/Server/Logger.cpp

CMakeFiles/gameserver.dir/Logger.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameserver.dir/Logger.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/GitHub/Asio/Asio/Server/Logger.cpp > CMakeFiles/gameserver.dir/Logger.i

CMakeFiles/gameserver.dir/Logger.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameserver.dir/Logger.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/GitHub/Asio/Asio/Server/Logger.cpp -o CMakeFiles/gameserver.dir/Logger.s

CMakeFiles/gameserver.dir/Logger.o.requires:

.PHONY : CMakeFiles/gameserver.dir/Logger.o.requires

CMakeFiles/gameserver.dir/Logger.o.provides: CMakeFiles/gameserver.dir/Logger.o.requires
	$(MAKE) -f CMakeFiles/gameserver.dir/build.make CMakeFiles/gameserver.dir/Logger.o.provides.build
.PHONY : CMakeFiles/gameserver.dir/Logger.o.provides

CMakeFiles/gameserver.dir/Logger.o.provides.build: CMakeFiles/gameserver.dir/Logger.o


CMakeFiles/gameserver.dir/LogicSystem.o: CMakeFiles/gameserver.dir/flags.make
CMakeFiles/gameserver.dir/LogicSystem.o: LogicSystem.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/gameserver.dir/LogicSystem.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameserver.dir/LogicSystem.o -c /mnt/d/GitHub/Asio/Asio/Server/LogicSystem.cpp

CMakeFiles/gameserver.dir/LogicSystem.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameserver.dir/LogicSystem.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/GitHub/Asio/Asio/Server/LogicSystem.cpp > CMakeFiles/gameserver.dir/LogicSystem.i

CMakeFiles/gameserver.dir/LogicSystem.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameserver.dir/LogicSystem.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/GitHub/Asio/Asio/Server/LogicSystem.cpp -o CMakeFiles/gameserver.dir/LogicSystem.s

CMakeFiles/gameserver.dir/LogicSystem.o.requires:

.PHONY : CMakeFiles/gameserver.dir/LogicSystem.o.requires

CMakeFiles/gameserver.dir/LogicSystem.o.provides: CMakeFiles/gameserver.dir/LogicSystem.o.requires
	$(MAKE) -f CMakeFiles/gameserver.dir/build.make CMakeFiles/gameserver.dir/LogicSystem.o.provides.build
.PHONY : CMakeFiles/gameserver.dir/LogicSystem.o.provides

CMakeFiles/gameserver.dir/LogicSystem.o.provides.build: CMakeFiles/gameserver.dir/LogicSystem.o


CMakeFiles/gameserver.dir/Main.o: CMakeFiles/gameserver.dir/flags.make
CMakeFiles/gameserver.dir/Main.o: Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/gameserver.dir/Main.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameserver.dir/Main.o -c /mnt/d/GitHub/Asio/Asio/Server/Main.cpp

CMakeFiles/gameserver.dir/Main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameserver.dir/Main.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/GitHub/Asio/Asio/Server/Main.cpp > CMakeFiles/gameserver.dir/Main.i

CMakeFiles/gameserver.dir/Main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameserver.dir/Main.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/GitHub/Asio/Asio/Server/Main.cpp -o CMakeFiles/gameserver.dir/Main.s

CMakeFiles/gameserver.dir/Main.o.requires:

.PHONY : CMakeFiles/gameserver.dir/Main.o.requires

CMakeFiles/gameserver.dir/Main.o.provides: CMakeFiles/gameserver.dir/Main.o.requires
	$(MAKE) -f CMakeFiles/gameserver.dir/build.make CMakeFiles/gameserver.dir/Main.o.provides.build
.PHONY : CMakeFiles/gameserver.dir/Main.o.provides

CMakeFiles/gameserver.dir/Main.o.provides.build: CMakeFiles/gameserver.dir/Main.o


CMakeFiles/gameserver.dir/ManagerModule.o: CMakeFiles/gameserver.dir/flags.make
CMakeFiles/gameserver.dir/ManagerModule.o: ManagerModule.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/gameserver.dir/ManagerModule.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameserver.dir/ManagerModule.o -c /mnt/d/GitHub/Asio/Asio/Server/ManagerModule.cpp

CMakeFiles/gameserver.dir/ManagerModule.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameserver.dir/ManagerModule.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/GitHub/Asio/Asio/Server/ManagerModule.cpp > CMakeFiles/gameserver.dir/ManagerModule.i

CMakeFiles/gameserver.dir/ManagerModule.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameserver.dir/ManagerModule.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/GitHub/Asio/Asio/Server/ManagerModule.cpp -o CMakeFiles/gameserver.dir/ManagerModule.s

CMakeFiles/gameserver.dir/ManagerModule.o.requires:

.PHONY : CMakeFiles/gameserver.dir/ManagerModule.o.requires

CMakeFiles/gameserver.dir/ManagerModule.o.provides: CMakeFiles/gameserver.dir/ManagerModule.o.requires
	$(MAKE) -f CMakeFiles/gameserver.dir/build.make CMakeFiles/gameserver.dir/ManagerModule.o.provides.build
.PHONY : CMakeFiles/gameserver.dir/ManagerModule.o.provides

CMakeFiles/gameserver.dir/ManagerModule.o.provides.build: CMakeFiles/gameserver.dir/ManagerModule.o


CMakeFiles/gameserver.dir/ManagerModuleBase.o: CMakeFiles/gameserver.dir/flags.make
CMakeFiles/gameserver.dir/ManagerModuleBase.o: ManagerModuleBase.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/gameserver.dir/ManagerModuleBase.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameserver.dir/ManagerModuleBase.o -c /mnt/d/GitHub/Asio/Asio/Server/ManagerModuleBase.cpp

CMakeFiles/gameserver.dir/ManagerModuleBase.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameserver.dir/ManagerModuleBase.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/GitHub/Asio/Asio/Server/ManagerModuleBase.cpp > CMakeFiles/gameserver.dir/ManagerModuleBase.i

CMakeFiles/gameserver.dir/ManagerModuleBase.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameserver.dir/ManagerModuleBase.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/GitHub/Asio/Asio/Server/ManagerModuleBase.cpp -o CMakeFiles/gameserver.dir/ManagerModuleBase.s

CMakeFiles/gameserver.dir/ManagerModuleBase.o.requires:

.PHONY : CMakeFiles/gameserver.dir/ManagerModuleBase.o.requires

CMakeFiles/gameserver.dir/ManagerModuleBase.o.provides: CMakeFiles/gameserver.dir/ManagerModuleBase.o.requires
	$(MAKE) -f CMakeFiles/gameserver.dir/build.make CMakeFiles/gameserver.dir/ManagerModuleBase.o.provides.build
.PHONY : CMakeFiles/gameserver.dir/ManagerModuleBase.o.provides

CMakeFiles/gameserver.dir/ManagerModuleBase.o.provides.build: CMakeFiles/gameserver.dir/ManagerModuleBase.o


CMakeFiles/gameserver.dir/ManagerModuleManager.o: CMakeFiles/gameserver.dir/flags.make
CMakeFiles/gameserver.dir/ManagerModuleManager.o: ManagerModuleManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/gameserver.dir/ManagerModuleManager.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameserver.dir/ManagerModuleManager.o -c /mnt/d/GitHub/Asio/Asio/Server/ManagerModuleManager.cpp

CMakeFiles/gameserver.dir/ManagerModuleManager.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameserver.dir/ManagerModuleManager.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/GitHub/Asio/Asio/Server/ManagerModuleManager.cpp > CMakeFiles/gameserver.dir/ManagerModuleManager.i

CMakeFiles/gameserver.dir/ManagerModuleManager.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameserver.dir/ManagerModuleManager.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/GitHub/Asio/Asio/Server/ManagerModuleManager.cpp -o CMakeFiles/gameserver.dir/ManagerModuleManager.s

CMakeFiles/gameserver.dir/ManagerModuleManager.o.requires:

.PHONY : CMakeFiles/gameserver.dir/ManagerModuleManager.o.requires

CMakeFiles/gameserver.dir/ManagerModuleManager.o.provides: CMakeFiles/gameserver.dir/ManagerModuleManager.o.requires
	$(MAKE) -f CMakeFiles/gameserver.dir/build.make CMakeFiles/gameserver.dir/ManagerModuleManager.o.provides.build
.PHONY : CMakeFiles/gameserver.dir/ManagerModuleManager.o.provides

CMakeFiles/gameserver.dir/ManagerModuleManager.o.provides.build: CMakeFiles/gameserver.dir/ManagerModuleManager.o


CMakeFiles/gameserver.dir/MessageCirularQueue.o: CMakeFiles/gameserver.dir/flags.make
CMakeFiles/gameserver.dir/MessageCirularQueue.o: MessageCirularQueue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/gameserver.dir/MessageCirularQueue.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameserver.dir/MessageCirularQueue.o -c /mnt/d/GitHub/Asio/Asio/Server/MessageCirularQueue.cpp

CMakeFiles/gameserver.dir/MessageCirularQueue.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameserver.dir/MessageCirularQueue.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/GitHub/Asio/Asio/Server/MessageCirularQueue.cpp > CMakeFiles/gameserver.dir/MessageCirularQueue.i

CMakeFiles/gameserver.dir/MessageCirularQueue.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameserver.dir/MessageCirularQueue.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/GitHub/Asio/Asio/Server/MessageCirularQueue.cpp -o CMakeFiles/gameserver.dir/MessageCirularQueue.s

CMakeFiles/gameserver.dir/MessageCirularQueue.o.requires:

.PHONY : CMakeFiles/gameserver.dir/MessageCirularQueue.o.requires

CMakeFiles/gameserver.dir/MessageCirularQueue.o.provides: CMakeFiles/gameserver.dir/MessageCirularQueue.o.requires
	$(MAKE) -f CMakeFiles/gameserver.dir/build.make CMakeFiles/gameserver.dir/MessageCirularQueue.o.provides.build
.PHONY : CMakeFiles/gameserver.dir/MessageCirularQueue.o.provides

CMakeFiles/gameserver.dir/MessageCirularQueue.o.provides.build: CMakeFiles/gameserver.dir/MessageCirularQueue.o


CMakeFiles/gameserver.dir/MessageProcessor.o: CMakeFiles/gameserver.dir/flags.make
CMakeFiles/gameserver.dir/MessageProcessor.o: MessageProcessor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/gameserver.dir/MessageProcessor.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameserver.dir/MessageProcessor.o -c /mnt/d/GitHub/Asio/Asio/Server/MessageProcessor.cpp

CMakeFiles/gameserver.dir/MessageProcessor.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameserver.dir/MessageProcessor.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/GitHub/Asio/Asio/Server/MessageProcessor.cpp > CMakeFiles/gameserver.dir/MessageProcessor.i

CMakeFiles/gameserver.dir/MessageProcessor.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameserver.dir/MessageProcessor.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/GitHub/Asio/Asio/Server/MessageProcessor.cpp -o CMakeFiles/gameserver.dir/MessageProcessor.s

CMakeFiles/gameserver.dir/MessageProcessor.o.requires:

.PHONY : CMakeFiles/gameserver.dir/MessageProcessor.o.requires

CMakeFiles/gameserver.dir/MessageProcessor.o.provides: CMakeFiles/gameserver.dir/MessageProcessor.o.requires
	$(MAKE) -f CMakeFiles/gameserver.dir/build.make CMakeFiles/gameserver.dir/MessageProcessor.o.provides.build
.PHONY : CMakeFiles/gameserver.dir/MessageProcessor.o.provides

CMakeFiles/gameserver.dir/MessageProcessor.o.provides.build: CMakeFiles/gameserver.dir/MessageProcessor.o


CMakeFiles/gameserver.dir/MsgInstanceMgr.o: CMakeFiles/gameserver.dir/flags.make
CMakeFiles/gameserver.dir/MsgInstanceMgr.o: MsgInstanceMgr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/gameserver.dir/MsgInstanceMgr.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameserver.dir/MsgInstanceMgr.o -c /mnt/d/GitHub/Asio/Asio/Server/MsgInstanceMgr.cpp

CMakeFiles/gameserver.dir/MsgInstanceMgr.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameserver.dir/MsgInstanceMgr.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/GitHub/Asio/Asio/Server/MsgInstanceMgr.cpp > CMakeFiles/gameserver.dir/MsgInstanceMgr.i

CMakeFiles/gameserver.dir/MsgInstanceMgr.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameserver.dir/MsgInstanceMgr.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/GitHub/Asio/Asio/Server/MsgInstanceMgr.cpp -o CMakeFiles/gameserver.dir/MsgInstanceMgr.s

CMakeFiles/gameserver.dir/MsgInstanceMgr.o.requires:

.PHONY : CMakeFiles/gameserver.dir/MsgInstanceMgr.o.requires

CMakeFiles/gameserver.dir/MsgInstanceMgr.o.provides: CMakeFiles/gameserver.dir/MsgInstanceMgr.o.requires
	$(MAKE) -f CMakeFiles/gameserver.dir/build.make CMakeFiles/gameserver.dir/MsgInstanceMgr.o.provides.build
.PHONY : CMakeFiles/gameserver.dir/MsgInstanceMgr.o.provides

CMakeFiles/gameserver.dir/MsgInstanceMgr.o.provides.build: CMakeFiles/gameserver.dir/MsgInstanceMgr.o


CMakeFiles/gameserver.dir/NetProxy.o: CMakeFiles/gameserver.dir/flags.make
CMakeFiles/gameserver.dir/NetProxy.o: NetProxy.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/gameserver.dir/NetProxy.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameserver.dir/NetProxy.o -c /mnt/d/GitHub/Asio/Asio/Server/NetProxy.cpp

CMakeFiles/gameserver.dir/NetProxy.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameserver.dir/NetProxy.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/GitHub/Asio/Asio/Server/NetProxy.cpp > CMakeFiles/gameserver.dir/NetProxy.i

CMakeFiles/gameserver.dir/NetProxy.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameserver.dir/NetProxy.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/GitHub/Asio/Asio/Server/NetProxy.cpp -o CMakeFiles/gameserver.dir/NetProxy.s

CMakeFiles/gameserver.dir/NetProxy.o.requires:

.PHONY : CMakeFiles/gameserver.dir/NetProxy.o.requires

CMakeFiles/gameserver.dir/NetProxy.o.provides: CMakeFiles/gameserver.dir/NetProxy.o.requires
	$(MAKE) -f CMakeFiles/gameserver.dir/build.make CMakeFiles/gameserver.dir/NetProxy.o.provides.build
.PHONY : CMakeFiles/gameserver.dir/NetProxy.o.provides

CMakeFiles/gameserver.dir/NetProxy.o.provides.build: CMakeFiles/gameserver.dir/NetProxy.o


CMakeFiles/gameserver.dir/PerfStatistics.o: CMakeFiles/gameserver.dir/flags.make
CMakeFiles/gameserver.dir/PerfStatistics.o: PerfStatistics.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/gameserver.dir/PerfStatistics.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameserver.dir/PerfStatistics.o -c /mnt/d/GitHub/Asio/Asio/Server/PerfStatistics.cpp

CMakeFiles/gameserver.dir/PerfStatistics.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameserver.dir/PerfStatistics.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/GitHub/Asio/Asio/Server/PerfStatistics.cpp > CMakeFiles/gameserver.dir/PerfStatistics.i

CMakeFiles/gameserver.dir/PerfStatistics.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameserver.dir/PerfStatistics.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/GitHub/Asio/Asio/Server/PerfStatistics.cpp -o CMakeFiles/gameserver.dir/PerfStatistics.s

CMakeFiles/gameserver.dir/PerfStatistics.o.requires:

.PHONY : CMakeFiles/gameserver.dir/PerfStatistics.o.requires

CMakeFiles/gameserver.dir/PerfStatistics.o.provides: CMakeFiles/gameserver.dir/PerfStatistics.o.requires
	$(MAKE) -f CMakeFiles/gameserver.dir/build.make CMakeFiles/gameserver.dir/PerfStatistics.o.provides.build
.PHONY : CMakeFiles/gameserver.dir/PerfStatistics.o.provides

CMakeFiles/gameserver.dir/PerfStatistics.o.provides.build: CMakeFiles/gameserver.dir/PerfStatistics.o


CMakeFiles/gameserver.dir/StringHelper.o: CMakeFiles/gameserver.dir/flags.make
CMakeFiles/gameserver.dir/StringHelper.o: StringHelper.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/gameserver.dir/StringHelper.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameserver.dir/StringHelper.o -c /mnt/d/GitHub/Asio/Asio/Server/StringHelper.cpp

CMakeFiles/gameserver.dir/StringHelper.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameserver.dir/StringHelper.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/GitHub/Asio/Asio/Server/StringHelper.cpp > CMakeFiles/gameserver.dir/StringHelper.i

CMakeFiles/gameserver.dir/StringHelper.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameserver.dir/StringHelper.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/GitHub/Asio/Asio/Server/StringHelper.cpp -o CMakeFiles/gameserver.dir/StringHelper.s

CMakeFiles/gameserver.dir/StringHelper.o.requires:

.PHONY : CMakeFiles/gameserver.dir/StringHelper.o.requires

CMakeFiles/gameserver.dir/StringHelper.o.provides: CMakeFiles/gameserver.dir/StringHelper.o.requires
	$(MAKE) -f CMakeFiles/gameserver.dir/build.make CMakeFiles/gameserver.dir/StringHelper.o.provides.build
.PHONY : CMakeFiles/gameserver.dir/StringHelper.o.provides

CMakeFiles/gameserver.dir/StringHelper.o.provides.build: CMakeFiles/gameserver.dir/StringHelper.o


CMakeFiles/gameserver.dir/SystemConfig.o: CMakeFiles/gameserver.dir/flags.make
CMakeFiles/gameserver.dir/SystemConfig.o: SystemConfig.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/gameserver.dir/SystemConfig.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameserver.dir/SystemConfig.o -c /mnt/d/GitHub/Asio/Asio/Server/SystemConfig.cpp

CMakeFiles/gameserver.dir/SystemConfig.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameserver.dir/SystemConfig.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/GitHub/Asio/Asio/Server/SystemConfig.cpp > CMakeFiles/gameserver.dir/SystemConfig.i

CMakeFiles/gameserver.dir/SystemConfig.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameserver.dir/SystemConfig.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/GitHub/Asio/Asio/Server/SystemConfig.cpp -o CMakeFiles/gameserver.dir/SystemConfig.s

CMakeFiles/gameserver.dir/SystemConfig.o.requires:

.PHONY : CMakeFiles/gameserver.dir/SystemConfig.o.requires

CMakeFiles/gameserver.dir/SystemConfig.o.provides: CMakeFiles/gameserver.dir/SystemConfig.o.requires
	$(MAKE) -f CMakeFiles/gameserver.dir/build.make CMakeFiles/gameserver.dir/SystemConfig.o.provides.build
.PHONY : CMakeFiles/gameserver.dir/SystemConfig.o.provides

CMakeFiles/gameserver.dir/SystemConfig.o.provides.build: CMakeFiles/gameserver.dir/SystemConfig.o


CMakeFiles/gameserver.dir/TimeHelper.o: CMakeFiles/gameserver.dir/flags.make
CMakeFiles/gameserver.dir/TimeHelper.o: TimeHelper.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/gameserver.dir/TimeHelper.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameserver.dir/TimeHelper.o -c /mnt/d/GitHub/Asio/Asio/Server/TimeHelper.cpp

CMakeFiles/gameserver.dir/TimeHelper.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameserver.dir/TimeHelper.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/GitHub/Asio/Asio/Server/TimeHelper.cpp > CMakeFiles/gameserver.dir/TimeHelper.i

CMakeFiles/gameserver.dir/TimeHelper.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameserver.dir/TimeHelper.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/GitHub/Asio/Asio/Server/TimeHelper.cpp -o CMakeFiles/gameserver.dir/TimeHelper.s

CMakeFiles/gameserver.dir/TimeHelper.o.requires:

.PHONY : CMakeFiles/gameserver.dir/TimeHelper.o.requires

CMakeFiles/gameserver.dir/TimeHelper.o.provides: CMakeFiles/gameserver.dir/TimeHelper.o.requires
	$(MAKE) -f CMakeFiles/gameserver.dir/build.make CMakeFiles/gameserver.dir/TimeHelper.o.provides.build
.PHONY : CMakeFiles/gameserver.dir/TimeHelper.o.provides

CMakeFiles/gameserver.dir/TimeHelper.o.provides.build: CMakeFiles/gameserver.dir/TimeHelper.o


CMakeFiles/gameserver.dir/TimerManager.o: CMakeFiles/gameserver.dir/flags.make
CMakeFiles/gameserver.dir/TimerManager.o: TimerManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/gameserver.dir/TimerManager.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameserver.dir/TimerManager.o -c /mnt/d/GitHub/Asio/Asio/Server/TimerManager.cpp

CMakeFiles/gameserver.dir/TimerManager.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameserver.dir/TimerManager.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/GitHub/Asio/Asio/Server/TimerManager.cpp > CMakeFiles/gameserver.dir/TimerManager.i

CMakeFiles/gameserver.dir/TimerManager.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameserver.dir/TimerManager.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/GitHub/Asio/Asio/Server/TimerManager.cpp -o CMakeFiles/gameserver.dir/TimerManager.s

CMakeFiles/gameserver.dir/TimerManager.o.requires:

.PHONY : CMakeFiles/gameserver.dir/TimerManager.o.requires

CMakeFiles/gameserver.dir/TimerManager.o.provides: CMakeFiles/gameserver.dir/TimerManager.o.requires
	$(MAKE) -f CMakeFiles/gameserver.dir/build.make CMakeFiles/gameserver.dir/TimerManager.o.provides.build
.PHONY : CMakeFiles/gameserver.dir/TimerManager.o.provides

CMakeFiles/gameserver.dir/TimerManager.o.provides.build: CMakeFiles/gameserver.dir/TimerManager.o


CMakeFiles/gameserver.dir/UserModule.o: CMakeFiles/gameserver.dir/flags.make
CMakeFiles/gameserver.dir/UserModule.o: UserModule.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object CMakeFiles/gameserver.dir/UserModule.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameserver.dir/UserModule.o -c /mnt/d/GitHub/Asio/Asio/Server/UserModule.cpp

CMakeFiles/gameserver.dir/UserModule.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameserver.dir/UserModule.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/GitHub/Asio/Asio/Server/UserModule.cpp > CMakeFiles/gameserver.dir/UserModule.i

CMakeFiles/gameserver.dir/UserModule.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameserver.dir/UserModule.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/GitHub/Asio/Asio/Server/UserModule.cpp -o CMakeFiles/gameserver.dir/UserModule.s

CMakeFiles/gameserver.dir/UserModule.o.requires:

.PHONY : CMakeFiles/gameserver.dir/UserModule.o.requires

CMakeFiles/gameserver.dir/UserModule.o.provides: CMakeFiles/gameserver.dir/UserModule.o.requires
	$(MAKE) -f CMakeFiles/gameserver.dir/build.make CMakeFiles/gameserver.dir/UserModule.o.provides.build
.PHONY : CMakeFiles/gameserver.dir/UserModule.o.provides

CMakeFiles/gameserver.dir/UserModule.o.provides.build: CMakeFiles/gameserver.dir/UserModule.o


CMakeFiles/gameserver.dir/UserModuleBase.o: CMakeFiles/gameserver.dir/flags.make
CMakeFiles/gameserver.dir/UserModuleBase.o: UserModuleBase.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Building CXX object CMakeFiles/gameserver.dir/UserModuleBase.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameserver.dir/UserModuleBase.o -c /mnt/d/GitHub/Asio/Asio/Server/UserModuleBase.cpp

CMakeFiles/gameserver.dir/UserModuleBase.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameserver.dir/UserModuleBase.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/GitHub/Asio/Asio/Server/UserModuleBase.cpp > CMakeFiles/gameserver.dir/UserModuleBase.i

CMakeFiles/gameserver.dir/UserModuleBase.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameserver.dir/UserModuleBase.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/GitHub/Asio/Asio/Server/UserModuleBase.cpp -o CMakeFiles/gameserver.dir/UserModuleBase.s

CMakeFiles/gameserver.dir/UserModuleBase.o.requires:

.PHONY : CMakeFiles/gameserver.dir/UserModuleBase.o.requires

CMakeFiles/gameserver.dir/UserModuleBase.o.provides: CMakeFiles/gameserver.dir/UserModuleBase.o.requires
	$(MAKE) -f CMakeFiles/gameserver.dir/build.make CMakeFiles/gameserver.dir/UserModuleBase.o.provides.build
.PHONY : CMakeFiles/gameserver.dir/UserModuleBase.o.provides

CMakeFiles/gameserver.dir/UserModuleBase.o.provides.build: CMakeFiles/gameserver.dir/UserModuleBase.o


# Object files for target gameserver
gameserver_OBJECTS = \
"CMakeFiles/gameserver.dir/AsioAcceptor.o" \
"CMakeFiles/gameserver.dir/AsioSocket.o" \
"CMakeFiles/gameserver.dir/Logger.o" \
"CMakeFiles/gameserver.dir/LogicSystem.o" \
"CMakeFiles/gameserver.dir/Main.o" \
"CMakeFiles/gameserver.dir/ManagerModule.o" \
"CMakeFiles/gameserver.dir/ManagerModuleBase.o" \
"CMakeFiles/gameserver.dir/ManagerModuleManager.o" \
"CMakeFiles/gameserver.dir/MessageCirularQueue.o" \
"CMakeFiles/gameserver.dir/MessageProcessor.o" \
"CMakeFiles/gameserver.dir/MsgInstanceMgr.o" \
"CMakeFiles/gameserver.dir/NetProxy.o" \
"CMakeFiles/gameserver.dir/PerfStatistics.o" \
"CMakeFiles/gameserver.dir/StringHelper.o" \
"CMakeFiles/gameserver.dir/SystemConfig.o" \
"CMakeFiles/gameserver.dir/TimeHelper.o" \
"CMakeFiles/gameserver.dir/TimerManager.o" \
"CMakeFiles/gameserver.dir/UserModule.o" \
"CMakeFiles/gameserver.dir/UserModuleBase.o"

# External object files for target gameserver
gameserver_EXTERNAL_OBJECTS =

/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/AsioAcceptor.o
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/AsioSocket.o
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/Logger.o
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/LogicSystem.o
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/Main.o
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/ManagerModule.o
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/ManagerModuleBase.o
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/ManagerModuleManager.o
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/MessageCirularQueue.o
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/MessageProcessor.o
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/MsgInstanceMgr.o
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/NetProxy.o
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/PerfStatistics.o
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/StringHelper.o
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/SystemConfig.o
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/TimeHelper.o
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/TimerManager.o
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/UserModule.o
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/UserModuleBase.o
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/build.make
/mnt/d/GitHub/Asio/Debug/gameserver: CMakeFiles/gameserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/GitHub/Asio/Asio/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_20) "Linking CXX executable /mnt/d/GitHub/Asio/Debug/gameserver"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gameserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gameserver.dir/build: /mnt/d/GitHub/Asio/Debug/gameserver

.PHONY : CMakeFiles/gameserver.dir/build

CMakeFiles/gameserver.dir/requires: CMakeFiles/gameserver.dir/AsioAcceptor.o.requires
CMakeFiles/gameserver.dir/requires: CMakeFiles/gameserver.dir/AsioSocket.o.requires
CMakeFiles/gameserver.dir/requires: CMakeFiles/gameserver.dir/Logger.o.requires
CMakeFiles/gameserver.dir/requires: CMakeFiles/gameserver.dir/LogicSystem.o.requires
CMakeFiles/gameserver.dir/requires: CMakeFiles/gameserver.dir/Main.o.requires
CMakeFiles/gameserver.dir/requires: CMakeFiles/gameserver.dir/ManagerModule.o.requires
CMakeFiles/gameserver.dir/requires: CMakeFiles/gameserver.dir/ManagerModuleBase.o.requires
CMakeFiles/gameserver.dir/requires: CMakeFiles/gameserver.dir/ManagerModuleManager.o.requires
CMakeFiles/gameserver.dir/requires: CMakeFiles/gameserver.dir/MessageCirularQueue.o.requires
CMakeFiles/gameserver.dir/requires: CMakeFiles/gameserver.dir/MessageProcessor.o.requires
CMakeFiles/gameserver.dir/requires: CMakeFiles/gameserver.dir/MsgInstanceMgr.o.requires
CMakeFiles/gameserver.dir/requires: CMakeFiles/gameserver.dir/NetProxy.o.requires
CMakeFiles/gameserver.dir/requires: CMakeFiles/gameserver.dir/PerfStatistics.o.requires
CMakeFiles/gameserver.dir/requires: CMakeFiles/gameserver.dir/StringHelper.o.requires
CMakeFiles/gameserver.dir/requires: CMakeFiles/gameserver.dir/SystemConfig.o.requires
CMakeFiles/gameserver.dir/requires: CMakeFiles/gameserver.dir/TimeHelper.o.requires
CMakeFiles/gameserver.dir/requires: CMakeFiles/gameserver.dir/TimerManager.o.requires
CMakeFiles/gameserver.dir/requires: CMakeFiles/gameserver.dir/UserModule.o.requires
CMakeFiles/gameserver.dir/requires: CMakeFiles/gameserver.dir/UserModuleBase.o.requires

.PHONY : CMakeFiles/gameserver.dir/requires

CMakeFiles/gameserver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gameserver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gameserver.dir/clean

CMakeFiles/gameserver.dir/depend:
	cd /mnt/d/GitHub/Asio/Asio/Server && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/GitHub/Asio/Asio/Server /mnt/d/GitHub/Asio/Asio/Server /mnt/d/GitHub/Asio/Asio/Server /mnt/d/GitHub/Asio/Asio/Server /mnt/d/GitHub/Asio/Asio/Server/CMakeFiles/gameserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gameserver.dir/depend

