# philo

Implementation of the dining philosophers problem using POSIX threads and mutexes.

## Build

```bash
make
./philo <nb_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [nb_meals]
```

```bash
./philo 5 800 200 200        # basic run, nobody dies, runs until interrupted
./philo 5 800 200 200 7      # stops once every philosopher has eaten 7 times
./philo 1 800 200 200        # single philosopher, dies at 800
```

Times are in milliseconds. Each line of output is `<ms since start> <id> <action>`, with ids starting at 1 and actions `has taken a fork`, `is eating`, `is sleeping`, `is thinking` or `died`.

## How it works

Each philosopher is a thread (`routine_philo`), each fork is a mutex. Philosopher `i` has fork `i - 1` on its right and fork `i % n` on its left. The main thread only sets things up, starts the threads and joins them. A separate monitor thread, `routine_checker`, decides when the simulation ends.

**Start:** the main thread holds a `ready` mutex while it creates the philosopher threads. Each philosopher waits on that mutex, so none of them starts before all are created and the start time is set.

**Fork order:** every philosopher takes its right fork first, then its left fork. To keep neighbours from all grabbing their right fork at the same moment, even-numbered philosophers wait 100 ms before their first meal.

**Cycle:** eat, sleep, think, repeat. Before each action a philosopher checks whether the simulation is over (someone died, or it has eaten `nb_meals` times). It does not check during a meal or a sleep, so it finishes that action first.

**Monitor:** `routine_checker` loops, without pausing, over two checks:
- `check_full`: when `nb_meals` is given and every philosopher has eaten that many times, the monitor stops. No message is printed. Each philosopher also stops on its own right after its last meal.
- `check_dead`: for each philosopher, if `now - last_meal >= time_to_die`, the monitor sets the shared `dead` flag, prints `died` and stops. `last_meal` is the time the philosopher started its last meal (0 before the first one).

**Shared state:** the `dead` flag is protected by the `check_dead` mutex. Each philosopher has its own mutex for `last_meal` (`check_meals[i]`) and for its `full` flag (`check_full[i]`). Output goes through `printf` with no dedicated print mutex. Timing uses `gettimeofday`, and `ft_usleep` sleeps in 500 µs steps until the requested time has passed.

## Input

- Wrong number of arguments: error, with an example command (`./philo 5 800 200 200`).
- Negative value: error, `negative number`.
- Value above `INT_MAX` or longer than 10 digits: error, `INT_MAX`.
- Non-numeric input is not rejected. Parsing stops at the first non-digit, so `abc` is read as 0 and `12abc` as 12.
- `nb_meals = 0`: no thread is started, but the message printed is `Error: failed to malloc something.`

## Edge cases

- 1 philosopher: it takes its only fork and cannot take a second one, so its thread stops there. The monitor prints `died` once `time_to_die` has passed (`800 1 died` for `./philo 1 800 200 200`).
- `time_to_eat > time_to_die`: the monitor measures from the start of the last meal and does not wait for a meal to end, so the death is reported at `time_to_die`. `./philo 4 310 400 100` prints a `died` line at 310 ms.
- Without `nb_meals`, the simulation only ends when a philosopher dies.

## Structure

```
├── includes/philo.h        - structs, error messages, prototypes
├── libft/                  - my libft (with ft_printf and get_next_line), built by the Makefile; philo only uses its headers
└── srcs/mandatory/
    ├── main.c                  - argument count, setup, joins
    ├── parsing.c               - argument parsing
    ├── init.c                  - mutexes, philosophers, threads
    ├── routine_philo.c         - eat / sleep / think loop
    ├── routine_philo_utils.c   - end check, meal count, start barrier
    ├── routine_checker.c       - monitor thread (check_full, check_dead)
    ├── philo_utils.c           - cleanup
    └── time.c                  - get_current_time, ft_usleep
```
