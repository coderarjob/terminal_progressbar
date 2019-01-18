#include<stdio.h>
#include<stddef.h> // for NULL
#include<stdlib.h> // for malloc,atoi
#include<string.h> // for strlen

#if defined(_WIN32) || defined(_WIN64)
	#include<windows.h>
#else
	#include<sys/ioctl.h> // for ioctl
#endif

#include"bar.h"

#define STDOUT 0

static char *bar; 
static int columns = 0;

char blankChar = '-';
char filledChar = '=';
char leftChar = '[';
char rightChar = ']';

static int getNeededColumnCount()
{
#if defined(_WIN32) || defined(_WIN64)
	CONSOLE_SCREEN_BUFFER_INFO w;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&w);
	// the -1 is only needed in windows (may be /r at the end is considered
	// another charracter in windows). Without the -1, every print_progressbar
	// is printing in another line.
	return w.dwSize.X - 1; 
#else
	struct winsize w;
	ioctl(STDOUT,TIOCGWINSZ,&w);
	return w.ws_col;
#endif
}

static void bar_init(int cols)
{
	columns = cols;
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
	// The following two lines, remove the NULL char, as this cannot be shown
	// in the printf. (NULL charracter indicated the end of the string)
	if (leftChar == '\0') leftChar = ' ';
	if (rightChar == '\0') rightChar = ' ';

	int index,artifact_strlen,bar_length;
	artifact_strlen = 2;
	artifact_strlen += strlen(left_text);
	artifact_strlen += strlen(right_text);
	
	int current_columns = getNeededColumnCount();
	if (current_columns > columns){
		bar_init(current_columns);
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
