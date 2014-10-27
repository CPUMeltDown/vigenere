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
  
  char * segmentptr = (char *)malloc(sizeof(char) * cipherlen + 1);
  char * searchptr = (char *)malloc(sizeof(char) * cipherlen + 1);

  strncpy(segmentptr, ciphertext, cipherlen);
  strncpy(searchptr, ciphertext, cipherlen);
  segmentptr[cipherlen] = '\0';
  searchptr[cipherlen] = '\0';

  // Trigraph
  size_t segmentlen = 3;

  size_t occurencelen = cipherlen/segmentlen;

  size_t occurences[occurencelen];
  size_t distances[occurencelen];
  char *segments[occurencelen];
  
  int i;
  int j;
  for(i = 1; i <= occurencelen; i++)
    {

      occurences[i-1] = 1;
      distances[i-1] = 0;
      segments[i-1] = (char *) malloc(sizeof(char) * segmentlen);
      searchptr = segmentptr + (segmentlen);

      size_t searchlen = strlen(searchptr);
      size_t searchoccurencelen = searchlen/segmentlen;

      char *segmentcheck = (char *) malloc(sizeof(char) * segmentlen);
      char *searchcheck= (char*) malloc(sizeof(char) * segmentlen);
      strncpy(segmentcheck, segmentptr,segmentlen);
      
      for(j = 1; j <= searchoccurencelen; j++)
	{
	  strncpy(searchcheck, searchptr, segmentlen);
	  // fprintf(stdout, "Comparing %s with %s\n", segmentcheck, searchcheck);
	  if(strncmp(segmentcheck, searchcheck, segmentlen) == 0)
	    {

	      occurences[i-1]++;
	      distances[i-1] = (searchptr - segmentptr);
	      strncpy(segments[i-1], segmentptr, segmentlen);
	      fprintf(stdout, "\nMatch FOUND! Segment length of %zu; Segment # %d, %s occurred for the %zu time and has a distance of %zu!\n", segmentlen, i, segments[i-1], occurences[i-1], distances[i-1]);
	    }
	   searchptr = searchptr + segmentlen;
	}
      
      segmentptr = segmentptr + segmentlen;
    }

  for(i = 1; i <= (occurencelen); i++)
    {
      if(distances[i-1] != 0)
	{
	  fprintf(stdout, "%zu ", distances[i-1]);
	}
    }
  fprintf(stdout, "\n");
  
  //  dictcheck("a", 1);
}
