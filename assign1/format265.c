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
char output[MAX_INPUT_LINES * MAX_CHARS_PER_LINE * 2];
char formatted[MAX_CHARS_PER_LINE];
int line_length = 0;

/*Prototype definitions*/
int formatting_type(char* processed);
void format(char *processed);
void read_input(FILE *data);
void chomp(char *line);

int main(int argc, char *argv[]) {
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
	char line[MAX_CHARS_PER_LINE];
	char original[MAX_CHARS_PER_LINE];
	while(fgets(line, MAX_CHARS_PER_LINE, (FILE*)data)) {
		strncpy(original, line, MAX_CHARS_PER_LINE);
		if(line != NULL){
			chomp(line);
		}
		if(strlen(line) == 0){
			strncat(output, "\n\n", MAX_CHARS_PER_LINE);
			if(spacing) {
				int i  = 0;
				while(i <= spacing){
					strncat(formatted, "\n", 1);
				}
			}
			line_length = 0;
		}
		if(formatting_type(line)){
			continue;
		}
		if(left){
			while(line_length < left-1){
				strncat(formatted, " ", 1);
				line_length++;
			}
		}
		if(formatting){
			format(line);
			strncat(output, formatted, MAX_CHARS_PER_LINE); 
			strncpy(formatted, "", MAX_CHARS_PER_LINE);
		} else{
			strncat(output, original, MAX_CHARS_PER_LINE);
			strncpy(original, "", MAX_CHARS_PER_LINE);
		}
	}
	if(formatting){
		if(original != NULL){
			int length = strlen(original);
			if(line[length-1] == '\n'){
				strncat(output, "\n", 1);
			}
		}
	}
	printf("%s", output);
	return;
}

int formatting_type (char* processed) {
	char current_line[MAX_CHARS_PER_LINE];
	strncpy(current_line, processed, MAX_CHARS_PER_LINE);
	strtok(current_line, " \n");
	if(!strncmp(current_line,".FT", MAX_CHARS_PER_LINE)){
		char* fmt = strtok(current_line, " \n");
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
	char *current_word = strtok(processed, " ");
	while(current_word != NULL) {
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

void chomp(char *line) {
	if(line != NULL){
		int length = strlen(line);
		if (line[length-1] == '\n') {
   	     	line[length-1] = '\0';
    		}
	}
}	

