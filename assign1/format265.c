#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LINES 500
#define MAX_CHARS_PER_LINE 132

/*Control keys */
int width = 0;
int left = 0;
int formatting = 0;
int spacing = 0;
char output[MAX_INPUT_LINES * MAX_CHARS_PER_LINE * 2];
int line_length = 0;
/*Prototype definitions*/
int formatting_type(char* processed);
void format(char *processed);
void read_input(FILE *data);

int main(int argc, char *argv[]) {
	FILE *data = fopen(argv[1], "r");
	if(data == 0){
		fprintf(stderr,"Unable to open %s\n", argv[1]);
	}
	read_input(data);
	fclose(data);
	return 1;
}

void read_input(FILE *data){
	char line[MAX_CHARS_PER_LINE];
	while(fgets(line, MAX_CHARS_PER_LINE, (FILE*)data)) {
		if(formatting_type(line)){
			continue;
		}
		if(left){
			while(line_length < left-1){
				strncat(formatted, " ", 1);
				line_length++;
			}
		}
		if(formatting && !strncmp(line, "\n", 1){
			strncat(output, "\n\n", MAX_CHARS_PER_LINE);
			if(spacing){
				int i = 0;
				while(i < spacing){
					strncat(formatted, "\n", 1);
				}
			}
			line_length = 0;
		}
		if(formatting){
			format(line);
			strncat(output, formatted, MAX_CHARS_PER_LINE);
			strncpy(formatted, "", MAX_CHARS_PER_LINE);
		} else{
			strncat(output, formatted, MAX_CHARS_PER_LINE);
		}
	}
	printf("%s", output);
	return;
}

void formatting_type (char *current_line) {
	if(strcmp(current_line[0],".LW") != 0){
		width = current_line[1];
		formatting = 1;
	}else if(strcmp(current_line[0],".LM") != 0){
		left = current_line[1];
		formatting = 1;
	} else if(strcmp(current_line[0],".LS") != 0){
		spacing = current_line[1];
		formatting = 1;
	}
    
}
void tokenize(char *processed) {
	char *tokenized_output;
	tokenized_output = strtok(processed, " ");

 /*	while (tokenized_output && num_words < MAX_INPUT_LINES) {
 		strncpy (words[num_words], tokenized_output, MAX_INPUT_LINES);
 		num_words++;
 		tokenized_output = strtok (NULL, " ");
 	} */
 	
}
void format(char *processed) {
	tokenized(processed);
	if(left) {
		int i;
		for( i = 0; i < left; i++){
			/* add " " to output */
		}
	}
	if(width) {
		int line_length = left;
		int i = 0;
		while(strlen(processed[i]) +  line_length < width) {
			/* add the word to output*/
			i++;
		}
	}
}

