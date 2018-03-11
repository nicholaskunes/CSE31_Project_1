#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 4096

/**
 * You can use this recommended helper function
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */

int matches_leading(char *partial_line, char *pattern) {
	int i = 0;
	while(pattern[i] != '\0') {
		if(partial_line[i] == '\0' || partial_line[i] == '\n'){ //end of line reached
			return 0;
		}
		if(pattern[i] == '\\') {
                        if(partial_line[i] != pattern[i+1]) {
                                return 0;
                        }
			if(pattern[i+2] == '+') {
				char prev_char = pattern[i+1];
				int incremented = 0;
                                while(partial_line[i+1] == prev_char) {
                                        partial_line++;
                                        incremented = 1;
                                }
                                if(pattern[i+3] == prev_char && incremented)
                                        partial_line--;
                                pattern = pattern + 3;
			} else {
                        	pattern++;
                        	i++;
			}
                } else if(pattern[i+1] == '+') {
			char prev_char = pattern[i];
			if(prev_char == '.'){
				while(partial_line[i] != '\0' && partial_line[i] != pattern[i+2]) {
					partial_line++;
				}
				pattern = pattern+2;
			} else {
				int incremented = 0;
				while(partial_line[i] == prev_char) {
					partial_line++;
					incremented = 1;
				}
				if(pattern[i+2] == prev_char && incremented)
					partial_line--;
				pattern = pattern + 2;
				if(!incremented)
					return 0;
			}
		} else if(pattern[i] == '.'){
			//implement . logic
			i++;
		} else if(pattern[i] == '?') {
			pattern++;//ignore ?'s
		} else if(partial_line[i] != pattern[i]) {
			return 0;
		} else {
			i++;
		}
	}
	return 1;
}

char * remove_optional(char *pattern) {
	char *new_pattern = (char *)malloc(MAXSIZE*sizeof(char));
	int count = 0;
	for(int i = 0; pattern[i] != '\0'; i++) {
		if(pattern[i] == '\\' && pattern[i+1] == '?') {
                        new_pattern[count] = pattern[i];
                        count++;
                        i++;
                        new_pattern[count] = pattern[i];
                        count++;
                } else if(pattern[i+1] != '?' && pattern[i] != '?') {
			new_pattern[count] = pattern[i];
			count++;
		}
	}
	return new_pattern;
}

/**
 * You may assume that all strings are properly null terminated 
 * and will not overrun the buffer set by MAXSIZE 
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {

	int length = 0;
	int count = 0;
	char *partial_line = (char*)malloc(MAXSIZE*sizeof(char));
	while(line[length] != '\0') {
		length++;
	}
	for(int i = 0; i < length; i++) {
		for(int j = 0; j < length; j++) {
			*(partial_line+j) = line[i+j];
		}
//		printf("loop1\n");
		if(matches_leading(partial_line, pattern) || matches_leading(partial_line, remove_optional(pattern))){
			return 1;
		}
		free(partial_line);
		partial_line = (char*)malloc(MAXSIZE*sizeof(char));
		count++;
	}

	return 0;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
		return 2;
	}

	/* we're not going to worry about long lines */
	char buf[MAXSIZE];

	while (!feof(stdin) && !ferror(stdin)) {
		if (!fgets(buf, sizeof(buf), stdin)) {
			break;
		}
		if (rgrep_matches(buf, argv[1])) {
			fputs(buf, stdout);
			fflush(stdout);
		}
	}

	if (ferror(stdin)) {
		perror(argv[0]);
		return 1;
	}

	return 0;
}

