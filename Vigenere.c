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

  fprintf(stdout, "%s", ciphertext);
  fprintf(stdout, "\n");

  dictcheck("a", 1);
}
