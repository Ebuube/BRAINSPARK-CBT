/*	ALL THE IMPORTANT FUNCTIONS FOR THIS CBT PROGRAM	*/

#include "brainspark.h"

void prepareWindow(void)	/*	this function resizes the command prompt's window size so that the questions will be better displayed IT ALSO CHANGES THE TITLE*/
{/*	THIS FUNCTION SHOULD BE CALLED AT THE BEGINNING OF THE PROGRAM	*/
	system("MODE CON: COLS=167 LINES=9000");
	system("TITLE \"BRAINSPARK COMPUTER BASED TEST ----- MANAGER: ONWUTA EBUBECHUKWU GIDEON ---- GOODLUCK\"");
}

void initializeWindow(void)	/*	this function resizes the command prompt's window size to the default i.e it's intitial dimensions	*/
{/*	THIS FUNCTION SHOULD BE CALLED AT THE END OF THE PROGRAM	*/
	system("MODE CON: COLS=120 LINES=9001");
}

int get_int(void)
{
	/* a function for reading integers from stdin.	*/

    int ch, i, sign = 1;
   
    /* Skip over any leading white space. */
   
    while ( isspace(ch = getchar()) )
    	;
   
    /* If the first character is nonnumeric, unget */
    /* the character and return 0. */
   
    if ( !isdigit(ch) && ch != EOF)
    {
	    ungetc(ch, stdin);
	    return 0;
    }
   
    /* Read characters until a nondigit is input. Assign */
    /* values, multiplied by proper power of 10, to i. */
   
    for (i = 0; isdigit(ch); ch = getchar() )
    	i = 10 * i + (ch - '0');
   
    /* If EOF was not encountered, a nondigit character */
    /* must have been read in, so unget it. */
   
    if (ch != EOF)
    	ungetc(ch, stdin);
   
    /* Return the input value. */
   
    return i;
}

int mark(char *ansfilename, int startline, char inputArray[], int requiredAns)
{
	/*	marks the users inputs and displays the result.	*/
	int startcount = 0;
	int count = 0;
	const int BUFSIZE = 10;
	const int CASE_DIFF = 32;	/*	a - A = 32	*/
	char buf[BUFSIZE];
	int totalCorrectAns = 0;
	char correctAns = 0;
	
	FILE *p_file = NULL;
	char filemode[] = "r";
	
	if ( (p_file = fopen(ansfilename, filemode)) == NULL)
		exitmsg("\nSorry, could not open the answer file.\n");
	
	/*	get to the correct line depending on the question number the user started with.	*/
	for(startcount=0; startcount < startline - 1; startcount++)	/*	get to the right line depending on where the user wants to start with.	*/
	{
		fgets(buf, BUFSIZE, p_file);
	}
	
	aligncen("USER RESULT\n");
	printf("\nS/N:\tYour choice\tEvaluation");	/* The result header.	*/
	printf("\n    \t===========\t==========\n");
	/*	read the answers and compare them with the user's answers.	*/
	while( !feof(p_file) && (count < requiredAns ))
	{
		
		fgets(buf, BUFSIZE, p_file);
		correctAns = lastItem(buf);
		
		/*	when there is no answer to the question, add a bonus mark	*/
		if( correctAns !='A' && correctAns !='B' && correctAns != 'C' && correctAns != 'D' && correctAns != 'E')
		{
			printf("\n%d:\t%c\t\tbonus mark\n", startline, inputArray[count]);
			totalCorrectAns++;
			startline++;
			count++;
			continue;
		}
				
		/*	answer compatibility test.	*/
		if( islower(inputArray[count]))
			inputArray[count] = inputArray[count] - CASE_DIFF;	/*	IF THE USER ENTERED A CAPITAL LETTER AS ANSWER.	*/
			
		if( (inputArray[count]) == correctAns)	/*	if answer is correct	*/
		{
			printf("\n%d:\t%c\t\tcorrect\n", startline, inputArray[count]);
			totalCorrectAns++;	/*	increment the total number of answers gotten correctly.	*/
		}
		else
			printf("\n%d:\t%c\t\twrong. The right answer is %c\n", startline, inputArray[count], correctAns);
		
		startline++;	/*	increment startline. This is very essential to the result.	*/
		count++;	/*	increment counter. This is very essential to this function.	*/
	}
	
	return totalCorrectAns;		/*	return the number of questions answered correctly.	*/
}

char lastItem( char string[])
{
	/*	this program returns the last item in this array before the end-of-file character.	*/
	char *p_end = NULL; 	/*	 A POINTER TO THE END OF FILE CHARACTER.	*/
	p_end = strchr( string, '\n');	/*	find the next line character which shows the end of the line.	*/
	p_end--;	/*	decrement pointer.	*/
	return (*p_end);	/* return the item before the end of file.	*/
}

int	chooseQnum(int availableQ, int *start, int *requiredQ)
{
	/* get the number of questions and the question number to start at.	*/
	int tester = 0;
	printf("\n\n%d number of questions are available starting from question number 1", availableQ);
	do
	{
		printf("\nEnter the number of questions you want to answer:	");
		*requiredQ = get_int();	/* recieve only an integer from stdin and discard other characters.	*/
		
		if( (*requiredQ) == 0)	/*	WHEN INPUT IS NOT AN INTEGER.	*/
		{
			printf("\nInvalid input.\n");
			fflush(stdin);
			continue;	
		}
		if ( ( (*requiredQ) <= availableQ) && ( (*requiredQ) > 0))	/*	when input is valid*/
		{
			tester = 0;
			break;
		}
		
		
	}while( 1 );	/*	infinite loop	*/
	
	do
	{
		printf("\nEnter the question number you will like to start from: ");
		*start = get_int();	/* recieve only an integer from stdin and discard other characters.	*/
		
		if( (*start) == 0)	/*	WHEN INPUT IS NOT AN INTEGER.	*/
		{
			printf("\nInvalid input.\n");
			fflush(stdin);
			continue;	
		}
		if ( ( (*start) >= 1) && ( (*start) + (*requiredQ) <= availableQ + 1) )	/*	check for valid input*/
		{
			tester = 0;
			break;
		}
		
	}while( 1 );	/*	infinite loop	*/
	
	return 0;	/*	showing a successful operation.	*/
}

char *copycat(char *dest, char *source, char *item)	
{
	/*	copy source to dest and concatenate item to dest, return dest afterwards	*/
	strcpy(dest, source);
	strcat(dest, item);
	
	return dest;
}

int displayquestions( char Qfile[], char myAns[], int start, int Qrequired)
{/*	starting from the designated questioin number	*/
	const int BUFSIZE = 256;
	const int LINESIZE = 75;
	int startcount = 0;
	int count = 0;
	char mode[] = "r";
	char buf[BUFSIZE];
	
	FILE *p_file = NULL;
	
	if( (p_file = fopen(Qfile, mode)) == NULL)
		exitmsg("\nSorry, could not open question file.\n");
	
	printf("\n\n\n");	/*	give enough space before displaying the header to create a clean program.	*/
	
	while(startcount < start - 1)	/*	get to the right line depending on where the user wants to start with.	*/
	{
		fgets(buf, BUFSIZE, p_file);
		if( buf[0] == '\n')	/*	empty line encountered, it means one question has finished.	*/
		{
			startcount++;
		}
	}
	
	getc(stdin);	/*	clear redundant input.	*/

	while( !feof(p_file) && count < Qrequired)	/*	display only the required number of questions.	*/
	{
		fgets(buf, LINESIZE, p_file);	/*	get and display the question.	*/
		printf("%s", buf);
	
		
		if(buf[0] == '\n')
		{	/*	get answer from the user.	*/
			do
			{	/*	user's answer compatibility test	*/				
				printf("\nSelect answer:\t");
				
				myAns[count] = (char) getchar();
												
				if( myAns[count] == 'a' || myAns[count] == 'A') break;
				if( myAns[count] == 'b' || myAns[count] == 'B') break;
				if( myAns[count] == 'c' || myAns[count] == 'C') break;
				if( myAns[count] == 'd' || myAns[count] == 'D') break;
				if( myAns[count] == 'e' || myAns[count] == 'E') break;
				
			}while( 1 );	/*	infinite loop	*/
			
			clearTrash();	/*	clear the next line character entered.	*/
			count++;
			printf("\n");

		}
	}
	
	printf("\n");	/* give space to ensure a clean program.	*/
	
	fclose(p_file);
	
	return 0;	/*	showing that all the questions were successfully displayed	*/
}

int calcQnum(FILE *p_file)
{
	/*	this program runs through the question-file of the choosen QuestionType, counts the number of questions there and returns this number of questions.	*/
	const int MAX_SIZE = 81;
	const int BUFSIZE = 256;
	int Qcount = 0;	/*	 the number of questions encountered.	*/
	
	char buf[BUFSIZE];
	char Qfile[MAX_SIZE];
	char filemode[] = "r";
	
	copycat(Qfile, HfilenameNEXT, "questions.txt");	/* add the correct extension and open the correct file.	*/
	
	if( (p_file = fopen(Qfile, filemode)) == NULL)
		exitmsg("\nError. Could not open the question file.\n");
	
	
	while( !feof(p_file) )	/*	search for questions until we reach the end of the file.	*/
	{
		fgets(buf, BUFSIZE, p_file);
		if( buf[0] == '\n')	/*	empty line encountered, it means one question has finished.	*/
		{
			Qcount++;
		}
	}
	
	return (Qcount-1);	/* there is an unused line at the end of questions.	*/
}

char *Qtypemenu(int *type)	/*	select the type of question to answer.	*/
{
	int counter = 0;
	char QuestionType[80];
	
	char HELLO[] = "\nThese are the available question types.\nChoose by entering the letter of your choice type:\n";
	printf("%s", HELLO);
	printf("A:\tBIO 101-GENETICS FOR MEDICAL STUDENTS 2011/2012\n");
	printf("B:\tBIO 101-GENETICS FOR MEDICAL STUDENTS 2012/2013\n");
	printf("C:\tNEW HORIZONS IN COMMUNICATION SKILLS GSP 101 WORKBOOK\n");
	printf("\nSelect an option:\t");
	
	(*type) = getchar();	/*	get the type of question.	*/
	fflush(stdin);	/*	to avoid complication.	*/
	
	printf("\n");	/*	JUST TO MAKE THE PROGRAM USER-FRIENDLY	*/
	
	/*	ASSIGN THE CORRECT QUESTION TYPE	*/
	if( (*type) == 'a' || (*type) == 'A')
	{
		strcpy(QuestionType, "bio-101-year2011-2012");
	}
	if( (*type) == 'b' || (*type) == 'B')
	{
		strcpy(QuestionType, "bio-101-year2012-2013");
	}
	if( (*type) == 'c' || (*type) == 'C')
	{
		strcpy(QuestionType, "gsp-101-workbook");
	}
	
	return QuestionType;
}

int charLine( int size, char element)
{
	for(int count=0;count<size;count++)
		printf("%c", element);
	
	return 0;	/*	showing succes.	*/
}

int displayhead( char *namef )
{	
	char buf[MAX_CHAR];
	
	if( (fp = fopen(Hfilename, mode)) == NULL)	/*	UNSUCCESSFUL OPENING	*/
		exitmsg("Failure in opening file");
		
	while( !feof(fp))	/*	while not end of file.	*/
	{
		fgets(buf, MAX_CHAR, fp);
		aligncen(buf);	/*	print the content of buf aligned to the center.	*/
	}
		
	return 0;	/*	showing that the process was successful.	*/
}

int aligncen(const char *fmt)
{
	/*	align the text to the center.	*/
	/*	instruction: This code adds an next-line character automatically.	*/
	int count = 0, start = 0, size = 0;
	char space = ' ';
	
	size = strsize((char *)fmt);
	
	start = (MAX_CHAR/2) - (size/2);
	
	printf("\n");
	for(count=0; count<start; count++)
		printf("%c", space);	/*	give the right number of spaces.	*/
	
	printf("%s", fmt);
	
	return 0;
}


int strsize(const char *fmt)
{
	/*	size of a string.	*/

	int count = 0;
	char *p_fmt = NULL;
	
	if( (p_fmt = (char *) malloc(sizeof(fmt)/sizeof(fmt[0]))) != NULL)
		strcpy(p_fmt, fmt);	/*	assign the value of fmt to the pointer p_fmt	*/
	else
	{
		printf("\nError! : malloc() could not allocate memory!\n");
		exit(EXIT_FAILURE);
	}
	
	if(p_fmt == NULL && fmt != NULL)
		printf("\np_fmt is still NULL\n");	/*	test	*/
	
	for(count=0; (*p_fmt) != '\0'; count++)
		p_fmt++;	/* increment the pointer to point to the next character.*/
	
	return count;	/*	return the size of the character array.	*/
}

void exitmsg(const char *fmt)
{
	/*	display the message and quit the program with failure.	*/
	printf("%s", fmt);
	exit(EXIT_FAILURE);
}

void intro(void)
{
	printf("\n");
	aligncen("Welcome to BRAINSPARK COMPUTER BASED TEST\n");
	charLine(78, '*');
}

void aboutUs(void)
{
	/*	display information about the writers of this code.	*/
	char aboutUsfile[]	= "aboutUs.txt";	/*	the file containing information about the programmers.	*/
	char myMode[] = "r";
	char buf[MAX_CHAR];
	
	FILE *p_file = NULL;
	
	if( (p_file = fopen(aboutUsfile, myMode)) == NULL)
		exitmsg("\nSorry, we could not display information about the writers of this code.\n");
	
	/*	DISPLAY THE CONTENTS OF THE FILE USING CENTER-ALIGNMENT	*/
	printf("\n");	/*	just for demarcation.	*/
	charLine(78, '=');	/* create a demarcation.	*/
	
	while( !feof(p_file))
	{
		fgets(buf, MAX_CHAR, p_file);
		aligncen(buf);
	}
}

void clearTrash(void)
{
	/*	clear the stdin.	*/
	char buf[256];
	gets(buf);
}
