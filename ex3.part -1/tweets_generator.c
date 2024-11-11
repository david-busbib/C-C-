#include "markov_chain.h"
#define MAX 1000
#define MAX1 100
#define MAX_ROW
#define F 5
#define T 4
#define TRETEEN 30
#define ONE 1


int help_dabase_zero(FILE *fp, MarkovChain
*markov_chain)
{
  if (!fp)
  {
    return EXIT_FAILURE;
  }
  char buf[MAX];

  while (fgets (buf, MAX, fp))
  {
    char *s = strtok (buf, " \n");
    while (s)
    {


      add_to_database (markov_chain, s );
      s = strtok(NULL, " \n");



      }
    }

  return EXIT_SUCCESS;
}
int fill_database (FILE *fp, int words_to_read, MarkovChain
*markov_chain)
{
  int count = 0;
  int line=0;
  int new=0;
  if (!fp)
  {
    return EXIT_FAILURE;
  }
  char buf[MAX];

  while (fgets (buf, MAX * words_to_read, fp))
  {


    char *s = strtok (buf, " \n");
    while (s && count < words_to_read)
    {
      if (line==1){
        new+=1;
        line =0;
      }
      add_to_database (markov_chain, s);
      s = strtok (NULL, " \n");
      count += 1;
      if(count==words_to_read ){
        if (new!=0){
          for (line=0;line<=new;line+=1){
            add_to_database (markov_chain, s);
            s = strtok (NULL, " \n");
          }
        }
        return EXIT_SUCCESS
            ;
      }
    }
    line=1;
  }
  return EXIT_SUCCESS;
}


int check (int argc, FILE *ptd)
{
  if (argc != F && argc != T)
  {
    fprintf (stdout, USSAGE);
    return 0;
  }
  if (!ptd)
  {
    fprintf (stdout, ERROR);
    return 0;
  }
  return 1;

}

void print_tweet (int num_tweets, MarkovChain *markov_chain,int t)
{
  if (num_tweets > 0)
  {

    fprintf (stdout,"Tweet %d: ",t-num_tweets+1);
    generate_random_sequence (markov_chain, get_first_random_node
        (markov_chain), MAX1);
    printf ("\n");
    print_tweet (num_tweets - ONE, markov_chain,t);

  }


}
int main (int argc, char *agrv[])
{
  FILE *ptd;
  ptd = fopen (agrv[3], "r");
  if (!check (argc, ptd))
  {
    return EXIT_FAILURE;
  }
  LinkedList lnk_list = {NULL, NULL, 0};
  MarkovChain a = {&lnk_list};
  MarkovChain *ptr=&a;
  long seed = strtol (agrv[1], NULL, 10);
  int tweet = strtol (agrv[2], NULL, 10);
  srand (seed);

  if (agrv[4])
  {
    fill_database (ptd, strtol
                       (agrv[4], NULL, 10),
                   ptr);
  }
  else
  {
    help_dabase_zero(ptd, ptr);
  }



  print_tweet (tweet, &a,tweet);
  free_markov_chain (&ptr);
  fclose (ptd);
  return EXIT_SUCCESS;
}