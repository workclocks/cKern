# cKern
## About
The operating system, called cKern, is a fast yet poorly written operating system developed in C and Assembly. It aims to provide a basic understanding of operating system development and serves as a starting point for further exploration and improvement.

## Prerequisites
To build and run the operating system, make sure you have the following prerequisites installed:
- i386-elf
- GNU Make
- GNU GCC
- NASM
- i386-elf-gdb (or GNU GDB)

## Building the Operating System
To build the operating system, execute the following command:

### make (or make os-image.bin)
This command will compile the C and Assembly source files and generate an `os-image.bin` file.

## Running the Operating System
To run the operating system in the QEMU emulator, use the following command:
*Currently no native run command for Bochs or any other emulator, bring your own command*

### make run
This command will execute the `os-image.bin` file in QEMU.

## Debugging the Operating System
For debugging purposes, you can use the following command to open a connection to QEMU and load the kernel object file with symbols:

### make debug
This command will start QEMU in debug mode and connect the GDB debugger to it.

## Cleaning the Project
To clean the project and remove the generated files, you can use the following commands:
- `make clean`: Removes the object files and other build artifacts.
- `make oclean`: Cleans only the object files.
- `make fclean`: Removes all generated files, including the `os-image.bin` and `kernel.elf`.

## Pull Request Guidelines
When submitting a pull request, please adhere to the following guidelines:
- Provide a clear and concise description of the proposed changes.
- Include the motivation behind the changes.
- Clearly state any dependencies or requirements introduced by the changes.
- Ensure that the code follows the project's coding conventions and style.
- Test the changes thoroughly to avoid introducing bugs.
- Keep the pull request focused on a single issue or feature.
