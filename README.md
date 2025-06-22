00        01      02  
03        0405  0607  
08090A    0B  0C  0D  
0E    0F  10      11  
  1213    14      15  

# byte-messenger
GUI based application for send/receiving binary data via communications channels such as TCP/IP.

# Platform
This application has currently been built in a Linux Ubuntu 20.04 development host for a
Linux target (x86_64-pc-linux-gnu) and a Windows target (x86_64-pc-linux-mingw32).

# Build Info

## Build Dependencies

### Linux Native Target
- git
- build-essentials
- autotools
- cmake
- qt5

### Windows Cross-Compile Target
- git
- build-essentials
- autotools
- cmake
- MXE
- mingw-w64
- qt5 for mingw-w64

## Build Instructions

**NOTE:** When building the Windows target, the CMakeLists.txt file is currently configured
to expect the MXE files to be located in /usr/lib/mxe.  This will need to be updated if you
have installed the MXE files in an alternate location.

### Linux Native Target
1.  Clone the repository from github with the `git clone` command.
2.  Navigate to the x86_64-pc-linux-gnu directory of the repository:  
    `cd x86_64-pc-linux-gnu`
3.  Run cmake:  
    `cmake .`
4.  Run make:  
    `make`
5.  The **byte-messenger** executable will be found in the current directory.

### Windows Native Target
1.  Clone the repository from github with the `git clone` command.
2.  Navigate to the x86_64-pc-linux-mingw32 directory of the repository:  
    `cd x86_64-pc-linux-mingw32`
3.  Run cmake:  
    `cmake .`
4.  Run make:  
    `make`
5.  The **byte-messenger.exe** executable will be found in the current directory.

# NOTES
- This project is a work in progress (including this README file!)
- To generate Doxygen documentation, execute the command `doxygen Doxyfile`.
