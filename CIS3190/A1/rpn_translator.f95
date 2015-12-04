!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! rpn_translators.f95: Modernized fortran polish notation converter                    !
! CIS*3190 Assignment 1, W15                                                           !
!                                                                                      !
! Takes an algebraic expression as user input, converts it to reverse polish notation, !
! and outputs the newly converted expression.                                          !
!                                                                                      !
! Created By: Michael Tran (mtran04)                                                   !
! ID: 0524704                                                                          !
! January 23, 2015                                                                     !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


!!!!  Constants used throughout the program  !!!!
module constants
    implicit none
 
    character(1), parameter :: BLANK = ' ', LPAREN = '(', RPAREN = ')', PLUS = '+', MINUS = '-', MULTIPLY = '*', DIVIDE = '/'
    character(1), parameter :: EXP = '^' !!! GOING BEYOND -- IMPLEMENTED EXPONENTIAL OPERATOR !!!

end module constants

!!!!!  Initializing the arrays to zero or blank  !!!!
subroutine InitializeArrays (userInput, inputHierarchy, operatorStack, operatorHierarchy, polishString)
    use constants
    implicit none

    integer(1), dimension(40), intent(inout) :: inputHierarchy, operatorHierarchy
    character(1), dimension(40), intent(inout) :: userInput, operatorStack, polishString
    integer :: i
    
    do i = 1, 40	
		inputHierarchy(i) = 0
		operatorHierarchy(i) = 0
		userInput(i) = BLANK
		operatorStack(i) = BLANK
		polishString(i) = BLANK
    end do

end subroutine InitializeArrays

!!!!  Translate to polish notation  !!!!
subroutine polishTranslation (userInput, inputHierarchy, operatorStack, operatorHierarchy, polishString, counter)
	implicit none

	integer(1), dimension(40), intent(inout) :: inputHierarchy, operatorHierarchy
	character(1), dimension(40), intent(inout) :: userInput, operatorStack, polishString
	integer, intent(in) :: counter
	integer :: i, j, k

	i = 1
	j = 2
	k = 1

	inputHierarchy(counter) = 0
	operatorHierarchy(1) = -1

	do
		!!! MOVE OPERAND TO POLISH STRING !!!
		if(inputHierarchy(i) == 0) then
			polishString(k) = userInput(i)
			i = i + 1
			k = k + 1
			call moveOperator(operatorHierarchy, inputHierarchy, polishString, operatorStack, i, j, k)
		!!! FOUND RIGHT PARENTHESIS -- DELETE CORRESPONDING LEFT PARENTHESIS !!!
		else if (inputHierarchy(i) == 2) then
			i = i + 1
			j = j - 1
			call moveOperator(operatorHierarchy, inputHierarchy, polishString, operatorStack, i, j, k)
		!!! SOME OTHER OPERATOR HERE -- MOVE TO OPERATOR STACK !!!
		else
			operatorStack(j) = userInput(i)
			operatorHierarchy(j) = inputHierarchy(i)
			i = i + 1
			j = j + 1
		end if

		!!! REACHED END OF TRANSLATION PRINT OUT RESULTS !!!
		if(i == counter) then
			write(*, 130) "input: ", userInput, "rpn:   ", polishString
130			format(1H ,A7, 40A1/1H , A7, 40A1)
			write(*,*)
			exit
		end if

	end do
	
end subroutine polishTranslation 

!!!!  Move operator to polish string  !!!!
subroutine moveOperator (operatorHierarchy, inputHierarchy, polishString, operatorStack, i , j, k)
	implicit none

	integer(1), dimension(40), intent(inout) :: inputHierarchy, operatorHierarchy
	character(1), dimension(40), intent(inout) :: operatorStack, polishString
	integer, intent(inout) :: i, j, k

	!!! CHECK HIERARCHY RANKING !!!
	do
		if(operatorHierarchy(j-1) >= inputHierarchy(i)) then 
			polishString(k) = operatorStack(j-1)
			k = k + 1
			j = j - 1
		else
			exit
		end if			
	end do

end subroutine moveOperator

program rpn_main
    use constants
    implicit none

    integer(1), dimension(40) :: inputHierarchy, operatorHierarchy
    character(1), dimension(40) :: userInput, operatorStack, polishString
    integer :: i, flag    

    !!! MAIN LOOP TO RUN THE PROGRAM !!!
    do while (i /= 1)
    	flag = 0

		call InitializeArrays(userInput, inputHierarchy, operatorStack, operatorHierarchy, polishString)
		write(*,*) "Input algebraic expression to convert to RPN : "
		read(*,30) userInput
30  	format(40A)
		
		!!! GO THROUGH USER INPUT AND CHECK FOR ERRORS OTHERWISE ASSIGN INPUT HIERARCHY VALUES ACCORDING TO OPERATOR !!!
		do i = 1, 40
	    	if(userInput(i) == BLANK) then
	    		exit
	    	else if(userInput(i) == LPAREN) then
				inputHierarchy(i) = 1
	    	else if(userInput(i) == RPAREN) then
				inputHierarchy(i) = 2
	    	else if(userInput(i) == PLUS .or. userInput(i) == MINUS) then
				inputHierarchy(i) = 3
	    	else if(userInput(i) == MULTIPLY .or. userInput(i) == DIVIDE) then
				inputHierarchy(i) = 4
			else if(userInput(i) == EXP) then
				inputHierarchy(i) = 5
	    	else if(i == 40 .and. userInput(i) /= BLANK) then !!! 40TH CHARACTER IS NOT BLANK INPUT ERROR !!!
				write(*,50)
50	    		format(1x, 'DATA INPUT IN ERROR - NO BLANKS')
				flag = 1
				exit				
	    	end if
		end do

		!!! USER INPUT IS GOOD -- TRANSLATE INTO RPN !!!
		if(i /= 1 .and. flag /= 1) then
			call polishTranslation(userInput, inputHierarchy, operatorStack, operatorHierarchy, polishString, i)
		end if

    end do

    write(*,*) "GoodBye!"

end program rpn_main