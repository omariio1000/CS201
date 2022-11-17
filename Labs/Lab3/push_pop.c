/* Omar Nassar
 * November 11, 2022
 * Portland State University CS201
 * Manipulating stack using push and pop instructions
 * A portion of this code was written by the instructor Jesse Chaney
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <assert.h>

#include "push_pop.h"

// The valid commands:
//   status
//   push %reg
//   push $val
//   pop %reg

int is_verbose = 0;
FILE *ofile = NULL;
static unsigned long stack_bot = DEF_STACK_BOT; // the high address for the stack
static unsigned long stack_limit = DEF_STACK_LIMIT; // the low address for the stack
static unsigned long rsp = DEF_RSP; // the initial value for the rsp register
static unsigned long *stack = NULL; // points to the bytes for the stack
static unsigned long registers[REG_RDX + 1] = { // the general purpose registers
    REG_RAX + 20,
    REG_RBX + 30,
    REG_RCX + 40,
    REG_RDX + 50
};

static void pop(char *);
static void push_reg(char *);
static void push_value(char *);

static void pop(char *reg) {
    //#error stuff goes in here
}

static void push_reg(char *reg) {
    //#error stuff goes in here
}

static void push_value(char *reg) {
    //#error stuff goes in here
}

int main(int argc, char *argv[]) {
    FILE *ifile = stdin;
    ofile = stdout;
    char buf[BUFFER_SIZE] = {0};
    int rows;
    long bytes;

    {
        int opt = 0;
        int res_count = 0;

        while ((opt = getopt(argc, argv, GETOPT_STRING)) != -1) {
            switch (opt) {
            case 'i':
                ifile = fopen(optarg, "r");
                if (!ifile) {
                    perror("failed to open file");
                    return EXIT_FAILURE;
                }
                break;
            case 'o':
                ofile = fopen(optarg, "w");
                    if (!ofile) {
                        perror("failed to open file");
                        return EXIT_FAILURE;
                    }
                break;
            case 'b':
                stack_bot = strtol(optarg, NULL, 16);
                if (stack_bot < stack_limit) {
                    fprintf(stderr, "stack botton must be higher than stack limit\n");
                    return EXIT_FAILURE;
                }
                else if (stack_bot % 8) {
                    fprintf(stderr, "stack_bot value must be a multiple of 8\n");
                    return EXIT_FAILURE;
                }
                break;
            case 'l':
                stack_limit = strtol(optarg, NULL, 16);
                if (stack_bot < stack_limit) {
                    fprintf(stderr, "stack botton must be higher than stack limit\n");
                    return EXIT_FAILURE;
                }
                else if (stack_limit % 8) {
                    fprintf(stderr, "stack_limit value must be a multiple of 8\n");
                    return EXIT_FAILURE;
                }
                break;
            case 's':
                rsp = strtol(optarg, NULL, 16);
                if (rsp > stack_bot || rsp < stack_limit) {
                    fprintf(stderr, "initial rsp value outside of stack\n");
                    return EXIT_FAILURE;
                }
                break;
            case 'v':
                is_verbose = 1;
                break;
            case 'h':
                printf("%s\n\toptions: %s\n", argv[0], GETOPT_STRING);
                printf("\ti: name of input file\n");
                printf("\to: name of output file\n");
                printf("\tb: stack_bottom (high address, as hex)\n");
                printf("\tl: stack limit (low address, as hex)\n");
                printf("\ts: beginning %%rsp value (within the stack, as hex)\n");
                printf("\tv  verbose output\n");
                printf("\th  help\n");

                exit(EXIT_SUCCESS);
                break;
            default:
                break;
            }
        }
    }

    bytes = stack_bot - stack_limit + 0x8;
    rows = bytes/8;

    stack = (unsigned long *) calloc(rows, REG_SIZE);

    if (is_verbose) printf(">> allocating stack: %ld bytes %d rows\n", bytes, rows);

    //#error lots of stuff goes in here
    while(fgets(buf, BUFFER_SIZE, ifile)) {
        char *remain = buf;
        char *reg;
        // int option = 0; //1 for status, 2 for push, 3 for pop

        remain = strtok(remain, WHITESPACE);
        if (!remain) continue;
        //printf("PARSED: %s OPTION: %d\n", remain, option);
        if (strcmp(remain, CMD_STATUS) == 0) {
            stack_status(stack, registers, rsp, stack_bot, stack_limit);
        }
        else if (strcmp(remain, CMD_PUSH) == 0) {
            printf("PUSH\n");
            remain = strtok(NULL, WHITESPACE);
            if (remain[0] == '$') {
                printf("value mode\n");
                reg = remain + 1;
                printf("new string: %s\n", reg);
            }
            else if (remain[0] == '%') {
                printf("register mode\n");
                reg = remain + 1;
                printf("new string: %s\n", reg);
            }
            else {
                fprintf(ofile, "unrecognized operand for push: %s\n", remain);
                continue;
            }
        }
        else if (strcmp(remain, CMD_POP) == 0) {
            printf("POP\n");
            remain = strtok(NULL, WHITESPACE);
            if (remain[0] == '%') {
                printf("register\n");
                reg = remain + 1;
                printf("new string: %s\n", reg);
            }
        }

        
    }
    
    if (ifile != stdin) fclose(ifile);
    if (ofile != stdout) fclose(ofile);
    if (stack) free(stack);
    
    return EXIT_SUCCESS;
}