#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/time.h>
#include<unistd.h>

struct shared
{
    int val;
};

int main(int argc, char *argv[])
{
    int shared_memory_id;
    struct shared *info;
    struct timeval start,end;

    shared_memory_id=shmget(IPC_PRIVATE,64,IPC_CREAT | 0666);
    if(shared_memory_id==-1)
    {
        printf("Error in creating shared memory segment\n");
        exit(EXIT_FAILURE);
    }
    info=shmat(shared_memory_id,NULL,0);
    if(info == (void *)-1)
    {
        printf("shmat error\n");
        exit(EXIT_FAILURE);
    }
    info->val=0;
    gettimeofday(&start,NULL);

    //Performing context switch
    pid_t pid=fork();
    for(int i=0;i<1000000;i++)
    {
        if(pid==0)
        {
            while(info->val==i)
            {
                //wait for parent process to write
                //printf("b\n");
                // int b=info->val;
                // info->val=b;
                // exit(EXIT_SUCCESS);
                info->val=i+1;
                //exit(EXIT_SUCCESS);
            }
           // info->val=i+1;
        }
        else
        {
            //info->val=i;
            while(info->val==i)
            {
                    info->val=i+2;
                    // //wait for child to write
                    // //printf("a\n");
                    // int b=info->val;
                    // info->val=b;
                    //exit(EXIT_SUCCESS);
            }
       
        }


    }

    gettimeofday(&end,NULL);
    double time=(end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
    time=time/10000;
    printf("Context switch time is %f microseconds\n",time);
    exit(0);
    shmdt(info);
    shmctl(shared_memory_id,IPC_RMID,NULL);
    return 0;

}