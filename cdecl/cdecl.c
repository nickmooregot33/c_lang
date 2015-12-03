/******************************************************************************************************************************************************
 *                                                                                                                                                    *
 *                                                   *************************                                                                        *
 *                                                   *        PROGRAM        *                                                                        *
 *                                                   *         CDECL         *                                                                        *
 *                                                   *************************                                                                        *
 *                                                                                                                                                    *
 *          Written by Nick Moore as a programming assignment in the book 'Expert C Programming: Deep C secrets" by Peter Van Der Linden              *
 *                                                                                                                                                    *
 *          A program to parse a file with C declarations and convert them into english language descriptions                                         *
 *                                                                                                                                                    *
 *          user defined types:                                                                                                                       *
 *               struct token_st { char type; char string[MAXTOKENLEN];};                                                                             *
 *                      char type: shows which type of token we are dealing with, from the set {qualifier, identifier}                                *
 *               enum token_class {QUALIFIER, IDENTIFIER};                                                                                            *
 *                      used for classifying the type member of struct token_t                                                                        *
 *          data structures used:                                                                                                                     *
 *               stack (LIFO):                                                                                                                        *
 *                      implemented as an array, to be managed by our own functions (it's c after all)                                                *
 *                      push():                                                                                                                       *
 *                            push a token onto the stack (decrement pointer, then add data)                                                          *
 *                      pop():                                                                                                                        *
 *                            pop a token off of the stack (get data, then increment pointer)                                                         *
 *          variables used:                                                                                                                           *
 *               stack[MAXTOKENS]:                                                                                                                    *
 *                      array of tokens to be used as the stack, holds tokens we read before reaching the first identifier                            *
 *               this:                                                                                                                                *
 *                      current token most recently read                                                                                              *
 *                                                                                                                                                    *
 *                                                                                                                                                    *
 ******************************************************************************************************************************************************
 */
#include <stdio.h>


/*****************************************************function prototypes to be used*******************************************************************/

/* pop a token off of the stack*/
struct token pop(struct token *data); 

/* push a token onto the stack*/
struct token *push(struct token data); 

/* token_class:
        takes a single token as parameter
        returns the class of the token
        
        we will not use the returned class for single character tokens, as we will store the character itself into this.type in those cases
*/
enum token_class classify_string(struct token data); 

/*get_token:
        takes a char* and reads next token into this.string, 
        if the token is alphanumeric it is classified, otherwise it's a single character token and we put the whole token into this.type
        we terminate this.string with NULL
 */
struct token gettoken(char* line); 

int main(){
  /**/
  return 0;
}
