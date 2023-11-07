#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "player.h"

//CONSTRUCTORS
Player::Player(const std::vector<std::string> aText, std::string aName) {
	Text = aText; //whole text file in vector
	Name = aName; //player name
}

//ACCESSORS
std::string Player::GetName(){
	return Name;
}

//OTHER FUNCTIONS
//finds the team the player plays for
std::string Player::GetTeam() {
	std::vector<std::string> all_teams; //holds team name
	for(unsigned int i = 0; i < Text.size(); i++){
		if(Text[i] == Name) {
			if(Text[i-1] == "("){
				all_teams.push_back(Text[i-4]);
			}
			else if(Text[i+1] == ")"){
				all_teams.push_back(Text[i-5]);
			}
			else{
				all_teams.push_back(Text[i-2]);
			}
		}
	}
	std::string name = all_teams[0];
	return name;
}

//returns vector of goals scored by player
int Player::Goals() {
	int count = 0; //stores number of goals
	for(unsigned int i = 0; i < Text.size(); i++) {
		if(Text[i] == Name){
			if(Text[i-1] == "goal"){
				count++;
			}
		}
	}
	return count;
}

//return how many assists the player has
int Player::Assists() {
	int count = 0; //stores number of assists
	for(unsigned int i = 0; i < Text.size(); i++) {
		if(Text[i] == Name){
			if(Text[i-1] == "(" || Text[i+1] == ")") {
				count++;
			}
		}
	}
	return count;
}

//returns how many penalties the player has
int Player::Penalties() {
	int count = 0; //stores number of penalties
	for(unsigned int i = 0; i < Text.size(); i++) {
		if(Text[i] == Name){
			if(Text[i-1] == "penalty"){
				count++;
			}
		}
	}
	return count;
}

int Player::Points() {
	int count = 0; //stores number of points

	//counts goals
	for(unsigned int i = 0; i < Text.size(); i++) {
		if(Text[i] == Name){
			if(Text[i-1] == "goal"){
				count++;
			}
		}
	}

	//counts assists
	for(unsigned int i = 0; i < Text.size(); i++) {
		if(Text[i] == Name){
			if(Text[i-1] == "(" || Text[i+1] == ")") {
				count++;
			}
		}
	}

	return count;
}

//useed for sorting
bool IsHigherThan(Player& p1, Player& p2) {
	if(p1.Points() == p2.Points()){
		if(p1.Penalties() == p2.Penalties()) {
			return p1.GetName() < p2.GetName();
		}
		else{
			return p1.Penalties() < p2.Penalties();
		}
	}
	else{
		return p1.Points() > p2.Points();
	}
}

