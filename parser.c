#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {}Lexer;

typedef struct{
	int token;
	char *type;
	int valid;
}Token;
// functions //

// lexer
char *ReadFile(FILE *stream, const char *filename){
	char *buffer;
	if ( stream == NULL ){
		stream = fopen(filename, "r");
		if (stream == NULL){
            exit(1);
		}
	}
	size_t size = BUFSIZ;
	buffer = (char*)malloc(BUFSIZ);
	if (buffer == NULL){
        exit(1);
	}
	size_t line = 1;
	int ch;
	size_t curser = 1;
	size_t n = 0;
	while(( ch = fgetc(stream) ) != EOF){
		if (n + 1 > size){
			size += BUFSIZ;
			buffer = (char*)realloc(buffer, size);
			if (buffer == NULL){
                exit(1);
			}
		}
		curser++;
		if (ch == '\n'){
			line++;
			curser = 1;
		}
		buffer[n++] = ch;
	}
	buffer[n] = '\0';
	fclose(stream);
	return buffer;
}

size_t tobit(char *str){
	size_t med = 1;
	size_t final = 0;
	int i = strlen(str) - 1;
	while (i >= 0 && isdigit(str[i])){
		if (isdigit(str[i])){
			final += ( str[i] - '0') * med;
		}
		med *= 10;
		i--;
	}
	return final;
}


/*/=========================================================================/
**                                                                         **
**                                                                         **
**                              MAIN LEXER                                 **
**                                                                         **
//=========================================================================*/

// makes a token
Token MakeTok(char *token, char *type, int valid){
	Token T;
    T.token = tobit(token);
	T.type = type;
	T.valid = valid;
	return T;
}

// looks at the next character, compares it with the function and checks if in bounds
int Peek(const char *buffer, size_t *curser, int (*func)(int ch)){
	if (*curser > strlen(buffer) - 2){
		return 0;
	}
	*curser += 1;
	if (func(buffer[*curser])){
		return 1;
	}
	return 0;
}

int Peekchar(const char *buffer, size_t *curser, char ch){
	if (*curser > strlen(buffer) - 2){
		return 0;
	}
	*curser += 1;
	if (ch == buffer[*curser]){
		return 1;
	}
	return 0;
}

// takes in a string and returns tokens
Token *Lex(const char *str, const char *fileout){
    /*
    FILE *file = fopen(fileout, "w");
    if (file == NULL){
        printf("Error\n");
        exit(1);
    }
    */
	if (str == NULL){
        exit(1);
	}
	Token *buffer = (Token*)malloc(BUFSIZ * sizeof(Token));
	if (buffer == NULL){
        exit(1);
	}
	size_t line = 1;
	size_t curser = 0;
	size_t bufsize = BUFSIZ;
	size_t current = 0;
	size_t bufloc = 0;
	size_t end;
    int isfirst = 1;
	while (str[current] != '\0'){
		if (isdigit(str[current]) && isfirst){
			size_t tokensize = 10;
			size_t tokenloc = 0;
			char *token = (char*)malloc(10);
			if (token == NULL){
                exit(1);
			}
			do {
				if (tokenloc + 1 > tokensize){
					tokensize += 10;
					token = (char*)realloc(token, tokensize);
					if (token == NULL){
                        exit(1);
					}
				}
				token[tokenloc] = str[current];
				tokenloc++;
			} while (Peek(str, &current ,isdigit));
            current--;
            if (Peekchar(str, &current, '\n')){
			    token[tokenloc] = '\0';
                if (bufloc + 1 > bufsize){
			    	bufsize += BUFSIZ;
			    	buffer = realloc(buffer, bufsize * sizeof(Token));
			    	if (buffer == NULL){
                     exit(1);
			    	}
			    }
			    buffer[bufloc] = MakeTok(token, "num", 1);
                free(token);
			    bufloc++;
                //fprintf(file, "Amount: %llu\n", bufloc);
            }
		}
		else if (str[current] == '\n'){
			isfirst = 1;
            //fprintf(file, "Current: %llu\n", current);
            current++;
		}
		else{
            isfirst = 0;
            //fprintf(file, "Current: %llu\n", current);
            current++;
		}
	}
	buffer[bufloc].valid = 0;
	return buffer;
}

int main(){
    FILE *stream = NULL;
    Token *tokens;
    const char *filename = "mega.txt";
    const char *fileout = "numarray.h";
    const char *header = "NUM_ARRAY_H";
    char *file;
    int i = 0;
    int j = 0;
    file = ReadFile(stream, filename);
    tokens = Lex(file, fileout);
    stream = fopen(fileout, "w");
    fprintf(stream, "#ifndef %s\n", header);
    fprintf(stream, "#define %s\n", header);
    fprintf(stream, "#include <stdint.h>\n");
    fputs("int_fast8_t numarray[] = {\n", stream);
    while(tokens[i].valid != 0){
        if (j == 6){
            i++;
            j = 0;
            continue;
        }
        fprintf(stream, "\t%d,\n", tokens[i].token);
        ++j;
        ++i;
    }
    fputs("};\n", stream);
    fprintf(stream, "#endif //%s", header);
    fclose(stream);
}
