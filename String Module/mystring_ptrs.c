/*###########################################
# Alexandros Angelakis                      #
# csd4334                                   #
# Exercise 2 ~ HY255                        #
# csd4334@csd.uoc.gr                        #
#                                           #
#############################################*/

#include "mystring.h"

/* Returns the length of string str. 
   It is checked runtime error for 'str' to be NULL
   Returns 0 if 'str' is empty */
size_t ms_length(const char *str){
    
    size_t length = 0; /* The length of the str before the loop. Equals 0 by default. */
    const char *str_temp = str;

    assert(str); /* Runtime Error for NULL input. */

    while(*str_temp != '\0'){ /* While str is not over increase the variable length by one. */

        length++;

        str_temp++;
    }
    
    return length;
}


/* Copies the string 'src' to string 'dest'
   It is checked runtime error for 'src' to be NULL
   Returns the string 'dest' after it has been copied */
char* ms_copy(char *dest, const char *src){

    const char *src_temp = src;
    
    assert(src);
    assert(dest); /* Runtime Error for NULL input. */

    while(*src_temp != '\0'){ /* While src is not over. */

        *dest = *src_temp; /* Copy src characters to dest. */

        dest++;
        src_temp++;
    }
    *dest = '\0'; /* Adding the terminating NULL character. */

    return dest;
}

/* Copies up to 'n' characters from string 'src' to string 'dest'
   It is checked runtime error for 'src' and 'dest' to be NULL
   Returns a pointer to 'dest' after it has been copied */
char* ms_ncopy(char *dest, const char *src, size_t n){

    const char *src_temp = src;

    assert(src || dest); /* Runtime Error for NULL input. */

    while(n > 0){

        if(*src_temp != '\0'){ /* If src is not over then copy its characters to dest. */
            *dest = *src_temp;
        } else{ /* If src is over the break the while loop. */
            break;
        }

        dest++;
        src_temp++;
        n--;
    }

    *dest = '\0'; /* Adding the terminating NULL character. */

    return dest;
}


/* Appends a copy of 'src' string to 'dest' string. The '\0' of string
   'dest' is overwritten by the first character of 'src' and the new concatenated
   string is formed. Returns a pointer to dest as the new string. It is checked 
   runtime error for 'dest' and 'src' to be NULL. */ 
char* ms_concat(char *dest, const char *src){ 

    const char *src_temp = src;
    size_t dest_len = ms_length(dest); /* The size of string 'dest' and the letters we have to skip for 'dest'. */

    assert(dest || src); /* Runtime Error for NULL input. */

    while(*src_temp != '\0'){

        *(dest + dest_len) = *src_temp; /* Append src characters to the end of dest. */

        dest++;
        src_temp++;
    }

    *(dest + dest_len) = '\0'; /* Adding the terminating NULL character. */

    return dest;
}

/* Appends the first n characters of 'src' to 'dest' with a '\0' character at the end.
   Returns a pointer to dest as the new string. It is checked runtime error for 'dest' 
   and 'src' to be NULL. */ 
char* ms_nconcat(char *dest, const char *src, size_t n){

    const char *src_temp = src;
    size_t dest_len = ms_length(dest); /* The size of string 'dest' and the letters we have to skip for 'dest'. */

    assert(dest || src); /* Runtime Error for NULL input. */

    while(n > 0){

        *(dest + dest_len) = *src_temp; /* Append src's first n characters to dest. */

        dest++;
        n--;
        src_temp++;
    }

    *(dest + dest_len) = '\0';  /* Adding the terminating NULL character. */

    return dest;
}


/* Compares the string str1 to the string str2. Returns 0 if the string are the same, 
   or negative/positive based on the difference of the ASCII values of the characters
   that are not the same have. If a str2 character is greater than a str1 character, then
   it will return a negative number. Otherwise a positive. It is checked runtime error for 
   'str1' and 'str2' to be NULL. */ 
int ms_compare(const char *str1, const char *str2){

    const char *str1_temp = str1;
    const char *str2_temp = str2;

    assert(str1 || str2); /* Runtime Error for NULL input. */

    while(*str1_temp == *str2_temp){ /* While we don't found a character that is not the same. */
    
        if(*(str1_temp) ==  '\0' || *(str2_temp) == '\0'){ /* Break the while loop if one of the strings compared are over. */
            break;
        }

        str1_temp++;
        str2_temp++;
    }

    return *(str1_temp) - *(str2_temp); /* Return the difference of the characters. */
}


/* Compares up to n characters of the string str1 to those of the string
   str2. Returns 0 if the string are the same, or negative/positive based on
   the difference of the ASCII values of the characters that are not the same have. 
   If a str2 character is greater than a str1 character, then it will return a negative
   number. Otherwise a positive. It is checked runtime error for 'str1' and 'str2' to be NULL. */   
int ms_ncompare(const char *str1, const char *str2, size_t n){

    const char *str1_temp = str1;
    const char *str2_temp = str2;

    assert(str1 || str2); /* Runtime Error for NULL input. */

    while(n > 0){
        if(*(str1_temp) != *(str2_temp)){ /* If you find a character that is not the same then break the while loop. */
            break;
        }

        if(*str1_temp == '\0' || *str2_temp == '\0'){ /* Break the while loop if one of the strings compared are over. */
            break;
        }

        str1_temp++;
        str2_temp++;
        n--;
    }

    if(n == 0){ /* If n is equal to 0, then return the difference of the characters before '\0'. */
        return *(str1_temp - 1) - *(str2_temp - 1);
    }

    return *(str1_temp) - *(str2_temp); /* Return the difference of the characters. */
}


/*  Searches for the needle inside of haystack and returns a pointer
    to the first occurence of the string needle inside the string haystack 
    or NULL if needle does not exist in haystack. It is checked runtime 
    error for 'haystack' and 'needle' to be NULL.    */
char* ms_search(const char *haystack, const char *needle){

    int i = 0; /* A variable that indicates how many times the while loop has been executed. */
    int counter = 0; /* A variable that indicates the times a character from the string needle is the same from the string haystack. */
    int begin = 0; /* A variable that remembers the first occurance of the string needle in string haystack. */
    size_t needle_len = ms_length(needle); /* The length of the string needle. */
    
    const char *haystack_temp = haystack;
    const char *needle_temp = needle;

    assert(haystack || needle); /* Runtime Error for NULL input. */

    while(*haystack_temp != '\0'){ /* Keep looking for the string needle until haystack points to the character '\0'. */

        if(*haystack_temp == *(needle_temp + counter)){ /* If you find a character that is the same, increase counter by one and remember the first position of it in the haystack string. */
            begin = i - counter;
            counter++;
        } else{
            begin = 0;
            counter = 0;
        }

        if(counter == needle_len){ /* If the needle is found, then return a pointer to the first occurence of needle inside haystack. */ 
            return (char*)(haystack + begin); 
        }

        haystack_temp++;
        i++;
    }

    return NULL; /* Return NULL if the string needle does not exist in haystack. */
}