# Full Proect CMake Template

## Briefing
Makefiles are the "defacto" Build system for C/C++ written codebases, every operating system and every IDE uses them behind the curtains. But the drawback of using Makefiles for projects is that it's very hard to
mantain, or to have complex functionalities embedded within the project like: automated testing, automated documentation, etc. That's when CMake comes to rescue. CMake is a build system of build systems, it uses a fairly easy to use scripting language with its own syntaxis to specify what do you want to compile and how, and it then generates the necessary Makefiles for that to be done automatically.

This repo serves as a CMake-based project that contains the following functionalities:
- Scripts to customize what toolchain to use.
- Adding new libraries easily.
- Automated testing using Google Test suite.
- Automated documentation using Doxygen and graph generation using Graphviz.
- A Dockerfile and a container config script to run the environment in an isolated Linux container.
- Automated configuration of the project using Kconfig and a GUI that's menuconfig-like.
- The potential of easily choose which source files to compile against conditionally, by evaluating macro variables defined at configuration stage.

TODO
- Integrate Code Coverage tools.
- Add conditionally compiled/linked sources.
- Add GDB scripts to automate debugging sessions. 

### Windows users
As a last comment, both Makefiles and CMake are Linux native, and while it's possible to be supported in Windows, it has many obstacles to do so. If you're developing in a non-Unix based
OS you can develop inside of the container in VS Code (Further instructions later on).


## Description
CMake projects have a hierarchy. All CMake scripts are named "CMakeLists.txt", and the main one lies in the root folder of the repository. From that script you
can add directories that contain other CMakeLists.txt, and when you configure the project their commands and actions will also be ran. That allows to have
each directory with their CMake scripts and to not have a single script that contains hundreds of lines of code and can get very hard to mantain.

### Directory layout
The layout of the source directory can of course be changed, although I wouldn't recommend to change the location of cmake-kconfig. And if you do change 
the locations of the other directories or their structure, you need to modify the subsequent CMakeLists.txt
```bash
.
├── app
│   └── main.c
├── cmake
│   ├── AddGitSubmodule.cmake
│   ├── CodeCoverage.cmake
│   ├── Docs.cmake
│   ├── linaroAarch64Toolchain.cmake
│   ├── Sanitizer.cmake
│   ├── top.cmake
│   └── Warnings.cmake
├── cmake-kconfig
│   ├── cmake
│   ├── CMakeCache.txt
│   ├── CMakeFiles
│   ├── CMakeLists.txt
│   ├── configs
│   ├── kconfig
│   ├── Kconfig
│   ├── README.md
│   └── scripts
├── CMakeLists.txt
├── CMakePresets.json
├── config
│   ├── autoconf.h
│   ├── CMakeLists.txt
│   ├── config.h.in
│   ├── defconfigs
│   └── Kconfig
├── Dockerfile
├── docs
│   └── Doxyfile
├── include
│   ├── interfaces
│   ├── libs
│   └── LinkedList.h
├── Makefile
├── src
│   ├── CMakeLists.txt
│   ├── LinkedList.c
│   ├── module_A
│   └── module_B
└── tests
    ├── CMakeLists.txt
    ├── linked_list
    └── main.cpp
```

#### app
Here is where the source file/s (.c .cpp) of the proper application of the project should be put.
#### cmake
Here there are .cmake scripts that act as libraries for CMake functions. The script that contains the toolchain config also lies here.
#### cmake-kconfig
This is actually a whole other repository. It has been modified to be included natively and to be used by running make commands from within the root directory (explained later).
#### config
Here all config related scripts, text, etc should be put. This project generates an autoconf.h with macro definitions automatically from the Kconfig + menuconfig stage (explained later).
#### docs
Here lies a Doxyfile, which is a script to tell Doxygen HOW to generate the documentation for the project. This folder will also be populated with the documentation output after building
the project (explained later).
#### include
Here all the headers should be put in (.h .hpp). Within interfaces, all headers that act as an interface for certain implementation are suggested to be put in, to be used later in the tests.
Pre-compiled libraries and other external dependencies can be put within libs
#### src
Here all source files should be put in (.c .cpp). If the project grows in size it could be a good idea to have them separated in different directories("modules") that gather subsystem functionalities, and using
meaningful names for each, for example: sensing module, processing module, configuration module, etc.
#### tests
Here the handling/fetching of the Google Test framework is done. And all the source files related with testing of the project are put in. 

### CMake Presets
One thing is the configuration of the project, which is described with more detail within the /config/README.md , and a whole different one is the configuration of the build.
The configuration of the build may include:
- Compiler flags like optimization or debugging flags
- Enabling tests or not.
- Enabling debugging printf's
- etc
Since it would be very tedious to have to change this by hand each time, and there are a lot of common expected configurations depending on what type of build we want.
CMake presets come into play. They allow you to define configuration sets gathering all of these flags or CMake variable definitions inside of a JSON script. Example:
```
"configurePresets": [
    {
      "name": "debug",
      "description": "Debug build with optimizations disabled and debugging symbols enabled",
      "cacheVariables": {
        "TOOLCHAIN_SELECT": "LinaroCrossArm64",
        "OPTIMIZATION_FLAG": "-O2",
        "DEBUG_FLAG": "-g3",
        "PRINTF_DEBUG": "ON",
        "EXTRA_WARNINGS": "ON",
        "UNIT_TESTING": "ON",
        "REGRESION_TESTING": "ON"
      }
    },
    {
      "name": "prod",
      "description": "Production build, no printing and optimized for runtime",
      "cacheVariables": {
        "TOOLCHAIN_SELECT": "LinaroCrossArm64",
        "OPTIMIZATION_FLAG": "-O3",
        "DEBUG_FLAG": "-g0",
        "PRINTF_DEBUG": "OFF",
        "EXTRA_WARNINGS": "OFF",
        "UNIT_TESTING": "OFF",
        "REGRESION_TESTING": "ON"
      }
    }
```
So you can easily switch from a debugging build or a production one easily, for example. Any number of sets can be added, these are configuration presets but there are also build and test ones. Refer to:
[CMake Presets](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html)

### Developing inside of a Docker container
This project has a Dockerfile and a vs code extension config script that automatically generates a container, and mounts the repository directory as a volume attached to the container. This allows you to
develop inside of the container while using all the capabilities of VS code, and every change you make will be reflected in the local repository on your computer. To do this, you must have the 
VS Code extension that's recommended on the .vscode scripts. In Unix-based OS this is fairly easy to do, in Windows there are a couple of extra steps and you must also have Docker Desktop installed and the
Docker engine running to be able to create the container. 

Refer to:

[VS Code Dev Containers](https://code.visualstudio.com/docs/devcontainers/containers)

[Docker Desktop for Windows](https://docs.docker.com/desktop/install/windows-install/)


### Further details
Each directory contains a README.md with specific info. Example: In the "tests" directory you can find instructions on how to add new tests to the suite.


## Commands and build
The project contains a Makefile in the root directory that you can inspect. It contains commands that are simply bash commands grouped together to ease the configuration, building, and testing of the project.

### setup
The setup of the project is the first step you should do, since it configures cmake (creates temporary necessary files), and it's done by running the following command:
```
make setup debug
```
In this example the "debug" configuration build was chosen.
This will create new folders like "build" and "executables", where all the temporary or executable files will lie on. 

### configuration
This can be done if you plan on using Kconfig based configuration. You can run the following command to open the menuconfig GUI:
```
make menuconfig
```
Then you should configure the project as you seem fit (By navigating menus and selecting the options you want)
And after you're done, you save. And you re-run the setup command detailed in the previous step.

### tests
You can run the automated tests by running:
```
make run_tests
```
This will compile and run all tests and output their results in the terminal.

### compile
This will compile and generate all specified executables, by running the following command:
```
make compile
```

### cleaning
This isn't recommended to be done. This cleans all temporary files, including the Google Test suite which is downloaded at the first setup. CMake is a differential build system,
so when you build again only the parts of the system that have been changed will be recompiled, and the rest will remain intact, saving build time. You should then ONLY use this
if there's some error that you cannot solve that's related with the build, or if you changed the main CMakeLists.txt script. 
The command is:
```
make clean
```
Will remove the cache and build folder.
