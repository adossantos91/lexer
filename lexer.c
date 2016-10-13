#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    nulsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5, multsym = 6,  slashsym = 7, oddsym = 8,
    eqsym = 9, neqsym = 10, lessym = 11, leqsym = 12, gtrsym = 13, geqsym = 14,
    lparentsym = 15, rparentsym = 16, commasym = 17, semicolonsym = 18, periodsym = 19,
    becomessym = 20, beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26,
    callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31, readsym = 32, elsesym = 33, colonsym = 34
    } token_type;


//function prototypes.
char* printSourceNoComment(char *code, int fileLength);
char* createSourceNoComment(char *code, int fileLength);
void printSourceWithComment(char *code, int fileLength);
void readTokens(char *code, int fileLength);

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
	char* argument1 = argv[2];
	char* argument2= argv[3];

    int c;
    char *code, *real;
    int i = 0, fileLength;

    code = malloc(20000 * sizeof(char));

    while(fscanf(fp, "%c", &c) != EOF)
    {
        code[i] = c;
        i++;
        fileLength++;
    }
	//printf("argument1 %s argument2 %s\n",argument1,argument2 );

	if (argument1 != NULL)
	{
		if (strcmp(argument1,"--source") == 0)
		{

			printSourceWithComment(code, fileLength);
		}
		else if (strcmp(argument1,"--clean") == 0)
		{
			real = printSourceNoComment(code, fileLength);
		}

		if (argument2 != NULL)
		{
			//printf("sjoudlnt be here");
			if (strcmp(argument2,"--source") == 0)
			{
				printSourceWithComment(code, fileLength);
			} else if (strcmp(argument2,"--clean") == 0) {
				real = printSourceNoComment(code, fileLength);
			}
		}
	}






    real = createSourceNoComment(code, fileLength);
    readTokens(real, fileLength);

	free(code);

    return 0;
}
void readTokens(char *code, int fileLength)
{

    int i;
	printf("tokens\n-------\n");

    for (i=0; i<fileLength; i++)
    {
        if((code[i] == 'v') && (code[i+1] == 'a') && (code[i+2] == 'r'))
        {
            printf("var\t\t29\n");
            i=i+3;
        }

        if(isdigit(code[i]))
        {

            if((isdigit(code[i+4])) && (isdigit(code[i+3])) && (isdigit(code[i+2])) && (isdigit(code[i+1])))
            {
               printf("%c%c%c%c%c \t3\n", code[i], code[i+1], code[i+2] ,code[i+3], code[i+4]);
               i=i+4;
            }
            else if((isdigit(code[i+3])) && (isdigit(code[i+2]))&& (isdigit(code[i+1])))
            {
               printf("%c%c%c%c   \t3\n", code[i], code[i+1], code[i+2], code[i+3]);
               i=i+3;
            }
            else if(isdigit(code[i+2]) && (isdigit(code[i+1])))
            {
               printf("%c%c%c \t\t3\n", code[i], code[i+1], code[i+2]);
               i=i+2;
            }
            else if(isdigit(code[i+1]))
            {
                printf("%c%c \t\t3\n", code[i], code[i+1]);
                i=i+1;
            }
            else
                printf("%c  \t\t3\n", code[i]);
        }

        if(code[i] == ',')
            printf("%c  \t\t17\n", code[i]);

        if(code[i] == ';')
            printf("%c  \t\t18\n", code[i]);

        if((code[i] == 'b') && (code[i+1] == 'e') && (code[i+2] == 'g') &&
           (code[i+3] == 'i') && (code[i+4] == 'n'))
        {
            printf("begin   \t21\n");
            i=i+5;
        }
        if(code[i] == ':' && code[i+1] == '=')
        {
            printf("%c%c \t\t20\n", code[i],code[i+1]);
            i=i+2;
        }
        if(code[i] == '+')
            printf("%c   \t\t4\n", code[i]);

        if((code[i] == 'e') && (code[i+1] == 'n') && (code[i+2] == 'd' ))
        {
            printf("end  \t\t22\n");
            i=i+3;
        }

        if(code[i] == '.')
            printf("%c   \t\t19\n", code[i]);

	// -----------------------------------  Alex's additions ----------------------------------------------

        // (
        
        if((code[i] == '(')){
        
        printf("(   \t\t15\n");
        
        i+=1;
        
        }


	// )

        if((code[i] == ')')){

        printf(")   \t\t16\n");

        i+=1;

        }

	// :
	
	if(code[i] == ':' && code[i+1] != '=')
        {
            printf("%c \t\t34\n", code[i]);
            i=i+1;
        }


	// =  
	
	if((code[i] == '=')){
	
	    printf("=   \t\t9 \n");
	
	        i+=1;
	
	}


	
	//!=  

	if((code[i] == '!') && (code[i+1] == '=')){

            printf("!=   \t10 \n");

            i+=2;

        }



	//>=

	if((code[i] == '>') && (code[i+1] == '=')){

            printf(">=   \t\t14\n");

            i+=2;

        }



	//<

	if((code[i] == '<') && (code[i+1] != '=')){

            printf("<   \t\t11\n");

            i+=1;

        }





	//>

	if((code[i] == '>') && (code[i+1] != '=')){

            printf(">   \t\t13\n");

            i+=1;

        }





	//<=
	if((code[i] == '<') && (code[i+1] == '=')){

            printf("<=   \t\t12\n");

            i+=2;

        }


	//do
	if((code[i] == 'd') && (code[i+1] == 'o')){

            printf("do   \t\t26\n");

            i+=2;

        }





	//if

	if((code[i] == 'i') && (code[i+1] == 'f')){

            printf("if   \t\t23\n");

            i+=2;

        }

	//then

	if((code[i] == 't') && (code[i+1] == 'h') && (code[i+2] == 'e') && (code[i+3] == 'n')) {

            printf("then   \t\t24\n");

            i+=4;

        }




	//while

	if((code[i] == 'w') && (code[i+1] == 'h') && (code[i+2] == 'i') && (code[i+3] == 'l') && (code[i+4] == 'e')){

            printf("while   \t25\n");

            i=i+5;

        }

	//call


	if((code[i] == 'c') && (code[i+1] == 'a') && (code[i+2] == 'l') && (code[i+3] == 'l')) {

            printf("call   \t\t27\n");

            i+=4;

        }




	//else

	if((code[i] == 'e') && (code[i+1] == 'l') && (code[i+2] == 's') && (code[i+3] == 'e')) {

            printf("else   \t\t33\n");

            i+=4;

        }





	//const



	if((code[i] == 'c') && (code[i+1] == 'o') && (code[i+2] == 'n') && (code[i+3] == 's') && (code[i+4] == 't')){

            printf("const   \t28\n");

            i=i+5;

        }



	//procedure

	if((code[i] == 'p') && (code[i+1] == 'r') && (code[i+2] == 'o') && (code[i+3] == 'c') && (code[i+4] == 'e') && (code[i+5] == 'd') && (code[i+6] == 'u') && 
	(code[i+7] == 'r') && (code[i+8] == 'e')){

            printf("procedure   \t30\n");

            i+=8;

        }




	//odd



	if((code[i] == 'o') && (code[i+1] == 'l') && (code[i+2] == 'd') && (code[i+3] == 'd')) {

            printf("odd   \t\t8\n");

            i+=3;

        }





	//read

	if((code[i] == 'r') && (code[i+1] == 'e') && (code[i+2] == 'a') && (code[i+3] == 'd')) {

            printf("read   \t32\n");

            i+=4;

        }



	//write

	if((code[i] == 'w') && (code[i+1] == 'r') && (code[i+2] == 'i') && (code[i+3] == 't') && (code[i+4] == 'e')){

            printf("write   \t31\n");

            i=i+5;

        }


	//null

	if((code[i] == 'n') && (code[i+1] == 'u') && (code[i+2] == 'l') && (code[i+3] == 'l')) {

            printf("null   \t\t1\n");

            i+=4;

        }




	// ----------------------------------- end of Alex's additions ----------------------------------------
	//
	if(isalpha(code[i]))
        {

         if((isalpha(code[i+4])) && (isalpha(code[i+3])) && (isalpha(code[i+2])) && (isalpha(code[i+1])))
            {
               printf("%c%c%c%c%c \t\t2\n", code[i], code[i+1], code[i+2] ,code[i+3], code[i+4]);
               i=i+4;
            }
            else if((isalpha(code[i+3])) && (isalpha(code[i+2]))&& (isalpha(code[i+1])))
            {
               printf("%c%c%c%c   \t\t2\n", code[i], code[i+1], code[i+2], code[i+3]);
               i=i+3;
            }
            else if(isalpha(code[i+2]) && (isalpha(code[i+1])))
            {
               printf("%c%c%c \t\t2\n", code[i], code[i+1], code[i+2]);
               i=i+2;
            }
            else if(isalpha(code[i+1]))
            {
                printf("%c%c \t\t2\n", code[i], code[i+1]);
                i=i+1;
            }
            else
                printf("%c  \t\t2\n", code[i]);
        }



    }

}
char *printSourceNoComment(char *code, int fileLength)
{
    int i;
    char *real;

    real = malloc(20000 * sizeof(char));

    printf("source code without comments:\n-----------------------------\n");
    for(i=0; i < fileLength; i++)
    {
        if(code[i] == '/' && code[i+1] == '*')
        {
            //skip ahead 2 spaces.
            i=i+2;
            while(code[i] != '*' && code[i+1] != '/')
                i++;
        }

        if(code[i] != '*' && code[i] != '/')
        {
            printf("%c", code[i]);
            real[i]=code[i];
        }
    }

	printf("\n\n");
    return real;

}
char *createSourceNoComment(char *code, int fileLength)
{
    int i;
    char *real;

    real = malloc(20000 * sizeof(char));

    //printf("source code without comments:\n-----------------------------\n");
    for(i=0; i < fileLength; i++)
    {
        if(code[i] == '/' && code[i+1] == '*')
        {
            //skip ahead 2 spaces.
            i=i+2;
            while(code[i] != '*' && code[i+1] != '/')
                i++;
        }

        if(code[i] != '*' && code[i] != '/')
        {
            //printf("%c", code[i]);
            real[i]=code[i];
        }
    }
    //printf("\n\ntokens\n-------\n");

    return real;

}


void printSourceWithComment(char *code, int fileLength)
{
    int i;
    printf("source code:\n------------\n");
    for(i=0; i < fileLength; i++)
        printf("%c", code[i]);

    printf("\n\n");
}
