#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 255
        enum
        {
           DONE, OK, EMPTY_LINE
        };
struct lable{
int location;
char* lable;
};
int main(int argc, char* argv[]) {

int isOpcode(char * lPtr){
	if (strcmp(lPtr,"ADD")==0) return 0;
	if (strcmp(lPtr,"AND")==0) return 0;
	if (strcmp(lPtr,"HALT")==0) return 0;
	if (strcmp(lPtr,"JMP")==0) return 0;
	if (strcmp(lPtr,"JSR")==0) return 0;
	if (strcmp(lPtr,"JSRR")==0) return 0;
	if (strcmp(lPtr,"LDB")==0) return 0;
	if (strcmp(lPtr,"LDW")==0) return 0;
	if (strcmp(lPtr,"LEA")==0) return 0;
	if (strcmp(lPtr,"NOP")==0) return 0;
	if (strcmp(lPtr,"NOT")==0) return 0;
	if (strcmp(lPtr,"RET")==0) return 0;
	if (strcmp(lPtr,"LSHF")==0) return 0;
	if (strcmp(lPtr,"RSHFL")==0) return 0;
	if (strcmp(lPtr,"RTI")==0) return 0;
	if (strcmp(lPtr,"STB")==0) return 0;
	if (strcmp(lPtr,"STW")==0) return 0;
	if (strcmp(lPtr,"TRAP")==0) return 0;
	if (strcmp(lPtr,"XOR")==0) return 0;
	if (strcmp(lPtr,"BR")==0) return 0;
	if (strcmp(lPtr,"BRn")==0) return 0;
	if (strcmp(lPtr,"BRz")==0) return 0;
	if (strcmp(lPtr,"BRp")==0) return 0;
	if (strcmp(lPtr,"BRnz")==0) return 0;
	if (strcmp(lPtr,"BRnp")==0) return 0;
	if (strcmp(lPtr,"BRzp")==0) return 0;
	if (strcmp(lPtr,"BRnzp")==0) return 0;
	return -1;
}
	int
	readAndParse( FILE * pInfile, char * pLine, char ** pLabel, char
	** pOpcode, char ** pArg1, char ** pArg2, char ** pArg3, char ** pArg4
	)
	{
	   char * lRet, * lPtr;
	   int i;
	   if( !fgets( pLine, MAX_LINE_LENGTH, pInfile ) )
		return( DONE );
	   for( i = 0; i < strlen( pLine ); i++ )
		pLine[i] = tolower( pLine[i] );
  
           /* convert entire line to lowercase */
	   *pLabel = *pOpcode = *pArg1 = *pArg2 = *pArg3 = *pArg4 = pLine + strlen(pLine);

	   /* ignore the comments */
	   lPtr = pLine;

	   while( *lPtr != ';' && *lPtr != '\0' &&
	   *lPtr != '\n' ) 
		lPtr++;

	   *lPtr = '\0';
	   if( !(lPtr = strtok( pLine, "\t\n ," ) ) ) 
		return( EMPTY_LINE );

	   if( isOpcode( lPtr ) == -1 && lPtr[0] != '.' ) /* found a label */
	   {
		*pLabel = lPtr;
		if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
	   }
	   
           *pOpcode = lPtr;

	   if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
	   
           *pArg1 = lPtr;
	   
           if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );

	   *pArg2 = lPtr;
	   if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );

	   *pArg3 = lPtr;

	   if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );

	   *pArg4 = lPtr;

	   return( OK );
	}

int toNum( char * pStr )
{
   char * t_ptr;
   char * orig_pStr;
   int t_length,k;
   int lNum, lNeg = 0;
   long int lNumLong;

   orig_pStr = pStr;
   if( *pStr == '#' )				/* decimal */
   { 
     pStr++;
     if( *pStr == '-' )				/* dec is negative */
     {
       lNeg = 1;
       pStr++;
     }
     t_ptr = pStr;
     t_length = strlen(t_ptr);
     for(k=0;k < t_length;k++)
     {
       if (!isdigit(*t_ptr))
       {
	 printf("Error: invalid decimal operand, %s\n",orig_pStr);
	 exit(4);
       }
       t_ptr++;
     }
     lNum = atoi(pStr);
     if (lNeg)
       lNum = -lNum;
 
     return lNum;
   }
   else if( *pStr == 'x' )	/* hex     */
   {
     pStr++;
     if( *pStr == '-' )				/* hex is negative */
     {
       lNeg = 1;
       pStr++;
     }
     t_ptr = pStr;
     t_length = strlen(t_ptr);
     for(k=0;k < t_length;k++)
     {
       if (!isxdigit(*t_ptr))
       {
	 printf("Error: invalid hex operand, %s\n",orig_pStr);
	 exit(4);
       }
       t_ptr++;
     }
     lNumLong = strtol(pStr, NULL, 16);    /* convert hex string into integer */
     lNum = (lNumLong > INT_MAX)? INT_MAX : lNumLong;
     if( lNeg )
       lNum = -lNum;
     return lNum;
   }
   else
   {
	printf( "Error: invalid operand, %s\n", orig_pStr);
	exit(4);  /* This has been changed from error code 3 to error code 4, see clarification 12 */
   }
}
     int line =0;
     struct lable lables[10];
     char *prgName   = NULL;
     char *iFileName = NULL;
     char *oFileName = NULL;

     prgName   = argv[0];
     iFileName = argv[1];
     oFileName = argv[2];
 printf("here");
     printf("program name = '%s'\n", prgName);
     printf("input file name = '%s'\n", iFileName);
     printf("output file name = '%s'\n", oFileName);
 	printf("here");
        char lLine[MAX_LINE_LENGTH + 1], *lLabel, *lOpcode, *lArg1,
                *lArg2, *lArg3, *lArg4;

           int lRet;

           FILE * lInfile;
           lInfile = fopen(iFileName, "r" );   /* open the input file */

           do
           {
                lRet = readAndParse( lInfile, lLine, &lLabel,
                        &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
                if( lRet != DONE && lRet != EMPTY_LINE )
                { 
		line++;
		if(strcmp(lOpcode,".ORIG"==0)){
		line=toNum(lArg1);	
		}
		if(lLabel != NULL){
		int i;
		for(i = 0; i<10; i++){
			if(lables[i].lable==NULL){
				lables[i].location=line;
				lables[i].lable=lLabel;
			}		
		}
		}
	
			printf("lable: %s\n",lLabel);
			printf("opcode: %s\n",lOpcode);
			printf("arg 1: %s\n",lArg1);
			printf("arg 2: %s\n",lArg2);
			printf("arg 3: %s\n",lArg3);
                }
           } while( lRet != DONE );



}
