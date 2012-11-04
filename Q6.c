#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

FILE * file;
char * line;
char str[1024];
int i;

void first()
{
	// first version: processor type, kernel version, time since last boot
	
	// Print out processor type
	file = fopen("/proc/cpuinfo", "r");
	
	if (file)
	{
		while(fgets(str, sizeof(str), file)) {
			//printf("%s\n", str);
			if(strstr(str, "model name")) {
				strtok(str, ":");
				line = strtok(NULL, ":");
				//printf(line);
				printf("Processor Type: %s", line);
			}
		}
		fclose(file);
	}
	
	// Print out kernel version
	file = fopen("/proc/version", "r");

	if(file) {
		fgets(str, sizeof(str), file);
		strtok(str, " ");
		strtok(NULL, " ");
		line = strtok(NULL, " ");

		printf("Kernel Version Number: %s\n", line);
		fclose(file);
	}
	
	// Print out time since last boot
	file = fopen("/proc/uptime", "r");
	
	if(file) {
		fgets(str, sizeof(str), file);
		line = strtok(str, " ");
		
		printf("Time since system boot (in seconds): %s\n", line);
		fclose(file);
	}
}

void second()
{
	// second: time in user mode, system mode, idle
	// # of disk read/write requests, # of context switches kernel did
	// time when system last booted, # processes created since boot
	
	// Print out time in user mode, system mode, idling
	//file = fopen("/proc/stat", "r");
	
	// Print out # of disk read/write requests
	
	// Print out # of context switches done by kernel
	
	// Print out time when system last booted
	
	// Print out # processes created since boot
}

void third()
{
	// third: amount of mem configured + currently available
	// list of load averages (read pdf for more about this)
	
}

int main(int argc, char *argv[]) {
	
	// User can print versions by:
	// add argument 1 to print version 1
	// add 2 to print version 1 and 2
	// add 3 to print version 3 (needs an additional 2 commands)
	if (argc == 2)
	{
		if (*argv[1] == '1')
		{
			first();
		}
		else if (*argv[1] == '2')
		{
			printf("Second version not implemented yet\n");
		}
		else if (*argv[1] == '3')
		{
			printf("Add load average and time interval after the 3 command to run version 3\n");
		}
		else
		{
			printf("Incorrect command. Type 1 for version 1, 2 for version 2, 3 for version 3\n");
		}
	}
	else if (argc == 4)
	{
		// version 3, need two more commands to specify load average and time interval
		printf("Third version not implemented yet\n");
	}
	else printf("Invalid number of args! Type 1 for version 1, 2 for version 2, 3 for version 3. Exiting...");
	
	return 0;
}
