/*
 * UVic SENG 265, Fall 2016,  A#4
 *
 * This will contain the bulk of the work for the fourth assignment. It
 * provide similar functionality to the class written in Python for
 * assignment #3.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formatter.h"

void chomp(char *line);
void format(char *processed);
int formatting_type (char* processed, int len);
void *emalloc(size_t n);
void add(char *word, int len);

static int width = 0;
static int left = 0;
static int formatting = 0;
static int spacing = 0;
static int line_length = 0;
static char **output; 
static char *formatted;
static int output_size = 10;
static int output_lines = 0;

/*This is called from driver.c*/
char **format_lines(char **lines, int num_lines) {
	int i = 0;
	for(i = 0; i < num_lines; i++){
		char line[strlen(lines[i])+1];
		strncpy(line, lines[i], strlen(lines[i])+1);

		char copy[strlen(lines[i])];
		strncpy(copy, line, strlen(line)+1);

        chomp(line);

    	if(formatting_type(line, strlen(line))){
            continue;
        }
        if(formatting){
        	format(line);
        } else{
            if(strlen(formatted) > 0){
				add(formatted, strlen(formatted));
			} 
            add(copy, strlen(copy));
        }
	}
	if(strlen(formatted) > 0){
		add(formatted, strlen(formatted));
	} 
	return output;
}

/*Checks for formatting keys and returns 1 if there was a key 
 *  detected, 0 otherwise*/
int formatting_type (char* processed, int len) {
        char current_line[len+1];
        strncpy(current_line, processed, len+1);
        strtok(current_line, " ");
        /*Check if the first token of the line matches one of 
 		 *the formatting key words and sets the key that 
 		 *corresponds to that type*/
        if(!strncmp(current_line,".FT", len)){
                char* fmt = strtok(current_line, " ");
                if(!strncmp(fmt, "on", 3)){
                        formatting = 1;
                }else{
                        formatting = 0;
                }
                return 1;
        } else if(!strncmp(current_line,".LM", len)){
        		/*NEED THE ADD THE + - CHECK*/
                left = atoi(strtok(NULL, " "));
                return 1;
        } else if(!strncmp(current_line,".LS", len)){
                spacing = atoi(strtok(NULL, " "));
                return 1;
        } else if(!strncmp(current_line, ".LW", len)){
        		int old_width = width;
                width = atoi(strtok(NULL, " "));
                formatting = 1;
                char tmp[width];
                strncpy(tmp, formatted, old_width);
                return 1;
        }
        return 0;
}

void format(char *processed){
	if(formatted == NULL){
		char tmp[width];
		formatted = tmp;
	}
	if(strlen(processed) == 0){
		/*add an empty string to the array to be returned*/
		add("", 0);
		
		if(spacing > 0){
			int i;
			for(i = 0; i < spacing*2; i++){
				/*add more blank strings*/
				/*realloc enough space for the new line to be added*/
				/*this means 1 + output_lines*/
				add("", 0);
			}
		}
		return;
	}
	char *current_word = strtok(processed, " ");
    while(current_word != NULL) {
		if(line_length == 0 && left > 0){
			int i;
			for(i = 0; i < left; i++){
				/*add spaces to the output string*/
				strncat(formatted, " ", 1);
				line_length++;
			}
		}
		if(strlen(current_word) + 1 <= width - left){
			if(line_length > 0){
				/*add a space*/
				strncat(formatted, " ", 1);
				/*add current_word*/
				strncat(formatted, current_word, strlen(current_word));
				/*update the line_length by adding current_word length +1*/
				line_length += strlen(current_word) + 1;
			} else{
				/*print the word then update the word 
 				 *then increment legnth*/
				strncat(formatted, current_word, strlen(current_word));
				line_length += strlen(current_word);
			}
		} else if(width > 0){
			line_length = 0;
			/*end this line and go to the next one*/

			/*NOW ADD THE FORMATTED ARRAY TO THE OUTPUT ARRAY*/
			add(formatted, width);
			/*this means looking at/making the next box in the output
 			* array*/
			if(spacing > 0){
           	            int i;
               	        	for(i = 0; i < spacing*2; i++){
                   	            	/*add more blank strings*/
               	        			add("", 0);
                       		}
	               	}
			if(left > 0){
                        	int i;
           	            	for(i = 0; i < left; i++){
               	        	    /*add spaces to the output string*/
                   	    		strncat(formatted, " ", 1);
								line_length++;                        		}
	                }
			/*add the word and update the line length*/
	        line_length += strlen(current_word);
            strncat(formatted, current_word, strlen(current_word));
		}
		current_word = strtok(NULL, " ");
	}
}

void *emalloc(size_t n){
	void *p;
	p = malloc(n);
	if(p == NULL){
		fprintf(stderr, "malloc of %zu bytes failed", n);
		exit(1);
	}
	return p;
}

/*Removes the newline character at the end of an input line*/
void chomp(char *line) {
	if(line != NULL){
		int length = strlen(line);
		if(length > 0){
			if (line[length-1] == '\n') {
	   	     	line[length-1] = '\0';
	    	}
		}
	}
}	

void add(char *word, int len){
	if(output == NULL){
		output = emalloc(output_size * sizeof(char *));
	}else if(output_lines == output_size) {
        output = realloc(output, (output_size * 2) * sizeof(char *));
        if(output == NULL){
            exit(1);
        }
    	output_size = output_size * 2;
    }
    output[output_lines] = (char *)emalloc(sizeof(char) * (strlen(word)+1));
	strncpy(output[output_lines], word, len);
	output_lines++;
}


/*This is called from format265alt.c*/
char **format_file(FILE *infile) {
	/*turn the input into a string array where each line is an element
 	  need to malloc the size of the array and then realloc each time the 
	  file has another input line. Need to malloc each index in the array to hold
	  the length of the line + 1 for the null char. */
	char **result;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int array_size = 1;
	char ** file;
	int i = 0;

	while((read = getline(&line, &len, infile)) != -1) {
		/*if(i == array_size){
			char **tmp = realloc(file, (array_size * 2) * sizeof(char *));
			if(tmp == NULL){
				exit(1);
			}
			array_size = array_size * 2;
			file = tmp;
			free(tmp);
		}
		file[i] = (char *)emalloc(sizeof(char) * strlen(line));
		file[i] = line;
		i++;*/

		if(file == NULL){
		file = emalloc(array_size * sizeof(char *));
		}else if(i == array_size) {
       		file = realloc(file, (array_size * 2) * sizeof(char *));
        	if(file == NULL){
            	exit(1);
        	}
    		array_size = array_size * 2;
    	}
    	file[i] = (char *)emalloc(sizeof(char) * (strlen(line)+1));
		strncpy(output[i], line, strlen(line));
		i++;

	}
	/*i is now the number of lines in the array*/
	result = format_lines(file, i);

	if(line){
		free(line);
	}
	return file;
}










