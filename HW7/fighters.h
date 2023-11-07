//
// Created by suber on 3/18/2023.
//

#ifndef INC_7_FIGHTERS_H
#define INC_7_FIGHTERS_H

#include <string>
#include <utility>

class fighters {
public:
    //CONSTRUCTORS
    fighters(std::string aName, int aJab, int aFwd_t, int aUp_t,
             int aDown_t, int aFwd_s, int aUp_S, int aDown_s);
    fighters();
    //ACCESSORS
    std::string get_name() const {return name;};
    int get_jab() const {return jab;};
    int get_fwdT() const {return fwd_tilt;};
    int get_upT() const {return up_tilt;};
    int get_downT() const {return down_tilt;};
    int get_fwdS() const {return fwd_smash;};
    int get_upS() const {return up_smash;};
    int get_downS() const {return down_smash;};

private:
    std::string name;
    int jab;
    int fwd_tilt;
    int up_tilt;
    int down_tilt;
    int fwd_smash;
    int up_smash;
    int down_smash;
};
//so we can use in sets
bool operator<(const fighters& f1, const fighters& f2);

#endif //INC_7_FIGHTERS_H
