#include "dictcheck.h"
int main(int argc, char **argv)
{

  char ciphertext[MAXLEN];
  char buf[MAXLEN];
  FILE *fp;
  int len;
  int keylength;
  
  switch(argc)
    {
    case 3:
      if(strlen(argv[1]) > 1)
	{
	  fprintusage(stderr, ++argv[0]);
	  exit(0);
	}
      // Break operation                                                                                                                                                                 
      // Open ciphertext file.                                                                                                                                                           
      if((fp = fopen(argv[2], "r")) == NULL)
	{
	  fprintf(stderr, "FILE %s MISSING OR BROKEN!\n", argv[2]);
	  exit(0);
	}

      break;

    case 4:
      if(strlen(argv[1]) > 1)
	{
	  fprintusage(stderr, ++argv[0]);
	  exit(0);
	}
      keylength = strlen(argv[2]);
      if(keylength > 100)
	{
	  fprintusage(stderr, ++argv[0]);
	  exit(0);
	}

      if((fp = fopen(argv[3], "r")) == NULL)
        {
          fprintf(stderr, "FILE %s MISSING OR BROKEN!\n", argv[2]);
          exit(0);
        }
      break;
      
    default:
      fprintusage(stderr, ++argv[0]);
      exit(0);
      break;
    }

  char *keyed = (char *) malloc(sizeof(char) * keylength);
  int keyindex = 0;
  if(toupper(argv[1][0]) == 'E')
    {
      strncpy(keyed, argv[2], keylength);
      // Encryption                                                                                                                                                              
      while((len = encrypt(buf, keyed, keyindex, keylength, MAXLEN, fp)) > 0)
	{
	   fprintf(stdout, "%s", buf);
	}
      fprintf(stdout, "\n");
      exit(0);
    }

  if(toupper(argv[1][0]) == 'D')
    {
      strncpy(keyed, argv[2], keylength);
      // Decryption
      while((len = decrypt(buf, keyed, keyindex, keylength, MAXLEN, fp)) > 0)
        {
	   fprintf(stdout, "%s", buf);
        }
      fprintf(stdout, "\n");
      exit(0);
    }

  // Break operation from here

  // Copy text from cipher file into ciphertext string.                                                                                                                         \
                                                                                                                                                                                     
  while((len = getcipherfile(buf, MAXLEN, fp)) > 0)
    {
      strncat(ciphertext, buf, strlen(buf));
    }

  //  fprintf(stdout, "%s\n", ciphertext);
  
  size_t cipherlen = strlen(ciphertext);
  
  char * trigraphptr = (char *)malloc(sizeof(char) * cipherlen + 1);
  char * searchtriptr = (char *)malloc(sizeof(char) * cipherlen + 1);

  strncpy(trigraphptr, ciphertext, cipherlen);
  strncpy(searchtriptr, ciphertext, cipherlen);
  trigraphptr[cipherlen] = '\0'; 
  searchtriptr[cipherlen] = '\0';

  // Find the occurences for each trigraph
  // How many trigraphs in the ciphertext
  size_t trigraphcount = cipherlen - 2;
  
  // Number of occurences of the trigraph
  size_t occurences[trigraphcount];
  
  // The trigraphs themselves.
  char *trigraphs[trigraphcount];
   
  // Current trigraph that is being searched for.                                                                                                                                
  char *currenttrigraph = (char *) malloc(sizeof(char) * 3);

  // Current trigraph in search.                                                                                                                                                 
  char *currenttrisearch= (char*) malloc(sizeof(char) * 3);

  int i;
  int j;
  
  // Outer loop, for each trigraph in the ciphertext.
  for(i = 0; i < trigraphcount; i++)
    {
      
      occurences[i] = 1;
      
      trigraphs[i] = (char *) malloc(sizeof(char) * 3);
      searchtriptr = trigraphptr + 1;
      
      // length of the remaining cipher text being searched.
      size_t searchlen = strlen(searchtriptr);
      
      // Count of trigraphs in the remaining cipher text.
      size_t searchtricount = searchlen - 2;

      strncpy(currenttrigraph, trigraphptr, 3);
      
      if(currenttrigraph[0] > 64 && currenttrigraph[0] < 91 && currenttrigraph[1] > 64 && currenttrigraph[1] < 91 && currenttrigraph[2] >64 && currenttrigraph[2] < 91)
	{
        // Inner loop, for each following trigraph.
      for(j = 0; j < searchtricount; j++)
	{
	  strncpy(currenttrisearch, searchtriptr, 3);
	  // fprintf(stdout, "Comparing %s with %s\n", currenttrigraph, currenttrisearch);
	  if(strncmp(currenttrigraph, currenttrisearch, 3) == 0)
	    {
	      
	      occurences[i]++;
	      strncpy(trigraphs[i], currenttrisearch, 3);
	    }
        
	  // Point to the next 3 characters.
	  searchtriptr = searchtriptr + 1;
	}
      
	}
      // Point to the next 3 characters.
      trigraphptr = trigraphptr + 1;
    }

  // Distances between the trigraph occurences.
  int highest = 0;
  int highestcount = 0;
  for(i = 0; i < trigraphcount; i++)
    {
      //      fprintf(stdout, "Occurence %d is %s with %zu occurences.\n", i+1, trigraphs[i], occurences[i]);
      // fprintf(stdout, "Highest now is %d\n", highest);
      if(occurences[i] > highestcount)
	{
	  //  fprintf(stdout, "Occurence %zu is %s\n", occurences[i], trigraphs[i]);
	  highestcount = occurences[i];
	  highest = i;
	}
    }

  fprintf(stdout, "Highest is %zu, and the segment is %s\n", occurences[highest], trigraphs[highest]);
  
  // loop through ciphertext adding distances between occurences
  char *previousloc = 0;
  char *currentloc = 0;
  size_t distances[occurences[highest] - 1];

  // Initialize distances.
  for(i = 0; i < occurences[highest] - 1; i++)
    {
      distances[i] = 0;
    }
  
  strncpy(trigraphptr, ciphertext, cipherlen);
  j = 0;
  for(i = 0; i < trigraphcount; i++)
    {
 
      strncpy(currenttrigraph, trigraphptr, 3);
      if(strncmp(currenttrigraph, trigraphs[highest], 3) == 0)
	{
	  if(previousloc != 0) 
	    {
	      currentloc = trigraphptr;
	      distances[j] = (currentloc - previousloc);
	      j++;
	    }
	  previousloc = trigraphptr;
	}
      trigraphptr = trigraphptr + 1;
    }
					       
  for (i = 0; i < occurences[highest] - 1; i++)
    {
      fprintf(stdout, "%zu ", distances[i]);
    }

  fprintf(stdout, "\n");

   int keylen = gcdr(distances[0], distances[1]);

  fprintf(stdout, "Possible key length is %d\n", keylen);
  
  // Frequncy analysis
  
  char characters[26];
  int frequencies[keylen][26];

  char key[keylen + 1];
  char seckey[keylen + 1];
  char thirdkey[keylen + 1];
  char fourkey[keylen + 1];
  char fifkey[keylen + 1];
  int index;

  key[keylen] = '\0';
  seckey[keylen] = '\0';
  thirdkey[keylen] = '\0';
  fourkey[keylen] = '\0';
  fifkey[keylen] = '\0';
  
  for(i = 0; i < keylen; i++)
    {
      // initialize frequencies                                                                                                                                                          
      for (j = 0; j< 26; j++)
	{
	  frequencies[i][j] = 0;
	}
      
      for(j = 0; j < cipherlen/keylen; j++)
	{
	  index = (j * keylen) + i;
	  frequencies[i][ciphertext[index] - 'A']++;

	}
      
      int highfreq = -1;
      int highfreqindex = -1;
      int sechighfreqindex = -1;
      int thirdhighfreqindex = -1;
      int fourhighfreqindex = -1;
      int fifhighfreqindex = -1;
      
      for(j = 0; j < 26; j++)
	{
	  if(frequencies[i][j] > highfreq)
	    {
	      fifhighfreqindex = fourhighfreqindex;
	      fourhighfreqindex = thirdhighfreqindex;
	      thirdhighfreqindex = sechighfreqindex;
	      sechighfreqindex = highfreqindex;
	      highfreqindex = j;
	      highfreq = frequencies[i][j];
	    }
	}

      int keypos = (highfreqindex - 4);
      int seckeypos = (sechighfreqindex - 4);
      int thirdkeypos = (thirdhighfreqindex - 4);
      int fourkeypos = (fourhighfreqindex - 4);
      int fifkeypos = (fifhighfreqindex - 4);
      
      keypos += keypos < 0 ? 26 : 0;
      seckeypos += seckeypos < 0 ? 26 : 0;
      thirdkeypos += thirdkeypos < 0 ? 26 : 0;
      fourkeypos += fourkeypos < 0 ? 26 : 0;
      fifkeypos += fifkeypos < 0 ? 26 : 0;
      
      //       fprintf(stdout, "Highest frequency letter at key pos %d is %c\n", highfreqindex, highfreqindex + 'A');
      //fprintf(stdout, "Key char at this index must be %c\n", (keypos) + 'A');
      key[i] = keypos + 'A';
      seckey[i] = seckeypos + 'A';
      thirdkey[i] = thirdkeypos + 'A';
      fourkey[i] = fourkeypos + 'A';
      fifkey[i] = fifkeypos + 'A';
    }
  
  fprintf(stdout, "Probable key is %s\n", key);
  fprintf(stdout, "Second probable key is %s\n", seckey);
  fprintf(stdout, "Third probable key is %s\n", thirdkey);
  fprintf(stdout, "Fourth probable key is %s\n", fourkey);
  fprintf(stdout, "Fifth probable key is %s\n", fifkey);
  
  // Decrypt
  //  dictcheck("a", 1);
}
