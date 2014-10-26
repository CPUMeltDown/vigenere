#include "dictcheck.h"
int main(int argc, char **argv)
{

  if (argc != 2)
    {
      // print usage
      fprintf(stderr, "Missing ciphertext!");
      fprintusage(stderr, ++argv[0]);
    }

  dictcheck("a",1);
}
