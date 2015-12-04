*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*> 
*> conv.cob: External function used to convert roman numeral to       *>  
*> decimal															  *>
*>    																  *> 																	
*> Created by: Michael Tran (mtran04) 								  *>
*> ID: 0524704 														  *>
*> March 17, 2015 													  *>
*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*>

identification division.
program-id. conversion.

environment division.

data division.
working-storage section.
01 i pic 99.
01 prev pic S9(8).
01 romanVal pic 9(4).

linkage section.
01 counter pic 99.
01 total pic 9(8).
01 err pic 9.
01 romanArray.
	05 romanCh pic x occurs 30 times.

procedure division using romanArray, counter, err, total.
	perform loop.
	goback.

*> subroutine to convert roman numeral to decimal
loop.
	move zero to total.
	move 1001 to prev.
	move 1 to i.

	perform until i is greater than counter 
		evaluate romanCh(i)
			when 'I'
				move 1 to romanVal
			when 'V'
				move 5 to romanVal
			when 'X'
				move 10 to romanVal
			when 'L'
				move 50 to romanVal
			when 'C'
				move 100 to romanVal
			when 'D'
				move 500 to romanVal
			when 'M'
				move 1000 to romanVal
			when other
				display " Cannot convert this roman numeral. Found illegal roman numeral [" romanCh(i) "] in " function trim (romanArray)
				move 1 to err
				exit perform
		end-evaluate

		add romanVal to total

		if romanVal is greater than prev
			compute total = total - 2 * prev
		end-if

		add 1 to i
		move romanVal to prev
	end-perform.


