#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LINES 500
#define MAX_CHARS_PER_LINE 132

/*Control keys */
int width = 0;
int left = 0;
int formatting = 0;
int spacing = 0;
char output[MAX_INPUT_LINES * MAX_CHARS_PER_LINE];

int main(int argc, char *argv[]) {
    FILE *data;
    data = fopen(argv[1], "r");
    if(data == 0){
        return 0;
    }
    read_input(data);
    return 1;
}

void read_input(FILE *data){
	char line[132];
	while(fgets(line, MAX_CHARS_PER_LINE, (FILE*)data)) {
		char processed[132];
		strncpy(line, processed, 132);
		formating_type(processed);
		if(formatting) {
			format(*processed);
		} else{
			printf("%s",line);
			break;
		}
		prinft("%s",processed);
	}
}
void formatting_type (char* current_line) {
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

 	while (tokenized_output && num_words < MAX_INPUT_LINES) {
 		strncpy (words[num_words], tokenized_output, MAX_INPUT_LINES);
 		num_words++;
 		tokenized_output = strtok (NULL, " ");
 	} 
 	
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
		
	}
}

