#ifndef _PROGRESS_BAR_H
#define _PROGRESS_BAR_H

// In order to customize the progress bar set these variables in your program 
// (before the first use of print_progressbar function.)

// Default values:
// *  blankChar = '-'
// *  filledChar = '='
// *  leftChar = '['
// *  rightChar = ']'

extern char blankChar; 		// makes the yet to be filled part of the bar.
extern char filledChar; 	// makes the filled part of the progress bar.
extern char leftChar; 		// left boundary char of the progress bar.
extern char rightChar; 		// right boundary char of the progress bar.

void print_progressbar(float progress,char *left_text,char *right_text);

#endif // _PROGRESS_BAR_H
