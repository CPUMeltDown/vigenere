#include "dictcheck.h"
int main(int argc, char **argv)
{

  char ciphertext[MAXLEN];
  char buf[MAXLEN];
  FILE *cipherfp;
  int len;

  if (argc != 2)
    {
      // Incorrect arguments print usage and exit.
      fprintusage(stderr, ++argv[0]);
      exit(0);
    }
  

  // Open ciphertext file.
  if((cipherfp = fopen(argv[1], "r")) == NULL)
    {
      fprintf(stderr, "FILE %s MISSING OR BROKEN!\n", argv[1]);
      exit(0);
    }

  // Copy text from cipher file into ciphertext string.
  while((len = getcipherfile(buf, MAXLEN, cipherfp)) > 0)
    {
      strncat(ciphertext, buf, strlen(buf));
    }

  size_t cipherlen = strlen(ciphertext);
  
  char * trigraphptr = (char *)malloc(sizeof(char) * cipherlen + 1);
  char * searchtriptr = (char *)malloc(sizeof(char) * cipherlen + 1);

  strncpy(trigraphptr, ciphertext, cipherlen);
  strncpy(searchtriptr, ciphertext, cipherlen);
  trigraphptr[cipherlen] = '\0';
  searchtriptr[cipherlen] = '\0';

  // Find the occurences for each trigraph
    
    // Tri is 3!
  size_t tri = 3;

    // How many trigraphs in the ciphertext
  size_t trigraphcount = cipherlen/tri;

    // Number of occurences of the trigraph
  size_t occurences[trigraphcount];

    // The trigraphs themselves.
  char *trigraphs[trigraphcount];
  
  int i;
  int j;
    
    // Outer loop, for each trigraph in the ciphertext.
  for(i = 1; i <= trigraphcount; i++)
    {

      occurences[i-1] = 1;

      trigraphs[i-1] = (char *) malloc(sizeof(char) * tri);
      searchtriptr = trigraphptr + (tri);

        // length of the remaining cipher text being searched.
      size_t searchlen = strlen(searchtriptr);
        // Count of trigraphs in the remaining cipher text.
      size_t searchtricount = searchlen/tri;

        // Current trigraph that is being searched for.
      char *currenttrigraph = (char *) malloc(sizeof(char) * tri);
        // Current trigraph in search.
      char *currenttrisearch= (char*) malloc(sizeof(char) * tri);
        
      strncpy(currenttrigraph, trigraphptr, tri);
      
        // Inner loop, for each following trigraph.
      for(j = 1; j <= searchtricount; j++)
	{
	  strncpy(currenttrisearch, searchtriptr, tri);
	  // fprintf(stdout, "Comparing %s with %s\n", currenttrigraph, currenttrisearch);
	  if(strncmp(currenttrigraph, currenttrisearch, tri) == 0)
	    {

	      occurences[i-1]++;
	      strncpy(trigraphs[i-1], trigraphptr, tri);
	      //   fprintf(stdout, "\nMatch FOUND! Segment length of %zu; Segment # %d, %s occurred for the %zu time and has a distance of %zu!\n", tri, i, trigraphs[i-1], occurences[i-1], distances[i-1]);
	    }
        
        // Point to the next 3 characters
	   searchtriptr = searchtriptr + tri;
	}
      trigraphptr = trigraphptr + tri;
    }

  // Distances between the trigraph occurences.
  int highest = 0;

  for(i = 0; i < trigraphcount; i++)
    {
      if(occurences[i] > highest)
	{
	  highest = i;
	}
    }

  fprintf(stdout, "Highest is %zu, and the segment is %s\n", occurences[highest], trigraphs[highest]);
  

  // loop through ciphertext adding distances between occurences
  char *previousloc = 0;
  char *currentloc = 0;
  size_t distances[occurences[highest]];

  // Initialize distances.
  for(i = 0; i < occurences[highest]; i++)
    {
      distances[i] = 0;
    }
  
  strncpy(trigraphptr, ciphertext, cipherlen);
  j = 0;
  for(i = 0; i < trigraphcount; i++)
    {
      
      if(strncmp(trigraphptr, trigraphs[highest], tri) == 0)
	{
	  if(previousloc != 0) 
	    {
	      currentloc = trigraphptr;
  	      distances[j] = (currentloc - previousloc);
	      fprintf(stdout, "MatchFound with a distance of %zu\n", distances[j]);
	      j++;
	    }
	  previousloc = trigraphptr;
	}
      trigraphptr = trigraphptr + tri;
    }
  //  dictcheck("a", 1);
}
