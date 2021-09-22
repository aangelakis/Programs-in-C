/*###########################################
# Alexandros Angelakis                      #
# csd4334                                   #
# Exercise 2 ~ HY255                        #
# csd4334@csd.uoc.gr                        #
#                                           #
#############################################*/

#include <stddef.h>
#include <stdio.h>
#include <assert.h>


/* Returns the length of string str. 
   It is checked runtime error for 'str' to be NULL
   Returns 0 if 'str' is empty */
size_t ms_length(const char str[]);


/* Copies the string 'src' to string 'dest'
   It is checked runtime error for 'src' and 'dest' to be NULL
   Returns the string 'dest' after it has been copied */
char* ms_copy(char dest[], const char src[]);


/* Copies up to 'n' characters from string 'src' to string 'dest'
   It is checked runtime error for 'src' and 'dest' to be NULL
   Returns a pointer to 'dest' after it has been copied */
char* ms_ncopy(char dest[], const char src[], size_t n);


/* Appends a copy of 'src' string to 'dest' string. The '\0' of string
   'dest' is overwritten by the first character of 'src' and the new concatenated
   string is formed. Returns a pointer to dest as the new string. It is checked 
   runtime error for 'dest' and 'src' to be NULL. */ 
char* ms_concat(char dest[], const char src[]);


/* Appends the first n characters of 'src' to 'dest' with a '\0' character at the end.
   Returns a pointer to dest as the new string. It is checked runtime error for 'dest' 
   and 'src' to be NULL. */ 
char* ms_nconcat(char dest[], const char src[], size_t n);


/* Compares the string str1 to the string str2. Returns 0 if the string are the same, 
   or negative/positive based on the difference of the ASCII values of the characters
   that are not the same have. If a str2 character is greater than a str1 character, then
   it will return a negative number. Otherwise a positive. It is checked runtime error for 
   'str1' and 'str2' to be NULL. */ 
int ms_compare(const char str1[], const char str2[]);


/* Compares up to n characters of the string str1 to those of the string
   str2. Returns 0 if the string are the same, or negative/positive based on
   the difference of the ASCII values of the characters that are not the same have. 
   If a str2 character is greater than a str1 character, then it will return a negative
   number. Otherwise a positive. It is checked runtime error for 'str1' and 'str2' to be NULL. */ 
int ms_ncompare(const char str1[], const char str2[], size_t n);


/* Searches for the needle inside of haystack and returns a pointer
   to the first occurence of the string needle inside the string haystack 
   or NULL if needle does not exist in haystack. It is checked runtime 
   error for 'haystack' and 'needle' to be NULL. */
char* ms_search(const char str1[], const char str2[]);
