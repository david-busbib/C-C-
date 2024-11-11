#include "markov_chain.h"

int get_random_number (int max_number)
{
    return rand () % max_number;
}
MarkovNode *help_get_first_random_node (Node
                                        *cur, int num)
{
    //this func help to go to the last node valid in the list
    int i = 0;
    while (i != num)
    {
        cur = cur->next;
        i += 1;
    }
//    char  *a=(char *)cur->data->data;
//    if (a){}
    return cur->data;
}
int help_list (LinkedList *database, MarkovNode *cur, int func,MarkovChain*
markov_chain)
{
    //this func help to know is the last in the node is
    // the one we are searching
    //for return 1 if yes else return 0
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

        if (markov_chain->is_last(cur->data)==0)
        {
            return 0;
        }
        return 1;
    }
    return 1;
}

int find_the_last_and_in_lst (MarkovNode *cur,MarkovChain *markov_chain)
{
//this func help us to know if is the last thing we want in case of tweet
//its will be poit in the snake just 100 and so on
    if  (!markov_chain->is_last(cur->data)==0)
    {
        return 0;
    }
    return 1;
}

MarkovNode *get_first_random_node (MarkovChain *markov_chain)
{
    //explain in marcov .h

    int random_1 = get_random_number
            ((markov_chain->database->size));
    MarkovNode *s =
            help_get_first_random_node
                    (markov_chain->database->first, random_1);
    while (!find_the_last_and_in_lst (s,markov_chain))
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
    //help the func next random to give us the next void we want
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
    //explain in marcov.h
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
    int random_1 = get_random_number (sum);
    int i = 0;
    int j = 1;
    int *fr = &state_struct_ptr->counter_list[0].frequency;
    int sum_to_del=*fr;
    while (i <= random_1 && random_1 != 0)
    {
        if (sum_to_del == 0)
        {
            fr = &state_struct_ptr->counter_list[j].frequency;
            sum_to_del=*fr;
            d = &state_struct_ptr->counter_list[j];
            j += 1;

        }
        else
        {
            i += 1;
            sum_to_del-=1;
        }

    }
    return d->markov_n;
}

int help_to_generate (MarkovNode *
first_node,MarkovNode *
first, int max_length,MarkovChain *markov_chain)
{
    //this func help to generate tweet and print them all
    //return nothing
    markov_chain->print_func(first_node->data);
    for (int i=0;i<max_length-1;i++){
        MarkovNode *cur = get_next_random_node (first);
        if (!cur){
            return 0;
        }
        if (!find_the_last_and_in_lst (cur,markov_chain))
        {
            markov_chain->print_func(cur->data);
            return 0;
        }
        else{
            markov_chain->print_func(cur->data);
        }
        //apdate the cur to be the next
        first=cur;

    }

    return 0;
}

void generate_random_sequence (MarkovChain *markov_chain, MarkovNode *
first_node, int max_length)
{
    if (!first_node)
    {
        first_node = get_first_random_node (markov_chain);
        help_to_generate (first_node,first_node, max_length,markov_chain);
    }
    else
    {
        help_to_generate (first_node,first_node, max_length,markov_chain);
    }
}

void free_node (Node *node,MarkovChain *markov_chain)
{
  //free the node
    markov_chain->free_data (node->data->data);
    free(node->data);
    free(node);
}
void help_free_node (Node *node,MarkovChain *markov_chain)
{
    if (node)
    {
      //free the counter list and the node
        free(node->data->counter_list);
        free_node (node,markov_chain);

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
        help_free_node (node,*ptr_chain);
        node = t;
        if (i==0){

        }

    }
//    free(data->last);
    free(data);
  (*ptr_chain)->database=NULL;
    free(*ptr_chain);
    *ptr_chain=NULL;
}




bool add_node_to_counter_list (MarkovNode *first_node, MarkovNode *second_node
        ,  MarkovChain *markov_chain)
//explain in the marcov h
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
        markov_chain->print_func(ALLOCATION_ERROR_MASSAGE);
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

Node *help_get_node (MarkovChain *markov_chain, void *data_ptr)
{
//help to return the node we want return node if sucses else Null
    Node *s = markov_chain->database->first;
    while (s)
    {
        if (markov_chain->comp_func (s->data->data, data_ptr) == 0)
        {
            return s;
        }
        s = s->next;
    }
    return NULL;

}
Node *get_node_from_database (MarkovChain *markov_chain, void *data_ptr)
{

    if (!help_get_node (markov_chain, data_ptr))
    {
        return NULL;
    }
    return help_get_node (markov_chain, data_ptr);
}

Node *find_last (Node *node, int num)
{
    //find the last node valid
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
int check_1 (void *data)
{
    //check paramatre

    if (!data )
    {

        free (data);
        fprintf(stdout,ALLOCATION_ERROR_MASSAGE);
        return 0;
    }
    return 1;
}

int check_node (Node *node)
{
    if (!node)
    {
        free (node);
        fprintf(stdout,ALLOCATION_ERROR_MASSAGE);
        return 0;
    }
    return 1;
}

Node *add_to_database (MarkovChain *markov_chain, void *data_ptr)
{
    Node *answer = get_node_from_database (markov_chain, data_ptr);
    if (answer)
    {
        markov_chain->database->last = answer;
        return answer;
    }
    else
    {
        MarkovNode *p_void = calloc (1,
                                     sizeof (MarkovNode));
        void *data = markov_chain->copy_func (data_ptr);
        if (!check_1 (data))
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
            if (markov_chain->comp_func (new->data->data, last->data->data)
            != 0)
            {
                if (help_list (markov_chain->database, p_void,
                               0,markov_chain)
                    != 0)
                {
                    markov_chain->database->size--;
                }
                else
                {
                    last->next = new;
                    markov_chain->database->last = new;
                }
            }
        }
    }
    markov_chain->database->size++;
    return get_node_from_database (markov_chain, data_ptr);
}