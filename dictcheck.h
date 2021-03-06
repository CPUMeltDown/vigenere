#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "mcgcd.h"
#define MAXLEN 100000

/** \brief
 *thoughts:
the algorithm should return the length of the word
    longer words = more likely plain text
        maybe create an array with each position+1 representing word length
        those keys with the most words in the higher positions of the array should be more accurate
sudo code:
while dict word & tested word < length of each word  && length of tested word < length of dict word
    check each char sequentially to see if matches
    if not skip to next dict word
if tested word is partial of dict word and no other matches
    the rest of the key must be cypher+key=that dict word
    then need to test that key to see if the rest of the text makes sense using that key.
    if not start over bad key
if entire decryption = words display key
 * \param
 * \param
 * \return
 *
 */

void fprintusage(FILE *fp, char* name)
{
	fprintf(fp, "usage: %s operation key plaintext/ciphertext\n\toperation: E for encryption, D for decryption, or B for break\n\tkey: key used for encryption or decryption operation 100 character maximum\n\tplaintext/ciphertext: file to be encrypted, decrypted, or broken\n", ++name);
}

int mod(int a, int b)
{
	int r = a % b;
	return r < 0 ? r + b : r;
}

size_t getcipherfile(char *s, size_t lim, FILE *fp)
{
	int x, i;
	for(i = 0; i < (lim - 1) && (x = toupper(getc(fp))) != EOF && x != '\n'; ++i)
	{
		if(x > 64 && x < 91)
		{
			s[i] = x;
		}
		else
		{
			s[i] = x;
		}
	}
	if(x == '\n')
	{
		s[i] = x;
		++i;
	}
	s[i] = '\0';
	return i;
}

size_t encrypt(char *s, char *key, int keyindex, int keylen, size_t lim, FILE *fp)
{
	int x, i;
	for(i = 0; i < (lim - 1) && (x = toupper(getc(fp))) != EOF && x != '\n'; ++i)
	{
		if(x > 64 && x < 91)
		{
		  s[i] = mod((x - 65) + toupper(key[keyindex]), 26) + 65;
		  // fprintf(stdout, "keychar is %c and %c goes to %c\n", key[keyindex], x, s[i]);
		  if(keyindex == (keylen - 1))
		    {
		      keyindex = 0;
		    }
		  else
		    {
		      keyindex++;
		    }
		}
		else
		  {
		    s[i] = x;
		  }
	}
	if(x == '\n')
	  {
	    s[i] = x;
	    ++i;
	  }
	s[i] = '\0';
	return i;
}

size_t decrypt(char *s, char *key, int keyindex, int keylen, size_t lim, FILE *fp)
{
  int y, i;
  for(i = 0; i < (lim - 1) && (y = toupper(getc(fp))) != EOF && y != '\n'; ++i)
    {
      if(y > 64 && y < 91)
	{
	  s[i] = mod((y - 65) - toupper(key[keyindex]), 26) + 65;
	  //	  fprintf(stdout, "keychar is %c and %c goes to %c\n", key[keyindex], y, s[i]);
	  if(keyindex == (keylen - 1))
	    {
	      keyindex = 0;
	    }
	  else
	    {
	      keyindex++;
	    }
	}
      else
	{
	  s[i] = y;
	}
    }
  if(y == '\n')
    {
      s[i] = y;
      ++i;
    }
  s[i] = '\0';
  return i;
}

int dictcheck(char *s, size_t len)
{
	FILE *fp;
	if((fp = fopen("words", "r")) == NULL)
	{
		fprintf(stderr, "DICTIONARY NOT FOUND!\n");
		exit(0);
	}
	int i = 0;
	/**< for (i = 0; i < (lim-1) && (x = toupper(getc(fp))) != EOF && x != '\n'; ++i) */
	while(i < len)
	{
		i++;
	}
	return -1;
}
//
///* Standard C Function: Greatest Common Divisor */
//int gcd ( int a, int b )
//{
//  int c;
//  while ( a != 0 ) {
//    c = a; a = b%a;  b = c;
//  }
//  return b;
//}
//
///* Recursive Standard C Function: Greatest Common Divisor */
//int gcdr ( int a, int b )
//{
//  if ( a==0 ) return b;
//  return gcdr ( b%a, a );
//}
