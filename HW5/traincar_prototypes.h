// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//                 This file is #include'd from traincar.h and main.cpp
//
// =======================================================================
//
// There are a number of additional functions used in main.cpp that
// you need to declare and implement.  Study main.cpp and the provided
// output to determine the arguments, return type, and overall
// behavior.
//
// Add all required additional function prototypes here
// (you may also add your own helper function prototypes here too)
//
// Implement these functions in "traincar.cpp"
//

//Two main algorithms that are mentioned in notes
std::vector<TrainCar*> ShipFreight(TrainCar*& engines, TrainCar*& freights,
                                   const int& min_speed, const int& max_cars);
void Separate(TrainCar*& main_train, TrainCar*& train1, TrainCar*& train2);

//Functions other than two main algorithms
//allows user to add different traincars to train
void PushBack(TrainCar*& train, TrainCar* train1);
//Deletes train to prevent memory leaks
void DeleteAllCars(TrainCar*& train);
//Functions that are used in to print train
void TotalWeightAndCountCars(TrainCar* train, int& total_weight, int& engine_num,
                            int& freight_cars, int& passenger_cars, int& dining_cars,
                            int& sleeping_cars);
float CalculateSpeed(TrainCar* train, TrainCar* train1 = NULL);
//the next two will also be used for the comfort level of passengers
float AverageDistanceToDiningCar(TrainCar* train);
int ClosestEngineToSleeperCar(TrainCar* train);
//Used in both of the main algorithms
int CountCars(TrainCar* train);
int CountEngines(TrainCar* train);
//used in ShipFreight optimization
TrainCar* PopFront(TrainCar*& train); //removes front element and returns it
TrainCar* Max_Weight(TrainCar* train); //finds the heaviest car
TrainCar* Remove(TrainCar*& train, TrainCar*& ptr); //removes cars in middle of train

