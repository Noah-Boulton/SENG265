#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LINES 500
#define MAX_CHARS_PER_LINE 132

/*Control keys */
int width = 0;
int left = 0;
int formatting = 0;
int spacing = 0;

int main() {
/* read the input file
 * tokenize the input 
 * check for the formatting keys
 * set flags for each flag (0 if false, 1 if not)
 * take in cooresponding int values for each key
 * call the formatting method passing the cooresponding paramaters
 * Maximum line will have 132 chars
 * Maximum file length is 500 lines
 */
	return 0;
}

int formatting_type (char* current_line) {
	char line_copy[MAX_CHARS_PER_LINE];
	strncpy(line_copy, current_line, MAX_CHARS_PER_LINE);
}
int tokenizeLine() {
	char c;
        char buff[132];
        c = getchar();
        count = 0;
        while(c != \n) {
                buff[count] = c;
                count++;
        }
	int line_width;
	if(strcmp(buff[0],.LW) == 0){
		/* set the line width flag */
		line_width = buff[1];
	}
	
	
}
int format() {
	
}
