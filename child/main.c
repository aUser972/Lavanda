#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) //Child
{
    int *shmPointer;
    if(argc < 2)
    {
        printf("Wrong number of arguments for the child process");
        exit(-1);
    }
    sscanf(argv[1], "%p", &shmPointer);
    printf( "%p\n", shmPointer);
	return 0;
}
