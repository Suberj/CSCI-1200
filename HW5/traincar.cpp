// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>
#include <algorithm>

#include "traincar.h"

// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//
//Implementing PushBack which is used in the tests
//Will put train at end of linked list
void PushBack(TrainCar*& train, TrainCar* train1) {
    if(train1 != NULL) {
        //checking if list is empty
        //if so the whole list is just the train
        if(train == NULL) {
            train = train1; //making train the whole list
            train->prev = NULL; //making it the first element in list
            train->next = NULL;
        }
        //dealing with cases when list has elements in it
        else {
            //finding the tail of the list
            //This loop will go through changing ptr until
            //next is equal to NULL since the only time the tail is equal
            //to NULL is when the element is the tail of the list
            TrainCar *temp_ptr = train;
            while (temp_ptr != NULL) {
                if (temp_ptr->next == NULL) {
                    break;
                } else {
                    temp_ptr = temp_ptr->next;
                }
            } //end of while loop
            //making the new train the new tail
            temp_ptr->next = train1; //making previous tail point to new train
            train1->prev = temp_ptr; //making the new train point back to the previous trail
            train1->next = NULL;
        }
    }
}

//Implementing DeleteAllCars which is also in test cases but not yet implemented
//This will allow for all the memory leaks to be dealt with
void DeleteAllCars(TrainCar*& train) {
    //If list is empty
    if (train == NULL) {
        return;
    }
    //If list is not empty
    TrainCar *ptr = train;
    while (ptr->next != NULL) {
        ptr = ptr->next;
        delete ptr->prev;
    }
    delete ptr;
    train = NULL;
}

//finds total weight and cars which will be used for the print train function
void TotalWeightAndCountCars(TrainCar* train, int& total_weight, int& engine_num,
                            int& freight_cars, int& passenger_cars, int& dining_cars,
                            int& sleeping_cars) {
    //setting baselines for stats
    TrainCar* ptr = train;
    total_weight = 0;
    sleeping_cars = 0;
    dining_cars = 0;
    passenger_cars = 0;
    freight_cars = 0;
    engine_num = 0;
    //loop that goes through every car and stops at the tail of the list
    while(ptr != NULL) {
        //finding total weight
        total_weight += ptr->getWeight();
        //finding number of each car
        if (ptr->isSleepingCar()) {
            sleeping_cars++;
        }
        else if (ptr->isDiningCar()) {
            dining_cars++;
        }
        else if (ptr->isPassengerCar()) {
            passenger_cars++;
        }
        else if (ptr->isFreightCar()) {
            freight_cars++;
        }
        else if (ptr->isEngine()) {
            engine_num++;
        }
        ptr = ptr->next; //moving pointer
    }
}

//function that calculates the speed of the train
//this is based on the equation given in the handout
float CalculateSpeed(TrainCar* train, TrainCar* train1) {
    //going through whole list to find horsepower and total weight
    //these two numbers will be crucial to calculating the speed
    int horse_pwr = 0;
    int weight = 0;
    TrainCar* ptr = train;
    while (ptr != NULL) {
        //adding hp if car is a engine
        if(ptr->isEngine()) {
            horse_pwr += 3000;
        }
        //adding weight per car
        weight += ptr->getWeight();
        //moving pointer to next car
        ptr = ptr->next;
    }
    //this will be used for ship freight function
    if(train1 != NULL) {
        weight += train1->getWeight();
    }
    float speed = (horse_pwr*550*36*1.0)/(4*528*weight);
    return speed;
}

//this returns the avg distance each passenger car
//is away from dinning car the lower the number
//the happier the passengers
float AverageDistanceToDiningCar(TrainCar* train){
    //initalizing everything that will be needed
    TrainCar* ptr = train;
    int distance;
    int passenger = 0;
    float total = 0;
    //looping through the whole train
    //this is where all of the distances will be found
    while(ptr != NULL) {
        //finding passenger car
        if(ptr->isPassengerCar()) {
            //setting everything to zero since passenger car is starting location
            passenger++;
            distance = -1;
            int bcount = 0;
            int fcount = 0;
            //start at pointer because pointer is currently on passenger car
            TrainCar* fptr = ptr; //will be used to go forward in train
            TrainCar* bptr = ptr; //will be used to backwards in train
            //going backwards through the train
            while(bptr->prev != NULL) {
                bptr = bptr->prev; //start with moving since it is on passenger
                bcount++; //everytime we move count goes up
                if(bptr->isDiningCar()) {
                    distance = bcount;
                    break;
                }
                if(bptr->isEngine()) {
                    break; //passengers cannot walk through engine car
                }
            }
            //going forward through train
            while(fptr->next != NULL) {
                fptr = fptr->next; //starts with moving since it is on passenger
                fcount++; //count keeps track of movement
                if(fptr->isDiningCar()) {
                    //finding min value for distance
                    //because who would go to the farther dining car
                    if(fcount < distance || distance == -1) {
                        distance = fcount;
                        break;
                    }
                }
                if(fptr->isEngine()) {
                    break; //passengers cannot walk through engine car
                }
            }
            //if there is no accessible dining car
            //then function returns -1
            if(distance == -1) {
                return -1;
            }
            else {
                total += distance;
            }
        }
        ptr = ptr->next;
    }
    float avg = total/passenger;
    return avg;
}

//finding the closest engine to sleeping car
//This is pretty much a copy of the function above
//Made a few minor changes to make it work for this context
int ClosestEngineToSleeperCar(TrainCar* train) {
    TrainCar* ptr = train;
    int distance = INT_MAX; //this will change because we are looking for min
    //looping through whole train looking for closest engine
    while(ptr != NULL) {
        if(ptr->isSleepingCar()) {
            int bcount = 0;
            int fcount = 0;
            //start at pointer because pointer is currently on passenger car
            TrainCar* fptr = ptr; //will be used to go forward in train
            TrainCar* bptr = ptr; //will be used to backwards in train
            //going backwards through train looking for engine
            while(bptr->prev != NULL) {
                bptr = bptr->prev; //moving to start since already on sleeping car
                bcount++;
                if(bptr->isEngine()) {
                    if(distance > bcount) {
                        distance = bcount;
                        break;
                    }
                }
            }
            //moving forward through train
            while(fptr->next != NULL) {
                fptr = fptr->next; //moving to start since already on sleeping car
                fcount++;
                if(fptr->isEngine()) {
                    if(distance > fcount) {
                        distance = fcount;
                        break;
                    }
                }
            }
        }
        ptr = ptr->next;
    }
    if(distance != INT_MAX) {
        return distance;
    }
    else {
        return -1;
    }
}

//counting total number of cars
int CountCars(TrainCar* train) {
    int cars = 0;
    TrainCar* ptr = train;
    while(ptr != NULL) {
        cars++;
        ptr = ptr->next;
    }
    return cars;
}

//counting total number of engines
int CountEngines(TrainCar* train) {
    int engines = 0;
    TrainCar* ptr = train;
    while(ptr != NULL) {
        if(ptr->isEngine()) {
            engines++;
        }
        ptr = ptr->next;
    }
    return engines;
}

//removes the first element in train and returns it
//this will be used when adding engines to trains in ShipFreight
//Since all engines are the same this will work fine
TrainCar* PopFront(TrainCar*& train){
    TrainCar* ptr = train;
    //Checking if list is empty
    if (train == NULL) {
        return NULL;
    }
    //Checking if only one element in train
    else if (train->next == NULL) {
        train = NULL;
        return ptr;
    }
    //If there is more than one element in train
    train = train->next;
    train->prev = NULL;
    ptr->next = NULL;
    return ptr;
}

TrainCar* Max_Weight(TrainCar* train) {
    TrainCar* ptr = train;
    TrainCar* ptr1 = train;
    int max = 0;
    //looping through whole train
    //finds the heaviest train car
    while(ptr != NULL) {
        int w = ptr->getWeight();
        if(max < w) {
            max = w;
        }
        ptr = ptr->next;
    }
    //finding the car
    while(ptr1 != NULL) {
        if(max == ptr1->getWeight()) {
            return ptr1;
        }
        ptr1 = ptr1->next;
    }
    return NULL;
}

//removes cars in middle of train class and changes pointers for elements around it
TrainCar* Remove(TrainCar*& train, TrainCar*& ptr) {
    //If train is empty
    if (train == NULL || ptr == NULL) {
        return NULL;
    }
    TrainCar *tmp = ptr;
    //If there is only one element
    if (ptr->prev == NULL && ptr->next == NULL) {
        train = NULL;
    }
    else if (ptr->next == NULL) {
        ptr->prev->next = NULL;
    }
    else if (ptr->prev == NULL) {
        ptr->next->prev = NULL;
        train = train->next;
    }
    else {
        ptr->next->prev = ptr->prev;
        ptr->prev->next = ptr->next;
    }
    ptr = ptr->next;
    tmp->prev = NULL;
    tmp->next = NULL;
    return tmp;
}

//Implementing two main algorithms
//These are the bulk of the assignment
//=================================================================================//
//This will allow us to handle shipping large quantity of frieght in multiple trains
//The arguments are a collection of engines, a collection of freights, the min speed
//the train must go and the max cars that the train can have
//This will return a vector of train head (each head points to a different train)
//=================================================================================//
/* --------------------------------------------------------------------------------
 * Basic Algorithm to optimize the number of train we will need to use
 * Loop through until all freight cars or engines are gone
 * make temp train and add an engine since all train need engine to go
 * loop until the max cars are reached or no more freight cars or no more engines
 * add heaviest cars one by one
 * check if speed is too low; if speed is too low add another engine
 * if max_cars are reached (or freight/engines are gone) then add temp train to vector
 ---------------------------------------------------------------------------------*/
std::vector<TrainCar*> ShipFreight(TrainCar*& engines, TrainCar*& freights,
                                   const int& min_speed, const int& max_cars) {

    //creating vector that will be returned
    std::vector<TrainCar*> trains;
    //loop until either engines or freight have no elements left
    while(engines != NULL && freights != NULL) {
        TrainCar* train = NULL;
        //moving engine from engines list to temp train
        PushBack(train, PopFront(engines));
        //making sure min speed is reached and max cars are not
        while(CalculateSpeed(train) > min_speed && CountCars(train) < max_cars) {
            //adding heaviest cars first
            TrainCar* temp = freights; //make sure adding next freight won't make train too slow
            TrainCar* temp2 = NULL;
            //this find ths heaviest car
            //it uses the two temp pointers having temp2 be the heaviest car
            //and temp just going through freights comparing each car to temp2
            while(temp != NULL) {
                //adding engine if possible to minimize the amount of trains going off
                if(CalculateSpeed(train, temp) <= min_speed && CountCars(train) < max_cars-1) {
                    PushBack(train, PopFront(engines));
                }
                //This is where finding the heaviest starts
                //this sets temp2 to first element in freights
                if(CalculateSpeed(train, temp) >= min_speed && temp2 == NULL) {
                    temp2 = temp;
                }
                //this is where the comparing of the two pointers happens
                else if(CalculateSpeed(train, temp) >= min_speed) {
                    if(temp->getWeight() > temp2->getWeight()) {
                        temp2 = temp;
                    }
                }
                temp = temp->next;
            }
            //Adding freight to train
            if(temp2 != NULL) {
                PushBack(train, Remove(freights, temp2));
            }
            else {
                break;
            }
        }
        trains.push_back(train);
    }
    return trains;
}

//=================================================================================//
//This function will take in a train with two engines and separate it into two
//different trains with approx the same speed as the original train
//=================================================================================//
/* --------------------------------------------------------------------------------
 * Basic Algorithm to optimize Separate function
 * adding engine to train1 while removing it from main train
 * add carts in succession from main train to train 1 until
 * the speed is about the same
 * then add the rest of the carts from main train to train2
 ---------------------------------------------------------------------------------*/
void Separate(TrainCar*& main_train, TrainCar*& train1, TrainCar*& train2) {
    //making sure main_train has exactly two engines
    if(CountEngines(main_train) != 2) {
        return;
    }
    //setting both new train to NULL to avoid any errors
    train1 = NULL;
    train2 = NULL;
    //removing first engine in main train and adding it to train1
    //This is so we can compare the speed of the two trains
    //checking if engines are on other sides of trains
    int count = 0;
    int car_count = CountCars(main_train);
    int half_count = car_count/2;
    TrainCar* temp3 = main_train;
    for(int i = 0; i < half_count; i++) {
        if(temp3->isEngine()) {
            count++;
        }
        temp3 = temp3->next;
    }
    //one past middle
    int count1 = 0;
    TrainCar* temp1 = main_train;
    for(int i = 0; i < half_count+1; i++) {
        if(temp1->isEngine()) {
            count1++;
        }
        temp1 = temp1->next;
    }
    //two past middle
    int count2 = 0;
    TrainCar* temp2 = main_train;
    for(int i = 0; i < half_count+2; i++) {
        if(temp2->isEngine()) {
            count2++;
        }
        temp2 = temp2->next;
    }
    //if there is only one engine in first half of the train
    //split train in half
    if(count == 1) {
        for(int i = 0; i < half_count; i++) {
            PushBack(train1, PopFront(main_train));
        }
    }
    else if(count1 == 1) {
        for(int i = 0; i < half_count+1; i++) {
            PushBack(train1, PopFront(main_train));
        }
    }
    else if(count2 == 1) {
        for(int i = 0; i < half_count+2; i++) {
            PushBack(train1, PopFront(main_train));
        }
    }
    //if there is no engine in first half
    //or both engines are in first half this will create both trains by looking a speed
    //this will not be as good for the costs of moving around cars
    else {
        TrainCar *ptr = main_train;
        while (ptr != NULL) {
            if (ptr->isEngine()) {
                PushBack(train1, Remove(main_train, ptr));
                break;
            }
            ptr = ptr->next;
        }
        //adding cars to each new train
        TrainCar* temp = main_train;
        //CalculateSpeed(main_train) <= CalculateSpeed(train1) && temp->next != NULL &&
        while (temp->next != NULL) {
            if (temp->isEngine()) {
                temp = temp->next;
            } else {
                PushBack(train1, Remove(main_train, temp));
            }
            if (CountCars(main_train) == CountCars(train1) + 1) {
                break;
            }
        }
    }

    //Dealing with second train
    while(main_train != NULL) {
        PushBack(train2, PopFront(main_train));
    }
}