#include "./process.h"

#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
    int process_n = atoi(argv[1]);

    pcb_t* pcb = (pcb_t*)malloc(sizeof(pcb_t) * process_n);

  /* CPU architecture
  ** CLOCK (CURRENT TIME)
  ** RECORD(LOG) -- logs are there to let us understand what cpu is doing.
  ** scheduling algorithm
  ** current_process
  ** ALGORITHM
  ** Process queue
  ** cpu pointer
  ** enqueue
  ** scheduling function ????
  */

  /* Evaluation function
  ** Display_times()
  ** Display_gantt()
  */

  /* Utility functions
  **
  */

  // TODO: initialize system, which initializes needed objects
  init_system();
  // TODO: initialize input process to run scheduling on
  config();
  // TODO: simulate for all scheduling algorithms, and the results are logged to log which is separate
  simulate(clk, js, cs, cpu, io);

  // TODO: using the log we evaluate all algorithms and display a gantt chart.
  evaluate(log); // Other logs
  
  // TODO: memory cleanup
  return 0;
}
