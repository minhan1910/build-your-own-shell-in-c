#ifndef __STRING_UTIL__
#define __STRING_UTIL__

char * read_line();
char ** split_str(const char * str, const char * delimiter, int * count);
int count_token(const char * str, const char * delimiter);
void free_strs(char ** tokens);

#endif