#include "../headers/timers.h"

extern int max_time;
extern double year_length;

Role timer_role = {timer_initialisation, timer_script, sizeof(Timer)};
// Function which initialises the Timing actor
void timer_initialisation(Actor* actor)
{
  Timer *t_props = actor->props;
  get_seed(actor);
  t_props->frog_count = initial_frog_count;
  t_props->diseased_frog_count = 0;
  t_props->year_start= MPI_Wtime();
  t_props->year_length = year_length;
	t_props->current_year = 0;

	actor->act_number=OPEN_CURTAINS;

	printf
  (
  	"TIMER: new year (%d/%d)\n\tTotal Frog Count = %d\n\tDisease Frog Count = %d\n",
    t_props->current_year,
    max_time,
    t_props->frog_count,
    t_props->diseased_frog_count
  );
}


// The job that the Timing actor runs; when the year is over it prints
// information about the state of the system, if the run time is up, it 
// messages the lead_actors of all systems to
void timer_script(Actor* actor)
{
  int i;
  Timer *t_props = actor->props;
	if(actor->act_number == OPEN_CURTAINS)
	{
		if(t_props->current_year >= max_time)
		{
			printf("End of simulation\n");
			for(i=0;i<number_of_processes;i++)
			{
				enter_dialogue(actor, i, CLOSE_CURTAINS);
			}
    	actor->poison_pill = 1;
		}
		else if(t_props->frog_count > max_frog_count)
		{
			printf("ERROR: frog count exceeded maximum (%d), exiting... \n", max_frog_count);
			for(i=0;i<number_of_processes;i++)
			{
				enter_dialogue(actor, i, CLOSE_CURTAINS);
			}
    	actor->poison_pill = 1;
		}
		else if(MPI_Wtime() - t_props->year_start > t_props->year_length)
		{
			t_props->year_start = MPI_Wtime();
			t_props->current_year++;
			printf
			(
				"TIMER: new year (%d/%d)\n\tTotal Frog Count = %d\n\tDisease Frog Count = %d\n",
				t_props->current_year,
				max_time,
				t_props->frog_count,
				t_props->diseased_frog_count
			);
			for(i=1;i<=initial_cell_count;i++)
			{
				enter_dialogue(actor, i, A_MONSOON_BRINGS_IN_THE_NEW_YEAR);
			}
		}
	}
	else if(actor->act_number == A_FROG_SPAWNS)
  {
    t_props->frog_count++;
		actor->act_number = OPEN_CURTAINS;
  }
  else if(actor->act_number == A_FROG_CONTRACTS_THE_PLAGUE)
  {
    t_props->diseased_frog_count++;
		actor->act_number = OPEN_CURTAINS;
  }
  else if(actor->act_number == A_FROG_CROAKS)
  {
    t_props->frog_count--;
    t_props->diseased_frog_count--;
		actor->act_number = OPEN_CURTAINS;
  }
  else if(actor->act_number == CLOSE_CURTAINS)
  {
		printf("told to close curtains...\n");
    actor->poison_pill = 1;
  }
}