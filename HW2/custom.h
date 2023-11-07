class Custom {

public:

	//CONSTRUCTOR
	Custom(std::vector<std::string> aText, std::string Name);

	//ACCESSORS
	std::string GetName(); //returns penalty name

	//OTHER FUNCTIONS
	int Amount(); //returns the amount of time penalty happened

private:
	std::vector<std::string> Text;
	std::string Name;
};

bool IsMoreThan(Custom& p1,Custom& p2); //used for sorting
