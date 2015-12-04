-----------------------------------------------------------------------
-- fleschindex.adb: Flesch index program written in ADA              --
--                                                                   --
-- Allows the user to calculate the Flesch index as well as the      --
-- Flesch-Kincaid grade level of written text                        --
--                                                                   --
-- This program can be compiled by typing: gnatmake fleschindex.adb  --
-- This program can be executed by typing: ./fleschindex             --
--                                                                   --
-- Created by: Michael Tran (mtran04)                                --
-- ID: 0524704                                                       --
-- April 11, 2015                                                    --
-----------------------------------------------------------------------

with Ada.Text_IO, Ada.Integer_Text_IO, Ada.Characters.Handling; 
use Ada.Text_IO, Ada.Integer_Text_IO, Ada.Characters.Handling;
with ada.float_text_io; use ada.float_text_io;
with ada.strings.unbounded; use ada.strings.unbounded;
with ada.strings.unbounded.Text_IO; use ada.strings.unbounded.Text_IO;

procedure fleschIndex is
	userAnswer : character := 'Y';
	punctuationFlag : boolean := false;

	--- Prints the summary of the text file that was read ---
	procedure printSummary(numWords, numSentences, numSyllable: in integer) is
		fleschScore, fleschKincaid : float;
		tempWords, tempSentences, tempSyllable : float;
	begin
		new_line;
		put_line("Number of Words:" & integer'image(numWords));
		put_line("Number of Syllables:" & integer'image(numSyllable));
		put_line("Number of Sentences:" & integer'image(numSentences));

		tempWords := float(numWords);
		tempSentences := float(numSentences);
		tempSyllable := float(numSyllable);

		fleschScore := 206.835 - (1.015 * tempWords/tempSentences + 84.6 * tempSyllable/tempWords);

		put("Flesch readability index = ");
		put(fleschScore, aft=>2, exp=>0);
		new_line;

		fleschKincaid := 0.39 * (tempWords/tempSentences) + 11.8 * (tempSyllable/tempWords) - 15.59;

		put("Flesch-Kincaid grade level = ");
		put(fleschKincaid, aft=>2, exp=>0);
		new_line;
		new_line;
	end printSummary;

	--- Counts the number of words that have the terminators ". ? ! ; :" at the end to count sentences ---
	procedure sentenceCounter (word: in unbounded_string; counter: in out integer; flag: in out boolean) is
	begin
		if Element(word,length(word)) = '.' or Element(word,length(word)) = '?' or Element(word,length(word)) = '!' 
			or Element(word,length(word)) = ';' or Element(word,length(word)) = ':' then
			counter := counter + 1;
			flag := true;
		elsif Element(word,length(word)) = ',' then
			flag := true;
		end if;	
	end sentenceCounter;

	--- Counts the number of syllables found in the word ---
	procedure syllableCounter (word: in unbounded_string; vowelCount: in out integer) is
		flag : boolean := false;
	begin
		if length(word) <= 3 then
			vowelCount := vowelCount + 1;
		else
			for i in 1..length(word) loop

				if to_upper(Element(word, i)) = 'A' then
					if flag = false then
						vowelCount := vowelCount + 1;
						flag := true;
					end if;
				elsif to_upper(Element(word, i)) = 'E' then
					if flag = false then
						vowelCount := vowelCount + 1;
						flag := true;
					end if;
				elsif to_upper(Element(word, i)) = 'I' then
					if flag = false then
						vowelCount := vowelCount + 1;
						flag := true;
					end if;
				elsif to_upper(Element(word, i)) = 'O' then
					if flag = false then
						vowelCount := vowelCount + 1;
						flag := true;
					end if;
				elsif to_upper(Element(word, i)) = 'U' then
					if flag = false then
						vowelCount := vowelCount + 1;
						flag := true;
					end if;
				elsif to_upper(Element(word, i)) = 'Y' then
					if flag = false then
						vowelCount := vowelCount + 1;
						flag := true;
					end if;
				else
					flag := false;
				end if;
			end loop;
		end if;
	end syllableCounter;

	--- Counts the number of words that end in -ES, -ED, -E (except for -LE) ---
	procedure suffixCounter (word: in unbounded_string; suffixCount: in out integer) is
		strLen : integer;
	begin
		strLen := length(word);
		if length(word) > 3 then
			--- if the word ends with 'E' check if the second last letter is not equal to 'L' ---
			if to_upper(Element(word, strLen)) = 'E' then
				if to_upper(Element(word, strLen - 1)) /= 'L' then
					suffixCount := suffixCount + 1;
				end if;
			--- check if second last letter of the word is 'E' then check if it the last letter is 'S' or 'D' ---
			elsif to_upper(Element(word, strLen - 1)) = 'E' then
				if to_upper(Element(word, strLen)) = 'S' or to_upper(Element(word, strLen)) = 'D' then
					suffixCount := suffixCount + 1;
				end if;
			end if;
		end if;
	end suffixCounter;

	--- Read in a file to calculate the flesch index score and the flesch-kincaid grade level ---
	procedure readFile is
		infile : file_type;
		fileName : string(1..26);
		line : unbounded_string;
		index, i: integer := 1;
		Last, numWords, numSentences, numSyllable, numSuffix : integer;
	begin
		put_line("Please input the name of the file:");
		get_line(fileName, Last);
		open(infile, in_file, fileName(1..Last));
		numWords := 0;
		numSentences := 0;
		numSyllable := 0;
		numSuffix := 0;

		loop
			exit when end_of_file(infile);
			get_line(infile, line);
			line := trim(line, Ada.Strings.Both);

			loop
				exit when i > length(line);

				--- Go through the line of text one character at a time until a whitespace is found which ---
				---	indicates the end of a word, than it is sent to functions be parsed ---
				if Element(line, i) = ' ' then
					sentenceCounter(to_unbounded_string(slice(line,index, i - 1)), numSentences, punctuationFlag);
					syllableCounter(to_unbounded_string(slice(line,index, i-1)), numSyllable);

					--- If a punctuation is found at the end of the word remove from word so it can be parsed ---
					if punctuationFlag = true then						
						suffixCounter(to_unbounded_string(slice(line,index, i-2)), numSuffix);
					else
						suffixCounter(to_unbounded_string(slice(line,index, i-1)), numSuffix);
					end if;

					index := i + 1;
					numWords := numWords + 1;
					punctuationFlag := false;

				--- This is to catch the last word in the line of text because it does not end with a whitespace ---
				--- than it is sent to functions be parsed ---
				elsif i = length(line) then
					sentenceCounter(to_unbounded_string(slice(line,index, i)), numSentences, punctuationFlag);
					syllableCounter(to_unbounded_string(slice(line,index, i)), numSyllable);

					if punctuationFlag = true then						
						suffixCounter(to_unbounded_string(slice(line,index, i-1)), numSuffix);
					else
						suffixCounter(to_unbounded_string(slice(line,index, i)), numSuffix);
					end if;

					numWords := numWords + 1;
					punctuationFlag := false;
				end if;
				i := i + 1;
			end loop;

			i := 1;
			index := 1;

		end loop;
		close(infile);
		printSummary(numWords, numSentences, numSyllable - numSuffix);

		--- User inputs bad file name asks for another file name ---
		exception
			when name_error =>
				new_line;
				put_line("Error, [ " & fileName(1..Last) & " ] file does not exist.");
				readFile;
	end readFile;

	--- Checks whether the user wants to read another file ---
	procedure checkAnswer is
		flag : boolean := true;
	begin
		put_line("Would you like to read in another file? (Y/N)");
		while flag = true loop
			get(userAnswer);
			skip_line;
			userAnswer := To_Upper(userAnswer);

			if userAnswer = 'Y' then
				flag := false;
			elsif userAnswer = 'N' then
				flag := false;
			else
				put_line("That is not an option. Choose (Y/N) to read another file.");
			end if;
		end loop;
	end checkAnswer;

--- Main program ---
begin 
	put("Welcome to the Flesch Index Program");
	new_line;

	while userAnswer = 'Y' loop
		readFile;
		checkAnswer;
	end loop;

	put_line("Exiting....");
end fleschIndex;