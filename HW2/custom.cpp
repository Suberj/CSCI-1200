#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "custom.h"

//CONSTRUCTORS
Custom::Custom(const std::vector<std::string> aText, std::string aName) {
	Text = aText; //whole text file in vector
	Name = aName; //penalty name
}

//ACCESSORS
std::string Custom::GetName() {
	return Name;
}

//OTHER FUNCTIONS
//returns amount of time penalty happened
int Custom::Amount() {
	std::vector<std::string> pens; //hold all penalties
	int count = 0; //hold amount of times penalty happened
	for(unsigned int i = 0; i < Text.size(); i++) {
		if(Text[i] == "penalty"){
			pens.push_back(Text[i+3]);
		}
	}

	for(unsigned int i = 0; i < pens.size(); i++) {
		if(pens[i] == Name) {
			count++;
		}
	}
	return count;
}

//used for sorting 
bool IsMoreThan(Custom& p1,Custom& p2) {
	if(p1.Amount() == p2.Amount()) {
		return p1.GetName() > p2.GetName();
	}
	else {
		return p1.Amount() > p2.Amount();
	}
}