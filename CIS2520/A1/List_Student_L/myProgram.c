#include "ListInterface.h"
/* some code here (e.g., #include directives, static functions) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char * argv[]) 
{
    FILE * infile = NULL;
    List L;
    Student S;
    char buffer[100], name[10], command[10];
    int position, grade, i;
    
    if (argc != 2)  // gives error message if a file is not entered on the command line
    { 
        printf( "usage: %s [name of input text file] \n", argv[0] );
        return 0;
    }
    
    infile = fopen (argv[1], "r"); // open the file
    
    if (infile == NULL)
    {
        printf("Error opening file"); exit(0);       
    }
    
    Initialize(&L); // initialize the list    

    while(fgets(buffer, sizeof(buffer), infile) != NULL)
    {
        if(Empty(&L) == 1 && Full(&L) == 0) // if list is empty and not full go in here
            printf("List is empty; List is not full; List is of length: %d\n", Length(&L));
        
        else if (Empty(&L) == 0 && Full(&L) == 1) // if list is not empty and list is full go in here
        { 
            printf("List is not empty; List is full; List is of length: %d\n", Length(&L));
            for(i = 0; i < Length(&L); i++)
            {
                Peek(i,&L,&S);
                printf("     %s %d%%\n", NameOfStudent(S), GradeOfStudent(S));     
            } 
        }
        else
        {
            printf("List is not empty; List is not full; List is of length: %d\n", Length(&L));
            for(i = 0; i < Length(&L); i++)
            {
                Peek(i,&L,&S);
                printf("     %s %d%%\n", NameOfStudent(S), GradeOfStudent(S));
            }
        }
        
        if(strncmp(buffer, "I", 1) == 0) // compare buffer to the letter 'I', if its equal InitializeStudent and Insert function is called
        {
            sscanf(buffer, "%s %d %s %d", command, &position, name, &grade);
            if(Full(&L) != 1) 
            {
                InitializeStudent(name,grade,&S);
                Insert(S,position,&L);
            }
        }
        
        if(strncmp(buffer, "D", 1) == 0) // compare buffer to the letter 'D', if its equal Remove function is called
        {
            sscanf(buffer, "%s %d", command, &position);
            if(Empty(&L) != 1)
                Remove(position,&L);
        }
    }
    
    if(Empty(&L) == 1 && Full(&L) == 0)
        printf("List is empty; List is not full; List is of length: %d\n", Length(&L));

    fclose(infile); 
}