#include "markov_chain.h"
#define MAX 1000
#define MAX1 20
#define MAX_ROW
#define F 5
#define T 4
#define TRETEEN 30
#define ONE 1
static int  help_fill_database_zero_case(FILE *fp, MarkovChain
*markov_chain);
static void print_st(void *your_output);
static void free_st(void *your_output);
static void *copy_data( void *your_output);
static int comp_funcs_str( void*first, void*second);
static bool is_last(void *x);
static void print_st(void * your_output){
        if (is_last((char *)your_output)){
    printf ("%s",(char *)your_output);
    } else
    {
        printf ("%s ",(char *)your_output);
    }

}
static void free_st(void *your_output){
    free (your_output);
}
static void *copy_data( void *your_output){
    //this func copy the name and put place in the zicaron
    int l = strlen ((char *)your_output);
    char *new = calloc (1, l + 1);
    if (!new)
    {
        fprintf (stderr, ALLOCATION_ERROR_MASSAGE);
        free (new);
        return NULL;
    }
    strcpy (new, your_output);
    return new;
}
static int  comp_funcs_str( void*first, void*second){

    return strcmp ((char *)first,(char *)second);
}
static bool is_last (void *x){
    char *y=(char *)x;
    if(y[strlen(y)-1] == '.'){
        return true;
    }
    return false;


}

static void call_func(MarkovChain *w);

static void call_func(MarkovChain *w){
    w->is_last= (is_lasts) is_last;
    w->comp_func= (comp_funcs) comp_funcs_str;
    w->copy_func= (copy_datas) copy_data;
    w->print_func= (print_funcs) print_st;
    w->free_data= (free_d) free_st ;
}
static int help_fill_database_zero_case(FILE *fp, MarkovChain
*markov_chain)
{
    //in case we read all the file i prefere to call this shordet func that the
    //other because she is more complited and build for the non zero case
    if (!fp)
    {
        return EXIT_FAILURE;
    }
    char buf[MAX];
    Node *vo=NULL;
    while (fgets (buf, MAX, fp))
    {
        char *s = strtok (buf, " \n");
        while (s)
        {
            Node *t= add_to_database(markov_chain, s);
            if (vo){
                add_node_to_counter_list(vo->data,t->data
                        ,markov_chain);
            }
            vo=t;
            s = strtok(NULL, " \n");
        }
    }
    return EXIT_SUCCESS;
}
static int fill_database (FILE *fp, int words_to_read, MarkovChain
*markov_chain)
{
    // in case that the tweet num is not zero we are calling this func
    int count = 0;

    if (!fp)
    {
        return EXIT_FAILURE;
    }
    char buf[MAX];
    Node *vo=NULL;

    while (fgets (buf, MAX * words_to_read, fp)) {
        char *s = strtok(buf, " ");
        if (!markov_chain->comp_func(s,"\n")){
            continue;
        }
        while (s && count <words_to_read) {

            Node *t = add_to_database(markov_chain, s);
            if (vo) {
                add_node_to_counter_list(vo->data,
                                         t->data, markov_chain);
            }
            vo = t;
//            printf("%s",s);
            s = strtok(NULL, "\n"" ");
            count += 1;
        }
    }



    return EXIT_SUCCESS;
}

static int check (int argc, FILE *ptd)
{
    //check the argm that the are currect
    if (argc != F && argc != T)
    {
        fprintf (stdout, ALLOCATION_ERROR_MASSAGE);
        return 0;
    }
    if (!ptd)
    {
        fprintf (stdout, ALLOCATION_ERROR_MASSAGE);
        return 0;
    }
    return 1;

}

static void print_tweet (int num_tweets, MarkovChain *markov_chain,int t)
{
    // this func print the tweet by calling the generete func
    if (num_tweets > 0)
    {

        fprintf (stdout,"Tweet %d: ",t-num_tweets+1);
        generate_random_sequence (markov_chain,
                                  get_first_random_node(markov_chain),
                                  MAX1);
        printf ("\n");
        print_tweet (num_tweets - ONE, markov_chain,t);

    }


}

int main (int argc, char *agrv[])
{
    //initialising the func to print tweet
    FILE *ptd;
    ptd = fopen (agrv[3], "r");
    if (!check (argc, ptd))
    {
        return EXIT_FAILURE;
    }
    LinkedList *lnk_list = calloc(1,
                                  sizeof(LinkedList));
    if (!lnk_list) {
        fprintf(stdout, ALLOCATION_ERROR_MASSAGE);
        free(lnk_list);
        return EXIT_FAILURE;
    }
    MarkovChain *a= calloc(1, sizeof(MarkovChain));
    if (!a) {
        fprintf(stdout, ALLOCATION_ERROR_MASSAGE);
        free(a);
        return EXIT_FAILURE;
    }
    call_func(a);
    a->database=lnk_list;
    call_func(a);

    long seed = strtol (agrv[1], NULL, 10);
    int tweet = strtol (agrv[2], NULL, 10);
    srand (seed);

    if (agrv[4])
    {
        fill_database (ptd, strtol
                               (agrv[4], NULL, 10),
                       a);
    }
    else
    {
        help_fill_database_zero_case (ptd, a);
    }
//    print_markov_chain(ptr);
    print_tweet (tweet,a,tweet);
    free_markov_chain (&a);
    fclose (ptd);
    return EXIT_SUCCESS;
}