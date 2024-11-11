#include <string.h> // For strlen(), strcmp(), strcpy()
#include "markov_chain.h"

#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

#define EMPTY -1
#define BOARD_SIZE 100
#define MAX_GENERATION_LENGTH 60

#define DICE_MAX 6
#define NUM_OF_TRANSITIONS 20
#define DEF 3
#define ONE_A "100"
static void free_sn(void *your_output);
static void *copy_data_sn( void *your_output);
static int comp_funcs_str_sn( void*first, void*second);
static bool is_last_sn(void *x);
static void call_func_sn(MarkovChain *w);
static void print_snake(void*your_output);
/**
 * represents the transitions by ladders and snakes in the game
 * each tuple (x,y) represents a ladder from x to if x<y or a snake otherwise
 */
typedef struct Cell {
    int number; // Cell number 1-100
    int ladder_to;  //
    // ladder_to represents the jump of the ladder
    // in case there is one from this square
    int snake_to;
    // snake_to represents the jump of the snake
    // in case there is one from this square
    //both ladder_to and snake_to should be -1 if the Cell doesn't have them
} Cell;

static bool is_last_sn(void *x){
  Cell *cell= (Cell *)x;
  if (cell->number == BOARD_SIZE){
    return true;
  }
  return false;
}
static void print_snake(void *your_output){
  Cell *cell= (Cell*)your_output;
  if (cell->number==BOARD_SIZE){
      printf ("[%d]",cell->number);
  }
  else{
  if (cell->number<BOARD_SIZE){


    printf ("[%d]",cell->number);
  }
  if (cell->ladder_to != EMPTY){
    printf ("-%s %d","ladder to",cell->ladder_to);
  }
  else if (cell->snake_to != EMPTY){
    printf ("-%s %d","snake to",cell->snake_to);
  }
  if (cell->number<BOARD_SIZE){
    printf (" -> ");
  }
  }

}
static void *copy_data_sn( void *your_output){
  Cell *cell= malloc (sizeof (Cell));
  if (!cell){
    fprintf (stdout,ALLOCATION_ERROR_MASSAGE);
    return NULL;
  }
  memcpy (cell,(Cell *)your_output, sizeof (Cell));
  return cell;

}
static int comp_funcs_str_sn( void*first, void*second){
  Cell *cell1,*cell2;
  cell1= (Cell *)first;
  cell2= (Cell *)second;

  return cell2->number -cell1->number;
}

static void free_sn(void *your_output){
  free((Cell *)your_output);
}

const int transitions[][2] = {{13, 4},
                              {85, 17},
                              {95, 67},
                              {97, 58},
                              {66, 89},
                              {87, 31},
                              {57, 83},
                              {91, 25},
                              {28, 50},
                              {35, 11},
                              {8,  30},
                              {41, 62},
                              {81, 43},
                              {69, 32},
                              {20, 39},
                              {33, 70},
                              {79, 99},
                              {23, 76},
                              {15, 47},
                              {61, 14}};

/**
 * struct represents a Cell in the game board
 */


/** Error handler **/
static int handle_error(char *error_msg, MarkovChain **database)
{
  printf("%s", error_msg);
  if (database != NULL)
  {
    free_markov_chain(database);
  }
  return EXIT_FAILURE;
}
static void call_func_sn(MarkovChain *w){
  w->is_last= (is_lasts) is_last_sn ;
  w->comp_func= (comp_funcs) comp_funcs_str_sn ;
  w->copy_func= (copy_datas) copy_data_sn ;
  w->print_func= (print_funcs) print_snake ;
  w->free_data= (free_d) free_sn;
}

static int create_board(Cell *cells[BOARD_SIZE])
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    cells[i] = malloc(sizeof(Cell));
    if (cells[i] == NULL)
    {
      for (int j = 0; j < i; j++) {
        free(cells[j]);
      }
      handle_error(ALLOCATION_ERROR_MASSAGE,NULL);
      return EXIT_FAILURE;
    }
    *(cells[i]) = (Cell) {i + 1, EMPTY, EMPTY};
  }

  for (int i = 0; i < NUM_OF_TRANSITIONS; i++)
  {
    int from = transitions[i][0];
    int to = transitions[i][1];
    if (from < to)
    {
      cells[from - 1]->ladder_to = to;
    }
    else
    {
      cells[from - 1]->snake_to = to;
    }
  }
  return EXIT_SUCCESS;
}

/**
 * fills database
 * @param markov_chain
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
static int fill_database(MarkovChain *markov_chain)
{
  Cell* cells[BOARD_SIZE];
  if(create_board(cells) == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }
  MarkovNode *from_node = NULL, *to_node = NULL;
  size_t index_to;
  for (size_t i = 0; i < BOARD_SIZE; i++)
  {
    add_to_database(markov_chain, cells[i]);
  }

  for (size_t i = 0; i < BOARD_SIZE; i++)
  {
    from_node = get_node_from_database(markov_chain,cells[i])->data;

    if (cells[i]->snake_to != EMPTY || cells[i]->ladder_to != EMPTY)
    {
      index_to = MAX(cells[i]->snake_to,cells[i]->ladder_to) - 1;
      to_node = get_node_from_database(markov_chain, cells[index_to])
          ->data;

      add_node_to_counter_list(from_node,
                               to_node, markov_chain);
    }
    else
    {
      for (int j = 1; j <= DICE_MAX; j++)
      {
        index_to = ((Cell*) (from_node->data))->number + j - 1;
        if (index_to >= BOARD_SIZE)
        {
          break;
        }
        to_node = get_node_from_database(markov_chain, cells[index_to])
            ->data;
        add_node_to_counter_list(from_node, to_node,
                                 markov_chain);
      }
    }
  }
  // free temp arr
  for (size_t i = 0; i < BOARD_SIZE; i++)
  {
    free(cells[i]);
  }
  return EXIT_SUCCESS;
}
void print_markov_chain (struct MarkovChain *markov_chain)
{
    printf ("MarkovChain:\n");
    LinkedList *list = markov_chain->database;
    Node *cur = list->first;
    for (int i = 0; i < list->size; i++)
    {
        Cell *d= cur->data->data;
        printf ("%d.\t%d : [ ", i, d->number);
        struct NextNodeCounter *arr = cur->data->counter_list;
        for (int j = 0; j < cur->data->size_of_brother; j++)
        {
            Cell *e=arr[j].markov_n->data;
            printf ("{%d : %d} ", e->number, arr[j].frequency);
        }
        printf ("]\n");
        cur = cur->next;
    }
}
/**
 * @param argc num of arguments
 * @param argv 1) Seed
 *             2) Number of sentences to generate
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
static void call_func(MarkovChain *w);

static void call_func(MarkovChain *w){
    w->is_last= (is_lasts) is_last_sn;
    w->comp_func= (comp_funcs) comp_funcs_str_sn;
    w->copy_func= (copy_datas) copy_data_sn;
    w->print_func= (print_funcs) print_snake ;
    w->free_data= (free_d) free_sn ;
}
static void print_tweet (int num_tweets, MarkovChain *markov_chain,int t)
{
    if (num_tweets > 0)
    {

        fprintf (stdout,"Random Walk %d: ",t-num_tweets+1);
        generate_random_sequence (markov_chain,

                                  markov_chain->database->first->data,
                                  MAX_GENERATION_LENGTH);

        printf ("\n");
        print_tweet (num_tweets - 1, markov_chain,t);

    }
}

    int main(int argc, char *argv[]) {
        if (argc != 3) {
            fprintf(stdout, ALLOCATION_ERROR_MASSAGE);
            return EXIT_FAILURE;
        }
        long seed = strtol(argv[1], NULL, 10);
        int way = strtol(argv[2], NULL, 10);

        LinkedList *lnk_list = calloc(1, sizeof(LinkedList));
        if (!lnk_list) {
            fprintf(stdout, ALLOCATION_ERROR_MASSAGE);
            free(lnk_list);
            return EXIT_FAILURE;
        }

        MarkovChain *a = calloc(1,
                                sizeof(MarkovChain));
        if (!a) {
            fprintf(stdout, ALLOCATION_ERROR_MASSAGE);
            free(a);
            return EXIT_FAILURE;
        }
        a->database = lnk_list;
        a->database=lnk_list;
        call_func(a);


        srand(seed);
        call_func_sn(a);
        fill_database(a);
      print_markov_chain (a);

     //   print_tweet(way, a, way);
//        MarkovChain *ptr=&a;
        free_markov_chain(&a);
        return EXIT_SUCCESS;

    }
