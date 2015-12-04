/*
* vcutil.c -- Implementation of the utility functions
* 
* Author: Michael Tran #0524704
* Date Created: January 10, 2014
* Updated: February 3, 2014
* Contact: mtran04@uoguelph.ca 
*/

#define _GNU_SOURCE
#include "vcutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include <ctype.h>

/*
 * Function retrieves the Vcard property name
 * 
 * Arguments:
 * type - a string that represents a VcPname 
 * 
 * Return value:
 * VcPname is returned
 */
static VcPname getVcPname ( char * type ){
    VcPname propName;
    
    if(strcasecmp(type, "BEGIN") == 0){
        propName = VCP_BEGIN;
        return propName;
    }    
    else if(strcasecmp(type, "END") == 0){
        propName = VCP_END;
        return propName;
    }    
    else if(strcasecmp(type, "VERSION") == 0){
        propName = VCP_VERSION;
        return propName;
    }
    else if(strcasecmp(type, "N") == 0){
        propName = VCP_N;
        return propName;
    }    
    else if(strcasecmp(type, "FN") == 0){
        propName = VCP_FN;
        return propName;
    }    
    else if(strcasecmp(type, "NICKNAME") == 0){
        propName = VCP_NICKNAME;
        return propName;
    }    
    else if(strcasecmp(type, "PHOTO") == 0){
        propName = VCP_PHOTO;
        return propName;
    }    
    else if(strcasecmp(type, "BDAY") == 0){
        propName = VCP_BDAY;
        return propName;
    }    
    else if(strcasecmp(type, "ADR") == 0){
        propName = VCP_ADR;
        return propName;
    }    
    else if(strcasecmp(type, "LABEL") == 0){
        propName = VCP_LABEL;
        return propName;
    }    
    else if(strcasecmp(type, "TEL") == 0){
        propName = VCP_TEL;
        return propName;
    }    
    else if(strcasecmp(type, "EMAIL") == 0){
        propName = VCP_EMAIL;
        return propName;
    }    
    else if(strcasecmp(type, "GEO") == 0){
        propName = VCP_GEO;
        return propName;
    }    
    else if(strcasecmp(type, "TITLE") == 0){
        propName = VCP_TITLE;
        return propName;
    }    
    else if(strcasecmp(type, "ORG") == 0){
        propName = VCP_ORG;
        return propName;
    }    
    else if(strcasecmp(type, "NOTE") == 0){
        propName = VCP_NOTE;
        return propName;
    }     
    else if(strcasecmp(type, "UID") == 0){
        propName = VCP_UID;
        return propName;
    }    
    else if(strcasecmp(type, "URL") == 0){
        propName = VCP_URL;
        return propName;
    }    
    else{
        propName = VCP_OTHER;
        return propName;
    }
}

/*
 * Function counts the number of semicolons in a line
 * 
 * Arguments:
 * semicolon - an unfolded line
 * 
 * Return value:
 * the number of semicolons found in the line
 */
static int countSemicolon ( char * semicolon ){
    int length = 0;
    int i = 0;
    int counter = 0;
    char ch = ';';
    
    length = strlen(semicolon);
    
    for(i = 0; i < length; i++){        
        if(semicolon[i] == ch){
            counter++;
        }        
    }    
    return counter;
}

/*
 * Function counts the number of colons in a line
 * 
 * Arguments:
 * colon - an unfolded line
 * 
 * Return value:
 * the number of colons found in the line
 */
static int countColon ( char * colon ){
    int length = 0;
    int i = 0;
    int counter = 0;
    char ch = ':';
    
    length = strlen(colon);
    
    for(i = 0; i < length; i++){        
        if(colon[i] == ch){
            counter++;
        }        
    }    
    return counter;
}

/*
 * Functions counts the number of equal signs in a line
 * 
 * Arguments:
 * equalSign - an unfolded line 
 * 
 * Returned value:
 * the number of equal signs found in the line
 */
static int countEqualSign ( char * equalSign ){
    int length = 0;
    int i = 0;
    int counter = 0;
    char ch = '=';
    
    length = strlen(equalSign);
    
    for(i = 0; i < length; i++){        
        if(equalSign[i] == ch){
            counter++;
        }        
    }    
    return counter;
}

/*
 * Function checks what parameter is being read
 * 
 * Arguments:
 * param - an unfolded line with parameters present
 * 
 * Returned value:
 * status, 1=type, 2=value, 3=encoding/charset, 4=parover error, 5=syntax error
 */
static int checkParam ( char *param ){
    
    if(strcasestr(param, "TYPE")){        
        if(param[4] == '='){
            return 1;
        }
        else if(isalnum(param[4])){
            return 4;
        }
        
        for(int i = 0; i < strlen(param); i++){
            if(param[i] == ' ')
                return 5;
        }
    }    
    else if(strcasestr(param, "VALUE")){        
        if(param[5] == '='){
            return 2;
        }
        else if(isalnum(param[5])){
            return 4;
        }
        
        for(int i = 0; i < strlen(param); i++){
            if(param[i] == ' ')
                return 5;
        }
    }    
    else if(strcasestr(param, "ENCODING")){        
        if(param[8] =='='){
            return 3;
        }
        else if(isalnum(param[8])){
            return 4;
        }
        
        for(int i = 0; i < strlen(param); i++){
            if(param[i] == ' ')
                return 5;
        }
    }    
    else if(strcasestr(param, "CHARSET")){        
        if(param[7] == '='){
            return 3;
        }
        else if(isalnum(param[7])){
            return 4;
        }
        
        for(int i = 0; i < strlen(param); i++){
            if(param[i] == ' ')
                return 5;
        }
    }
    
    if(param[0] == ' ' || param[0] == '='){
        return 5;
    }    
    return 4;    
}

/*
 * Function checks if there is a group present
 * 
 * Arguments:
 * group - an unfolded line
 * 
 * Return value:
 * status, 0=no group, 1=group found
 */
static int checkGroup ( const char * group ){
    int i;
    int length = 0;

    length = strlen(group);
    
    for(i = 0; i < length; i++){        
        if(group[i] == '.'){
            return 1;
        }
        else if(group[i] == ';' || group[i] == ':'){
            break;
        }        
    }    
    return 0;
}

/*
 * Function checks the string length of group
 * 
 * Arguments:
 * lenGroup - unfolded line
 * 
 * Returned value:
 * length of the string
 */
static int lengthOfGroup ( const char * lenGroup ){
    int i = 0;
    int counter = 0;
    char ch = '.';
    
    while(lenGroup[i] != ch){
        counter++;
        i++;
    }    
    return counter;    
}

/*
 * Function checks for unexpected blank space in a line
 * 
 * Arguments:
 * blankSpace - an unfolded line
 * 
 * Returned value:
 * status, 0=no unexpected blank, 1=found unexpected blank
 */
static int unexpectedBlank ( const char * blankSpace ){
    int i;
    int length = 0;
    
    length = strlen(blankSpace);
    
    for(i = 0; i < length; i++){        
        if(blankSpace[i] == ' ' || blankSpace[i] == '\t'){
            return 1;
        }        
    }    
    return 0; 
}

/*
 * Function frees Vcard properties
 * 
 * Arguments:
 * cardp - a Vcard that needs to be freed
 */
void freeVCard( Vcard * cardp ){
    
    for(int i = 0; i < (*cardp).nprops; i++){        
        if((*cardp).prop[i].value != NULL){
            free((*cardp).prop[i].value);
        }        
        if((*cardp).prop[i].partype != NULL){
            free((*cardp).prop[i].partype);
        }        
        if((*cardp).prop[i].parval != NULL){
            free((*cardp).prop[i].parval);
        }        
    }
}

/*
Precondition: vcf has been opened for reading, and is assumed to be positioned at beginning-of-file. filep points to the VcFile structure to be 
filled in (its current contents is ignored).

Postcondition: If status=OK, the file was read to normal EOF and is available in memory for access via the filep pointer. VcStatus line numbers 
give the total lines read from the file. The caller is responsible for eventually freeing the contents of filep with the help of freeVcFile. 
If status is not OK, VcStatus contains both the error code and the line numbers in the file where the error was detected, and the VcFile contents
(*cardp) has already been freed.

Errors returned: any of VcError can be returned.

Return to caller with OK status when readVcard returns OK and NULL, signifying EOF
*/
VcStatus readVcFile( FILE *const vcf, VcFile *const filep ){    
    VcStatus status;       // Status after reading Vcard
    Vcard *newCard;        // Holds new Vcard
    
    assert(vcf);
    assert(filep);
    
    status.code = OK;     
    filep->ncards = 0; 
    filep->cardp = NULL; 
    
    if(vcf == NULL){
        return status;
    }
    
    while(status.code == OK){        
        status = readVcard(vcf,&newCard);

        if(newCard == NULL){
            break;
        }
        
        /*Stores new Vcard when status is OK*/
        if(status.code == OK && newCard->nprops > 0){
            filep->cardp = realloc(filep->cardp, sizeof(Vcard*) * (filep->ncards + 1));
            assert(filep->cardp);
            filep->cardp[filep->ncards] = newCard;
            filep->ncards++;
            newCard = NULL;
        }
        
        if(feof(vcf)){
            break;
        }
    }
    
    if(status.code != OK){        
        if(filep != NULL){
            freeVcFile(filep);
        }     
    }
    
    if(newCard != NULL){
        free(newCard);
    }    
    return status;        
}

/*
VcStatus readVcard( FILE *const vcf, Vcard **const cardp );

Precondition: vcf is open for reading. cardp points to a variable where the address of a newly allocated Vcard will be returned.

Postcondition: If status=OK, and * cardp is non-NULL, the Vcard structure has been filled in. OK status and NULL * cardp means normal EOF, and 
VcStatus line numbers are the total lines read from the file. If error status, * cardp contents are undefined (but no additional storage remains
allocated).

Errors returned: any of VcError, with line number(s) where the error was detected.

This function repeatedly calls getUnfolded to read the next content line, or set of lines from the file, and unfold them into a single buffer
*/
VcStatus readVcard( FILE *const vcf, Vcard **const cardp ){   
    VcStatus status;            // Status after parsing
    VcProp propp;               // Gets the property information from parsing
    char * buff = NULL;         // Holds the unfolded line
    int counter = 0;            // To make sure certain lines are being read from Vcard
    int nameCheck = 0;          // N property check
    int fnCheck = 0;            // FN property check
    int beginFlag = 0;          // Begin Vcard check
    int versionFlag = 0;        // Version flag check
    int endFlag = 0;            // END Vcard check
    
    status.code = OK;
    *cardp = malloc(sizeof(Vcard));
    assert(*cardp);
    (*cardp)->nprops = 0;
    
    /*While status.code is OK store cards properties*/
    while(status.code == OK){        
        status = getUnfolded(vcf,&buff);
        status.code = parseVcProp(buff, &propp);
        
        if(status.code == SYNTAX || status.code == PAROVER){
            freeVCard((*cardp));
        }
        
        if(feof(vcf)){
            if(propp.value == NULL){
                free(*cardp);
                *cardp = NULL;

                if(buff != NULL){
                    free(buff);
                }
                if(propp.value != NULL){
                    free(propp.value);
                }
                break;
            }

            if(strcmp(buff, "") == 0){
                if(buff != NULL){
                    free(buff);
                }
                if(propp.value != NULL){
                    free(propp.value);
                }
                return status;
            }

            if(status.code == SYNTAX || status.code == PAROVER){ // Error occurs at EOF
                if(buff != NULL){
                    free(buff);
                }
                if(propp.value != NULL){
                    free(propp.value);
                }                
                return status;                
            }
            
            if(propp.name != VCP_END){ // END:VCARD was not found at the end of file
                status.code = BEGEND;
                freeVCard((*cardp));

                if(buff != NULL){
                    free(buff);
                }
                if(propp.value != NULL){
                    free(propp.value);
                }
                return status;
            }
            
            if(strcasecmp(propp.value, "VCARD") != 0){
                status.code = BEGEND;
                freeVCard((*cardp));
                
                if(buff != NULL){
                    free(buff);
                }
                if(propp.value != NULL){
                    free(propp.value);
                }                
                return status;
            }

            if(nameCheck != 1  || fnCheck != 1){// N and FN were not found in card                
                status.code = NOPNFN; 
                freeVCard((*cardp));
                
                if(buff != NULL){
                    free(buff);
                }
                if(propp.value != NULL){
                    free(propp.value);
                }                
                return status;
            }
            
            if(buff != NULL){
                free(buff);
            }
            if(propp.value != NULL){
                free(propp.value);
            }            
            break;
        }

        /*Vcard must start with BEGIN:VCARD*/
        if(counter == 0 && propp.name == VCP_BEGIN){
            if(strcasecmp(propp.value, "VCARD") == 0){
                beginFlag = 1;            
            }
            else{
                status.code = BEGEND;
                freeVCard((*cardp));
                
                if(buff != NULL){
                    free(buff);
                }
                if(propp.value != NULL){
                    free(propp.value);
                }                
                return status;
            }
        }
        else if(counter == 0 && propp.name != VCP_BEGIN){
            status.code = BEGEND;
            freeVCard((*cardp));
            
            if(buff != NULL){
                free(buff);
            }
            if(propp.value != NULL){
                free(propp.value);
            }            
            return status;
        }            
        
        /*Version must follow BEGIN:VCARD*/
        if(counter == 1 && beginFlag == 1 && propp.name == VCP_VERSION){            
            if(strcmp(propp.value, VCARD_VER) == 0){
                versionFlag = 1;
            }            
            else if (strcmp(propp.value, VCARD_VER) != 0){
                status.code = BADVER;  
                freeVCard((*cardp));
                
                if(buff != NULL){
                    free(buff);
                }
                if(propp.value != NULL){
                    free(propp.value);
                }                
                return status;
            }   
        }
        else if (counter == 1 && beginFlag == 1 && propp.name != VCP_VERSION){
            status.code = NOPVER;
            freeVCard((*cardp));
            
            if(buff != NULL){
                free(buff);
            }
            if(propp.value != NULL){
                free(propp.value);
            }            
            return status;
        }
        
        if(propp.name == VCP_N){
            nameCheck = 1;
        }        
        if(propp.name == VCP_FN){
            fnCheck = 1;
        }       
        
        /*Vcard must end with END:VCARD*/
        if(propp.name == VCP_END && counter == 2){
            if(strcasecmp(propp.value, "VCARD") == 0){
                counter++;
                endFlag = 1;
            }
            else{
                status.code = BEGEND;
                freeVCard((*cardp));
                
                if(buff != NULL){
                    free(buff);
                }
                if(propp.value != NULL){
                    free(propp.value);
                }                
                return status;
            }
            
            if(nameCheck != 1  || fnCheck != 1){                
                status.code = NOPNFN;
                freeVCard((*cardp));
                
                if(buff != NULL){
                    free(buff);
                }
                if(propp.value != NULL){
                    free(propp.value);
                }                
                return status;
            }
        }
        else if(propp.name == VCP_BEGIN && counter == 2){
            status.code = BEGEND; 
            freeVCard((*cardp));
            
            if(buff != NULL){
                free(buff);
            }
            if(propp.value != NULL){
                free(propp.value);
            }            
            return status;
        }
        
        /*Store Vcard properties*/
        if (counter == 2 && beginFlag == 1 && versionFlag == 1){            
            if(status.code == OK){
                (*cardp) = realloc(*cardp, (sizeof(Vcard)) + (sizeof(VcProp) * ((*cardp)->nprops + 1)));
                assert(*cardp);
                (*cardp)->prop[(*cardp)->nprops] = propp;
                (*cardp)->nprops++;
            }
            else{                
                if(buff != NULL){
                    free(buff);
                }                
                return status;
            }   
        }
        else{            
            if(propp.value != NULL){
                free(propp.value);
            }
        }
        
        /*Finished reading all the properties of a card*/
        if(counter == 3 && endFlag == 1 && beginFlag == 1 && versionFlag == 1){            
            if(buff != NULL){
                free(buff);
            }            
            return status;
        }
        
        if(counter == 2){            
            if(buff != NULL){
                free(buff);
            }
            continue;
        }
        else if (counter < 2)
            counter++;
                
        if(buff != NULL){
            free(buff);
        }
    }
    return status;
}

/*
Special: If vcf is NULL, this is a special call for the function to reset its state in preparation for initiating a new series of reads. 
Reset any static variables and free any allocated storage, such as line counts and read-ahead buffers. Return OK status with linefrom=lineto=0. 
buff is ignored in this case.

Precondition: vcf is open for reading. buff points to a variable where the address of a newly allocated buffer will be returned.

Postcondition: * buff contains the file's next unfolded content line with trailing EOL characters removed, and the caller is responsible to 
eventually free * buff . VcStatus is OK and indicates the line (or lines) that were included in the unfolded buffer. In the case of EOF, * buff 
contains NULL, VcStatus is OK and linefrom=lineto=total number of lines read from the file.

Errors returned: None.

This function has to read lines ahead to check for folding. Multiple folded lines are reassembled into an allocated buffer
*/
VcStatus getUnfolded( FILE *const vcf, char **const buff ){   
    
    VcStatus status;             // Status after unfolding each line
    static char buffer;          // Buffer to keep next character read
    char * tempLine = NULL;      // Holds the unfolded line to pass to buff
    char * whiteSpaces = NULL;   // Holds blank characters
    int wtSpCounter = 0;         // Counts white spaces in a line
    int flag = 0;                // Flag to see how the file starts
    int wtFlag = 0;              // Flag to tell white spaces need to be concatenated
    static int numLinesRead = 1; // Number of lines read from the file
    int counter = 0;             // Counts the number of characters read from the file
    int counter2 = 0;            // Counts white spaces in a line to realloc if needed
    static int currentLine = 1;  // Keeps track of where the current line is being read from file
    static int doneReading = 0;  // Flag that stops reading the file

    assert(buff);
    
    // special case reset everything
    if(vcf == NULL){
        buffer = '\0';
        currentLine = 0;
        numLinesRead = 0;
        doneReading = 0;
        status.code = OK; 
        status.linefrom = status.lineto = 0;
        return status;
    }
    
    if(doneReading == 1 ){
        *buff = NULL;
        status.code = OK;
        return status;
    }

    if(buffer == EOF){
        *buff = NULL;
        status.code = OK;
        return status;
    }
    
    
    if(buffer == '\0'){
        buffer = fgetc(vcf);
        
        if(buffer == '\r'){ // file starts with EOL
            flag = 1;
        }        
        if(buffer == ' '){
            flag = 2;
        }        
    }

    tempLine = calloc(200,sizeof(char));
    assert(tempLine);
    whiteSpaces = calloc(100,sizeof(char));
    assert(whiteSpaces);
    
    /*
     * Unfolding a line from the file
     */
    while(doneReading == 0){        
        if(isgraph(buffer)){            
            if(wtFlag == 1){
                strncat(tempLine, whiteSpaces, wtSpCounter); 
                wtSpCounter = 0;
            }            
            while(buffer != '\r' && buffer != EOF){ // read in line                
                strcat(tempLine, &buffer);
                buffer = fgetc(vcf);
                counter++;

                // realloc memory if the number of characters read is approaching the limit of malloc'd memory
                if(counter >= 199){
                    counter = 0;
                    tempLine = realloc(tempLine, sizeof(char)* (200 + strlen(tempLine))); 
                    assert(tempLine);
                }  
            }
        }
        
        while(buffer == '\r' || buffer == '\n'){ // read past EOL characters
            if(buffer == '\n'){
                numLinesRead++;
            }
            
            buffer = fgetc(vcf);
            
            if(flag == 1){
                if(buffer == ' '){
                    flag = 3;
                }
            }            
            if(buffer == EOF){
                doneReading = 1;
                break;
            }
        }  
        
        if(!isblank(buffer)){ // not a folded line            
            if(flag == 1){
                while(buffer != '\r' && buffer != EOF){ 
                    strcat(tempLine, &buffer);
                    buffer = fgetc(vcf);
                }
                flag = 0;
            }
            else{
                if(flag == 2){
                    flag = 0;
                    continue;
                }
                break;
            }
        }
        
        while(isblank(buffer)){ // check for folding          
            buffer = fgetc(vcf);
            
            if(isblank(buffer)){
                whiteSpaces[wtSpCounter] = buffer;
                wtSpCounter++;
                counter2++;
                
               if(counter2 >= 99){
                   counter2 = 0;
                   whiteSpaces = realloc(whiteSpaces, sizeof(char)* (100 + strlen(whiteSpaces))); 
                   assert(whiteSpaces);
               }
            }
            if(flag == 2 || flag == 3){
                continue;
            } 
            if(isgraph(buffer) && wtSpCounter >= 1){
                wtFlag = 1;
            }              
        }
    }    
    *buff = malloc(sizeof(char)*(strlen(tempLine) + 1));
    assert(*buff);
    strcpy(*buff,tempLine);
    
    if(tempLine != NULL){
        free(tempLine);
    }
    if(whiteSpaces != NULL){
        free(whiteSpaces);
    }    
    status.linefrom = currentLine + 1;
    currentLine = numLinesRead ;
    status.code = OK;
    status.lineto = numLinesRead;    
    return status;
}

/*
Precondition: buff contains the unfolded line to be parsed and propp points to a VcProp structure to be filled in.

Postcondition: If status=OK, *propp structure has been filled in, otherwise its contents are undefined (but no storage remains allocated).

Errors returned: SYNTAX, PAROVER.

Function parses the buffer as a Vcard property
*/
VcError parseVcProp( const char *buff, VcProp *const propp ){
    
    VcError status;             // Status after parsing each line
    VcPname name;               // Property name
    char * tempBuffer = NULL;   // Copy of the buffer to tokenize
    char * cpyTempBuff = NULL;  // Copy of the tempbuffer
    char * leftSide = NULL;     // Leftside of the line after the colon to tokenize
    char * copyLeftSide = NULL; // Copy of leftside
    int numColons = 0;          // Number of colons 
    int numSemicolons = 0;      // Number of semicolons
    int numEqualSign = 0;       // Number of equal signs
    int length = 0;             // Length of a string
    int storeLength = 0;        // Stores length of a string for future use
    int paramCheck = 0;         // Paramater flag check
    int numType = 0;            // Number of parameter types
    int numVal = 0;             // Number of parameter values
    
    assert(buff);
    
    status = OK;
    propp->partype = propp->parval = propp->value = propp->hook = NULL;
    
    /*
     * Check if there is a group and ignore it
     */
    
    if(checkGroup(buff) == 1){
        length = lengthOfGroup(buff);
        tempBuffer = malloc(sizeof(char) * (strlen(buff) - length) + 1);
        assert(tempBuffer);
        strcpy(tempBuffer, &buff[length + 1]);
    }
    else if(checkGroup(buff) == 0){
        tempBuffer = malloc(sizeof(char) * (strlen(buff) + 1));
        assert(tempBuffer);
        strcpy(tempBuffer,buff);
    }

    if(strcmp(tempBuffer, "") == 0){
        if(tempBuffer != NULL){
            free(tempBuffer);
        }
        status = OK;
        return status;
    }
    
    if(tempBuffer != NULL){
        numColons = countColon(tempBuffer);
    }   
    
    /*
     * Check for syntax errors before parsing
     */
    
    if(numColons == 0){
        propp->name = -1;
        
        if(tempBuffer != NULL){
            free(tempBuffer);
        }        
        status = SYNTAX;        
        return status;
    }
    
    if(buff[0] == ';' || buff[0] == ':'){
        propp->name = -1;
        
        if(tempBuffer != NULL){
            free(tempBuffer);
        }        
        status = SYNTAX;        
        return status;
    }
    
    cpyTempBuff = malloc(sizeof(char) * (strlen(tempBuffer) + 1 ));
    assert(cpyTempBuff);
    strcpy(cpyTempBuff, tempBuffer);    
    leftSide = strtok(tempBuffer, ":");
    storeLength = strlen(leftSide);

    if(leftSide != NULL){
        numSemicolons = countSemicolon(leftSide);
        numEqualSign = countEqualSign(leftSide);
    }
      
    if(numSemicolons != numEqualSign){
        propp->name = -1;
        
        if(cpyTempBuff != NULL){
            free(cpyTempBuff);
        }
        if(tempBuffer != NULL){
            free(tempBuffer);
        }        
        status = SYNTAX;        
        return status;
    }
    
    /*
     * Case 1 only property name and value
     */
    
    if(numSemicolons == 0){
        if(unexpectedBlank(leftSide) == 1){
            propp->name = -1;
            
            if(cpyTempBuff != NULL){
                free(cpyTempBuff);
            }
            if(tempBuffer != NULL){
                free(tempBuffer);
            }
            status = SYNTAX;            
            return status;
        }        
        length = strlen(leftSide);        
        name = getVcPname(leftSide);

        if(name == VCP_OTHER){
            propp->name = name;
            propp->value = calloc(strlen(cpyTempBuff) + 5, sizeof(char));
            assert(propp->value);
            strcpy(propp->value, cpyTempBuff);
        }
        else{
            propp->name = name;            
            propp->value = calloc((strlen(&cpyTempBuff[length + 1]) + 500), sizeof(char));
            assert(propp->value);
            strcpy(propp->value, &cpyTempBuff[length + 1]);
        }

        if(cpyTempBuff != NULL){
            free(cpyTempBuff);
        }
        if(tempBuffer != NULL){
            free(tempBuffer);
        }
    }
    
    /*
     * case 2 optional parameters present
     */
    
    if(numSemicolons > 0){        
        copyLeftSide = strtok(leftSide, ";");
        
        if(unexpectedBlank(copyLeftSide) == 1){
            propp->name = -1;
            
            if(cpyTempBuff != NULL){
                free(cpyTempBuff);
            }
            if(tempBuffer != NULL){
                free(tempBuffer);
            }
            status = SYNTAX;            
            return status;
        }

        if(getVcPname(copyLeftSide) == VCP_OTHER){
            propp->name = VCP_OTHER;
            propp->value = calloc(strlen(cpyTempBuff) + 500, sizeof(char));
            assert(propp->value);
            strcpy(propp->value, cpyTempBuff);
            
            if(cpyTempBuff != NULL){
                free(cpyTempBuff);
            }
            if(tempBuffer != NULL){
                free(tempBuffer);
            }            
            status = OK;            
            return status; 
        }
        else{
            name = getVcPname(copyLeftSide);
            propp->name = name;
        }
        
        while(copyLeftSide != NULL){// Parse left side of colon            
            copyLeftSide = strtok(NULL, ";");      

            if(copyLeftSide != NULL){
                paramCheck = checkParam(copyLeftSide);
                length = strlen(copyLeftSide);
            }

            if(paramCheck == 1){// Paramater is TYPE                
                if(numType >= 1){
                    propp->partype = realloc(propp->partype, sizeof(char) 
                      * ((strlen(&copyLeftSide[5]) + 1) * (strlen(&copyLeftSide[5]) + 1)));
                    assert(propp->partype);
                    strcat(propp->partype, ",");
                    strcat(propp->partype, &copyLeftSide[5]);
                }                
                else{
                    propp->partype = calloc(strlen(&copyLeftSide[5]) + 1, sizeof(char));
                    assert(propp->partype);
                    strcpy(propp->partype, &copyLeftSide[5]);
                    numType++;
                }
            }
            
            if(paramCheck == 2){// Paramater is VALUE                
                if(numVal >= 1){
                    propp->parval = realloc(propp->parval, sizeof(char) 
                      * ((strlen(&copyLeftSide[6]) + 1) * (strlen(&copyLeftSide[6]) + 1)));
                    assert(propp->parval);
                    strcat(propp->parval, ",");
                    strcat(propp->parval, &copyLeftSide[6]);
                }                
                else{
                    propp->parval = calloc(strlen(&copyLeftSide[6]) + 1, sizeof(char));
                    assert(propp->parval);
                    strcpy(propp->parval, &copyLeftSide[6]);
                    numVal++;
                }
            }
            
            if(paramCheck == 3){
                continue;
            }
            
            if(paramCheck == 4){ // Paramater not recognized
                propp->name = -1;
                
                if(cpyTempBuff != NULL){
                    free(cpyTempBuff);
                }
                if(tempBuffer != NULL){
                    free(tempBuffer);
                }
                if(propp->value != NULL){
                    free(propp->value);
                }
                if(propp->partype != NULL){
                    free(propp->partype);
                }
                if(propp->parval != NULL){
                    free(propp->parval);
                }                
                status = PAROVER;                
                return status;
            }
            
            if(paramCheck == 5){// Paramater SYNTAX error
                propp->name = -1;
                
                if(cpyTempBuff != NULL){
                    free(cpyTempBuff);
                }
                if(tempBuffer != NULL){
                    free(tempBuffer);
                }
                if(propp->value != NULL){
                    free(propp->value);
                }
                if(propp->partype != NULL){
                    free(propp->partype);
                }
                if(propp->parval != NULL){
                    free(propp->parval);
                }    
                status = SYNTAX;                
                return status;
            }            
            paramCheck = 0;            
        }        
        propp->value = calloc(strlen(&cpyTempBuff[length + 1]) + 500, sizeof(char));
        assert(propp->value);
        strcpy(propp->value, &cpyTempBuff[storeLength + 1]);
        
        if(cpyTempBuff != NULL){
            free(cpyTempBuff);
        }
        if(tempBuffer != NULL){
            free(tempBuffer);
        }
    }    
    return status;
}

/*
Precondition: filep points to a VcFile structure.

Postcondition: All pointers within VcFile have been freed. filep itself is not freed (that is the caller's responsibility if applicable).

Traverse the data structure, freeing all of the pointers, including char* arrays and variable length arrays. 
*/
void freeVcFile( VcFile *const filep ){    
    int i = 0;
    int j = 0;
    
    assert(filep);
    
    for(i = 0; i < filep->ncards; i++){        
        if(filep->cardp[i] != NULL){            
            for(j = 0; j < filep->cardp[i]->nprops; j++){                
                if(filep->cardp[i]->prop[j].value != NULL){ 
                    free(filep->cardp[i]->prop[j].value);
                }                
                if(filep->cardp[i]->prop[j].parval != NULL){
                    free(filep->cardp[i]->prop[j].parval);
                }                
                if(filep->cardp[i]->prop[j].partype != NULL){
                    free(filep->cardp[i]->prop[j].partype);
                }
            }            
            free(filep->cardp[i]);
        }
    }    
    if(filep->cardp != NULL){
        free(filep->cardp);
    }    
    filep->ncards = 0;
}

/*
 * Function returns the Vcard property name in a string
 * 
 * Arguments:
 * VcProp - an integer that represents a VcPname 
 * 
 * Return value:
 * the string corresponding to the VcPname
 */
static char * propertyName( int VcProp ){
    char * name;

    if(VcProp == VCP_VERSION){
        name = "VERSION";
        return name;
    }
    else if(VcProp == VCP_N){
        name = "N";
        return name;
    }
    else if(VcProp == VCP_FN){
        name = "FN";
        return name;
    }
    else if(VcProp == VCP_NICKNAME){
        name = "NICKNAME";
        return name;
    }
    else if(VcProp == VCP_PHOTO){
        name = "PHOTO";
        return name;
    }
    else if(VcProp == VCP_BDAY){
        name = "BDAY";
        return name;
    }
    else if(VcProp == VCP_ADR){
        name = "ADR";
        return name;
    }
    else if(VcProp == VCP_LABEL){
        name = "LABEL";
        return name;
    }
    else if(VcProp == VCP_TEL){
        name = "TEL";
        return name;
    }
    else if(VcProp == VCP_EMAIL){
        name = "EMAIL";
        return name;
    }
    else if(VcProp == VCP_GEO){
        name = "GEO";
        return name;
    }else if(VcProp == VCP_TITLE){
        name = "TITLE";
        return name;
    }
    else if(VcProp == VCP_ORG){
        name = "ORG";
        return name;
    }
    else if(VcProp == VCP_NOTE){
        name = "NOTE";
        return name;
    }
    else if(VcProp == VCP_UID){
        name = "UID";
        return name;
    }
    else if(VcProp == VCP_URL){
        name = "URL";
        return name;
    }
    else{
        name = "";
        return name;
    }
}

/*
Precondition: vcf is already open for writing and is assumed to be positioned at beginning of file. *filep contains the 
contents (at least one card) to be written out on the file in textual form.

Postcondition: The contents have been written on the specified file, status is OK, and the total number of lines output 
is returned in VcStatus.linefrom and lineto (same number). An IOERR status return indicates failure (which could arise 
from disk full, file actually write-protected, or some hardware fault), in which case the file contents is undefined. 
In either case, the file is left open, and any storage allocated by this function has been freed.

Errors returned: IOERR.

Prints out the Vcard to a file
*/
VcStatus writeVcFile( FILE *const vcf, const VcFile *filep ){
    VcStatus status;
    status.code = OK;
    int i,j,k;
    int length = 0;
    int numLines = 1;
    int folded = 0;

    #define foldedLine\
    if(length == FOLD_LEN){\
        if(!fprintf(vcf, "\r\n")){\
            status.code = IOERR;\
            return status;\
        }\
        folded = 1;\
        length = 1;\
        numLines++;\
    }

    #define addSpace\
    if(folded == 1){\
        if(!fprintf(vcf, " ")){\
            status.code = IOERR;\
            return status;\
        }\
        folded = 0;\
    }

    for(i = 0; i < filep->ncards; i++){
        if(filep->cardp[i] != NULL){
            if(!fprintf(vcf, "BEGIN:VCARD\r\n")){
                status.code = IOERR;
                status.lineto = status.linefrom = numLines;
                return status;
            }
            numLines++;
            if(!fprintf(vcf, "VERSION:"VCARD_VER"\r\n")){
                status.code = IOERR;
                status.lineto = status.linefrom = numLines;
                return status;
            }
            numLines++;
            for(j = 0; j < filep->cardp[i]->nprops; j++){
                if(strcmp((propertyName(filep->cardp[i]->prop[j].name)), "") != 0){
                    if(!fprintf(vcf, "%s", (propertyName(filep->cardp[i]->prop[j].name)))){
                        status.code = IOERR;
                        status.lineto = status.linefrom = numLines;
                        return status;
                    }
                }
                length = strlen(propertyName(filep->cardp[i]->prop[j].name));
                if(filep->cardp[i]->prop[j].partype != NULL){
                    if(!fprintf(vcf, ";TYPE=")){
                        status.code = IOERR;
                        status.lineto = status.linefrom = numLines;
                        return status;
                    }
                    length += 6;
                    for(k = 0; k < strlen(filep->cardp[i]->prop[j].partype); k++){
                        addSpace
                        if(!fprintf(vcf, "%c", filep->cardp[i]->prop[j].partype[k])){
                            status.code = IOERR;
                            status.lineto = status.linefrom = numLines;
                            return status;
                        }
                        length++;
                        foldedLine
                    }
                }
                if(filep->cardp[i]->prop[j].parval != NULL){
                    if(!fprintf(vcf, ";VALUE=")){
                        status.code = IOERR;
                        status.lineto = status.linefrom = numLines;
                        return status;
                    }
                    length += 7;
                    for(k = 0; k < strlen(filep->cardp[i]->prop[j].parval); k++){
                        addSpace
                        if(!fprintf(vcf, "%c", filep->cardp[i]->prop[j].parval[k])){
                            status.code = IOERR;
                            status.lineto = status.linefrom = numLines;
                            return status;
                        }
                        length++;
                        foldedLine
                    }                 
                }
                if(filep->cardp[i]->prop[j].value != NULL){
                    if(length != 0){
                        if(!fprintf(vcf, ":")){
                            status.code = IOERR;
                            status.lineto = status.linefrom = numLines;
                            return status;
                        }
                        length += 1;
                    }
                    for(k = 0; k < strlen(filep->cardp[i]->prop[j].value); k++){
                        addSpace
                        if(!fprintf(vcf, "%c", filep->cardp[i]->prop[j].value[k])){
                            status.code = IOERR;
                            status.lineto = status.linefrom = numLines;
                            return status;
                        }
                        length++;
                        foldedLine
                    }             
                }
                if(length > 1){
                    if(!fprintf(vcf, "\r\n")){
                        status.code = IOERR;
                        status.lineto = status.linefrom = numLines;
                        return status;
                    }
                }
                numLines++;
            }
            if(!fprintf(vcf, "END:VCARD\r\n")){
                status.code = IOERR;
                status.lineto = status.linefrom = numLines;
                return status;
            }
            numLines++;
            length = 0;
        }
    }
    #undef foldedLine
    #undef addSpace
    
    status.lineto = status.linefrom = numLines;
    return status;
}