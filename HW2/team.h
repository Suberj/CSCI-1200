class Team {

public:

	//CONSTRUCTORS
	Team(std::vector<std::string> aScores, const std::vector<std::string> aText_all);

	//ACESSORS
	void getScores();

	//Statistics to print
	std::vector<std::string> Unique();
	std::string Total_Goals();
	std::vector<std::string> Wins();
	std::vector<std::string> Losses();
	std::vector<std::string> Ties();
	std::vector<std::string> Pens();

private:

	std::vector<std::string> scores;
	std::vector<std::string> text;


};

