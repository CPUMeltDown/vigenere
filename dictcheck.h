#ifndef DICTCHECK_H_INCLUDED
#define DICTCHECK_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
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
