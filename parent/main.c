#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <sched.h>
#include <sys/wait.h>
#include <errno.h>

int main() //Parent
{
    int childStatus;
    const size_t sharedBuffLength = 1024;
    int fd = 0;
    char arg1[16];
    memset(arg1, 0, 16);

    fd = shm_open("/Konoos", O_RDWR | O_CREAT, 0640);
    int *array = mmap(NULL, sharedBuffLength, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    snprintf(arg1, 16,"%p\n", array);
    printf("%s\n", arg1);
    printf("%p\n", array);
    char *argv[] = {"IpcChild", arg1, NULL};

    pid_t tpid;
	pid_t pid = fork();
	switch(pid)
	{
    case 0:
            chdir("/home/jason/Desktop/StudyProject/Lavanda/child/build");
            int fd = open("logs2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, 1);
            close(fd);
            execv("./IpcChild", argv);
            perror("Error while exec");
            exit(-1);
    case 1:
         do {
           tpid = waitpid(pid, &childStatus, 0);
           if(tpid != pid) sleep(1);
         } while(tpid != pid);
	}
	munmap(array, sharedBuffLength);

	return 0;
}
