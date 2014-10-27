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
  
  char * segmentptr = (char *)malloc(sizeof(char) * cipherlen);
  char * searchptr = (char *)malloc(sizeof(char) * cipherlen);

  strncpy(segmentptr, ciphertext, cipherlen);
  strncpy(searchptr, ciphertext, cipherlen);
  
  // Trigraph
  size_t segmentlen = 3;

  size_t occurences[cipherlen/segmentlen];
  size_t distances[cipherlen/segmentlen];
  char *segments[cipherlen/segmentlen];
  
  int i;
  int j;
  for(i = 1; i <= (cipherlen/segmentlen); i++)
    {

      occurences[i-1] = 1;
      distances[i-1] = 0;
      segments[i-1] = (char *) malloc(sizeof(char) * segmentlen);
      searchptr = segmentptr + (i * segmentlen);

      size_t searchlen = strlen(searchptr);
      for(j = 0; j < (searchlen/segmentlen); j++)
	{
	  //	  fprintf(stdout, "%s\n", segmentptr);
	  if(strncmp(segmentptr, searchptr, segmentlen) == 0)
	    {
	    
	      occurences[i-1]++;
	      distances[i-1] = (searchptr - segmentptr);
	      strncpy(segments[i-1], segmentptr, segmentlen);
	      fprintf(stdout, "\nMatch FOUND! Segment length of %zu; Segment # %d, %s occurred for %zu times!\n", segmentlen, i-1, segments[i-1], occurences[i-1]);
	    }
	  
	  searchptr = searchptr + segmentlen;
	}
      segmentptr = segmentptr + segmentlen;
    }

  for(i = 1; i <= (cipherlen/segmentlen); i++)
{
  
  if(distances[i-1] != 0)
    {
      fprintf(stdout, "%zu ", distances[i-1]);
    }
 }
  
  //  dictcheck("a", 1);
}
