#ifndef __FROGS_H__
#define __FROGS_H__

#include <actor_metaphor.h>
#include "extra_functions.h"
#include "../provided-functions/ran2.h"
#include "../provided-functions/frog-functions.h"

int initial_frog_count;
int max_frog_count;
int initial_diseased_frog_count;
extern Role frog_role;

typedef struct {
	long state;
  float pos[2];
  int diseased;
  int hop_count;
	int current_cell;
  int population_history[300];
  int infection_history[500];
} Frog;

void frog_initialisation(Actor *actor, void *prop);
void frog_script(Actor *actor);
int choose_disease(Actor *actor);

#endif

