#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

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
		
		printf("Time since last system boot: %s seconds\n", line);
		fclose(file);
	}
}

void second()
{
	// second: time in user mode, system mode, idle
	// # of disk read/write requests, # of context switches kernel did
	// time when system last booted, # processes created since boot
	file = fopen("/proc/stat", "r");
	if(file){
	//first line contains all the information we need
		fgets(str,1024,file);
		strtok(str, " ");
		line = strtok(NULL, " ");
		printf("Processor Time spent in user mode: %s\n",line);
		strtok(NULL, " ");
		line = strtok(NULL, " ");
		printf("Processor Time spent in system: %s\n",line);
		line = strtok(NULL, " ");
		printf("Amount of time system was idle: %s\n",line);
		line = strtok(NULL, " ");
		printf("Number of I/O request: %s\n",line);
		fclose(file);
		}	

	//Number of context switch, 
	//time at which the system was last booted
	//the number of process that have been created since the system was booted

	file = fopen("/proc/stat", "r");
	if(file){
		while(fgets(str,1024,file)){
			if(strstr(str,"ctxt")){
				strtok(str, " ");
				line = strtok(NULL, " ");
				printf("Number of context switches are: %s",line);
			}
			else if(strstr(str,"btime")){
				strtok(str, " ");
				line = strtok(NULL, " ");
				printf("Last booted time: %s",line);
			}
			else if(strstr(str,"processes")){
				strtok(str, " ");
				line = strtok(NULL, " ");
		printf("Number of processes created since boot: %s",line);
			}	
		}
	fclose(file);
	} 
}

void third(int interval, int runtime)
{
	// third: amount of mem configured + currently available
	// list of load averages (read pdf for more about this)

	//calculate number of samples to perform for load average
	int samples;
	samples = runtime/interval;

	//print the memory information on this computer
	file = fopen("/proc/meminfo", "r");
	if (file)
	{
		while(fgets(str,1024,file))
		{
			//print out total amount of memory
			if (strstr(str,"MemTotal"))
			{
				strtok (str," ");
				line = strtok(NULL," ");
				printf("Total memory is %s kB \n",line);
			}

			//print out amount of free memory
			else if (strstr(str,"MemFree"))
			{
				strtok (str," ");
				line = strtok(NULL," ");
				printf("Amount of free memory is %s kB \n",line);
			}
		}
		fclose(file);
	}
	printf ("The follow will show a list of load averages with time interval %d over a runtime of %d \n",interval,runtime);

	//get the load avg according to the time interval and total runtime
	int i=0;
	for (i=0;i<samples;i++)
	{
		file = fopen("/proc/loadavg","r");
		fgets(str,1024,file);
		strtok(str," ");
		printf("%s \n",str);
		sleep(interval);
	}
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
			printf("This is the first version: \n");
			first();
		}
		else if (*argv[1] == '2')
		{
			printf("This is the second version: \n");
			first();
			second();
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
		first();
		second();
		third(atoi(argv[2]),atoi(argv[3]));
	}
	else printf("Invalid number of args! Type 1 for version 1, 2 for version 2, 3 for version 3. Exiting...");
	
	return 0;
}
