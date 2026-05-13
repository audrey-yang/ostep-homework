# Homework

1. Run a few randomly-generated problems with just two jobs and
   two queues; compute the MLFQ execution trace for each. Make
   your life easier by limiting the length of each job and turning off
   I/Os.

   ```
   ./mlfq.py -j 2 -Q 1,2 -m 5 -M 0 -s 1

    Here is the list of inputs:
   OPTIONS jobs 2
   OPTIONS queues 2
   OPTIONS allotments for queue  1 is   1
   OPTIONS quantum length for queue  1 is  1
   OPTIONS allotments for queue  0 is   1
   OPTIONS quantum length for queue  0 is  2
   OPTIONS boost 0
   OPTIONS ioTime 5
   OPTIONS stayAfterIO False
   OPTIONS iobump False


    For each job, three defining characteristics are given:
    startTime : at what time does the job enter the system
    runTime : the total CPU time needed by the job to finish
    ioFreq : every ioFreq time units, the job issues an I/O
    (the I/O takes ioTime units to complete)

    Job List:
    Job  0: startTime   0 - runTime   3 - ioFreq   0
    Job  1: startTime   0 - runTime   4 - ioFreq   0

    Compute the execution trace for the given workloads.
    If you would like, also compute the response and turnaround
    times for each of the jobs.

    Time    0   1   2   3   4   5   6   7
    Q1      0   1
    Q0              0   0   1   1   1

    J0: response 0, turnaround 4
    J1: response 1, turnaround 7

    Average: response 0.5, turnaround 5.5
   ```

2. How would you run the scheduler to reproduce each of the examples in the chapter?

   ```
   Example 1: ./mlfq.py -l 0,200,0 -Q 10,10,10
   Example 2: ./mlfq.py -l 0,200,0:100,20,0 -Q 10,10,10
   Example 3: ./mlfq.py -l 0,200,0:50,15,1 -i 9 -S -Q 10,10,10

   ```

3. How would you configure the scheduler parameters to behave just
   like a round-robin scheduler?

   ```
   ./mlfq.py -Q 1
   ```

4. Craft a workload with two jobs and scheduler parameters so that
   one job takes advantage of the older Rules 4a and 4b (turned on
   with the -Sflag) to game the scheduler and obtain 99% of the CPU
   over a particular time interval.

   ```
   ./mlfq.py -l 0,100,0:50,50,9 -i 1 -Q 10,10,10 -S
   ```

5. Given a system with a quantum length of 10 ms in its highest queue,
   how often would you have to boost jobs back to the highest priority
   level (with the -B flag) in order to guarantee that a single long-
   running (and potentially-starving) job gets at least 5% of the CPU?

   5% CPU means that in 200ms, it will need to run for 10ms, giving us `-B 200`.

6. One question that arises in scheduling is which end of a queue to
   add a job that just finished I/O; the -I flag changes this behavior
   for this scheduling simulator. Play around with some workloads
   and see if you can see the effect of this flag.

   -I flag gives priority to jobs with finished I/O. Some observations:
   - Non-I/O jobs wait for longer and end with a greater turnaround time
   - With multiple I/O jobs starting at the same time, those which start running first finish first

   ```
   Random
   ./mlfq.py -j 5 -Q 5,5,5 -I
   Job List (ioTime 5):
    Job  0: startTime   0 - runTime  84 - ioFreq   7
    Job  1: startTime   0 - runTime  42 - ioFreq   3
    Job  2: startTime   0 - runTime  51 - ioFreq   4
    Job  3: startTime   0 - runTime  78 - ioFreq   3
    Job  4: startTime   0 - runTime  48 - ioFreq   6
   Without -I
    Job  0: startTime   0 - response   0 - turnaround 279
    Job  1: startTime   0 - response   5 - turnaround 237
    Job  2: startTime   0 - response   8 - turnaround 256
    Job  3: startTime   0 - response  12 - turnaround 346
    Job  4: startTime   0 - response  15 - turnaround 202
   With -I
    Job  0: startTime   0 - response   0 - turnaround 296
    Job  1: startTime   0 - response   5 - turnaround 206
    Job  2: startTime   0 - response   8 - turnaround 238
    Job  3: startTime   0 - response  12 - turnaround 329
    Job  4: startTime   0 - response  18 - turnaround 261

   Gaming the system example
   ./mlfq.py -l 0,100,0:50,50,9 -i 1 -Q 10,10,10 -I
   Job List (ioTime 1):
    Job  0: startTime   0 - runTime 100 - ioFreq   0
    Job  1: startTime  50 - runTime  50 - ioFreq   9
   Without -I
    Job  0: startTime   0 - response   0 - turnaround 140
    Job  1: startTime  50 - response   0 - turnaround 101
   With -I
    Job  0: startTime   0 - response   0 - turnaround 150
    Job  1: startTime  50 - response   0 - turnaround  81

   One non-I/O job with many I/O jobs
   ./mlfq.py -l 0,50,0:5,50,8:6,50,8:7,50,8 -i 1 -Q 10,10,10 -I
   Job List:
    Job  0: startTime   0 - runTime 100 - ioFreq   0
    Job  1: startTime   5 - runTime  50 - ioFreq   8
    Job  2: startTime   6 - runTime  50 - ioFreq   8
    Job  3: startTime   7 - runTime  50 - ioFreq   8
   Without -I
    Job  0: startTime   0 - response   0 - turnaround 140
    Job  1: startTime   5 - response   5 - turnaround 191
    Job  2: startTime   6 - response  12 - turnaround 192
    Job  3: startTime   7 - response  19 - turnaround 193
   With -I
    Job  0: startTime   0 - response   0 - turnaround 200
    Job  1: startTime   5 - response   5 - turnaround 166
    Job  2: startTime   6 - response  12 - turnaround 157
    Job  3: startTime   7 - response  21 - turnaround 186

   Multiple of the same I/O job
   ./mlfq.py -l 0,50,1:0,50,1:0,50,1:0,50,1:0,50,1:0,50,1 -i 1 -Q 10,10,10 -I
   Job List:
    Job  0: startTime   0 - runTime  50 - ioFreq   1
    Job  1: startTime   0 - runTime  50 - ioFreq   1
    Job  2: startTime   0 - runTime  50 - ioFreq   1
    Job  3: startTime   0 - runTime  50 - ioFreq   1
    Job  4: startTime   0 - runTime  50 - ioFreq   1
    Job  5: startTime   0 - runTime  50 - ioFreq   1
   Without -I
    Job  0: startTime   0 - response   0 - turnaround 295
    Job  1: startTime   0 - response   1 - turnaround 296
    Job  2: startTime   0 - response   2 - turnaround 297
    Job  3: startTime   0 - response   3 - turnaround 298
    Job  4: startTime   0 - response   4 - turnaround 299
    Job  5: startTime   0 - response   5 - turnaround 300
   With -I
    Job  0: startTime   0 - response   0 - turnaround 180
    Job  1: startTime   0 - response   1 - turnaround 179
    Job  2: startTime   0 - response  20 - turnaround 239
    Job  3: startTime   0 - response  21 - turnaround 240
    Job  4: startTime   0 - response  40 - turnaround 300
    Job  5: startTime   0 - response  41 - turnaround 299
   ```
