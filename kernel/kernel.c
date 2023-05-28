#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include "../libc/delay.h"
#include "../libc/itoa.h"
#include "../libc/atoi.h"

#define MAX_ASM_LINES 100

int asm_programmer = 0;
char asm_lines[MAX_ASM_LINES][80];
int num_asm_lines = 0;

void main() {
    clear_screen();
    isr_install();
    irq_install();
    
    kprint("cKern v0.0.5\nReporting Kernel v10\n\n");
    
    kprint("Welcome to the KShell!\n"
        "Type HELP for the command list\n> ");
}

void execute_asm_code(const char* code) {
    // Implement the execution of ASM code here
    // Assume the code is in Intel syntax
    
    // Inline assembly to execute the ASM code
    asm volatile (
        "mov $0, %%eax\n"       // Clear the EAX register
        "jmp 1f\n"              // Jump over the ASM code
        
        // Start of the ASM code
        "0:\n"
        "nop\n"                 // Placeholder for the ASM code
        
        // End of the ASM code
        "1:\n"
        "nop\n"                 // Placeholder for the end of the ASM code
        
        :                       // Output operands (none)
        : "S" (code)            // Input operands
        : "eax"                 // Clobbered registers
    );
}


void handle_asm_programmer(char *input) {
    if (strcmp(input, "ASM ]]") == 0) {
        // Close ASM programmer and execute the code
        asm_programmer = 0;
        kprint("\nRunning ASM program...\n");

        // Concatenate all ASM lines into a single buffer
        char asm_code[80 * num_asm_lines];
        asm_code[0] = '\0';
        for (int i = 0; i < num_asm_lines; i++) {
            strcat(asm_code, asm_lines[i]);
            strcat(asm_code, "\n");
        }

        // Call the function that executes the ASM code
        execute_asm_code(asm_code);
        
        kprint("\nASM program execution completed.\n");
        kprint("\n> ");
    } else if (num_asm_lines >= MAX_ASM_LINES) {
        // Maximum number of ASM lines reached
        kprint("Maximum number of ASM lines reached.\n");
        kprint("\n> ");
    } else {
        // Add the ASM line to the buffer
        strcpy(asm_lines[num_asm_lines], input);
        num_asm_lines++;
    }
}

void user_input(char *input) {
    if (strcmp(input, "END") == 0) {
        kprint("Stopping the CPU.\nIt is safe to shutdown/restart the system.\n");
        asm volatile("hlt");
    } else if (strcmp(input, "PAGE") == 0) {
        u32 phys_addr;
        u32 page = kmalloc(1000, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Page: ");
        kprint(page_str);
        kprint(", physical address: ");
        kprint(phys_str);
    } else if (strcmp(input, "CLR") == 0) {
        clear_screen();
        kprint("Cleared!");
    } else if (strcmp(input, "HELP") == 0) {
        kprint("HELP - Displays this command list\nCLR - Clears the screen\nEND - Halts CPU (NOT A SHUTDOWN!!)\nPAGE - Allocate a memory page\nVER - Display current version\nECHO - Repeats the message you say after it\nFIB - Generates Fibonacci sequence\nREVERSE - Reverses a string\nSQUARE - Finds the square root of a number\nASM - Run or program assembly programs");
    } else if (strcmp(input, "VER") == 0) {
        kprint("cKern v0.0.5\nReporting Kernel v10\n");
    } else if (strncmp(input, "ECHO ", 5) == 0) {
        kprint(input + 5); // Print the text after "ECHO "
    } else if (strcmp(input, "FIB") == 0) {
        // Generate Fibonacci sequence
        int a = 0, b = 1;
        kprint("Fibonacci Sequence:\n");
        char fib_str[16];
        itoa(a, fib_str);
        kprint(fib_str); // Print the first number
        kprint("\n");
        while (b < 1000) {
            itoa(b, fib_str);
            kprint(fib_str); // Print the current number
            kprint("\n");
            int temp = a + b;
            a = b;
            b = temp;
        }
    } else if (strncmp(input, "REVERSE ", 8) == 0) {
        char* str = input + 8;
        int length = strlen(str);
        kprint("Reversed string: ");
        for (int i = length - 1; i >= 0; i--) {
            char reverse_str[2] = {str[i], '\0'};  // Create a string of a single character
            kprint(reverse_str);
        }
        kprint("\n");
    } else if (strncmp(input, "SQUARE ", 7) == 0) {
        int num = atoi(input + 7);
        int square = num * num;
        char square_str[16];
        itoa(square, square_str);
        kprint("Square: ");
        kprint(square_str);
        kprint("\n");
    } else if (strcmp(input, "ASM") == 0) {
        asm_programmer = 1;
        num_asm_lines = 0;
        kprint("ASM Programmer activated.\nStart typing ASM code.\nTo run the code, type 'ASM ]]'\n\n");
        return;
    } else if (asm_programmer) {
        handle_asm_programmer(input);
        return;
    } else {
        kprint("SYNTAX ERROR");
    }

    kprint("\n> ");
}
