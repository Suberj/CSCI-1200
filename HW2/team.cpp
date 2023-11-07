#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "team.h"


//CONSTRUCTORS
Team::Team(std::vector<std::string> aScores, const std::vector<std::string> aText_all) {
	scores = aScores;
	text = aText_all;
}

//ALL GET FUNCTIONS

//prints all the scores to the termainal
void Team::getScores() {
	for(unsigned int i = 0; i < scores.size(); i++){

		std::cout << scores[i] << " ";

		if((i+1)%2 == 0) {
			std::cout << std::endl;
		}
		if((i+1)%4 == 0) {
			std::cout << "--------------" << std::endl;
		}
		

	}
}

//Makes vector with all the teams occuring once
std::vector<std::string> Team::Unique() {

	std::vector<std::string> names;

	for(unsigned int i = 0; i < scores.size(); i += 2) {
			if(std::find(names.begin(), names.end(), scores[i]) == names.end()) {
		    	names.push_back(scores[i]);
		    }
	}

	return names;

}

//Returns a list of all the team names who win
std::vector<std::string> Team::Wins() {
	
	std::vector<std::string> w; //store names of team when they win

	for(unsigned int i = 0; i < scores.size(); i += 4) {
		
		int home_score = std::stoi(scores[i+1]);
		int away_score = std::stoi(scores[i+3]);

		if(home_score > away_score) {
			w.push_back(scores[i]);
		}
		else if(away_score > home_score) {
			w.push_back(scores[i+2]);
		}
	}

	return w;


}

//Returns a list of all the team names who loses
std::vector<std::string> Team::Losses() {
	
	std::vector<std::string> l; //store names of team when they lose

	for(unsigned int i = 0; i < scores.size(); i += 4) {
		
		int home_score = std::stoi(scores[i+1]);
		int away_score = std::stoi(scores[i+3]);

		if(home_score > away_score) {
			l.push_back(scores[i+2]);
		}
		else if(away_score > home_score) {
			l.push_back(scores[i]);
		}
	}

	return l;


}

//Returns a list of all the team names who tie
std::vector<std::string> Team::Ties() {
	
	std::vector<std::string> t; //store names of team when they tie

	for(unsigned int i = 0; i < scores.size(); i += 4) {
		
		int home_score = std::stoi(scores[i+1]);
		int away_score = std::stoi(scores[i+3]);

		if(home_score == away_score) {
			t.push_back(scores[i]);
			t.push_back(scores[i+2]);
		}
		
	}

	return t;


}

/* This function takes in a vector of strings and 
returns a vector that containns the penalties for 
each team */
std::vector<std::string> Team::Pens() {
	std::vector<std::string> penalties; //will add names of teams that got penalties
	const char* colon = ":"; //used to see if word contains a colon

	for(unsigned int i = 0; i < text.size(); i++) {
		std::string word = text[i];
		if (word.find(colon) != std::string::npos) {
			if(text[i+2] == "penalty") {
				penalties.push_back(text[i+1]);
			}

		}
	}
	return penalties;
}

