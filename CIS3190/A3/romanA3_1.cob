*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*> 
*> romanA3_1.cob: A roman numeral-decimal converter written in cobol. *>  
*> 																	  *>
*> Allows the user to input a roman-numeral string to be converted 	  *>
*> into a decimal. 													  *>
*> 																	  *>
*> Calls an external function from conv.cob   						  *>
*> 																	  *>
*> This program can be compiled by typing: 	         				  *>
*> 			cobc -x -free -Wall romanA3_1.cob conv.cob				  *>
*> This program can be executed by typing: 							  *>
*> 			./romanA3_1												  *> 
*>    																  *> 																	
*> Created by: Michael Tran (mtran04) 								  *>
*> ID: 0524704 														  *>
*> March 17, 2015 													  *>
*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*>

identification division.
program-id. romanNumerals.

environment division.
input-output section.
file-control.
select ifile assign to fileName organization is line sequential.

data division.
file section.
fd ifile.
01 file-data.
	05 roman-string pic x(30).

working-storage section.
01 eof-switch pic 9 value 1.
01 fileName pic x(30).
01 userInput pic x(30).
01 readFile pic x.

*> array that holds user input to convert roman numeral
01 romanNumeral.
    05 roman pic x occurs 30 times.

01 i pic 99.
01 inputLen pic 99 value zero.
01 numWhiteSpace pic 99 value zero.
01 romanValue pic 9(8).
01 err pic 9.

*> formatted header for table
01 title-line.
	05 filler pic x(11) value spaces.
    05 filler pic x(24) value 'ROMAN NUMBER EQUIVALENTS'.

01 underline-1.
    05 filler pic x(45) value ' --------------------------------------------'.

01 col-heads.
    05 filler pic x(9) value spaces.
    05 filler pic x(12) value 'ROMAN NUMBER'.
    05 filler pic x(13) value spaces.
    05 filler pic x(11) value 'DEC. EQUIV.'.

01 underline-2.
    05 filler pic x(45) value ' ------------------------------   -----------'.	

*> formatted print statement to show converted roman numeral
01 print-roman.
	05 filler pic x value space.
	05 romanString pic x(30).
	05 filler pic x(3) value spaces.
	05 convertedRoman pic z(9).

procedure division.
	perform mainProgram.
stop run.

*> prints formatted table header
printHeader.
	display title-line.
	display underline-1.
	display col-heads.
	display underline-2.

*> reads in a file and converts all the roman numerals to decimal
convertFile.
	read ifile into file-data at end move zero to eof-switch end-read.
	if eof-switch is not equal to zero
		initialize inputlen
		initialize numWhiteSpace
		initialize err
		
		inspect roman-string converting 'abcdefghijklmnopqrstuvwxyz' to 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
		move roman-string to romanNumeral

		inspect romanNumeral tallying inputLen for all characters before initial '\0'
		inspect romanNumeral tallying numWhiteSpace for trailing spaces

		compute inputLen = inputLen - numWhiteSpace

		call "conversion" using romanNumeral, inputLen, err, romanValue

		if err is not equal to 1
			move romanValue to convertedRoman
			move romanNumeral to romanString
			display print-roman
		end-if
	end-if.

*> convertes user input roman numeral to decimal
convertUserInput.
	display "Enter a roman numeral or press q to exit: "
	display " "
	perform printHeader.
	perform until userInput is equal to 'Q'

    	accept userInput
    	inspect userInput converting 'abcdefghijklmnopqrstuvwxyz' to 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

    	initialize inputlen
    	initialize numWhiteSpace
    	initialize err

    	if userInput is not equal to 'Q'
    		move userInput to romanNumeral
    		inspect romanNumeral tallying inputLen for all characters before initial '\0'
    		inspect romanNumeral tallying numWhiteSpace for trailing spaces
    		compute inputLen = inputLen - numWhiteSpace

    		call "conversion" using romanNumeral, inputLen, err, romanValue
    		
			*> if no illegal character found in roman numeral print out value 
    		if err is not equal to 1
    			move romanValue to convertedRoman
    			move romanNumeral to romanString
    			display print-roman
    		end-if
    	end-if
	end-perform.

*> runs the program
mainProgram.
	display "Welcome to the Roman Numeral Converter!!".
	display "Would you like to read in a file? (Y/N) ".
	perform until userInput is equal to 'Q'
		accept readFile
		inspect readFile converting 'abcdefghijklmnopqrstuvwxyz' to 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

		if readFile is equal to 'Y'
			display "Please enter the file name: "
			accept fileName
			open input ifile
			perform printHeader
			perform convertFile until eof-switch = 0
			close ifile
			move 1 to eof-switch
			display "Would you like to read in another file? (Y/N) "
		else
			perform convertUserInput
		end-if
	end-perform.
