/*
 * UVic SENG 265, Fall 2016, A#4
 *
 * This will contain a solution to format265alt.c. In order to complete the
 * task of formatting a file, it must open the file and pass the result
 * to a routine in formatter.c.
 */

#include <stdio.h>
#include <stdlib.h>
#include "formatter.h"

int main(int argc, char *argv[]) {
/*#ifdef DEBUG
	printf("%s does nothing right now.\n", argv[0]);
#endif*/
	char **result;
	FILE * input_file = fopen(argv[1], "r");
	if(input_file == NULL){
		exit(1);
	}
	result = format_file(input_file);

	fclose(input_file);
	if (result == NULL) {
		printf("%s: it appears 'format_lines' is not yet complete\n",
			argv[0]);
		exit(1);
	}
	char **line;
	for (line = result; *line != NULL; line++) {
		printf("%s\n", *line);
	}

	exit(0);
}
