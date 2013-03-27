#ifndef __FROG_EXTRA_H__
#define __FROG_EXTRA_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../provided-functions/ran2.h"
#include "frogs.h"
#include "land_cells.h"
#include "timers.h"
#include "string.h"

long state;

// List of possible messages to send; this just makes message passing a bit
// clearer for the user, it's not necessary
enum {
  CLOSE_CURTAINS,
	OPEN_CURTAINS,
	OFF_STAGE,
	ON_STAGE,
	A_LAND_CELL_CHANGES,
	A_FROG_SURVEYS_THE_LAND,
  A_MONSOON_BRINGS_IN_THE_NEW_YEAR,
  A_FROG_HOPS_INTO_THE_UNKNOWN,
	A_FROG_SPEAKS_OF_ITS_HEALTH,
	A_FROG_NEEDS_SPACE_TO_SPAWN,
	A_LAND_CELL_KNOWS_SUCH_A_PLACE,
	A_LAND_CELL_ADOPTS_A_TADPOLE,
  A_FROG_SPAWNS,
  A_FROG_CONTRACTS_THE_PLAGUE,
  A_FROG_CROAKS
};

Role choose_role(int id);
int min(int a, int b);
void initialise_array(int *arr, int size, int val);
void calculate_average(int *arr, int size, float *out);
int collect_input(int argc, char *argv[]);
void help(char *program_name);

#endif
