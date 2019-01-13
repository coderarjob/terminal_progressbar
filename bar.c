#include<stdio.h>
#include<stddef.h> // for NULL
#include<stdlib.h> // for malloc,atoi
#include<string.h> // for strlen
#include<sys/ioctl.h> // for ioctl
#include"bar.h"

#define STDOUT 0

static char *bar; 
static int columns;

char blankChar = '-';
char filledChar = '=';
char leftChar = '[';
char rightChar = ']';

static int getNeededColumnCount()
{
	struct winsize w;
	ioctl(STDOUT,TIOCGWINSZ,&w);

	return w.ws_col;
}

static void bar_init()
{
	columns = getNeededColumnCount();

	//create the bar
	int totalsize = columns * 2;

	// free the bar before creating a new one.
	if (bar != NULL) free(bar);
	bar = malloc(sizeof(char) * totalsize);
	
	// Fill in the chareacters into the buffer
	char c = blankChar;
	while(--totalsize)
	{
		if (totalsize == (columns -1))
			c = filledChar;
		bar[totalsize] = c;
	}
}

void print_progressbar(float progress,char *left_text,char *right_text)
{
	int index,artifact_strlen,bar_length;
	artifact_strlen = (leftChar == '\0')? 0:1;
	artifact_strlen += (rightChar == '\0')? 0:1;
	artifact_strlen += strlen(left_text);
	artifact_strlen += strlen(right_text);
	
	int current_columns = getNeededColumnCount();
	if (current_columns > columns){
		bar_init();
	}

	bar_length = current_columns - artifact_strlen;
	index = columns - (progress * bar_length);
	printf("%s%c%.*s%c%s\r",left_text,
			leftChar,
			bar_length,
			&bar[index],
			rightChar,
			right_text);
	fflush(stdout);
}
