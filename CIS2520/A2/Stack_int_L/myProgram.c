#include "StackInterface.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    
        FILE *test;
        Item X, Y, Z;
        int buffer, sum, addS1, addS2, lengthS1, lengthS2, extraNum;
        int counter = 0, carry = 0;       
        Stack S1;
        Stack S2;
        Stack S3;
        
        Initialize(&S1);
        Initialize(&S2);
        Initialize(&S3);
        
        test = fopen("test.txt","r");
        
        while((buffer=fgetc(test))!= EOF){ // read each character one by one
            if(buffer == '\n') // when a new line is encountered increase counter
                counter++;           
            else if(counter == 0){
                Push(buffer - '0',&S1); // subtract the ascii value of '0' to get the correct integer then Push the number into stack 1
            }
            else if (counter == 1){
                Push(buffer - '0',&S2); // subtract the ascii value of '0' to get the correct integer then Push the number into stack 2
            }
        }
        
        lengthS1 = Size(&S1);
        lengthS2 = Size(&S2);
        
        if(lengthS1 > lengthS2){ // Stack 1 is bigger in size
            while(Size(&S2) != 0){ // while the size of stack 2 is not 0 add the numbers from stack 1 and stack 2 and push into stack 3 
                Top(&S1,&Y);
                Top(&S2,&Z);
                addS1 = Y;
                addS2 = Z;
                sum = addS1 + addS2 + carry;
                
                if(sum >= 10){ // if sum is greater than 10, mod the sum by 10 and push into stack 3 and make carry equal to 1
                    Push(sum%10,&S3);
                    carry = 1;
                }
                else{
                    Push(sum%10,&S3);
                    carry = 0;
                }
                Pop(&S1);
                Pop(&S2);
            }
            while(Size(&S1) != 0){ // while there are still numbers in stack 1 push them into the third stack
                Top(&S1,&Y);
                extraNum = Y;
                Push(extraNum,&S3);
                Pop(&S1);
            }
        }
        
        else if(lengthS2 > lengthS1){ // Stack 2 is bigger in size
            while(Size(&S1) != 0){ // while the size of stack 1 is not 0 add the numbers from stack 1 and stack 2 and push into stack 3 
                Top(&S1,&Y);
                Top(&S2,&Z);
                addS1 = Y;
                addS2 = Z;
                sum = addS1 + addS2 + carry;
                if(sum >= 10){ // if sum is greater than 10, mod the sum by 10 and push into stack 3 and make carry equal to 1
                    Push(sum%10,&S3);
                    carry = 1;
                }
                else{
                    Push(sum%10,&S3);
                    carry = 0;
                }
                Pop(&S1);
                Pop(&S2);
            }
            while(Size(&S2) != 0){ // while there are still numbers in stack 2 push them into the third stack
                Top(&S2,&Y);
                extraNum = Y;
                Push(extraNum,&S3);
                Pop(&S2);
            }
        }
        
        test = fopen("test.txt", "a");
        printf("Length of sum is %d \n", Size(&S3));
        printf("The sum of the two numbers is: \n");
        fprintf(test, "\n\nThe sum equals:\n");
        
        while(Size(&S3) != 0){
            Top(&S3,&X);
            printf("%d", X);
            fprintf(test, "%d", X);
            Pop(&S3);
        }
        printf("\n");
                       
        fclose(test);
        Destroy(&S1);
        Destroy(&S2);
        Destroy(&S3);

        return EXIT_SUCCESS;
}
