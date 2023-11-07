/* This file will take in a text file
and make it either flush left, flush right,
or full justified */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>



/* This function will take in a file name and width,
but a box around the text,
and then flush left the text */
void flush_left(std::string filename, std::string output, int w) {

	//opening file to read from
	std::ifstream text;
	text.open(filename);
	//opening new file
	std::fstream myFile;
	myFile.open(output, std::ios::out); //opening file to write in it

	std::string word;
	text >> word;

	//printing top line
		for(int i = 1; i <= w + 4; i++) {

			myFile << "-";
		}
		myFile << std::endl;

	//making sure not at end of the file
	while(text.good()) {

		//counts the characters 
		int count = 0;

		myFile << "| ";
		//printing the words
		while( (count + word.length() <= w) && (text.good())) {

			count += word.length() + 1; //plus one for space
			myFile << word << " ";
			text >> word;

		}

		//printing spaces at the end
		int spaces = w - count;
		for (int i = 0; i <= spaces; i++) {

			myFile << " ";

		}


		myFile << "|" << std::endl;
	}


	//printing bottom line
		for(int i = 1; i <= w + 4; i++) {

			myFile << "-";
		}
		myFile << std::endl;
}


/*This function takes in a file name and the width
then outputs the text file 
flushes right with a box around it*/
void flush_right(std::string filename, std::string output, int w) {

	//opening input file to read from
	std::fstream f;
	f.open(filename, std::ios::in);

	//opening output file to write to
	std::fstream myFile;
	myFile.open(output, std::ios::out);
	std::vector<int> spaces; //holds the number of spaces

	if (f.is_open()) {
		std::string word;
		while(f.good()) {
			
			int count = 0; //count the characters
			

			while((count + word.length() <= w) && f.good()){
				
				count += word.length() + 1; //adds characters to count
				f >> word; //load one word at a time
			}

			spaces.push_back(w - count);

		
		}

	}

f.close();

//opening file to read from
	std::ifstream text;
	text.open(filename);
	//opening new file
	std::fstream myF;
	myF.open(output, std::ios::out); //opening file to write in it

	std::string word;
	text >> word;

	//printing top line
		for(int i = 1; i <= w + 4; i++) {

			myF << "-";
		}
		myF << std::endl;

	//printing body
	int linenum = 0; //keep track of line num
	while(text.good()) {

		//counts the characters 
		int count = 0;
		

		myF << "| ";

		//printing the words
		if(linenum == 0){
			myF << " ";
			for(int i = 0; i <= spaces[linenum]; i++){
					myF << " ";
			}
		}
		else{
			for(int i = 0; i <= spaces[linenum]; i++){
				myF << " ";
			}
		}
		while( (count + word.length() <= w) && (text.good())) {


			count += word.length() + 1; //plus one for space
			myF << word << " ";
			text >> word;
			
		}

		linenum ++;

		myF << "|" << std::endl;
	}


	//printing bottom line
		for(int i = 1; i <= w + 4; i++) {

			myF << "-";
		}
		myF << std::endl;


}


/*This function takes in a file name and the width
then outputs the text file 
full justified with a box around it*/
void full_justified(std::string filename, std::string output, int w){

	//opening input file to read from
	std::fstream f;
	f.open(filename, std::ios::in);

	//opening output file to write to
	std::fstream myFile;
	myFile.open(output, std::ios::out);
	std::vector<int> spaces; //holds the number of spaces
	std::vector<int> remainders; //hold the remainder for spaces

	if (f.is_open()) {
		std::string word;
		while(f) {
			
			int count = 0; //count the characters
			int word_count = 0; //keeps track of word count per line

			while((count + word.length() <= w) && f){
				

				
				count += word.length() + 1; //adds characters to count
				f >> word; //load one word at a time
				word_count++;
				
			}

			int tot_space = (w - count)/word_count;
			int tot_remainder = (w - count)%word_count;
		

			spaces.push_back(tot_space); //adding number of spaces to a vector for later use
			remainders.push_back(tot_remainder); //adding number of words that get extra spaces to vector for later use
			
		
		}

	}

remainders[0] += 1;
f.close();


//opening file to read from
	std::ifstream text;
	text.open(filename);
	//opening new file
	std::fstream myF;
	myF.open(output, std::ios::out); //opening file to write in it

	std::string word;
	text >> word;

	//printing top line
		for(int i = 1; i <= w + 4; i++) {

			myF << "-";
		}
		myF << std::endl;

	//printing body
	int linenum = 0; //keep track of line num
	while(text.good()) {

		//counts the characters 
		int count = 0;
		int word_count2 = 0; //keeps track of what word we are on

		myF << "| ";

		//printing the words
		
		while( ((count + word.length() <= w) && (text.good())) || (word.length() > w)) {

			//if word is too long to fit on one line
			if(word.length() > w) {
				for(int i = 1; i <= w; i++){
					char c;
					text.get(c);
					myF << c;
				}

			}

			else{
				count += word.length() + 1; //plus one for space
				myF << word << " ";


				//printing the spaces after the words
				for(int i = 1; i <= spaces[linenum]; i++){
					myF << " ";
				}

				//adding extra space if it needs it because of odd numbers
				if(word_count2 <= remainders[linenum]) {
					myF << " ";
				}

		}
				
		
			text >> word;

			word_count2++;
			
		}

		linenum ++;

		myF << "|" << std::endl;
	}


	//printing bottom line
		for(int i = 1; i <= w + 4; i++) {

			myF << "-";
		}
		myF << std::endl;

}







int main(int argc, char*argv[]) {

	//checking to make sure there if four arguments given
	if(argc == 5) {

		//This is where the main code happens

		std::string input_file = {argv[1]};
		std::string output_file = {argv[2]};
		int width = std::stoi(argv[3]);
		std::string flush = {argv[4]};

		//this is where the functions are called depending on user input for flush type
		if(flush == "flush_left"){
			flush_left(input_file, output_file, width);
		}

		else if(flush == "flush_right") {
			flush_right(input_file, output_file, width);
		}

		else if(flush == "full_justify") {
			full_justified(input_file, output_file, width);
		}

	}


	//if not exactly four arguments were given error message prints
	else {

		std::cerr << "Four arguments were not inputed" << std::endl;
	}

}