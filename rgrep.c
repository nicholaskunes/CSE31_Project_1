#include <stdio.h>
#define MAXSIZE 4096

/**
 * You can use this recommended helper function
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {
  // Implement if desire
  //DO THE \ AND + LOGIC PATTERN CHECKS
  // AND THEN UPLOAD TO GITHUB FOR hNERY
  int x = 0, inc = 0;

  int matches_leading(char *partial_line, char *pattern) {
	while(pattern[x] != '\0') {
		if(partial_line[x] == '\0' || partial_line[x] == '\n'){ //end of line reached
			return 0;
		}
		if(pattern[x] == '\\') {
                        if(partial_line[x] != pattern[x+1]) {
                                return 0;
                        }
			if(pattern[x+2] == '+') {
				char prev_char = pattern[x+1];
				int incremented = 0;
                                while(partial_line[x+1] == prev_char) {
                                        partial_line++;
                                        incremented = 1;
                                }
                                if(pattern[x+3] == prev_char && inc)
                                        partial_line--;
                                pattern = pattern + 3;
			} else {
                        	pattern++;
                        	x++;
			}
                } else if(pattern[x+1] == '+') {
			char prev_char = pattern[x];
			if(prev_char == '.'){
				while(partial_line[x] != '\0' && partial_line[x] != pattern[x+2]) {
					partial_line++;
				}
				pattern = pattern+2;
			} else {
				int inc = 0;
				while(partial_line[x] == prev_char) {
					partial_line++;
					inc = 1;
				}
				if(pattern[x+2] == prev_char && inc)
					partial_line--;
				pattern = pattern + 2;
				if(!inc)
					return 0;
			}
		} else if(pattern[x] == '.'){
			//implement . logic
			x++;
		} else if(pattern[x] == '?') {
			pattern++;//ignore ?'s
		} else if(partial_line[x] != pattern[x]) {
			return 0;
		} else {
			x++;
		}
	}
	return 1;
}

char * remove_optional(char *pattern) {
	char *new_pattern = (char *)malloc(MAXSIZE*sizeof(char));
	int count = 0;
	for(int x = 0; pattern[x] != '\0'; x++) {
		if(pattern[x] == '\\' && pattern[x+1] == '?') {
                        new_pattern[count] = pattern[x];
                        count++;
                        x++;
                        new_pattern[count] = pattern[x];
                        count++;
                } else if(pattern[x+1] != '?' && pattern[x] != '?') {
			new_pattern[count] = pattern[x];
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

    int len = 0,y = 0, z = 0, count = 0;

    char *partial_line = (char*)malloc(MAXSIZE* size _of(char));
        while (line[len] != '\0') {
            len++;
        }
        for(int y = 0; y < len; y++) {
            for ( z = 0; z < len; z++){
                *(partial_line+j) = line[y+z];
            }
            if (matches_leading(partial_line, pattern) || matches_leading(partial_line, remove_optional(pattern))){
                return 1;
            }
            free(partial_line);
            partial_line = (char*)malloc(MAXSIZE* sizeof(char));
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
