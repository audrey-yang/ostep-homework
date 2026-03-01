# Homework

1. **Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.**

   ```
   ./scheduler.py -p SJF -l 200,200,200

    Job 0 ( length = 200.0 )
    Job 1 ( length = 200.0 )
    Job 2 ( length = 200.0 )
   ```

   | 0   | 200 | 400 |
   | --- | --- | --- |
   | 0   | 1   | 2   |

   Turnaround time (t_completion - t_arrival):
   - Job 0: 200 - 0 = 200
   - Job 1: 400 - 0 = 400
   - Job 2: 600 - 0 = 600
   - Average = 400

   Response time (t_firstrun - t_arrival):
   - Job 0: 0 - 0 = 0
   - Job 1: 200 - 0 = 200
   - Job 2: 400 - 0 = 400
   - Average = 200

   ```
   ./scheduler.py -p FIFO -l 200,200,200

    Job 0 ( length = 200.0 )
    Job 1 ( length = 200.0 )
    Job 2 ( length = 200.0 )
   ```

   | 0   | 200 | 400 |
   | --- | --- | --- |
   | 0   | 1   | 2   |

   Turnaround time (t_completion - t_arrival):
   - Job 0: 200 - 0 = 200
   - Job 1: 400 - 0 = 400
   - Job 2: 600 - 0 = 600
   - Average = 400

   Response time (t_firstrun - t_arrival):
   - Job 0: 0 - 0 = 0
   - Job 1: 200 - 0 = 200
   - Job 2: 400 - 0 = 400
   - Average = 200

2. **Now do the same but with jobs of different lengths: 100, 200, and 300.**

   ```
   ./scheduler.py -p SJF -l 300,200,100

    Job 0 ( length = 300.0 )
    Job 1 ( length = 200.0 )
    Job 2 ( length = 100.0 )
   ```

   | 0   | 100 | 200 | 300 | 400 | 500 |
   | --- | --- | --- | --- | --- | --- |
   | 2   | 1   | 1   | 0   | 0   | 0   |

   Turnaround time (t_completion - t_arrival):
   - Job 0: 600 - 0 = 600
   - Job 1: 300 - 0 = 300
   - Job 2: 100 - 0 = 100
   - Average = 333.33

   Response time (t_firstrun - t_arrival):
   - Job 0: 300 - 0 = 300
   - Job 1: 100 - 0 = 100
   - Job 2: 0 - 0 = 0
   - Average = 133.33

   ```
   ./scheduler.py -p FIFO -l 300,200,100

    Job 0 ( length = 300.0 )
    Job 1 ( length = 200.0 )
    Job 2 ( length = 100.0 )
   ```

   | 0   | 100 | 200 | 300 | 400 | 500 |
   | --- | --- | --- | --- | --- | --- |
   | 0   | 0   | 0   | 1   | 1   | 2   |

   Turnaround time (t_completion - t_arrival):
   - Job 0: 300 - 0 = 300
   - Job 1: 500 - 0 = 500
   - Job 2: 600 - 0 = 600
   - Average = 466.67

   Response time (t_firstrun - t_arrival):
   - Job 0: 0 - 0 = 0
   - Job 1: 300 - 0 = 300
   - Job 2: 500 - 0 = 500
   - Average = 266.67

3. **Now do the same, but also with the RR scheduler and a time-slice of 1.**

   ```
   ./scheduler.py -p RR -q 1 -l 200,200,200

    Job 0 ( length = 200.0 )
    Job 1 ( length = 200.0 )
    Job 2 ( length = 200.0 )
   ```

   Turnaround time (t_completion - t_arrival):
   - Job 0: 598 - 0 = 598
   - Job 1: 599 - 0 = 599
   - Job 2: 600 - 0 = 600
   - Average = 599

   Response time (t_firstrun - t_arrival):
   - Job 0: 0 - 0 = 0
   - Job 1: 1 - 0 = 1
   - Job 2: 2 - 0 = 2
   - Average = 1

   ```
   ./scheduler.py -p RR -q 1 -l 300,200,100

    Job 0 ( length = 300.0 )
    Job 1 ( length = 200.0 )
    Job 2 ( length = 100.0 )
   ```

   Turnaround time (t_completion - t_arrival):
   - Job 0: 300 - 0 = 600
   - Job 1: 500 - 0 = 500
   - Job 2: 600 - 0 = 300
   - Average = 466.67

   Response time (t_firstrun - t_arrival):
   - Job 0: 0 - 0 = 0
   - Job 1: 1 - 0 = 1
   - Job 2: 2 - 0 = 2
   - Average = 1

4. **For what types of workloads does SJF deliver the same turnaround times as FIFO?**
   SJF delivers the same turnaround time as FIFO when the workload lengths are all the same or the workloads are introduced in order of increasing job length.

5. **For what types of workloads and quantum lengths does SJF deliver the same response times as RR?**
   SFJ delivers the same response time as RR when quantum lengths are the same as job lengths and the job lengths are all the same.

6. **What happens to response time with SJF as job lengths increase? Can you use the simulator to demonstrate the trend?**
   As job lengths increase, the response time with SJF also increases.

   ```
    ./scheduler.py -p SJF -l 1,2,3 -c
    Average -- Response: 1.33

    ./scheduler.py -p SJF -l 1,20,30 -c
    Average -- Response: 7.33

    ./scheduler.py -p SJF -l 1,200,300 -c
    Average -- Response: 67.33
   ```

7. **What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case response time, given N jobs?**
   As quantum lengths increase, the response time also increases.

   Say we have $N$ jobs and a quantum length $q$. The first job with run at time 0, the second at time $q$, and the $N$th at time $(N-1)q$. If we assume all jobs arrive at time 0, then these start times are also the response times.

   The longest response time is then $$(N-1)q$$

   The average response time is then $$\frac{q\sum_{i=1}^{N-1}i}{N} = \frac qN\frac{N(N-1)}{2} = \frac{q(N-1)}{2}$$
