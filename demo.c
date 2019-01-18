/*
* This is a demostration of the progressbar.
* Author: Arjob Mukherjee (arjobmukherjee@gmail.com)
* Date: 12 Jan 2019
*/

#if defined(_WIN32) || defined(_WIN64)
	#include<Windows.h> // for sleep(miliseconds)
#else
	#include<unistd.h> // for sleep(seconds) [TODO: Use posix nanosleep instead]
#endif
#include<stdio.h>
#include"bar.h"

#define PROGRESS_BAR_SETUP() blankChar = '-'; \
							 filledChar = '#'; \
							 leftChar = ' '; \
							 rightChar = ' '

int main()
{
	// Customizes the progress bar. Uncomment to see the effect.
	PROGRESS_BAR_SETUP();

	char right_text[10], left_text[100];
	float progress = 0.0;

	sprintf(left_text,"%-50s","Progress:");

	for(;;){
		sprintf(right_text,"%6.1f%%",progress * 100);
		print_progressbar(progress,left_text,right_text);
		progress += 0.01f;
		if (progress > 1.0){
			printf("\n");
			progress = 0;
		}
#if defined(_WIN32) || defined(_WIN64)
		Sleep(1000);
#else
		sleep(1);
#endif
	}
	return 0;
}
