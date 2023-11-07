//
// Created by suber on 3/18/2023.
//

#include "fighters.h"

//CONSTRUCTORS
//default
fighters::fighters() {
    name = "default";
    jab = 0;
    fwd_tilt = 0;
    up_tilt = 0;
    down_tilt = 0;
    fwd_smash = 0;
    up_smash = 0;
    down_smash = 0;
}
//normal
fighters::fighters(std::string aName, int aJab, int aFwd_t, int aUp_t,
                   int aDown_t, int aFwd_s, int aUp_S, int aDown_s) {
        name = aName;
        jab = aJab;
        fwd_tilt = aFwd_t;
        up_tilt = aUp_t;
        down_tilt = aDown_t;
        fwd_smash = aFwd_s;
        up_smash = aUp_S;
        down_smash = aDown_s;
}

//OVERLOAD OPERATORS
//this is important because it allows us to use this class in sets
bool operator< (fighters const& f1, fighters const& f2) {
    return f1.get_name() < f2.get_name();
}


