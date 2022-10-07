/*	THIS IS THE HEADER FILE FOR MY BRAINSPARK CBT PROGRAM	*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_CHAR 81

void aboutUs(void);
int strsize(const char *fmt);
int aligncen(const char *fmt);
void exitmsg(const char *fmt);
int displayhead( char *namef );
int charLine( int size, char element);
char *Qtypemenu(int *type);	/*	select the type of question to answer.	*/
int readQnum(FILE *p_file);
char *copycat(char *dest, char *source, char *item);	/*	copy source to dest and concatenate item to dest, return dest afterwards	*/
int	chooseQnum(int availableQ, int *start, int *requiredQ);
int displayquestions( char Qfile[], char myAns[], int start, int Qrequired);
char lastItem( char string[]);
int mark(char *ansfilename, int startline, char inputArray[], int requiredAns);
int calcQnum(FILE *p_file);
int get_int(void);
void clearTrash(void);
void intro(void);
void prepareWindow(void);	/*	this function resizes the command prompt's window size so that the questions will be better displayed IT ALSO CHANGES THE TITLE*/
void initializeWindow(void);	/*	this function resizes the command prompt's window size to the default i.e it's intitial dimensions	*/


FILE *fp = NULL;
char USERNAME[MAX_CHAR];	/* NAME OF THE USER.	*/
char Qfilename[MAX_CHAR];	/*	CONTAINING THE QUESTIONS.	*/
char Ansfilename[MAX_CHAR];	/*	CONTAINING THE ANSWERS OF THE PARTICULAR EXAM TYPE CHOSEN	*/
char HfilenameNEXT[MAX_CHAR];	/*	Hfilename No Extension.	*/
char Hfilename[MAX_CHAR];	/*	CONTAINING THE HEADER OF THE QUESTION YEAR SELECTED.	*/
char mode[4] = "r";
