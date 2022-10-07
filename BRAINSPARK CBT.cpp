/*	NEW COMPILATION OF THE BRAINSPARK CBT	*/
/*	THIS PROGRAM WAS WRITTEN BY INVENTOR ONWUTA EBUBECHUKWU GIDEON WITH THE AIM OF HELPING FIRST YEAR STUDENTS PREPARE FOR THEIR EXAMINATION	*/

#include "CBTfuncs.cpp"

int main()
{
	
	int count = 0;
	int Qtype;	/*	option for the type of question chosen by the user.	*/
	int Qnum = 0;
	int totalCorrect = 0;	/*	the total number of correct answers.	*/
	float percentAns = 0.0;
	
	prepareWindow();	/*	THIS FUNCTION MUST BE CALLLED AT THE BEGINNING OF THE PROGRAM.	*/
	
	intro();	/*	an introduction to the program	*/	
	
	strcpy(HfilenameNEXT, Qtypemenu(&Qtype) );	/*	fecht the 'Hfilename No Extension'.	*/
	
	copycat(Hfilename, HfilenameNEXT, "head.txt");	/* copy HfilenameNEXT to Hfilename and concatenate the extenstion to Hfilename	*/
	
	displayhead( Hfilename);
	rewind(fp);	/* start afresh to read the number of questions.	*/
	Qnum = calcQnum(fp);	/*	read the number of question available on the file.	*/
	
	int start = 0, choiceQnum = 0;	/*	 the question number to start at and the choice number of questions	*/
	chooseQnum(Qnum, &start, &choiceQnum);
	
	/*	decalare array for the user's answers and the correct answers.	*/
	char userAnsArray[choiceQnum], correctAns[choiceQnum];
	
	copycat(Qfilename, HfilenameNEXT, "questions.txt");	/* copy HfilenameNEXT to Qfilename and add the extension.	*/
	copycat(Ansfilename, HfilenameNEXT, "ans.txt");
	
	
	displayquestions(Qfilename, userAnsArray, start, choiceQnum);	/*	DISPLAYS THE QUESTIONS AND COLLECTS THE ANSWERS.	*/
	totalCorrect = mark(Ansfilename, start, userAnsArray, choiceQnum);	/*	marks the answers supplied by the user.	*/
	
	printf("\n\nYou scored %d out of %d\n", totalCorrect, choiceQnum);	/*	display the result.	*/
	percentAns = (float) 100 * totalCorrect/choiceQnum;	/*	calculate the percentage Accuracy of the user.	*/
	printf("\nThat is %.2f%%\n", percentAns);
	
	fclose(fp);
	
	aboutUs();	/*	DISPLAY INFORMATION ABOUT THE PROGRAMMER OF THIS CODE	*/
	printf("\n\nEnter anything to quit the program:\t");	
	getchar();	/* to delay	*/
	fflush(stdin);
	
	initializeWindow();	/*	THIS FUNCTION MUST BE CALLED AT THE END OF THE PROGRAM	*/
	return 0;
}
/*	END OF MAIN()	*/
