# CppND-System-Monitor

This project implements a Linux based process manager, similar to htop. Linux stores information about  processes in a couple of files. The code written reads from those files, extracts the important data, formats it and uses Ncurses to display them inside the console. Code implements the `System`, `Process`, and `Processor` classes, as well as functions within the `LinuxParser` namespace.

![System Monitor](images/monitor.png)

## ncurses
[ncurses](https://www.gnu.org/software/ncurses/) is a library that facilitates text-based graphical output in the terminal. This project relies on ncurses for display output.

Within the Udacity Workspace, `.student_bashrc` automatically installs ncurses every time you launch the Workspace.

If you are not using the Workspace, install ncurses within your own Linux environment: `sudo apt install libncurses5-dev libncursesw5-dev`

## Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts

## Original repository

The original repository: `git clone https://github.com/udacity/CppND-System-Monitor-Project-Updated.git`

## How to run

1. Clone the project repository: `git clone https://github.com/VedadCausevic/system-monitor.git`
2. Build the project: `make build`
3. Run the resulting executable: `./build/monitor`



