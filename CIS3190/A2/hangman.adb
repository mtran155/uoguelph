-----------------------------------------------------------------------
-- hangman.adb: A Hangman game written in ADA                        --
--                                                                   --
-- Allows the user to play Hangman using a command line interface    --
--                                                                   --
-- This program can be compiled by typing: gnatmake hangmand.adb     --
-- This program can be executed by typing: ./hangman                 --
--                                                                   --
-- Created by: Michael Tran (mtran04)                                --
-- ID: 0524704                                                       --
-- February 26, 2015                                                 --
-----------------------------------------------------------------------

with Ada.Text_IO, Ada.Integer_Text_IO, Ada.Characters.Handling; 
use Ada.Text_IO, Ada.Integer_Text_IO, Ada.Characters.Handling;
with ada.strings.unbounded; use ada.strings.unbounded;
with ada.strings.unbounded.Text_IO; use ada.strings.unbounded.Text_IO;
with ada.numerics; use ada.numerics;
with ada.numerics.Discrete_Random;

procedure Hangman is

	continueGame : boolean := true;
	numWrongGuess, numGuesses, maxWords, counter, numWords : integer;	 

	type vector is array (integer range <>, integer range <>) of character;
	hangmanPicture : vector(1..14,1..12);

	type wordList is array(1..200) of unbounded_string;
	wordBank : wordList;

	type vector2 is array(integer range <>) of character;
	storeUserGuess : vector2 (1..26);

	dashedWord : String(1..26);
	wordToGuess: unbounded_string;
	wordUsed : array (1..200) of boolean := (others => false);	

	--- Read in a file to fill up word bank to play game ---
	procedure readFile (maxWords : out integer; choice : in character) is
		infile : file_type;
		fileName: string(1..26);	
		unboundString : unbounded_string;
		letter : vector2(1..26) := (others => ' ');
		counter, index : integer := 1;
		Last, maxWordLength : integer;
	begin
		--- Player has decided to use their own text file ---	
		if choice = 'Y' then
			put_line("Please input the name of the file:");
			get_line(fileName,Last);
			put_line("Maximum word length? ");
			get(maxWordLength);
			open(infile,in_file,fileName(1..Last));

		--- Use default text for word bank ---
		elsif choice = 'N' then
			put_line("Using default dictionary");
			put_line("Maximum word length? ");
			get(maxWordLength);
			open(infile,in_file,"default_dictionary.txt");
		end if;

		put_line("Dictionary is being built....");

		loop
			exit when end_of_file(infile);
			get_line(infile, unboundString);
			unboundString := trim(unboundString,Ada.Strings.Both);

			--- Check if the word read from the file is less than or equal to the max word length ---
			if length(unboundString) <= maxWordLength then

			    for i in 1..length(unboundString) loop
					if is_upper(element(unboundString, i)) then
				   		replace_element(unboundString, i, to_lower(element(unboundString, i)));
					end if;
			    end loop;

			    wordBank(index) := unboundString;
			    index := index + 1;

			end if;
		end loop;

		close(infile);
		numWords := index - 1;
		new_line;
		put("There are ");
		put(numWords,1);
		put(" words less than ");
		put(maxWordLength,1);
		put_line(" characters in length.");
		put_line("How many words to randomly select?");
		get(maxWords);
		
		--- Checks if player input is within the range of how many words they can play ---
		if maxWords > numWords then
		    maxWords := numWords;
		elsif maxWords = 0 then
			while maxWords = 0 loop
				put("Can't play with zero words. Must choose between 1 - " );
				put(numWords,1);
				new_line;
				get(maxWords);
			end loop;
		end if;

		new_line;
		put_line("Let's begin!");
		new_line;

		--- User inputs bad file name defaults to default dictionary ---
		exception
			when name_error =>
				new_line;
				put_line("Error, [" & fileName(1..Last) & "] file does not exist. Will use default dictionary.");
				readFile(maxWords,'N');

	end readFile;

	--- Taken from http://code.wikia.com/wiki/Random_number ---
	--- Get random number from 1-50 ---
	function randomNumber return integer is
		r : integer;
	begin
		declare
			type Rand_Range is range 1..200;
			package Rand_Int is new Ada.Numerics.Discrete_Random(Rand_Range);
			seed : Rand_Int.Generator;
			Num : Rand_Range;
		begin
			Rand_Int.Reset(seed);
			Num := Rand_Int.Random(seed);
			r := integer(Num);
		end;
		return r;
	end randomNumber;

	--- Initialize arrays to start the game --
	procedure InitializeArrays is	
	begin
		hangmanPicture := (others => (others => ' '));

		for i in 1..14 loop
			hangmanPicture(i,1) := 'X';
		end loop;

		for i in 1..7 loop
			hangmanPicture(1,i) := 'X';
		end loop;

		for i in 1..12 loop
			hangmanPicture(14,i) := 'X';
		end loop;

		hangmanPicture(2,7) := 'X';
		storeUserGuess := (others => ' ');
		dashedWord := (others => '-'); 
	end InitializeArrays;

	--- Initialize values to start the game ---
	procedure InitializeGame is
		number : integer;
	begin
		InitializeArrays;
		numGuesses := 0;
		numWrongGuess := 0;
		--- Randomly choose a word from word bank that has not been used ---
		loop
			number := (randomNumber mod numWords) + 1;

			if wordUsed(number) = true then
				number := (randomNumber mod numWords) + 1;
			elsif length(wordBank(number)) = 0 then
				number := (randomNumber mod numWords) + 1;
				wordUsed(number) := true;
			else
				wordUsed(number) := true;
				exit;
			end if;
		end loop;

		wordToGuess := wordBank(number);
		put("      ");
		put_line(dashedWord(1..length(wordToGuess)));
		new_line;
	end InitializeGame;

	--- Draw the picture of the man being hung according to number of wrong guesses ---
	procedure drawHangman(man: in out vector; counter: in integer) is
		index : integer := 11;
	begin
		if counter = 1 then
			put_line("First we draw a head.");
			man(3,6) := '-'; 
			man(3,7) := '-'; 
			man(3,8) := '-'; 
			man(4,5) := '('; 
			man(4,6) := '.';
			man(4,8) := '.'; 
			man(4,9) := ')'; 
			man(5,6) := '-'; 
			man(5,7) := '-'; 
			man(5,8) := '-';

		elsif counter = 2 then
			put_line("Now we draw a body.");
			for i in 6..9 loop
				man(i,7) := 'X';
			end loop;

		elsif counter = 3 then
			put_line("Next we draw an arm.");
			for i in 4..7 loop
				man(i,i-1) := '\';
			end loop;

		elsif counter = 4 then
			put_line("This time it's the other arm.");
			for i in 4..7 loop
				man(i, index) := '/';
				index := index - 1;
			end loop;

		elsif counter = 5 then
			put_line("Now, let's draw the right leg.");
			man(10,6) := '/'; 
			man(11,5) := '/';

		elsif counter = 6 then
			put_line("This time we draw the left leg.");
			man(10,8) := '\'; 
			man(11,9) := '\';

		elsif counter = 7 then
			put_line("Now we put up a hand.");
			man(3,11) := '\';

		elsif counter = 8 then
			put_line("Next the other hand.");
			man(3,3) := '/';

		elsif counter = 9 then
			put_line("Now we draw one foot.");
			man(12,10) := '\'; 
			man(12,11) := '-';

		elsif counter = 10 then	
			put_line("Here's the other foot -- You're hung!!." );
			man(12,3) := '-'; 
			man(12,4) := '/';
			man(4,6) := 'x';
			man(4,8) := 'x'; 
		end if;				
		
		for i in 1..14 loop
			for j in 1..12 loop
				put(man(i,j));
			end loop;
			new_line;
		end loop;

		new_line;
		put("      ");
		put_line(dashedWord(1..length(wordToGuess)));
		new_line;
	end drawHangman;

	--- Print out letters the player have used ---
	procedure printLettersUsed (storedGuesses : in vector2) is		
	begin
		put_line("Here are the letters you used:");
		for i in storedGuesses'range loop
			if storedGuesses(i) = ' ' then
				exit;
			end if;
			put(storedGuesses(i));
			put(",");
		end loop;
		new_line;
	end printLettersUsed;

	--- Gives player a chance to guess the word --
	procedure checkUserAnswer (correctGuess : out boolean) is
		userAnswer : unbounded_string;
	begin
		put_line("What is your guess for the word?");
		get_line(userAnswer);
		--- Checks if player has guessed the correct word ---
		if userAnswer  = wordToGuess then
			new_line;
			put("Right! It took you ");
			put(numGuesses,1);
			if numGuesses > 1 then
				put(" guesses");
			else
				put(" guess");
			end if;
			new_line;
			correctGuess := true;
		else
			put_line("Wrong. Try another letter.");
			new_line;
		end if;
	end checkUserAnswer;

	--- Check if player guessed a letter in the word ---
	procedure checkGuess(word : in unbounded_string; correctGuess : out boolean) is
		flag : boolean := false;
		rightGuess, counter : integer;
		userGuess : character;
	begin
		put_line("What is your guess? ");
		get(userGuess);
		userGuess := to_lower(userGuess);
		skip_line;
		rightGuess := 0;

		--- Checks if player has already used that letter before ---
		for i in storeUserGuess'range loop
			if storeUserGuess(i) = ' ' then
				counter := i;
				exit;
			elsif storeUserGuess(i) = userGuess then
				put_line("You guessed that letter before");
				new_line;
				flag := true;
				exit;
			end if;
		end loop;

		--- Player has not used that letter yet check if it's in the word ---
		if flag = false then
			storeUserGuess(counter) := userGuess;
			numGuesses := numGuesses + 1;

			--- Check if letter is in the word, if so replace dash with the letter ---
			for i in 1..length(wordToGuess) loop
				if Element(wordToGuess, i) = userGuess then
					dashedWord(i) := userGuess;
					rightGuess := rightGuess + 1;
				end if;
			end loop;

			--- The letter was not in the word ---
			if rightGuess = 0 then
				numWrongGuess := numWrongGuess + 1;
				put_line("Sorry, that letter isn't in the word.");
				drawHangman(hangmanPicture, numWrongGuess);
			else
				--- Was the last letter in the word that was hidden ---
				if dashedWord(1..length(wordToGuess)) = word then
					new_line;
					put("Congratulations! You found the word! It was [" & word &"] It took you ");
					put(numGuesses, 1);
					put_line(" guesses.");
					correctGuess := true;
				--- Show player where the correct guessed letter is in the word ---
				else
					new_line;
					put("      ");
					put_line(dashedWord(1..length(wordToGuess)));
					new_line;
					checkUserAnswer(correctGuess);
				end if;
			end if;
		end if;
	end checkGuess;

	--- Carries out all the functions to play game ---
	procedure playGame is
		correctGuess : boolean := false;
	begin
		while correctGuess = false loop
			printLettersUsed(storeUserGuess);
			checkGuess(wordToGuess,correctGuess);
			if numWrongGuess = 10 then
				put("Sorry you lose. The word was ");
				put(wordToGuess & ".");
				new_line;
				put_line("You missed that one.");
				correctGuess := true;
			end if;
		end loop;
	end playGame;

	--- Check whether the player wants to play the game again ---
	procedure restartGame is
		flag : boolean := true;
		userAnswer : character;
	begin
		put_line("Would you like to play again with a new word? (Y/N)");
		while flag = true loop
			get(userAnswer);
			skip_line;
			userAnswer := To_Upper(userAnswer);

			if userAnswer = 'N' then
				put_line("Thank you for playing!");
				put_line("It's been fun! Bye for now.");
				new_line;
				flag := false;
				continueGame := false;
			elsif userAnswer = 'Y' then
				put_line("Generating new word....");
				new_line;
				InitializeGame;
				flag := false;
			else
				put_line("That is not an option. Choose (Y/N) to play again.");
			end if;
		end loop;
	end restartGame;

	--- Checks whether the player wants to use their own dictionary for words ---
	procedure useOwnDictionary is
		flag : boolean := true;
		userAnswer : character;
	begin
		put_line("Would you like to load your own dictionary? (Y/N)");
		while flag = true loop
			get(userAnswer);
			skip_line;
			userAnswer := To_Upper(userAnswer);

			if userAnswer = 'Y' then
				readFile(maxWords,userAnswer);
				flag := false;
			elsif userAnswer = 'N' then
				readFile(maxWords, userAnswer);
				flag := false;
			else
				put_line("That is not an option. Choose (Y/N) to load your own dictionary.");
			end if;

		end loop;		
	end useOwnDictionary;

--- Main program ---
begin
	put_line("Welcome to the Game of Hangman");
	new_line;
	useOwnDictionary;
	InitializeGame;
	counter := 0;

	--- Checks if player wants to continue playing ---
	while continueGame = true loop
		if counter = maxWords then
			continueGame := false;
			new_line;
			put_line("You did all the words");
			put_line("Thank you for playing!");
			put_line("It's been fun! Bye for now.");
			new_line;
		else
			playGame;
			counter := counter + 1;
			if counter < maxWords then
				restartGame;
			end if;
		end if;		
	end loop;
end Hangman;