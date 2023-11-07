/* This file will take in a file with hockey stats
and print the team statistics, player statistics 
and a special statistic */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "team.h"
#include "player.h"
#include "custom.h"

/* This function allows me to see
what my vectors display*/
void display(std::vector<std::string> &v) {
	for(unsigned int i = 0; i < v.size(); i++) {
			std::cout << v[i] << " ";
		}
		std::cout << std::endl;
}

//Makes vector with all the items only occuring once
std::vector<std::string> once(std::vector<std::string> v) {

	std::vector<std::string> names;

	for(unsigned int i = 0; i < v.size(); i += 2) {
			if(std::find(names.begin(), names.end(), v[i]) == names.end()) {
		    	names.push_back(v[i]);
		    }
	}

	return names;

}

/*This function will parse the text in 
the input file so it will be easy to pass
through classes */
std::vector<std::string> parsing(const std::string input) {

	std::vector<std::string> v;
	//opening file to read from
	std::ifstream text;
	text.open(input);

	std::string word;
	text >> word;

	while(text.good()) {
		v.push_back(word);
		text >> word;
	}

	return v;
}

//takes in inputed text and outputs all penalties in vector
std::vector<std::string> all_pens (std::vector<std::string> text) {
	std::vector<std::string> pens; //hold all penalties
	for(unsigned int i = 0; i < text.size(); i++) {
		if(text[i] == "penalty"){
			pens.push_back(text[i+3]);
		}
	}
	return pens;
}

//takes in inputed text vector and outputs players name in vector
std::vector<std::string> all_players(std::vector<std::string> text, std::vector<std::string> teams) {
	std::vector<std::string> all_players; //will hold all player names
	std::vector<std::string> all_players2; //checks to make sure only players are in list
	std::vector<std::string> unique; //puts players name in vector only once

	//loop adds name everytime someone scores, or get penalty
	for(unsigned int i = 0; i < text.size(); i++) {
		std::string word = text[i];
		if (word.find(":") != std::string::npos) { //checks if word has a colon in it
			all_players.push_back(text[i+3]);
		}

		if(word.find("(") != std::string::npos) { //checks if word has ( in it
			all_players.push_back(text[i+1]);
			all_players.push_back(text[i+2]);
		}
	}
	//adds only players name to vector 
	for(unsigned int i = 0; i < all_players.size(); i++) {
		if (all_players[i].find("_") != std::string::npos) { //checks if word has a underscore in it
			all_players2.push_back(all_players[i]);
		}
	}
	//checking to make sure all assist names are in
	for(unsigned int i = 0; i < text.size(); i++) {
		if(text[i] == ")" && text[i-1] != "(") {
			all_players2.push_back(text[i-1]);
		}
		if(text[i] == "(" && text[i+1] != ")") {
			all_players2.push_back(text[i+1]);
		}
	}
	//finds unique names
	for(unsigned int i = 0; i < all_players2.size(); i ++) {
		//making sure name is not already in list or a team name
		if(std::find(unique.begin(), unique.end(), all_players2[i]) == unique.end() && std::find(teams.begin(), teams.end(), all_players2[i]) == teams.end()) { 
		    unique.push_back(all_players2[i]);
		}
	}
	//sorting names
	std::sort(unique.begin(), unique.end());
	return unique;
}
	


/* This function takes in a vector
and outputs the team stats in a vector */
std::vector<std::string> scores(std::vector<std::string> &v) {

	std::vector<std::string> scores; //hold home team names with scores


	//This loop will be used to count up the scores for each home team
	for(unsigned int i = 0; i <= v.size(); i++) { 
			if(v[i] == "FINAL") {
				scores.push_back(v[i+1]);
				scores.push_back(v[i+2]);
				scores.push_back(v[i+3]);
				scores.push_back(v[i+4]);
			}
		}

	return scores;
}


/*This function takes in the scores for the 
season, and a name then prints the total goals
for that team in the season*/ 
std::string tot_goals(std::vector<std::string> scores, std::string name) {

	std::vector<std::string> nums; //will hold all the scores for the games

	//This will add all the scores to vector nums
	for(unsigned int i = 0; i < scores.size(); i++){
		if(scores[i] == name){
			nums.push_back(scores[i+1]);
		}
	}

	//This protion of the function turns all the scores to ints and adds them all up
	int goals = 0;
	for(unsigned int i = 0; i < nums.size(); i++){
		int game = std::stoi(nums[i]); //converts string to int
		goals += game;
	}

	//Turns the total goals to a string so it can be printed
	std::string goals_str = std::to_string(goals);

	return goals_str;

}


/*This function takes in the vector of names and a name 
and outputs how many times that name shows up.
This will be used when counting wins, losses, and ties */
int occur(std::vector<std::string> v_n, std::string name) {

	int count = 0;

	for(unsigned int i = 0; i < v_n.size(); i++) {

		if(v_n[i] == name){
			count++;
		}

	}
	return count;
}

//takes in wins and losses and prints the win%
double percent(int w, int l, int t) {
	double p = ((w + (t*0.5)))/(w+l+t);
	return p;
}

//finds longest word in vector
int longest(std::vector<std::string> &names) {
	std::vector<int> lengths; //hold length of names
	
	for(unsigned int i = 0; i < names.size(); i++) {
		lengths.push_back(names[i].size());
	}

	std::sort(lengths.begin(), lengths.end());
	
	return lengths[names.size() - 1];
}

//sorts names based on most goals
std::vector<std::string> sort_goals(std::vector<std::string> scores, std::vector<std::string> names) {
	std::vector<std::string> goals_vect; //holds goals for each team
	std::vector<std::string> goals_sorted;
	std::vector<std::string> sorted_names;

	for(unsigned int i = 0; i < names.size(); i++) {
		goals_vect.push_back(tot_goals(scores,names[i]));
	}
	std::sort(goals_vect.begin(), goals_vect.end());
	for(unsigned int i = 1; i <= goals_vect.size(); i++) {
		std::string x = goals_vect[goals_vect.size() - i];
		goals_sorted.push_back(x);
	}
	for(unsigned int i = 0; i < goals_sorted.size(); i++) {
		for(unsigned int j = 0; j < names.size(); j++) {
			std::string x = tot_goals(scores,names[j]);
			if(goals_sorted[i] == x && std::find(sorted_names.begin(), sorted_names.end(), names[j]) == sorted_names.end()){
				sorted_names.push_back(names[j]);
				goals_sorted[i] = "x";
			}
		}
	}

	return sorted_names;
}

//sorts names based on most wins
std::vector<std::string> sort_wins(std::vector<std::string> text) {
	std::vector<std::string> s = scores(text);
	Team stats(s,text);
	std::vector<std::string> teams = stats.Unique(); //creating vector of unique team names
	std::vector<std::string> wins = stats.Wins(); //creating a vector of teams that won each game
	std::vector<std::string> losses = stats.Losses(); //creating a vector of team that won each game
	std::vector<std::string> ties = stats.Ties(); //creating a vector of team that tie each game

	std::vector<double> win_nums;
	std::vector<double> win_sorted;
	std::vector<std::string> sorted_names;

	for(unsigned int i = 0; i < teams.size(); i++) {
		win_nums.push_back(percent(occur(wins,teams[i]),occur(losses,teams[i]),occur(ties,teams[i])));
	}
	std::sort(win_nums.begin(), win_nums.end());
	for(unsigned int i = 1; i <= win_nums.size(); i++) {
		double x = win_nums[win_nums.size() - i];
		win_sorted.push_back(x);
	}
	std::vector<std::string> sort1 = sort_goals(s, teams);
	for(unsigned int i = 0; i < win_sorted.size(); i++) {
		for(unsigned int j = 0; j < sort1.size(); j++) {
			double x = percent(occur(wins, sort1[j]), occur(losses, sort1[j]),occur(ties,sort1[j]));
			if(win_sorted[i] == x && std::find(sorted_names.begin(), sorted_names.end(), sort1[j]) == sorted_names.end()){
				sorted_names.push_back(sort1[j]);
				win_sorted[i] = 1000;
			}
		}
	}

	return sorted_names;
}

int main(int argc, char*argv[]) {

	if(argc == 4) {
		std::string input = {argv[1]}; //name of input file
		std::string output = {argv[2]}; //name of output file
		std::string type = {argv[3]}; //type of statistic user wants to print

		//opening new file
		std::fstream MyFile;
		MyFile.open(output, std::ios::out); //opening file to write in it

		if(type == "--team_stats") {

			std::vector<std::string> all_text = parsing(input); //puts each word from file into vector
			std::vector<std::string> sorted_names = sort_wins(all_text);
			std::vector<std::string> score_vect = scores(all_text); //creating a vector that has each score per game
			Team stats(score_vect, all_text); //creating a Team class variable
			std::vector<std::string> teams = stats.Unique(); //creating vector of unique team names
			std::vector<std::string> wins = stats.Wins(); //creating a vector of teams that won each game
			std::vector<std::string> losses = stats.Losses(); //creating a vector of teams that lost each game
			std::vector<std::string> ties = stats.Ties(); //creating a  vector of teams that tied each game
			std::vector<std::string> pens = stats.Pens(); //creating a vector of teams that got penalities
			int longest_name = longest(teams);

			//printing header
			MyFile << "Team Name";
			for(int i = 0; i < longest_name - 5; i++) { //printing spaces
				MyFile << " ";
			}
			MyFile << "W   L   T   Win%  Goals  Penalties" << std::endl;
			//print body of table
			for(unsigned int i = 0; i < sorted_names.size(); i++) {
				int w = occur(wins, sorted_names[i]); //wins for the team
				int l = occur(losses, sorted_names[i]); //losses for the team
				int t = occur(ties, sorted_names[i]); //ties for the team
				double p = percent(w,l,t); //win% for the team
				std::string g = tot_goals(score_vect, sorted_names[i]); //goals for the team
				int penalties = occur(pens,sorted_names[i]);

				MyFile << sorted_names[i];
				MyFile.width(longest_name - sorted_names[i].size() + 5); MyFile << w; //prints wins in the right format
				MyFile.width(4); MyFile << l; //prints losses in right format
				MyFile.width(4); MyFile << t; //prints ties in right format
				MyFile.precision(2);MyFile.width(7); MyFile << std::fixed << p; //prints win% in right format
				MyFile.width(7); MyFile << g; //prints goals in right format
				MyFile.width(11); MyFile << penalties; //prints ties in right format
				MyFile << std::endl;
		}

		}

		else if(type == "--player_stats"){

			std::vector<std::string> all_text = parsing(input); //puts each word from file into vector

			//GETTING TEAM NAMES
			std::vector<std::string> score_vect = scores(all_text); //creating a vector that has each score per game
			Team stats(score_vect, all_text); //creating a Team class variable
			std::vector<std::string> teams = stats.Unique(); //creating vector of unique team names

			std::vector<std::string> players = all_players(all_text, teams); //hold all player names in alphabetical order
			std::vector<Player> players_class; //will hold all player classes
			int longest_name = longest(players);
			int longest_team = longest(teams);

			for(unsigned int i = 0; i < players.size(); i++){
				Player p(all_text,players[i]);
				players_class.push_back(p);

			}
			
			sort(players_class.begin(),players_class.end(),IsHigherThan);
			
			//printing Header
			MyFile << "Player Name";
			MyFile.width(longest_name - 5); MyFile << "Team";
			MyFile.width(longest_team + 4); MyFile << "Goals";
			MyFile << "  " << "Assists" << "  " << "Penalties" << std::endl;
			//prints table
			for(unsigned int i = 0; i < players_class.size(); i++) {
				MyFile << players_class[i].GetName();
				//printing spaces
				for(unsigned int j = 0; j < longest_name - players_class[i].GetName().size() + 2; j++){
					MyFile << " ";
				}
				MyFile << players_class[i].GetTeam();
				MyFile.width(longest_team - players_class[i].GetTeam().size() + 8); MyFile << players_class[i].Goals();
				MyFile.width(9); MyFile << players_class[i].Assists();
				MyFile.width(11); MyFile << players_class[i].Penalties() << std::endl;

			}
			
			
		}

		else if(type == "--custom_stats"){
			std::vector<std::string> all_text = parsing(input); //puts each word from file into vector
			std::vector<std::string> all_penalties = all_pens(all_text); //puts all pens from text into vector

			if(all_penalties.size() > 0){
				std::vector<std::string> unique_pens = once(all_penalties); //makes a vector of all unique penalties
				std::vector<Custom> class_pens; //will hold all penalty custom classes
				int longest_name = longest(unique_pens); //number of char in longest penalty name

				for(unsigned int i = 0; i < unique_pens.size(); i++) {
					Custom c(all_text, unique_pens[i]);
					class_pens.push_back(c);
				}
				sort(class_pens.begin(),class_pens.end(),IsMoreThan); //sorts based on most times penalty happened
			
				//PRINTING HEADER
				MyFile << "Penalty Name";
				for(int i = 0; i < longest_name-10; i++){
					MyFile << " ";
				}
				MyFile << "Time(s) Occurred" << std::endl;

				//PRINT BODY
				for(unsigned int i = 0; i < class_pens.size(); i++) {
					std::string name = class_pens[i].GetName();
					int time = class_pens[i].Amount();
					MyFile << name;
					MyFile.width(longest_name - name.size() + 18); MyFile << time << std::endl;
				}
			}
			else {
				MyFile << "There were no penalties this season!";
			}
		}
	

		else{
			std::cerr << "Invalid Type Entered." << std::endl;
		}
	}


	else {

		std::cerr << "You did not input 3 arguemnts." << std::endl;
	}

}