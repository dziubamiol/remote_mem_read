#include <sys/ptrace.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	printf("Start\n");

	long ptrace_res = ptrace(PTRACE_ATTACH, 8997, 0, 0);
	
	std::cout << "ptrace_res " << ptrace_res << "\n"; 
	int wpd_res = waitpid(8997, NULL, 0);
	std::cout << "waitpid id " << wpd_res << "\n";
        	
	char file[255];
	sprintf(file, "/proc/%d/mem", 8997);
	FILE *fd;
	fd = fopen(file, "r");

	
	int res;
	fseek(fd, 1, SEEK_SET);
	fread(&res, 100, sizeof(res), fd);
	std::cout << "res " << res << "\n"; 
	ptrace(PTRACE_DETACH, 8997, 0, 0);
	fclose(fd);
}
