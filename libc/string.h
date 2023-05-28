#ifndef STRING_H
#define STRING_H

/* Define size_t if it is not available */
#ifndef _SIZE_T_DEFINED
typedef unsigned int size_t;
#define _SIZE_T_DEFINED
#endif

void int_to_ascii(int n, char str[]);
void hex_to_ascii(int n, char str[]);
void reverse(char s[]);
int strlen(const char* s);
void backspace(char s[]);
void append(char s[], char n);
int strcmp(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);
char* strcat(char* destination, const char* source);
char* strcpy(char* destination, const char* source);

#endif
