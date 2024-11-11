#include "markov_chain.h"
char *allocate_and_cpy (char *p)
{
  //this func copy the name and put place in the zicaron
  int l = strlen (p);
  char *new = calloc (1, l + 1);
  if (!new)
  {
    fprintf (stderr, ALLOCATION_ERROR_MASSAGE);
    free (new);
    return NULL;
  }
  strcpy (new, p);
  return new;
}
int get_random_number (int max_number)
{
  return rand () % max_number;
}
MarkovNode *help_get_first_random_node (Node
                                        *cur, int num)
{
  int i = 0;
  while (i != num)
  {
    cur = cur->next;
    i += 1;
  }
  return cur->data;
}
int help_list (LinkedList *database, MarkovNode *cur, int func)
{
  Node *answer = database->first;
  int j = 0;
  if (func == 0)
  {
    while (j > database->size)
    {
      if (answer->data != cur)
      {
        answer = answer->next;
      }
      else
      {
        return 1;
      }
    }
    return 0;
  }
  else if (func == 1)
  {
    int leangth = strlen ((cur->data));
    if ((cur->data)[leangth - 1] == '.')
    {
      return 0;
    }
    return 1;
  }
return 1;
}

int find_the_last_and_in_lst (MarkovNode *cur)
{

  int leangth = strlen ((cur->data));
  if ((cur->data)[leangth - 1] == '.')
  {
    return 0;
  }
  return 1;
}

MarkovNode *get_first_random_node (MarkovChain *markov_chain)
{
  int random_1 = get_random_number
      ((markov_chain->database->size));
  MarkovNode *s =
      help_get_first_random_node
          (markov_chain->database->first, random_1);
  while (!find_the_last_and_in_lst (s))
  {
    random_1 = get_random_number (markov_chain->database->size);
    s = help_get_first_random_node
        (markov_chain->database->first, random_1);
  }
  return s;
}
MarkovNode *help_next_random (NextNodeCounter *d, NextNodeCounter *next, int
num, int cur_fre)
{
  if (num == 0)
  {
    return next->markov_n;
  }
  if (cur_fre > 0)
  {
    help_next_random (d, next, num - 1, cur_fre - 1);
  }
  else if (cur_fre == 0)
  {
    help_next_random (d, (d + 1), num - 1, (d + sizeof
        (NextNodeCounter))->frequency);

  }
  return 0;

}
MarkovNode *get_next_random_node (MarkovNode *state_struct_ptr)
{
  if (state_struct_ptr->size_of_brother == 0)
  {
    return NULL;
  }
  int sum = 0;
  int count = state_struct_ptr->size_of_brother;
  NextNodeCounter *d = state_struct_ptr->counter_list;
  for (int i = 0; i < count; i += 1)
  {
    sum += (d + i)->frequency;

  }
  int tandom_1 = get_random_number (sum);
  int i = 0;
  int j = 1;
  int *fr = &state_struct_ptr->counter_list[0].frequency;
  while (i <= tandom_1 && tandom_1 != 0)
  {
    if (*fr == 0)
    {
      fr = &state_struct_ptr->counter_list[j].frequency;
      d = &state_struct_ptr->counter_list[j];
      j += 1;

    }
    else
    {
      i += 1;
      *fr -= 1;
    }

  }
  return d->markov_n;
}
/**
 * Receive markov_chain, generate and print random sentence out of it. The
 * sentence most have at least 2 words in it.
 * @param markov_chain
 * @param first_node markov_node to start with,
 *                   if NULL- choose a random markov_node
 * @param  max_length maximum length of chain to generate
 */
int help_to_generate (MarkovNode *
first_node, int max_length)
{
  printf ("%s ", first_node->data);
  MarkovNode *next = get_next_random_node (first_node);
  if (max_length == 0 || !find_the_last_and_in_lst (next))
  {
    printf ("%s", next->data);
    return 0;
  }
  else
  {
    help_to_generate (next, max_length - 1);
  }
  return 0;
}
void generate_random_sequence (MarkovChain *markov_chain, MarkovNode *
first_node, int max_length)
{
  if (!first_node)
  {
    first_node = get_first_random_node (markov_chain);
    help_to_generate (first_node, max_length);
  }
  else
  {
    help_to_generate (first_node, max_length);
  }
}
/**
 * Free markov_chain and all of it's content from memory
 * @param markov_chain markov_c
 * hain to free
 */
void free_node (Node *node)
{
  free (node->data);
  free (node);
}
void help_free_node (Node *node)
{
  if (node)
  {
    free (node->data->data);
    free (node->data->counter_list);
    free_node (node);

  }
}

void free_markov_chain (MarkovChain **ptr_chain)
{
  LinkedList *data = (*ptr_chain)->database;
  int i = 0;
  Node *node = data->first;
  for (; i < data->size; i++)
  {
    Node *t = node->next;
    help_free_node (node);
    node = t;
  }
}




/**
 * Add the second markov_node to the counter list of the first markov_node.
 * If already in list, update it's counter value.
 * @param first_node
 * @param second_node
 * @return success/failure: true if the process was successful, false if in
 * case of allocation error.
 */
bool add_node_to_counter_list (MarkovNode *first_node, MarkovNode *second_node)
{
  if (!first_node || !second_node)
  {
    return false;

  }
  int index = 0;
  while (index < first_node->size_of_brother)
  {
    if (first_node->counter_list[index].markov_n == second_node)
    {
      first_node->counter_list[index].frequency += 1;
      return true;
    }
    ++index;
  }

  NextNodeCounter *f = realloc (first_node->counter_list,
                                (first_node->size_of_brother + 1)
                                * sizeof (NextNodeCounter));
  if (!f)
  {
    free (f);
    return false;
  }
  first_node->counter_list = f;
  if (!first_node->counter_list->markov_n)
  {

    first_node->counter_list->markov_n = second_node;
    first_node->counter_list->frequency = 1;
  }
  else
  {
    first_node->counter_list = f;
    first_node->counter_list[first_node->size_of_brother].markov_n =
        second_node;
    first_node->counter_list[first_node->size_of_brother].frequency = 1;
  }
  first_node->size_of_brother++;
  return true;

}
/**
* Check if data_ptr is in database.
 * If so, return the markov_node wrapping it in
 * the markov_chain, otherwise return NULL.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return Pointer to the Node wrapping given state, NULL if state not in
 * database.
 */
Node *help_get_node (MarkovChain *markov_chain, char *data_ptr)
{

  Node *s = markov_chain->database->first;
  while (s)
  {
    if (strcmp (s->data->data, data_ptr) == 0)
    {
      return s;
    }
    s = s->next;
  }
  return NULL;

}
Node *get_node_from_database (MarkovChain *markov_chain, char *data_ptr)
{

  if (!help_get_node (markov_chain, data_ptr))
  {
    return NULL;
  }
  return help_get_node (markov_chain, data_ptr);
}
/**
* If data_ptr in markov_chain, return it's markov_node. Otherwise, create new
 * markov_node, add to end of markov_chain's database and return it.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return markov_node wrapping given data_ptr in given chain's database,
 * returns NULL in case of memory allocation failure.
 */

Node *find_last (Node *node, int num)
{
  Node *tmp = node;
  int i = num;
  for (; i != 1;)
  {
    if (!node)
    {
      return tmp;
    }
    else
    {
      tmp = node;
      node = node->next;
    }
  }
  return NULL;
}
int check_1 (char *data, MarkovNode *p_void)
{

  if (!data || !p_void)
  {
    free (data);
    free (p_void);
    fprintf (stderr, ALLOCATION_ERROR_MASSAGE);
    return 0;
  }
  return 1;
}

int check_node (Node *node)
{
  if (!node)
  {
    free (node);
    fprintf (stderr, ALLOCATION_ERROR_MASSAGE);
    return 0;
  }
  return 1;
}

Node *add_to_database (MarkovChain *markov_chain, char *data_ptr)
{

  Node *answer = get_node_from_database (markov_chain, data_ptr);
  if (answer)
  {
    add_node_to_counter_list (markov_chain->database->last->data,
                              answer->data);
    markov_chain->database->last = answer;
    return answer;
  }
  else
  {
    MarkovNode *p_void = calloc (1,
                                 sizeof (MarkovNode));
    char *data = allocate_and_cpy (data_ptr);
    if (!check_1 (data, p_void))
    {
      return NULL;
    }
    Node *new = malloc (sizeof (Node));
    if (!check_node (new))
    {
      return NULL;
    }

    p_void->data = data;
    p_void->counter_list = NULL;
    p_void->size_of_brother = 0;
    new->data = p_void;
    new->next = NULL;
    Node *last = find_last (markov_chain->database->first, 0);
    if (!last)
    {
      markov_chain->database->first = new;
      markov_chain->database->last = new;
    }
    else
    {
      if (strcmp (new->data->data, last->data->data) != 0)
      {
        if (help_list (markov_chain->database, p_void, 0)
        != 0)
        {
          add_node_to_counter_list (markov_chain->database->last->data,
                                    p_void);
          markov_chain->database->size--;
        }
        else
        {
          add_node_to_counter_list (markov_chain->database->last->data,
                                    p_void);
          last->next = new;
          markov_chain->database->last = new;
        }
      }
    }
  }

  markov_chain->database->size++;
  return get_node_from_database (markov_chain, data_ptr);
}