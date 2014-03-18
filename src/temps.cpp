#include "temps.h"

#include <time.h>
#include <stdio.h>

static struct timespec myTimerStart;

void demarrer_mesure_temps()
{
  clock_gettime(CLOCK_REALTIME, &myTimerStart);
}

void afficher_mesure_temps(const char * legende)
{
  struct timespec current;
  clock_gettime(CLOCK_REALTIME, &current);
  double elapsed_in_ms =    (( current.tv_sec - myTimerStart.tv_sec) *1000 +
          ( current.tv_nsec - myTimerStart.tv_nsec)/1000000.0);
  printf("Temps passé (ms) sur %s : %lf\n", legende, elapsed_in_ms);
}
