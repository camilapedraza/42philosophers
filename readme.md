# Philosophers

_This project has been created as part of the 42 curriculum by mpedraza._

## Description

The **Philosophers** project is a multithreaded simulation of the classic *Dining Philosophers Problem* formulated by Edsger Dijkstra. The goal is to learn correct synchronization and timing strategies in a concurrent program using POSIX threads and mutexes in C.

In the simulation:

- Philosophers sit at a round table and alternate between **thinking**, **eating**, and **sleeping**.
- Each philosopher needs **two forks** (shared resources protected by mutexes) to eat.
- If a philosopher does not eat within `the stipulated milliseconds, they **die** and the simulation stops.
- Optionally, the simulation also stops once every philosopher has eaten a required number of meals.

This project focuses on preventing:
- **Deadlocks**
- **Data races**
- **Starvation** (under reasonable constraints)

and ensuring:
- Correct, readable output
- Accurate timing (death printed within **10ms** of the actual death moment)

### Implementation Notes
In this implementation:
- Fork acquisition uses a deterministic ordering to prevent deadlocks (philosophers always grabbing for the same fork or waiting forever on a fork).
- Every other philosopher (even ID number) is slightly staggered at start to reduce initial contention (and avoid starvation and death)
- Shared state (last meal time, meal counters, stop flag) is protected by mutexes.
- Printing is serialized and mutexed to avoid interleaved output and to guarantee no logs after death.
- Timing uses `gettimeofday()` (project constraint) with millisecond timestamps.
- A custom `precise_sleep()` loop avoids accumulated drift from `usleep()` oversleeping.
- A small thinking delay to desynchronize philosophers (enough to avoid race for resources but not too much as to induce unnecessary death from starvation).

Testing ensured:
- Correct death detection within the allowed 10ms (best case 0ms, worst case 4ms)
- Absence of data races with Helgrind
- Stability under common stress cases:
  ```bash
  ./philo 5 800 200 200
  ./philo 4 310 200 100
  ./philo 200 203 100 100
  ```

## Instructions

### Compiling & Running

Build with:
```bash
cd philo
make
```

Run with at least 4 arguments, as follows:
```bash
./philo philosophers time_to_die time_to_eat time_to_sleep [required_meals]
```
where:
- `philosophers` is how many philosophers will sit at the table
- `time_to_die` is the max time than can elapse between meals otherwise the philosopher dies
- `time_to_eat` is how long each meal will take
- `time_to_sleep` is how long each philosopher will sleep after eating
- `[required_meals]` (optional) is the minimum number of meals per philosopher after which the simulation can stop.

All **times** must be provided in milliseconds, and the _minimum_ for each argument is `1`.

## Resources

- [Original Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Understanding Philosophers Gitbook](https://42-cursus.gitbook.io/guide/3-rank-03/philosophers/understand-philosophers)

### AI Usage
AI tools were used as a learning and documentation assistant for:
- Understanding concurrency concepts in depth (deadlocks, starvation, jitter, print compression)
- Testing reasoning about timing drift and why `usleep()` can overshoot
- Reviewing responsiveness and performance (designing test cases, identifying red flags and signals)

AI was NOT used to directly generate the project’s final core implementation. The synchronization strategy, thread routines, timing logic, utilities and modules were all implemented and validated manually (including testing and Helgrind checks).