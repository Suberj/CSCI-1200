class Player {

public:

	//CONSTRUCTOR
	Player(const std::vector<std::string> aText, std::string aName);

	//ASSESSORS
	std::string GetName(); //returns player name

	//Functions
	std::string GetTeam(); //get players team
	int Goals(); //gets players goals
	int Assists(); //gets players assists
	int Penalties(); //gets players penalties
	int Points(); //gets players points (goals + assists)


private:
	std::vector<std::string> Text;
	std::string Name;

};

bool IsHigherThan(Player& p1,Player& p2); //used for sorting

