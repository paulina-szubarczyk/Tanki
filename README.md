ShipsTheGame
=====

Multiplayer Game Server - ShipsTheGame

1. Dependencies:
	1. Boost:
		system, thread, asio, singals2, bind, program_options; possibly others

	2. Google:
		protocol buffers, glog, C++ testing framework
	
	3. OpenGL:
		glut, glui

	3. Compilers:
		Windows: Visual Studio
		Linux:	 Gcc >= 4.8.0

	4. Build System:
		CMake >= 2.8.0

2. Building under Linux:
	1. clone: git clone https://github.com/mikrro/Tanki
	2. enter project directory: cd Tanki
	3. create a build directory: mkdir build && cd build
	4. configure: Configuration depends on IDE
		Linux:
			Default: cmake ../src
			Eclipse: cmake -G"Eclipse CDT4 - Unix Makefiles" ../src
			Codeblocks or QtCreator: cmake -G"Codeblocks - UnixMakefiles" ../src
		
		Windows:
			No Idea

		Additional options: 
			To be specified between -G and ../src
			-DCMAKE_BUILD_TYPE=Debug	debug build type
			-DCMAKE_CXX_COMPILER_ARG1='-std=c++11' c++11

		Example:
			cmake -G"Eclipse CDT4" -DCMAKE_BUILD_TYPE=Debug ../src

	5. compiling:
		make -j<number of threads> 		
		
		 
