#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LINES 500
#define MAX_CHARS_PER_LINE 133

/*Control keys */
int width = 0;
int left = 0;
int formatting = 0;
int spacing = 0;
int newline = 1;
char output[MAX_INPUT_LINES * MAX_CHARS_PER_LINE * 2];
char formatted[MAX_CHARS_PER_LINE];
int line_length = 0;

/*Prototype definitions*/
int formatting_type(char* processed);
void format(char *processed);
void read_input(FILE *data);
void chomp(char *line);

int main(int argc, char **argv) {
	FILE *data = fopen(argv[1], "r");
	if(data == 0){
		fprintf(stderr,"Unable to open %s\n", argv[1]);
		exit(0);
	}
	read_input(data);
	fclose(data);
	return 1;
}

void read_input(FILE *data){
	/*Two char arrays so that in the case the output is not to be 
	formatted the original array can be added to the output file*/
	char line[MAX_CHARS_PER_LINE];
	char original[MAX_CHARS_PER_LINE];
	/*Each line is tokenized then processed*/
	while(fgets(line, MAX_CHARS_PER_LINE, (FILE*)data)) {
		strncpy(original, line, MAX_CHARS_PER_LINE);
		/*Removes the newline character from the end of the input line*/
		chomp(line);
		/*If the original line was a single newline character 
 		it needs to be added back in*/
		if(strlen(line) == 0){
			strncat(output, "\n\n", MAX_CHARS_PER_LINE);
			/*Adds the correct spacing in between newlines*/
			if(spacing) {
				int i  = 0;
				while(i <= spacing){
					strncat(formatted, "\n", 1);
					i++;
				}
			}
			line_length = 0;
		}
		/*Checks for formatting type and sets the keys accordingly*/
		if(formatting_type(line)){
			/*If a key was set then jump to the next loop cycle*/
			continue;
		}
		if(formatting){
			format(line);
			/*After each line has been formatted, add the 
 			formatted text to the output array and clear 
			the formatted array*/
			strncat(output, formatted, MAX_CHARS_PER_LINE); 
			strncpy(formatted, "", MAX_CHARS_PER_LINE);
		} else{
			/*If formatting is off, output the original 
 			unaltered text*/
			strncat(output, original, MAX_CHARS_PER_LINE);
		}
	}
	/*If the original file ends in a newline it needs to be 
 	added back in by checking the newline and formatting keys*/
	if(formatting){
		int orig_length = strlen(original);
		if(original[orig_length-1] == '\n' && orig_length != 1){
			strncat(output, "\n", 1);
		}
	}
	/*Print the output array to the file*/
	printf("%s", output);
	return;
}
/*Checks for formatting keys and returns 1 if there was a key 
 detected, 0 otherwise*/
int formatting_type (char* processed) {
	char current_line[MAX_CHARS_PER_LINE];
	strncpy(current_line, processed, MAX_CHARS_PER_LINE);
	strtok(current_line, " ");
	/*Check if the first token of the line matches one of 
 	the formatting key words and sets the key that corresponds to that type*/
	if(!strncmp(current_line,".FT", MAX_CHARS_PER_LINE)){
		char* fmt = strtok(current_line, " ");
		if(!strncmp(fmt, "on", 3)){
			formatting = 1;
		}else{
			formatting = 0;
		}
		return 1;
	} else if(!strncmp(current_line,".LM", MAX_CHARS_PER_LINE)){
		left = atoi(strtok(NULL, " "));
		formatting = 1;
		return 1;
	} else if(!strncmp(current_line,".LS", MAX_CHARS_PER_LINE)){
		spacing = atoi(strtok(NULL, " "));
		formatting = 1;
		return 1;
	} else if(!strncmp(current_line, ".LW", MAX_CHARS_PER_LINE)){
		width = atoi(strtok(NULL, " "));
		formatting = 1;
		return 1;
	} 
	return 0; 
}

void format(char *processed){
	/*Tokenizes each line and adds formatted tokens to the output*/
	char *current_word = strtok(processed, " ");
	while(current_word != NULL) {
		/*Adds left spacing if the left key is set*/
		if(left){
			while(line_length < left-1){
				strncat(formatted, " ", 1);
				line_length++;
			}
		}
		/*Checks to see if the next token will fit on the current line*/
		if(line_length + strlen(current_word) >= width) {
			strncat(formatted, "\n", 1);
			if(spacing) {
				int i = 0;
				while(i < spacing){
					strncat(formatted, "\n", 1);
					i++;
				}
			}
			line_length = 0;
			if(left) {
				while(line_length < left){
					strncat(formatted, " ", 1);
					line_length++;
				}
			}	
		}
		else if(line_length != 0 && line_length <= width+1) {
			strncat(formatted, " ", 1);
			line_length++;
		}
		line_length += strlen(current_word);
		strncat(formatted, current_word, MAX_CHARS_PER_LINE);
    	current_word = strtok(NULL, " ");
	}
	return;
}

/*Removes the newline character at the end of an input line*/
void chomp(char *line) {
	if(line != NULL){
		int length = strlen(line);
		if(length > 0){
			if (line[length-1] == '\n') {
	   	     	line[length-1] = '\0';
	    		}
			newline = 1;
		}else{
			newline = 0;
		}	
	}
}	

