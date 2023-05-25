#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/time.h>
#include<stdbool.h>

int main()
{
	int file_descriptor1[2],file_descriptor2[2];
	char buffer;
	pid_t pid;
	int val1=pipe(file_descriptor1);
	int val2=pipe(file_descriptor2);
	if(val1==-1 || val2==-1)
	{
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	pid=fork();
	if(pid==-1)
	{
		printf("Error in fork()\n");
		exit(EXIT_FAILURE);
	}
	struct timeval start,end;
	double time;
	int i;
	if(pid==0)
	{
		for(i=0;i<1000000;i++)
		{
			if(read(file_descriptor1[0],&buffer,1)==-1)
			{
				printf("Read Error\n");
				exit(EXIT_FAILURE);
			}
			
			if(write(file_descriptor2[1],"a",1)==-1)
			{
				printf("Write Error\n");
				exit(EXIT_FAILURE);
			}
			
			
		}
		exit(EXIT_SUCCESS);
		
	}
	else
	{
		gettimeofday(&start,NULL);
		for(i=0;i<1000000;i++)
		{
			if(write(file_descriptor1[1],"b",1)==-1)
			{
				printf("Write error\n");
				exit(EXIT_FAILURE);
			}
			if(read(file_descriptor2[0],&buffer,1)==-1)
			{
				printf("Read Error\n");
				exit(EXIT_FAILURE);
			}
			
		}
		
	}
	gettimeofday(&end,NULL);
	time = (double)(end.tv_sec - start.tv_sec) * 1000000 + (double)(end.tv_usec - start.tv_usec);
	printf("context switch: %f microseconds\n", time/(1000000*2));
	
	
return 0;	
	
	
}
