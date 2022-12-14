#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// ./front3 < front3.c
// ./front3 -f front3.c
// ./front3 front3.c -n 3
// ./front3 -n6 -ffront3.c
// ./front3 -n 2 < front3.c

#define BUFFER_SIZE 1024
#define MAX_LINES 5

int main(int argc, char *argv[]) {
    FILE *ifile = stdin;
    int line_count = 0;
    int max_lines = MAX_LINES;
    char buf[BUFFER_SIZE] = {0};
    char *file_name = NULL;

    {
        int opt = 0;

        while ((opt = getopt(argc, argv, "f:n:h")) != -1) {
            switch(opt) {
            case 'f':
                file_name = optarg;
                ifile = fopen(file_name, "r");
                if (ifile == NULL) {
                    perror("failed to open file");
                    fprintf(stderr, " could not open the file: %s\n", file_name);
                    exit(EXIT_FAILURE);
                }
                break;
            case 'n':
                //max_lines = atoi(optarg);
                max_lines = strtol(optarg, NULL, 10);
                if (max_lines <= 0) {
                    max_lines = MAX_LINES;
                }
                break;
            case 'h':
                printf("%s [-f file] [-n #] [-h]\n", argv[0]);
                exit(EXIT_SUCCESS);
                break;
            default:
                exit(EXIT_FAILURE);
            }
        }
    }

    while ((line_count++ < max_lines) && fgets(buf, BUFFER_SIZE, ifile) != NULL) {
        printf("%s", buf);
    }

    if (file_name != NULL) fclose(ifile);

    return EXIT_SUCCESS;
}