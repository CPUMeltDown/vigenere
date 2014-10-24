#ifndef DICTCHECK_H_INCLUDED
#define DICTCHECK_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
/** \brief
 *thoughts:
the algorithem should return the length of the word
longer words = more likely plain text
sudo code:
while dict word & tested word < lenght of each word
    check each char seq to see if matches
    if not skip to next dict word
if tested word is partial of dict word and no other matches
    the rest of the key must = that dict word
    then need to test that key to see if the rest of the text makes sense using that key.
    if not start over
 * \param
 * \param
 * \return
 *
 */

int dictcheck(char *s, size_t len)
{
	FILE *fp;
	if((fp = fopen("words", "r")) == NULL)
	{
		fprintf(stderr, "DICTIONARY NOT FOUND!\n");
		exit(0);
	}
	int i=0;
	/**< for (i = 0; i < (lim-1) && (x = toupper(getc(fp))) != EOF && x != '\n'; ++i) */
	while(i<len)
	{
		i++;
	}
}
#endif // DICTCHECK_H_INCLUDED
