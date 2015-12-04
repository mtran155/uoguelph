/*
* vcftool.c -- A tool for manipulating Vcard Files from the command line
* 
* Author: Michael Tran #0524704
* Date Created: January 28, 2014
* Contact: mtran04@uoguelph.ca 
* Credit/Reference: I used a library that was created by a classmate named Przemyslaw Gawron that was 
*                   posted on moodle and made minor changes.
*/

#define _GNU_SOURCE
#include "vcutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include <ctype.h>
#include <regex.h>

/**********************************************/
/* This library was made by Przemyslaw Gawron */
/**********************************************/
#include "iso3166-2_CountryCodes.h"

#define STRING_SIZE 500

/*
 * Function checks whether the vcf file is sorted or not
 * 
 * Arguments:
 * filep - contains the vcards 
 * 
 * Returned value:
 * status, 0=sorted, 1=not sorted
 */
static int checkSorted (const VcFile * filep){
	int i,j;
	int nameFound = 0;      // flag used to check names of the cards
	char * cardOne = NULL;  // stores the name of the first card found
	char * cardTwo = NULL;  // stores the name of the second card found

	/*Loop through cards and check if they are sorted*/
	for(i = 0; i < filep->ncards; i++){
		if(filep->cardp[i] != NULL){
			for(j = 0; j < filep->cardp[i]->nprops; j++){
				if(filep->cardp[i]->prop[j].name == VCP_N){
					if(nameFound == 0){
						cardOne = calloc(strlen(filep->cardp[i]->prop[j].value) + 1, sizeof(char));
						assert(cardOne);
						strcpy(cardOne, filep->cardp[i]->prop[j].value);
						nameFound++;
						break;
					}
					else if (nameFound == 1){
						cardTwo = calloc(strlen(filep->cardp[i]->prop[j].value) + 1, sizeof(char));
						assert(cardTwo);
						strcpy(cardTwo, filep->cardp[i]->prop[j].value);
						break;
					}
				}
			}
			if(cardOne != NULL && cardTwo != NULL){
				if(strcasecmp(cardOne,cardTwo) > 0){
					if(cardOne != NULL){
						free(cardOne);
					}
					if(cardTwo != NULL){
						free(cardTwo);
					}
					return 1;
				}

				if(cardOne != NULL){
					free(cardOne);
					cardOne = calloc(strlen(cardTwo) + 1, sizeof(char));
					assert(cardOne);
					strcpy(cardOne, cardTwo);
				}
				if(cardTwo != NULL){
					free(cardTwo);
				}
				
			}
		}
	}
	if(cardOne != NULL){
		free(cardOne);
	}
	return 0;
}

/*
 * Function frees Vcard properties
 * 
 * Arguments:
 * card - a Vcard that needs to be freed
 */
static void freeCard( Vcard * card ){
	int i;

	for(i = 0; i < card->nprops; i++){                
	    if(card->prop[i].value != NULL){ 
	        free(card->prop[i].value);
	    }                
	    if(card->prop[i].parval != NULL){
	        free(card->prop[i].parval);
	    }                
	    if(card->prop[i].partype != NULL){
	        free(card->prop[i].partype);
	    }
	}
	free(card);
}

/*
 * Function prints error message to stderr
 * 
 * Arguments:
 * status - status containing the error code
 */
static void errorMsg ( int status ){
	switch(status)
	{
		case IOERR:
			fprintf(stderr, "IOERR found\n");
			break;
		case SYNTAX:
			fprintf(stderr, "SYNTAX ERROR found\n");
			break;
		case PAROVER:
			fprintf(stderr, "PAROVER ERROR found\n");
			break;
		case BEGEND:
			fprintf(stderr, "BEGEND ERROR found\n");
			break;
		case BADVER:
			fprintf(stderr, "BADVER ERROR found\n");
			break;
		case NOPVER: 
			fprintf(stderr, "NOPVER ERROR found\n");
			break;
		case NOPNFN:
			fprintf(stderr, "NOPNFN ERROR found\n");
			break;
	}
}

/*
 * Function determines whether name is in canonical from, if not try to make it canonical
 * 
 * Arguments:
 * value - string containing the name
 *
 * Returned value:
 * status, 1=canonical, 2=succeeded making canonical, 3=could not make canonical
 */
static int makeNCanon ( char * value ){
	regex_t reg;
	int regVal = 0;
	int i, counter = 0;
	char * regexNPattern = "^([A-Z][aA-zZ ']*[;][A-Z][aA-zZ ']*)([;]*?[A-Z]?[aA-zZ ']*$)";
	char * addNoneString = NULL;  // used to insert "(none)" if family name or given name are blank
	char * ptr = NULL;            // used to get the substring of the name value
	int changeMade = 1;           // checks if there was a change made to the name value

	if(regcomp(&reg, regexNPattern, REG_EXTENDED) != 0){
		fprintf(stderr, "Regcomp() failed\n");
		return EXIT_FAILURE;
	}

	regVal = regexec(&reg, value,0,NULL,0);
	if(regVal == 0){ // matches with regex, in canonical form already
		regfree(&reg);
		return 1;
	}
	regfree(&reg);

	for(i = 0; i < strlen(value); i++){
		if(value[i] == ';'){
			counter++;
		}
	}

	if(counter > 4){ // could not put into canonical form because data is not recognized
		return 3;
	}

	addNoneString = calloc(STRING_SIZE, sizeof(char));
	assert(addNoneString);

	/*If value is empty add (none)*/
	if(strlen(value) == 0){
		strcpy(addNoneString, "(none);(none)");
		strcat(value,addNoneString);
		changeMade = 0;
	}

	/*Check if Family name is capitalized or if empty put (none)*/
	if(value[0] == ';'){
		strcpy(addNoneString,"(none)");
		strcat(addNoneString, value);
		strcpy(value, addNoneString);
		changeMade = 0;
	}
	else if(islower(value[0])){
		value[0] = toupper(value[0]);
		changeMade = 0;
	}

	/*Checks if Given name is capitalized or if empty put (none)*/
	ptr = strstr(value, ";");
	if(ptr == NULL){
		strcat(value, ";");
		ptr = strstr(value, ";");
	}
	
	if(ptr[0] == ';'){
		if(islower(ptr[1])){
			ptr[1] = toupper(ptr[1]);
			changeMade = 0;
		}
		if(ptr[1] == ';'){
			strcpy(addNoneString, &ptr[1]);
			strcpy(ptr, ";(none)");
			strcat(ptr, addNoneString);
			changeMade = 0;
		}
		
		if(strlen(ptr) == 1){
			strcat(value, "(none)");
			changeMade = 0;
		}
	}

	if(changeMade != 1){ // put into canonical form succeeded
		free(addNoneString);
		return 2;
	}
	else{
		free(addNoneString);
		return 1;
	}

	return EXIT_SUCCESS;
}

/*
 * Function determines whether address is in canonical from, if not try to make it canonical
 * 
 * Arguments:
 * value - string containing the address
 *
 * Returned value:
 * status, 1=canonical, 2=succeeded making canonical, 3=could not make canonical
 */
static int makeAdrCanon( char * value ){	
	int i = 0, j = 0, k = 0, x = 0;
	regex_t reg;
	int regVal = 0;
	char * regexAdrPattern = "^([;]+)([A-Z 0-9 a-z]*)([;])([A-Z 0-9 a-z]*)([;])([A-Z 0-9 a-z]*)([;][A-Z 0-9 a-z]{2})([;])([A-Z 0-9 a-z -]*)([;][A-Z]{2})";
	char * region = NULL;       // gets the region in the string
	char * country = NULL;      // gets the country in the string
	char * regionCode = NULL;   // puts the reigion into ISO 2 form
	char * countryCode = NULL;  // puts the country into ISO 2 form
	char * midString = NULL;    // gets the string inbetween region and country
	char * finalString = NULL;  // builds the address into canonical form
	int numSemiColon = 0;       // counts the number of semicolons
	int regionFlag = 0;         // checks if region is present
	int province = 0;           // the region is a province
	int state = 0;              // the region is a state
	int noRegCount = 0;         // flag to see if region and country are present
	int changeMade = 1;         // flag to see if a change was made to the address
	int NA_flag = 0;            // flag to see if country is Canada or US

	#define freeStrings\
	free(region);\
	free(country);\
	free(midString);\
	free(finalString);

	region = calloc(STRING_SIZE, sizeof(char));
	assert(region);
	country = calloc(STRING_SIZE, sizeof(char));
	assert(country);
	midString = calloc(STRING_SIZE, sizeof(char));
	assert(midString);
	finalString = calloc((strlen(value) + 500), sizeof(char));
	assert(finalString);

	/*Loop checks for semicolons and copies what is in region and country in the string*/
	for(i = 0; i < strlen(value); i++){
		if(value[i] == ';'){
			numSemiColon++;
		}
		if(value[i] == '\\'){
			if(value[i+1] == ';'){
				numSemiColon--;
				continue;
			}
		}
		if(numSemiColon == 4){
			if(value[i] != ';'){
				region[j] = value[i];
				j++;
			}
		}
		if(numSemiColon == 5){
			midString[x] = value[i];
			x++;
		}
		if(numSemiColon == 6){
			if(value[i] != ';' && value != NULL){
				country[k] = value[i];
				k++;
			}
		}	
	}

	if(numSemiColon != 6){
		freeStrings
		return 3;
	}

	if(regcomp(&reg, regexAdrPattern, REG_EXTENDED) != 0){
		fprintf(stderr, "Regcomp() failed\n");
		return EXIT_FAILURE;
	}

	regVal = regexec(&reg, value,0,NULL,0);
	if(regVal == 0){
		regfree(&reg);
		freeStrings
		return 1;
	}
	regfree(&reg);

	if(strlen(region) == 0){
		noRegCount = 1;
		regionFlag = -1;
	}

	if(noRegCount == 1){
		if(strlen(country) == 0){
			noRegCount = 2;
		}
	}

	/*No region or country was found in value cannot apply heuristics*/
	if(noRegCount == 2){
		freeStrings
		return 3;
	}

	/*Checks if region is either a province or a state*/
	if(regionFlag == 0){
		regionCode = provinceToCode(region);
		if(strlen(regionCode) > 0){
			province = 1;
		}
		else if(strlen(regionCode) == 0){
			regionCode = codeToProvince(region);
			if(strlen(regionCode) > 0){
				strcpy(region, regionCode);
				regionCode = provinceToCode(region);
				if(strlen(regionCode) > 0){
					province = 1;
				}
			}
		}
		
		if (strlen(regionCode) == 0){
			regionCode = stateToCode(region);
			if(strlen(regionCode) > 0){
				state = 1;
			}
			else if(strlen(regionCode) == 0){
				regionCode = codeToState(region);
				if(strlen(regionCode) > 0){
					strcpy(region, regionCode);
					regionCode = stateToCode(region);
					if(strlen(regionCode) > 0){
						state = 1;
					}
				}
			}
		}
	}

	countryCode = countryToCode(country);

	if(strcasecmp(countryCode, "CA") == 0){
		NA_flag = 1;
	}
	if(strcasecmp(countryCode, "US") == 0){
		NA_flag = 2;
	}

	if(province == 0 && NA_flag == 1){
		freeStrings
		return 3;
	}
	else if(state == 0 && NA_flag == 2){
		freeStrings
		return 3;
	}

	numSemiColon = 0;

	/*Builds the final string to make canonical*/
	for(i = 0; i < strlen(value); i++){
		finalString[i] = value[i];
		if(value[i] == ';'){
			numSemiColon++;
		}
		if(numSemiColon == 4){
			if(noRegCount == 0){
				if(strlen(regionCode) == 0){
					if(strlen(region) != 0){
						strcat(finalString, region);
					}
				}
				else{
					strcat(finalString, regionCode);
					strcat(finalString, midString);
					if(province == 1){
						strcat(finalString, ";CA");
						changeMade = 0;
						break;
					}
					else if(state == 1){
						strcat(finalString, ";US");
						changeMade = 0;
						break;
					}				
				}
			}
			strcat(finalString,midString);
			strcat(finalString, ";");
			if(strlen(countryCode) != 0){
				strcat(finalString, countryCode);
				changeMade = 0;
				break;
			}
			else{
				strcat(finalString, country);
				changeMade = 0;
				break;
			}
		}
	}

	if(changeMade != 1){
		strcpy(value,finalString);
		freeStrings
		return 2;
	}
	else{
		freeStrings
		return 3;
	}
	#undef freeStrings
}

/*
 * Function determines whether telephone number is in canonical from, if not try to make it canonical
 * 
 * Arguments:
 * value - string containing the telephone number
 *
 * Returned value:
 * status, 1=canonical, 2=succeeded making canonical, 3=could not make canonical
 */
static int makeTelCanon ( char * value ){
	regex_t reg;
	int regVal = 0;
	char * regexTelPattern = "^([+][0-9][0-9]?[ ][(][0-9]{1,3}[)][ ][0-9]{3}[- ]?[0-9]{3,4})([ -]?[0-9]*?)([\\|]?[0-9]*?$)";
	int i, j; 
	int counter = 0;     
	int counter2 = 0; 
	int changeMade = 1;  // flag to see if a change was made to the phone number value	   
	int alphCounter = 0; // counter for letters found in phone number
	int ext = 0;         // flag to see an extension is present
	int flag = 0;        // flag to check if number starts with a '1'
	char * string;       // is used to build the phone number into canonical form
	char * string2;      // a copy of the phone number
	char * extString;    // contains the extension part of the phone number
	char * ptr = NULL;   // used to get the substring of a phone number

	#define shortNum\
	string[4] = '0';\
	string[5] = '0';\
	string[6] = '0';\
	string[9] = string2[0];\
	string[10] = string2[1];\
	string[11] = string2[2];\
	string[13] = string2[3];\
	string[14] = string2[4];\
	string[15] = string2[5];\
	string[16] = string2[6];

	#define longNum\
	string[4] = string2[0];\
	string[5] = string2[1];\
	string[6] = string2[2];\
	string[9] = string2[3];\
	string[10] = string2[4];\
	string[11] = string2[5];\
	string[13] = string2[6];\
	string[14] = string2[7];\
	string[15] = string2[8];\
	string[16] = string2[9];

	#define longNumWithOne\
	string[1] = string2[0];\
	string[4] = string2[1];\
	string[5] = string2[2];\
	string[6] = string2[3];\
	string[9] = string2[4];\
	string[10] = string2[5];\
	string[11] = string2[6];\
	string[13] = string2[7];\
	string[14] = string2[8];\
	string[15] = string2[9];\
	string[16] = string2[10];

	if(regcomp(&reg, regexTelPattern, REG_EXTENDED) != 0){
		fprintf(stderr, "Regcomp() failed\n");
		return EXIT_FAILURE;
	}

	regVal = regexec(&reg, value,0,NULL,0);
	if(regVal == 0){
		regfree(&reg);
		return 1;
	}
	regfree(&reg);

	string = calloc(STRING_SIZE, sizeof(char));
	assert(string);
	string2 = calloc(STRING_SIZE, sizeof(char));
	assert(string2);
	extString = calloc(STRING_SIZE, sizeof(char));
	assert(extString);

	/*Loop checks if an extension is present or a letter is found inbetween the phone number*/
	for(i = 0; i < strlen(value); i++){
		if(isdigit(value[i])){
			string2[counter] = value[i];
			counter++;
		}
		if(ext == 1 || ext == 2){
			counter--;
		}
		if(value[i] == 'X' || value[i] == 'x'){
			ptr = strcasestr(value, "X");
			for(j = 1; j < strlen(ptr); j++){
				if(!isspace(ptr[j])){
					extString[counter2] = ptr[j];
					counter2++;
				}
			}
			ext = 1;
			break;
		}
		else if((value[i] == 'E' || value[i] == 'e') && (value[i+1] == 'x' || value[i+1] == 'X') 
			&& (value[i+2] == 't' || value[i+2] == 'T') && value[i+3] == '.'){

			ptr = strcasestr(value, "Ext.");
			for(j = 4; j < strlen(ptr); j++){
				if(!isspace(ptr[j])){
					extString[counter2] = ptr[j];
					counter2++;
				}
			}
			ext = 2;
			break;
		}
		if(isalpha(value[i])){
			alphCounter++;
		}
	}

	/*Could not put into canonical form*/
	if(alphCounter > 0){
		free(string);
		free(string2);
		free(extString);
		return 3;
	}
	else if(counter >= 11){
		if(value[0] == '+'){
			if(value[1] != '1'){
				free(string);
				free(string2);
				free(extString);
				return 3;
			}
		}
		else{
			if(value[0] != '1'){
				free(string);
				free(string2);
				free(extString);
				return 3;
			}
		}
	}

	/*Build phone number into canonical form*/
	if(counter > 6){
		if(value[0] != '+'){
			string[0] = '+';
			if(value[0] != '1'){
				flag = 1;
				string[1] = '1';
			}
			string[2] = ' ';
			string[3] = '(';
			string[7] = ')';
			string[8] = ' ';
			string[12] = '-';
			changeMade = 0;
		}
		else{
			if(value[0] != '1' && value[1] != '1'){
				flag = 1;
				string[1] = '1';
			}
			string[0] = '+';
			string[2] = ' ';
			string[3] = '(';
			string[7] = ')';
			string[8] = ' ';
			string[12] = '-';
			changeMade = 0;
		}

		if(counter == 7 && ext == 0){
			shortNum
		}
		else if(counter >= 10 && ext == 0){
			if(flag == 0){
				longNumWithOne
			}	
			else if (flag == 1){
				longNum
			}
		}

		/*Extension present put into canonical form*/
		if(ext == 1){
			if (counter == 7){
				shortNum
				string[17] = '|';
				strcat(string,extString);
			}
			else if(counter >= 10){
				if(flag == 0){
					longNumWithOne
				}	
				else if (flag == 1){
					longNum
				}
				string[17] = '|';
				strcat(string,extString);
			}
		}
		else if(ext == 2){
			if (counter == 7){
				shortNum
				string[17] = '|';
				strcat(string,extString);
			}
			else if(counter >= 10){
				if(flag == 0){
					longNumWithOne
				}	
				else if (flag == 1){
					longNum
				}
				string[17] = '|';
				strcat(string,extString);
			}
		}
	}
	#undef shortNum
	#undef longNum
	#undef longNumWithOne

	if(changeMade != 1){
		strcpy(value,string);
		free(string);
		free(string2);
		free(extString);
		return 2;
	}
	else{
		free(string);
		free(string2);
		free(extString);
		return 3;
	}

	return EXIT_SUCCESS;
}

/*
 * Function determines whether geo is in canonical from, if not try to make it canonical
 * 
 * Arguments:
 * value - string containing the geo
 *
 * Returned value:
 * status, 1=canonical, 2=succeeded making canonical, 3=could not make canonical
 */
static int makeGeoCanon ( char * value ){
	regex_t reg;
	int regVal = 0;	
	char * regexGeoPattern =  "^([-]?)([0-9]?[0-9]?[\\.][0-9]{6})([;])([-]?)([1]?[0-9]?[0-9]?[\\.][0-9]{6})";
	int i;
	int counter = 0;
	int changeMade = 1;         // checks if a change was made to the geo string
	char * latitude = NULL;     // gets the latitude part of the string
	char * longitude = NULL;    // gets the longitude part of the string
	char * finalString = NULL;  // builds the final string into canonical form
	int splitUp = 0;	        // a flag to split up the coordinates
	float latValue = 0;         // used to check if latitude value is in range
	float lonValue = 0;         // used to check if longitude value is in range
	int addZero = 0;            // flag used to add zeros at the end of the coordinate
	char * ptr = NULL;          // used for adding zeros at the end of the coordinate

	latitude = calloc(STRING_SIZE, sizeof(char));
	assert(latitude);
	longitude = calloc(STRING_SIZE, sizeof(char));
	assert(longitude);

	/*Check if coordinates are in range*/
	#define checkRange\
	for(i = 0; i < strlen(value); i++){\
		if(value[i] == ';'){\
			splitUp = 1;\
		}\
		if(splitUp == 0){\
			if(value[i] != ';');{\
				latitude[i] = value[i];\
			}\
		}\
		else if(splitUp == 1){\
			if(value[i] != ';'){\
				longitude[counter] = value[i];\
				counter++;\
			}\
		}\
	}\
	latValue = strtof(latitude, NULL);\
	lonValue = strtof(longitude, NULL);\
	\
	if(latValue > 90 || latValue < -90){\
		free(latitude);\
		free(longitude);\
		return 3;\
	}\
	if(lonValue > 180 || lonValue < -180){\
		free(latitude);\
		free(longitude);\
		return 3;\
	}


	if(regcomp(&reg, regexGeoPattern, REG_EXTENDED) != 0){
		fprintf(stderr, "Regcomp() failed\n");
		return EXIT_FAILURE;
	}
	
	regVal = regexec(&reg, value,0,NULL,0);

	if(regVal == 0){ // matches regex 
		checkRange
		regfree(&reg);
		free(latitude);
		free(longitude);
		return 1;
	}
	regfree(&reg);

	for(i = 0; i < strlen(value); i++){
		if(isalpha(value[i])){
			free(latitude);
			free(longitude);
			return 3;
		}
	}

	/*Check for space or comma delimiters and replace with semicolon*/
	for(i = 0; i < strlen(value); i++){
		if(isspace(value[i])){
			value[i] = ';';
			changeMade = 0;
		}
		else if(value[i] == ','){
			value[i] = ';';
			changeMade = 0;
		}
	}

	checkRange

	/*Adding zeros if needed at the end of the coordinates*/
	if(strlen(latitude) < 10){
		ptr = strstr(latitude, ".");
		if(ptr == NULL){
			free(latitude);
			free(longitude);
			free(finalString);
			return 3;
		}
		addZero = strlen(ptr);
		for(i = 0; i < strlen(ptr); i++){
			if(addZero < 7){
				strcat(latitude, "0");
				addZero++;
			}
		}
		changeMade = 0;
	}

	if(strlen(longitude) < 11){
		ptr = strstr(longitude, ".");
		if(ptr == NULL){
			free(latitude);
			free(longitude);
			free(finalString);
			return 3;
		}
		addZero = strlen(ptr);
		for(i = 0; i < strlen(ptr); i++){
			if(addZero < 7){
				strcat(longitude, "0");
				addZero++;
			}
		}
		changeMade = 0;
	}

	finalString = calloc(STRING_SIZE, sizeof(char));
	assert(finalString);
	strcat(finalString, latitude);
	strcat(finalString, ";");
	strcat(finalString, longitude);
	#undef checkRange

	if(changeMade != 1){
		strcpy(value, finalString);
		free(latitude);
		free(longitude);
		free(finalString);
		return 2;
	}
	else{
		free(latitude);
		free(longitude);
		free(finalString);
		return 3;
	}
	return EXIT_SUCCESS;
}

/*
Precondition: outfile is already open for writing, and *filep was successfully constructed by readVcFile.

Postcondition: Required info has been printed on outfile , or errors have been printed on stderr .

Run through the cards and keep track of whether they are in ascending alphabetical order (case insensitive) by 
family name and given name. Keep count of the cards having PHOTO, URL, and GEO properties, and those having UIDs 
indicating canonical status for the card.
*/
int vcfInfo( FILE *const outfile, const VcFile *filep ){
	int i,j;
	int numPhoto = 0;   // keep track of number of PHOTO properties in vcf file
	int numUrl = 0;     // keep track of number of URL properties in vcf file
	int numGeo = 0;     // keep track of number of GEO properties in vcf file
	int numCanon = 0;   // keep track of number of CANONICAL properties in vcf file
	int photoFound = 0; // flag when photo was found in card
	int urlFound = 0;   // flag when url was found in card
	int geoFound = 0;   // flag when geo was found in card
	int canonFound = 0; // flag when canon was found in card
	int sorted;         // flag to check if vcf file is sorted or not

	/*Loop through cards and add up specific properties*/
	for(i = 0; i < filep->ncards; i++){
		photoFound = 0;
		urlFound = 0;
		geoFound = 0;
		canonFound = 0;

		if(filep->cardp[i] != NULL){
			for(j = 0; j < filep->cardp[i]->nprops; j++){
				if(filep->cardp[i]->prop[j].name == VCP_PHOTO){
					if(photoFound == 0){
						numPhoto++;
						photoFound = 1;
					}					
				}
				else if(filep->cardp[i]->prop[j].name == VCP_URL){
					if(urlFound == 0){
						numUrl++;
						urlFound = 1;
					}					
				}
				else if(filep->cardp[i]->prop[j].name == VCP_GEO){
					if(geoFound == 0){
						numGeo++;
						geoFound = 1;
					}
				}
				else if(filep->cardp[i]->prop[j].name == VCP_UID){
					if(filep->cardp[i]->prop[j].value[0] == '@' && filep->cardp[i]->prop[j].value[5] == '@' 
						&& filep->cardp[i]->prop[j].value[1] != '*' && filep->cardp[i]->prop[j].value[2] != '*' 
						&& filep->cardp[i]->prop[j].value[3] != '*' && filep->cardp[i]->prop[j].value[4] != '*' 
						&& strlen(filep->cardp[i]->prop[j].value) >= 6){
						if(canonFound == 0){
							numCanon++;
							canonFound = 1;
						}						
					}
				}
			}
		}
	}

	sorted = checkSorted(filep);
	fprintf(outfile, "%d cards ", filep->ncards);

	if(sorted == 0){
		fprintf(outfile, "(sorted)\n");
	}
	else if (sorted == 1){
		fprintf(outfile, "(not sorted)\n");
	}

	fprintf(outfile, "%d with photos\n", numPhoto);
	fprintf(outfile, "%d with URLS\n", numUrl);
	fprintf(outfile, "%d with geographic coordinates\n", numGeo);
	fprintf(outfile, "%d in canonical form\n", numCanon);

	return EXIT_SUCCESS;
}

/*
Precondition: *filep was successfully constructed by readVcFile. which is a string that indicates the property(ies) 
to be selected for output.

Postcondition: *filep may have been modified, even having 0 cards, and the storage for any non-selected components 
has been freed.

vcfSelect is responsible for confirming whether selecting *which components would result in zero cards, and printing 
a message on stderr if this is so.
*/
int vcfSelect( VcFile *const filep, const char *which ){
	int i,j,k;
	int photoFlag = 0;  // flag to check if user wants to look for cards with PHOTO
	int urlFlag = 0;    // flag to check if user wants to look for cards with URL
	int geoFlag = 0;    // flag to check if user wants to look for cards with GEO
	int photoFound = 0; // flag set if PHOTO is found in card
	int urlFound = 0;   // flag set if URL is found in card
	int geoFound = 0;   // flag set if GEO is found in card

	/*Free card that do not contain the properties the user is searching for*/
	#define removeCard\
	if(filep->cardp[i] != NULL){\
		freeCard(filep->cardp[i]);\
	}\
	for(k = i; k < filep->ncards - 1; k++){\
		filep->cardp[k] = filep->cardp[k+1];\
	}\
	filep->ncards--;\
	i--;

	/*Check what properties user wants to find*/
	for(i = 0; i < strlen(which); i++){
		if(which[i] == 'p'){
			photoFlag = 1;
		}
		else if(which[i] == 'u'){
			urlFlag = 1;
		}
		else if(which[i] == 'g'){
			geoFlag = 1;
		}
	}

	/*
	Loop through cards looking for the properties and free cards that do not contain the properties the user 
	is looking for
	*/
	for(i = 0; i < filep->ncards; i++){
		photoFound = 0;
		urlFound = 0;
		geoFound = 0;

		if(filep->cardp[i] != NULL){
			for(j = 0; j < filep->cardp[i]->nprops; j++){
				if(filep->cardp[i]->prop[j].name == VCP_PHOTO){
					photoFound = 1;
				}
				else if(filep->cardp[i]->prop[j].name == VCP_URL){
					urlFound = 1;
				}
				else if(filep->cardp[i]->prop[j].name == VCP_GEO){
					geoFound = 1;
				}
			}
			if(photoFlag == 1 && photoFound == 0){
				removeCard
			}
			else if(urlFlag == 1 && urlFound == 0){
				removeCard
			}
			else if(geoFlag == 1 && geoFound == 0){
				removeCard
			}
		}
	}
	#undef removeCard

	if(filep->ncards == 0){
		fprintf(stderr, "No cards selected\n");
	}

	return EXIT_SUCCESS;
}

/*
 * Function called from qsort to compare names of each Vcard and sort them in ascending alphabetical order
 */
int compareFunc ( const void * c1, const void * c2 ){
	int i = 0, j = 0, x = 0;
	int compareVal;       // value from strcasecmp to return
	int numSemiColon = 0; // counts number of semicolons
	char * C1_FirstName;  // first name of card one
	char * C1_LastName;   // last name of card one
	char * C2_FirstName;  // first name of card two
	char * C2_LastName;   // last name of card two

	for(i = 0; i < (*(Vcard * const *)c1)->nprops; i++){
		if((*(Vcard * const *)c1)->prop[i].name == VCP_N){
			C1_FirstName = calloc((strlen((*(Vcard * const *)c1)->prop[i].value) + 1), sizeof(char));
			assert(C1_FirstName);
			C1_LastName = calloc((strlen((*(Vcard * const *)c1)->prop[i].value) + 1), sizeof(char));
			assert(C1_LastName);

			for(j = 0; j < strlen((*(Vcard * const *)c1)->prop[i].value); j++){
				if((*(Vcard * const *)c1)->prop[i].value[j] == ';'){
					numSemiColon++;
				}
				if(numSemiColon == 0){
					C1_LastName[j] = (*(Vcard * const *)c1)->prop[i].value[j];
				}
				else{
					C1_FirstName[x] = (*(Vcard * const *)c1)->prop[i].value[j];
					x++;
				}
			}
			break;
		}
	}

	x = 0;
	numSemiColon = 0;

	for(i = 0; i < (*(Vcard * const *)c2)->nprops; i++){
		if((*(Vcard * const *)c2)->prop[i].name == VCP_N){
			C2_FirstName = calloc((strlen((*(Vcard * const *)c2)->prop[i].value) + 1), sizeof(char));
			assert(C2_FirstName);
			C2_LastName = calloc((strlen((*(Vcard * const *)c2)->prop[i].value) + 1), sizeof(char));
			assert(C2_LastName);

			for(j = 0; j < strlen((*(Vcard * const *)c2)->prop[i].value); j++){
				if((*(Vcard * const *)c2)->prop[i].value[j] == ';'){
					numSemiColon++;
				}
				if(numSemiColon == 0){
					C2_LastName[j] = (*(Vcard * const *)c2)->prop[i].value[j];
				}
				else{
					C2_FirstName[x] = (*(Vcard * const *)c2)->prop[i].value[j];
					x++;
				}
			}
			break;
		}
	}

	/*Checks if any name has (none) and replaces with an empty string*/
	if(strcasecmp(C1_FirstName, "(none)") == 0){
		strcpy(C1_FirstName, "");
	}
	if(strcasecmp(C1_LastName, "(none)") == 0){
		strcpy(C1_LastName, "");
	}
	if(strcasecmp(C2_FirstName, "(none)") == 0){
		strcpy(C2_FirstName, "");
	}
	if(strcasecmp(C2_LastName, "(none)") == 0){
		strcpy(C2_LastName, "");
	}

	/*If last name are the same compare first names*/
	compareVal = strcasecmp(C1_LastName,C2_LastName);
	if(compareVal == 0){
		compareVal = strcasecmp(C1_FirstName,C2_FirstName);
	}

	free(C1_FirstName);
	free(C1_LastName);
	free(C2_FirstName);
	free(C2_LastName);

	return compareVal;
}

/*
Precondition: *filep was successfully constructed by readVcFile.

Postcondition: *filep may have been modified, and its cards are in ascending alphabetical order (case insensitive) by 
family name and given name.

This module is required to use the qsort library function.
*/
int vcfSort( VcFile *const filep ){
	qsort(filep->cardp, filep->ncards, sizeof(Vcard *) ,compareFunc);
	return EXIT_SUCCESS;
}

/*
Precondition: *propp was constructed by parseVcProp.

Postcondition: The return value gives the status of the operation: 0, canonicalization does not apply to this type of 
property; 1, it was already in canonical form; 2, canonicalization succeeded; 3, canonicalization failed because the data 
could not be recognized. *propp has been modified if 2 is returned.

Check the card's properties to see if they can be put into canonical form or try to canonicalize the property
*/
int vcfCanProp( VcProp *const propp ){
	
	int nCanonCheck = 0;   // catches return value from helper function and returns that value to vcfCanon
	int adrCanonCheck = 0; // catches return value from helper function and returns that value to vcfCanon
	int telCanonCheck = 0; // catches return value from helper function and returns that value to vcfCanon
	int geoCanonCheck = 0; // catches return value from helper function and returns that value to vcfCanon

	if(propp->name == VCP_N){
		nCanonCheck = makeNCanon(propp->value);
		return nCanonCheck;
	}
	else if (propp->name == VCP_ADR){
		adrCanonCheck = makeAdrCanon(propp->value);
		return adrCanonCheck;
	}
	else if (propp->name == VCP_TEL){
		telCanonCheck = makeTelCanon(propp->value);
		return telCanonCheck;
	}
	else if (propp->name == VCP_GEO){
		geoCanonCheck = makeGeoCanon(propp->value);
		return geoCanonCheck;
	}
	else{
		return 0;
	}
	return EXIT_SUCCESS;
}

/*
Precondition: *filep was successfully constructed by readVcFile.

Postcondition: *filep may have been modified.

For each card, send every N, ADR, TEL, and GEO property to vcfCanProp. Depending on the results, construct a new UID 
property with the flags set appropriately, and append it to the card's prop array.
*/
int vcfCanon( VcFile *const filep ){
	int i,j;
	int nCanonCheck = 0;   // catches return from vcfcanprop to see if name is canon
	int adrCanonCheck = 0; // catches return from vcfcanprop to see if address is canon
	int telCanonCheck = 0; // catches return from vcfcanprop to see if tel is canon
	int geoCanonCheck = 0; // catches return from vcfcanprop to see if geo is canon
	int uidFlag = 0;       // flag to see if card has a UID property present
	char * uidProp = NULL; // builds the UID string
	VcProp propp; 

	propp.parval = NULL;
	propp.partype = NULL;
	propp.hook = NULL;

	/*
	Loop through cards and check if N, ADR, TEL or GEO are canon form, and construct new UID 
	with appropriate flags
	*/
	for(i = 0; i < filep->ncards; i++){
		uidProp = calloc(STRING_SIZE, sizeof(char));
		assert(uidProp);
		uidProp[0] = uidProp[5] = '@';
		uidProp[1] =  uidProp[2] = uidProp[3] = uidProp[4] = '-';

		nCanonCheck  = 0;
		adrCanonCheck = 0;
		telCanonCheck = 0;
		geoCanonCheck = 0;
		uidFlag = 0;

		if(filep->cardp[i] != NULL){
			for(j = 0; j < filep->cardp[i]->nprops; j++){
				if(filep->cardp[i]->prop[j].name == VCP_N){
					nCanonCheck = vcfCanProp(&filep->cardp[i]->prop[j]);
				}
				else if(filep->cardp[i]->prop[j].name == VCP_ADR){
					adrCanonCheck = vcfCanProp(&filep->cardp[i]->prop[j]);
				}
				else if(filep->cardp[i]->prop[j].name == VCP_TEL){
					telCanonCheck = vcfCanProp(&filep->cardp[i]->prop[j]);
				}
				else if(filep->cardp[i]->prop[j].name == VCP_GEO){
					geoCanonCheck = vcfCanProp(&filep->cardp[i]->prop[j]);
				}
				else if(filep->cardp[i]->prop[j].name == VCP_UID){
					uidFlag = 1;
				}
			}

			if(nCanonCheck == 1 || nCanonCheck == 2){
				uidProp[1] = 'N';
			}
			else if(nCanonCheck == 3){
				uidProp[1] = '*';
			}

			if(adrCanonCheck == 1 || adrCanonCheck == 2){
				uidProp[2] = 'A';
			}
			else if (adrCanonCheck == 3){
				uidProp[2] = '*';
			}

			if(telCanonCheck == 1 || telCanonCheck == 2){
				uidProp[3] = 'T';
			}
			else if(telCanonCheck == 3){
				uidProp[3] = '*';
			}

			if(geoCanonCheck == 1 || geoCanonCheck == 2){
				uidProp[4] = 'G';
			}
			else if (geoCanonCheck == 3){
				uidProp[4] = '*';
			}
		}

		/*Add UID property if not present or concat with updated UID*/
		if(uidFlag == 0){
			propp.name = VCP_UID;
			propp.value = calloc(STRING_SIZE, sizeof(char));
			assert(propp.value);
			strcpy(propp.value, uidProp);

			int position = filep->cardp[i]->nprops;
			filep->cardp[i] = realloc(filep->cardp[i], (sizeof(Vcard)) + (sizeof(VcProp) * (position + 1)));
			assert(filep->cardp[i]);	

			filep->cardp[i]->prop[position] = propp;
			filep->cardp[i]->nprops++;

			if(uidProp != NULL){
				free(uidProp);
			}
		}
		else if(uidFlag == 1){
			strcat(uidProp, ";");
			int position = filep->cardp[i]->nprops;
			strcat(uidProp,filep->cardp[i]->prop[position-1].value);
			strcpy(filep->cardp[i]->prop[position-1].value, uidProp);

			if(uidProp != NULL){
				free(uidProp);
			}
		}
	}
	return EXIT_SUCCESS;
}

int main(int argc, char *argv[]){
	VcFile filep;
	VcStatus status;
	VcStatus writeStatus;
	int i;
	int photoFlag = 0;       // flag to check if user selected pictures multiple times to search for
	int urlFlag = 0;         // flag to check if user selected url multiple times to search for
	int geoFlag = 0;         // flag to check if user selected geo multiple times to search for
	char * argCheck = NULL;  // used to check what type of options user selected for vcfselect

	writeStatus.code = OK;

	if(argc < 2 || argc > 3){
		fprintf(stderr, "Syntax Error\n");
		fprintf(stderr, "An Expected Syntax:  ./vcftool -info < samples-10.vcf\n");
		fprintf(stderr, "Other commands available: -sort -select -canon\n");
		return EXIT_FAILURE;
	}

	status = readVcFile(stdin, &filep);

	if(status.code != OK){
		errorMsg(status.code);
		fprintf(stderr, "Line from = %d  Line to = %d\n", status.linefrom, status.lineto);
		return EXIT_FAILURE;
	}

	if(strcmp(argv[1], "-info") == 0){
		if(argc == 3){
			fprintf(stderr, "Cannot combine commands with -info\n");
			fprintf(stderr, "Expecting ./vcftool -info \"Vcard textfile\"\n");
			return EXIT_FAILURE;
		}
		vcfInfo(stdout, &filep);
	}
	else if(strcmp(argv[1], "-sort") == 0){
		if(argc == 3){
			fprintf(stderr, "Cannot combine commands with -sort\n");
			fprintf(stderr, "Expecting ./vcftool -sort \"Vcard textfile\"\n");
			return EXIT_FAILURE;
		}
		vcfSort(&filep);
		writeStatus = writeVcFile(stdout, &filep);
	}
	else if(strcmp(argv[1], "-select") == 0){
		if(argv[2] == NULL){
			fprintf(stderr, "No options selected. Expected a combination of p, u or g.\n");
			return EXIT_FAILURE;
		}

		/*Checking if user inputs duplicate option or an option that is not offered*/
		argCheck = calloc((strlen(argv[2]) + 1), sizeof(char));
		assert(argCheck);
		strcpy(argCheck,argv[2]);

		for(i = 0; i < strlen(argCheck); i++){
			if(argCheck[i] == 'p'){
				photoFlag++;
				if(photoFlag == 2){
					fprintf(stderr, "Cannot have same option twice\n");
					return EXIT_FAILURE;
				}
			}
			if(argCheck[i] == 'u'){
				urlFlag++;
				if(urlFlag == 2){
					fprintf(stderr, "Cannot have same option twice\n");
					return EXIT_FAILURE;
				}
			}
			if(argCheck[i] == 'g'){
				geoFlag++;
				if(geoFlag == 2){
					fprintf(stderr, "Cannot have same option twice\n");
					return EXIT_FAILURE;
				}
			}
			if(argCheck[i] != 'p' && argCheck[i] != 'u' && argCheck[i] != 'g'){
				fprintf(stderr, "Not an option. Expected a combination of p, u or g.\n");
				return EXIT_FAILURE;
			}
		}
		free(argCheck);
		vcfSelect(&filep, argv[2]);
		writeStatus = writeVcFile(stdout, &filep);
	}
	else if(strcmp(argv[1], "-canon") == 0){
		if(argc == 3){
			fprintf(stderr, "Cannot combine commands with -canon\n");
			fprintf(stderr, "Expecting ./vcftool -canon \"Vcard textfile\"\n");
			return EXIT_FAILURE;
		}
		vcfCanon(&filep);
		writeStatus = writeVcFile(stdout, &filep);
	}
	else{
		fprintf(stderr, "Syntax Error\n");
		fprintf(stderr, "An Expected Syntax:  ./vcftool -info < samples-10.vcf\n");
		fprintf(stderr, "Other commands available: -sort -select -canon\n");
		return EXIT_FAILURE;
	}

	if(writeStatus.code != OK){
		errorMsg(writeStatus.code);
		fprintf(stderr, "Line from = %d  Line to = %d\n", writeStatus.linefrom, writeStatus.lineto);
		return EXIT_FAILURE;
	}

	if(status.code == OK){
		freeVcFile(&filep);
	}
	return EXIT_SUCCESS;
}
