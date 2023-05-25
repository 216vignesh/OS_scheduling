#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct job
{
	int id;
	int arrival_time;
	int length;
	int remaining_time;
	int start_time;
    int end_time;
    int turnaround_time;
    int wait_time;
    int response_time;
	struct job *next;
};

struct completed_job {
    int id;
    int arrival_time;
    int length;
    int remaining_time;
    int start_time;
    int end_time;
    int turnaround_time;
    int wait_time;
    int response_time;
    struct completed_job* next;
};



struct merged_job
{
	int id;
	int response_time;
	int turnaround_time;
	int wait_time;
	struct merged_job *next;
	
};

struct job2
{
	int id;
	int response_time;
	int turnaround_time;
	int wait_time;
	struct job2 *next;
	
};




void swap(struct job *a,struct job *b)
{
	int id=a->id;
	int arrival_time=a->arrival_time;
	int length=a->length;
	a->id=b->id;
	a->arrival_time=b->arrival_time;
	a->length=b->length;
	
	b->id=id;
	b->arrival_time=arrival_time;
	b->length=length;
}
//Function for implementing FIFO
void FIFO(char *argv,char *arg)
{
			FILE *fp;
			fp=fopen(argv,"r");
			if(fp==NULL)
			{
				printf("Error opening the file\n");
				exit(1);
			}
			struct job *head=NULL;
			struct job *tail=NULL;
			int arrival_time,length,id=0;
			while(fscanf(fp, "%d,%d", &arrival_time, &length) == 2)
			{
				//printf("%d, %d\n",arrival_time,length);
				struct job *new = (struct job *) malloc(sizeof(struct job));
				new->id=id;
				new->arrival_time=arrival_time;
				new->length=length;
				new->next=NULL;
				if(head==NULL)
				{
					head=new;
					tail=new;
				}
				else
				{
					tail->next=new;
					tail=new;
				}
				id++;
				
			}
			printf("Execution trace with FIFO:\n");
			int current=0;
			struct job *curr=head;
			while(curr!=NULL)
			{
				//int wait_time=current-curr->arrival_time;
				
				//printf("%d\n",current);
				printf("t=%d: [Job %d] arrived at [%d], ran for: [%d]\n",current,curr->id,curr->arrival_time,curr->length);
				current=current+curr->length;
				
				curr=curr->next;
				
			}
			printf("End of execution with FIFO.\n");
			
			if(strcmp(arg,"1")==0)
			{
				int current =0;
				//int clock=0;
				//int waiting_time=0;
				int total_turnaround_time=0;
				int total_response_time=0;
				struct job *curr = head;
				int sum_r = 0, sum_t = 0, sum_wait=0,count=0;
				printf("Begin analyzing FIFO:\n");
				while(curr!=NULL)
				{
					int response_time = current - curr->arrival_time;
					total_response_time += response_time;
					int finish_time = current + curr->length;
					int turnaround_time = finish_time - curr->arrival_time;
					total_turnaround_time+=turnaround_time;
					int wait_time = response_time;
					
					printf("Job %d -- Response time: %d  Turnaround: %d  Wait: %d\n", curr->id, response_time, turnaround_time, wait_time);
					sum_r+=response_time;
					sum_t+=turnaround_time;
					sum_wait+=wait_time;
					current=finish_time;
					
					count++;
					curr = curr->next;
					
					
					
				}
				
				//printf("%d\n",count);
				//printf("%d\n",sum_r);
				float avg_r=0.0, avg_t=0.0, avg_wait = 0.0;
				avg_r=(float)sum_r/count;
				avg_t=(float)sum_t/count;
				avg_wait=(float)sum_wait/count;
				
				printf("Average -- Response: %.2f  Turnaround %.2f  Wait %.2f\n",avg_r,avg_t, avg_wait);
				printf("End analyzing FIFO.\n");
				
			}
			
			
}

//Function for implementing SJF
void SJF(char *argv,char *arg)
{
			FILE *fp;
			fp=fopen(argv,"r");
			if(fp==NULL)
			{
				printf("Error opening the file\n");
				exit(1);
			}
			struct job *head=NULL;
			struct job *tail=NULL;
			
			
			int arrival_time,length,id=0;
			while(fscanf(fp, "%d,%d", &arrival_time, &length) == 2)
			{
				//printf("%d, %d\n",arrival_time,length);
				struct job *new = (struct job *) malloc(sizeof(struct job));
				
				new->id=id;
				new->arrival_time=arrival_time;
				new->length=length;
				new->next=NULL;
				
				
				
				if(head==NULL)
				{
					head=new;
					tail=new;
				}
				else
				{
					tail->next=new;
					tail=new;
				}
				
				
				id++;
				
			}
			printf("Execution trace with SJF:\n");
			int current=0;
			int clock=0;
			struct job *curr=head;
			struct job *crnt, *next;
			for(crnt=head; crnt!=NULL; crnt=crnt->next) {
  				for(next=crnt->next; next!=NULL; next=next->next) {
    				if(crnt->length > next->length) {
      					swap(crnt, next);
    				}
  			}
			}
			while(curr!=NULL)
			{
				struct job *temp=curr->next;
				struct job *min = curr;
				
				while(temp!=NULL)
				{
					if(curr->arrival_time>temp->arrival_time )
					{
						swap(curr,temp);
					}
					
					else if(curr->arrival_time == temp->arrival_time)
					{
						if(curr->length>temp->length)
						{
							swap(curr,temp);
						}
						else if(curr->length==temp->length)
						{
							if(curr->id>temp->id)
							{
								swap(curr,temp);
							}
						}
					}
					
					if(temp->arrival_time <=clock && temp->length < min->length)
					{
						min=temp;
					}
					
					
					temp=temp->next;
				}
				if(min!=curr)
				{
					swap(min,curr);
				}
				clock+=curr->length+1;
				//printf("%d\n",clock);
				curr=curr->next;
			}
			
			
			curr=head;
			while(curr!=NULL)
			{
			
				if(current<curr->arrival_time)
				{
					current=curr->arrival_time;
				}
				printf("t=%d: [Job %d] arrived at [%d], ran for: [%d]\n",current,curr->id,curr->arrival_time,curr->length);
				current=current+curr->length;
				
				curr=curr->next;
				
			}	
			
				
				
			printf("End of execution with SJF.\n");
			
			
			if(strcmp(arg,"1")==0)
			{
				int current =0;
				//int clock=0;
				//int waiting_time=0;
				int total_turnaround_time=0;
				int total_response_time=0;
				struct job *curr = head;
				int sum_r = 0, sum_t = 0, sum_wait=0,count=0;
				struct job2 *head3=NULL;
				struct job2 *tail3=NULL;
				printf("Begin analyzing SJF:\n");
				while(curr!=NULL)
				{
					if(current<curr->arrival_time)
					{
						current=curr->arrival_time;
					}
					int response_time = current - curr->arrival_time;
					//printf("%d\n",curr->length);
					//printf("%d\n",curr->arrival_time);
					
					total_response_time += response_time;
					int finish_time = current + curr->length;
					int turnaround_time = finish_time - curr->arrival_time;
					
					total_turnaround_time+=turnaround_time;
					int wait_time = response_time;
					struct job2 *new3 = (struct job2 *) malloc(sizeof(struct job2));
					new3->id=curr->id;
					new3->response_time=response_time;
					new3->turnaround_time=turnaround_time;
					new3->wait_time=wait_time;
					new3->next=NULL;
					if(head3==NULL)
					{
						head3=new3;
						tail3=new3;
					}
					else
					{
						tail3->next=new3;
						tail3=new3;
					}
					sum_r+=response_time;
					sum_t+=turnaround_time;
					sum_wait+=wait_time;
					current=finish_time;
					
					count++;
					curr = curr->next;
					
					
					
				}
				
				struct job2 *i=head3;
				struct job2 *sorted = NULL;
				while(i!=NULL)
				{
					//printf("%d, %d, %d, %d\n",i->id,i->response_time,i->turnaround_time,i->wait_time);
					//i=i->next;
					
					
					struct job2 *next_node = i->next;
					if(sorted==NULL || i->id < sorted->id){
						i->next = sorted;
						sorted = i;
					}
					else{
						struct job2 *search=sorted;
						while(search->next!=NULL && search->next->id <= i->id)
						{
							search=search->next;
						}
						i->next=search->next;
						i->next=search->next;
						search->next=i;
						if(i->next==NULL)
						{
							tail3=i;
						}
						
					}
					i=next_node;					
				}
				head3=sorted;
				struct job2 *j=sorted;
				
				
				while(j!=NULL)
				{
					printf("Job %d -- Response time: %d  Turnaround: %d  Wait: %d\n",j->id,j->response_time,j->turnaround_time,j->wait_time);
					j=j->next;
				}
				
				j=sorted;
				while(j!=NULL)
				{
					struct job2 *next_node = j->next;
					free(j);
					j=next_node;
				}
				
				
				
				
				//printf("%d\n",count);
				//printf("%d\n",sum_r);
				float avg_r=0.0, avg_t=0.0, avg_wait = 0.0;
				avg_r=(float)sum_r/count;
				avg_t=(float)sum_t/count;
				avg_wait=(float)sum_wait/count;
				
				printf("Average -- Response: %.2f  Turnaround %.2f  Wait %.2f\n",avg_r,avg_t, avg_wait);
				printf("End analyzing SJF.\n");
				
			}
}
//function for removing completed jobs in Round Robin
void remove_process(struct job** head_ref, struct job** tail_ref,struct job* process_to_remove) {
    struct job* current = *head_ref;
    if (current == process_to_remove) {
        *head_ref = current->next;
        if (*head_ref == NULL) {
            *tail_ref = NULL;
        }
    } else {
        while (current->next != process_to_remove) {
            current = current->next;
        }
        current->next = process_to_remove->next;
        if (current->next == NULL) {
            *tail_ref = current;
        }
    }
}
//function to sort linked list in ascending order of id.
struct merged_job *sort_linked_list(struct merged_job *head) {
    struct merged_job *temp, *i, *j;

    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->id > j->id) {
                temp = (struct merged_job *)malloc(sizeof(struct merged_job));
                temp->id = i->id;
                temp->response_time = i->response_time;
                temp->turnaround_time = i->turnaround_time;
                temp->wait_time = i->wait_time;

                i->id = j->id;
                i->response_time = j->response_time;
                i->turnaround_time = j->turnaround_time;
                i->wait_time = j->wait_time;

                j->id = temp->id;
                j->response_time = temp->response_time;
                j->turnaround_time = temp->turnaround_time;
                j->wait_time = temp->wait_time;

                free(temp);
            }
        }
    }

    return head;
}
//Function to remove duplicates from the sorted linked list
struct merged_job *remove_duplicates(struct merged_job *head) {
    struct merged_job *current, *prev, *temp;
    int id;

    current = head;
    while (current != NULL) {
        id = current->id;
        prev = current;
        while (prev->next != NULL) {
            if (prev->next->id == id) {
                temp = prev->next;
                prev->next = temp->next;
                free(temp);
            } else {
                prev = prev->next;
            }
        }
        current = current->next;
    }

    return head;
}



//Function to implement Round Robin algorithm
void Round_Robin(char *argv, char *arg, char *timeslice)
{
	FILE *fp;
	fp=fopen(argv,"r");
	if(fp==NULL)
	{
		printf("Error opening the file\n");
		exit(1);
	}
	struct job *head=NULL;
	struct job *tail=NULL;
	
	int count=0;
			
	int arrival_time,length,id=0;
	while(fscanf(fp, "%d,%d", &arrival_time, &length) == 2)
	{
		//printf("%d, %d\n",arrival_time,length);
		struct job *new = (struct job *) malloc(sizeof(struct job));
		
				
		new->id=id;
		new->arrival_time=arrival_time;
		new->length=length;
		new->remaining_time=length;
		new->start_time=0;
    		new->end_time=0;
    		new->turnaround_time=0;
    		new->wait_time=0;
    		new->response_time=-1;
		
		new->next=NULL;
		
			
				
				
		if(head==NULL)
		{
			head=new;
			tail=new;
		}
		else
		{
			tail->next=new;
			tail=new;
			//insert_process(&head,new);
		}
		
		
				
		count++;		
		id++;
				
	}
		
	printf("Execution trace with RR:\n");
	int current_time = 0;
    int time_quantum = atoi(timeslice);
    struct job *head2=head;
    struct job *curr = head2;
    
    //struct job *curr2=curr;
    int flag = 0;
    int total_wait_time = 0, total_turnaround_time = 0, total_response_time = 0;
    //int num_jobs = id;
    //struct job2 *new2 = (struct job2 *) malloc(sizeof(struct job2));
    //struct job2 *new_head=NULL;
    //struct job2 *new_tail=NULL;
    //new2=new_head;
    struct completed_job* completed_head = NULL;
    struct completed_job* completed_tail = NULL;
    struct merged_job* merged_head=NULL;
    struct merged_job* merged_tail=NULL;
    
    struct merged_job* merged_head2=NULL;
    struct merged_job* merged_tail2=NULL;

    while(head2 != NULL)
    {
        flag = 0;
        curr = head2;
        while(curr != NULL)
        {
        	
            if(curr->arrival_time <= current_time && curr->remaining_time > 0)
            {
                flag = 1;
                if(curr->remaining_time > time_quantum)
                {
                    if(curr->response_time==-1)
                    {
                    	curr->response_time=current_time-curr->arrival_time;
                    	
                    }
                    printf("t=%d: [Job %d] arrived at [%d], ran for: [%d]\n", current_time, curr->id, curr->arrival_time, time_quantum); 
                    //printf("%d\n",curr->id);
                    
                    
                                     
                    curr->remaining_time -= time_quantum;
                   
                    current_time += time_quantum;
                    curr->wait_time += (current_time - time_quantum - curr->arrival_time);
                   
                    //printf("%d\n",curr->wait_time);
                    
                   //total_wait_time += (current_time - curr->arrival_time - time_quantum);
                }
                else
                {
                    if(curr->response_time == -1) {
                        curr->response_time = current_time-curr->arrival_time; // Update response time                        
                    }
                    printf("t=%d: [Job %d] arrived at [%d], ran for: [%d]\n", current_time, curr->id, curr->arrival_time, curr->remaining_time);
                    //printf("%d\n",curr->id);
                    
                    curr->end_time=current_time+curr->remaining_time;
        	     curr->turnaround_time=curr->end_time-curr->arrival_time;
        	     curr->wait_time=curr->turnaround_time-curr->length;
        	     
        	   
        	     
                     total_wait_time += curr->wait_time;
                     total_turnaround_time += curr->turnaround_time;
                     total_response_time += curr->response_time;
             
                    current_time += curr->remaining_time;
                    curr->remaining_time = 0;
                    
                    //printf("%d\n",curr->wait_time);                    
                }
            }
            curr = curr->next;
           
        }

        if(flag == 0)
        {
            current_time++;
        }
        curr=head2;
	
        
        while(curr != NULL)
        {
            if(curr->remaining_time == 0)
            {
            	
            	//curr->response_time=current_time-curr->arrival_time;
            	
            	
            	struct completed_job* completed_job = (struct completed_job*)malloc(sizeof(struct completed_job));
    		completed_job->id = curr->id;
    		completed_job->response_time = curr->response_time;
    		completed_job->turnaround_time = curr->turnaround_time;
    		completed_job->wait_time = curr->wait_time;
    		completed_job->next = NULL;
    		if (completed_head == NULL) {
        		completed_head = completed_job;
        		completed_tail = completed_job;
    		} 
    		else {
        		completed_tail->next = completed_job;
        		completed_tail = completed_job;
    		}
            	
                struct job *temp = curr;
                //struct job3 *temp2=curr_new;
                 
                curr = curr->next;
             
                
                remove_process(&head2, &tail,temp);
                
                //insert_process(&head2,temp);
            }
            else
     
            {
            	//printf("%d\n", curr->wait_time);
            	//curr->response_time=current_time-curr->arrival_time;
            	
            	 
                curr = curr->next;
                
                //insert_process(&head2, temp);
                //curr = curr->next;
            }
        }
        //head2=head2->next;
    }

    printf("End of execution with RR.\n");   
    if(strcmp(arg,"1")==0)
    {
    	printf("Begin analyzing RR:\n");
    	struct job *i=head;
    	
    	int id;
	int response_time;
	int turnaround_time;
	int wait_time;
    	while(i!=NULL)
    	{
    		struct merged_job* merged = (struct merged_job*)malloc(sizeof(struct merged_job));
    		id=i->id;
    		merged->id = id;
    		response_time=i->response_time;
    		merged->response_time = response_time;
    		turnaround_time=i->turnaround_time;
    		merged->turnaround_time = turnaround_time;
    		wait_time=i->wait_time;
    		merged->wait_time = wait_time;
    		merged->next = NULL;
    		if (merged_head == NULL) {
        		merged_head = merged;
        		merged_tail = merged;
    		} 
    		else {
        		merged_tail->next = merged;
        		merged_tail = merged;
    		}
    		
    		
    		i=i->next;
    	}    	
    	struct completed_job *j=completed_head;
    	while(j!=NULL)
    	{
    		struct merged_job* merged2 = (struct merged_job*)malloc(sizeof(struct merged_job));
    		id=j->id;
    		merged2->id = id;
    		response_time=j->response_time;
    		merged2->response_time = response_time;
    		turnaround_time=j->turnaround_time;
    		merged2->turnaround_time = turnaround_time;
    		wait_time=j->wait_time;
    		merged2->wait_time = wait_time;
    		merged2->next = NULL;
    		if (merged_head2 == NULL) {
        		merged_head2 = merged2;
        		merged_tail2 = merged2;
    		} 
    		else {
        		merged_tail2->next = merged2;
        		merged_tail2 = merged2;
    		}
    		
    		
    		j=j->next;
    	}    	
    	struct merged_job *a=merged_head;
    	while(a->next!=NULL)
    	{
    		//printf("%d\n",a->id);
    		a=a->next;
    	}
    	//printf("%d\n",a->id);
    	
    	a->next=merged_head2;
    	
    	merged_head = sort_linked_list(merged_head);
    	merged_head = remove_duplicates(merged_head);
    	struct merged_job *k=merged_head;
    	while(k!=NULL)
    	{
    		printf("Job %d -- Response time: %d  Turnaround: %d  Wait: %d\n",k->id,k->response_time,k->turnaround_time,k->wait_time);
    		k=k->next;
    	}
    	int sum_r=0,sum_t=0,sum_wait=0;
    	struct merged_job *p = merged_head;
    	while(p!=NULL)
    	{
    		sum_r+=p->response_time;
    		sum_t+=p->turnaround_time;
    		sum_wait+=p->wait_time;
    		
    		p=p->next;
    	}   	
    	float avg_r=0.0, avg_t=0.0, avg_wait = 0.0;
	avg_r=(float)sum_r/count;
	avg_t=(float)sum_t/count;
	avg_wait=(float)sum_wait/count;
	printf("Average -- Response: %.2f  Turnaround %.2f  Wait %.2f\n",avg_r,avg_t, avg_wait);
	printf("End analyzing RR.\n");				
    }
}
int main(int argc, char *argv[])
{
	
	if(strcmp(argv[1],"0")==0)
	{
		if (strcmp(argv[2],"FIFO")==0)
		{
			
			FIFO(argv[3],argv[1]);
			
		}
		else if(strcmp(argv[2],"SJF")==0)
		{
			
			SJF(argv[3],argv[1]);
		}
		else if(strcmp(argv[2],"RR")==0)
		{
			Round_Robin(argv[3],argv[1],argv[4]);
		}
		
	}
	else if(strcmp(argv[1],"1")==0)
	{
		if (strcmp(argv[2],"FIFO")==0)
		{
			FIFO(argv[3],argv[1]);
		}
		else if(strcmp(argv[2],"SJF")==0)
		{
			SJF(argv[3],argv[1]);
		}
		else if(strcmp(argv[2],"RR")==0)
		{
			Round_Robin(argv[3],argv[1],argv[4]);
		}
	}
	return 0;
}

