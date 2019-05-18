/*
* This is a demostration of the progressbar.
* Author: Arjob Mukherjee (arjobmukherjee@gmail.com)
* Date: 12 Jan 2019
*/

#include<stdio.h>
#include<unistd.h> // for sleep
#include"bar.h"

#define PROGRESS_BAR_SETUP() blankChar = '-'; \
							 filledChar = '#'; \
							 leftChar = '\0'; \
							 rightChar = '\0'

int main()
{
	// Customizes the progress bar. Uncomment to see the effect.
	PROGRESS_BAR_SETUP();

	char right_text[10], left_text[100];
	float progress = 0.0;

	sprintf(left_text,"%-50s ","Progress:");

	for(;;){
		progress += 0.1f;
		sprintf(right_text,"%6.1f%%",progress * 100);
		print_progressbar(progress,left_text,right_text);
		if (progress > 1.0){
			printf("\n");
			progress = 0;
		}
		sleep(1);
	}
	return 0;
}
