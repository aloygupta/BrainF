
/*	For license, see the LICENSE file.
	For providing feedback and pointing out bugs , mail me.
	-Aloy Gupta
	 aloygupta1993@gmail.com
*/	



#include <stdio.h>
#include<string.h>
#include<stdlib.h>

/* The memory of MAXMEMORYSIZE number of cells where the computation takes place */
#define MAXMEMORYSIZE 35000
char memory[MAXMEMORYSIZE];         

/*Stack for pushing '[' whenever encountered and popping whenever a matching ']' is encountered */
#define MAXSTACKSIZE 1000
short int stack[MAXSTACKSIZE];

/* Array for holding corresponding matching locations of '[' and ']' */
#define MAXMATCHINGSIZE 65536
short int matching[MAXMATCHINGSIZE];

/* Array for holding the source code of the input program */
#define MAXSOURCESIZE 65536
char source[MAXSOURCESIZE];

FILE *sourceFile;

short int sourcePointer;
short int sourceSize;

/* Top-of-stack initialized to -1 indicating its empty state */
int tos=-1;

char *ptr=memory;

/* Pushes p into stack */
void push(short int p){
stack[++tos]=p;
}

/* Performs pop on stack */
short int pop(){
	return stack[tos--];
}

/* Reads the source program file */
void readSource(char *file){
	short int i,j;
	char c;
	sourceFile=fopen(file,"r");
	
	if(!sourceFile){
	fprintf(stderr,"Error: There was some error opening the file %s. Check whether it exists on disk.\n", file);
	exit(1);
	}

	sourceSize=0;

	for(i=0;i<MAXSOURCESIZE;i++){
	c=fgetc(sourceFile);	/* Read charcater by character */

	if(feof(sourceFile))	/* check for end-of-file */
	break;

	++sourceSize;
	source[i]=c;
	
	if(c=='[')
	push(i);
	else if(c==']'){
	if(tos==-1){
	 /* if ']' is encountered but there's no matching '[' on stack, then it is an error */
        fprintf(stderr,"Error: Unmatched ']' at byte %d.\n", i);
	exit(1);
}
	j=pop();
	matching[j]=i;	/* store matching location for '[' */
	matching[i]=j;	/* store matching location for ']' */
	}

	
    }
	if(tos>-1){ 
	/* If at the end of reading file , there are still left over '[' on stack then it is an error */
        fprintf(stderr,"Error: Unmatched '[' at byte %d.\n", stack[tos]);
	 exit(1);
}

fclose(sourceFile);
}


/* Execute the commands based on the character scanned */
void execute(char c){

switch(c){
	
	case '<':
	--ptr;
	break;
	
	case '>':
	++ptr;
	break;
	
	case '+':
	++*ptr;
	break;
	
	case '-':
	--*ptr;
	break;
	
	case ',':
	*ptr=getchar();
	break;
	
	case '.':
	putchar(*ptr);
	break;
	
	case '[':
	if(*ptr==0)
	sourcePointer=matching[sourcePointer];
	
	break;
	
	case ']':
	if(*ptr!=0)
	sourcePointer=matching[sourcePointer];
	
	break;
	
	default :
	break;
	
}
	

} 



int main(int argc, char *argv[])
{
	
	if (argc > 2){
	 fprintf(stderr, "Error: Too many arguments.Please provide only the source filename.\n");
	 exit(1);
	}
    	if (argc < 2){
	 fprintf(stderr, "Error : No source filename provided.\n");
	 exit(1);
	}
    	
	/* Clear the 'array' and 'memory' arrays */
	memset(matching,0,MAXMATCHINGSIZE);
	memset(memory,0,MAXMEMORYSIZE);
	
	readSource(argv[1]);
	
	for(sourcePointer=0;sourcePointer<sourceSize;sourcePointer++)
	execute(source[sourcePointer]);
		
	
	return 0;
}
