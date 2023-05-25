Team members:
Vignesh Sundaram (vsundaram@wpi.edu), Padmesh Naik (pnaik@wpi.edu)


Part 5:

In the file "measurement.c" we are using the methodology described in OSTEP chapter 6 to measure context switch times. We are using a design where 2 processes communicate using pipes. Child process reads a character from one pipe and writes character to other pipe in loop and similarly parent process writes to first pipe and reads from second pipe. We measure context switch times by checking how long it takes to do iterations of passing the characters back and forth between parent and child process. Two pipes have been created i.e. file_descriptor1 and file_descriptor2.

However, the measurement given here may not be accurate. It may also include other things that affect the performance of the system. One issue is the processes takes time to read and write from pipes and may not actually reflect to time it takes to save and restore the state of process. There are certain factors which include size of the message, buffering of pipe and scheduling by OS.
There can also be other factors like cache miss, memory latency, etc. which may be included in our measurement. Scheduler can also schedule another process to run while the parent and child are waiting for other process to read or write from file. This scenario can increase context switch time since system has to save the state of more processes.

Also, there can be system call overhead. Whenever process needs to make system call, it needs to switch to kernel mode, thus incurring additional overhead.

The context switch time following the above approach turns out to be 13.493 microseconds.

Another approach for measuring context switch time is using the concept of shared memory.
We create a shared memory segment using shmget system call. We then attach this shared memory segment to address of child and parent process using shmat system call.
We then activate the timer using gettimeofday(). Parent process writes the value to the shared memory and waits for child process to read the value and write the new value to shared memory segment. In the child process, read the value, calculate new value and write new value to shared memory segment. Then wait for parent to read the new value and this process goes on for multiple times and context switch times are measured. We then obtain average of all the context switch times.
This code is in measure.c