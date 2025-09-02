#ifndef MAIN_H
#define MAIN_H

int _putchar(char c);

void *malloc_checked(unsigned int b);
char *string_nconcat(char *s1, char *s2, unsigned int n);
void *_calloc(unsigned int nmemb, unsigned int size);
int *array_range(int min, int max);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

int _strlen(char *s);
int is_digits(char *s);
void print_str(char *s);
void print_error_exit(void);
void print_number_array(int *a, int len);
char *normalize(char *s, int *out_len);

#endif /* MAIN_H */

