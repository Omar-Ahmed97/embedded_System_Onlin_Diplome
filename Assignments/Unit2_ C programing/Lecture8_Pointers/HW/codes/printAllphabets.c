/*
 * printAllphabets.c
 *
 *  Created on: ??�/??�/????
 *      Author: Omar
 */



#include <stdio.h>


int main(){

char ch = 'A';
char *pch = &ch;

while(*pch <= 'Z')
{
	printf("%c   ",(*pch)++);
}

	return 0;
}
