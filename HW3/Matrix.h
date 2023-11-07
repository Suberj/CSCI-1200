//
// Created by suber on 2/5/2023.
//

#ifndef DATASTRUCTURES_MATRIX_H
#define DATASTRUCTURES_MATRIX_H
#include <fstream>

class Matrix {
public:
    //Constructor
    Matrix();
    Matrix(const Matrix& m1);
    Matrix(const unsigned int& aRows, const unsigned int& aColumns, const double& aFill);

    //Deconstructors to help with memory leaks
    ~Matrix();
    Matrix& operator=(const Matrix& m);


    //Accessors
    const unsigned int& num_rows() const {return rows;}
    const unsigned int& num_cols() const {return columns;}
    bool get(const unsigned int& r, const unsigned int& c, double& value) const;

    //Other functions
    void clear();
    bool set(const unsigned int& r, const unsigned int& c, double value);

    //Simple Matrix Operations
    void multiply_by_coefficient(const double& coefficient);
    bool swap_row(const unsigned int& source, const unsigned int& target);
    void transpose();

    //Binary Matrix Operations
    bool add(const Matrix& m2);
    bool subtract(const Matrix& m2);

    //Operators
    bool operator== (const Matrix& m2) const;
    bool operator!= (const Matrix& m2) const;

    //Harder Operations
    double* get_row(const unsigned int& r) const;
    double* get_col(const unsigned int& c) const;
    Matrix* quarter();

private:
    //Used in quarter function
    void create(const unsigned int& r,const unsigned int& c, const double& f);

    //Variables
    unsigned int rows;
    unsigned int columns;
    double fill; //default value for the matrix
    double **data; //hold matrix
};

//Overload operator
std::ostream& operator<< (std::ostream& out, const Matrix& m);


#endif //DATASTRUCTURES_MATRIX_H
