//
// Created by suber on 2/5/2023.
//

#include "Matrix.h"
#include <iostream>

//Constructor
Matrix::Matrix() {
    rows = 0;
    columns = 0;
    fill = 0.0;
    data = NULL;
}

Matrix::Matrix(const Matrix& m1) {
    rows = m1.num_rows();
    columns = m1.num_cols();

    //creating matrix of doubles on stack
    data = new double *[rows];
    for(unsigned int i=0; i < rows; i++){
        data[i] = new double[columns];
    }

    //setting all values to fill
    for(unsigned int i=0; i < rows; i++) {
        for(unsigned int j=0; j < columns; j++){
            double value;
            m1.get(i,j, value);
            data[i][j] = value;
        }
    }

}

Matrix::Matrix(const unsigned int& aRows, const unsigned int& aColumns, const double& aFill){
    rows = aRows;
    columns = aColumns;
    fill = aFill;

    //if either row or column is zero it will return a 0x0 matrix
    if(rows == 0 || columns == 0) {
        data = NULL;
    }

    else{
        //creating matrix of doubles on stack
        data = new double *[rows];
        for(unsigned int i=0; i < rows; i++){
            data[i] = new double[columns];
        }

        //setting all values to fill
        for(unsigned int i=0; i < rows; i++) {
            for(unsigned int j=0; j < columns; j++){
                data[i][j] = fill;
            }
        }
    }
}

//Deconstructors
//This is how I fixed my memory leaks
Matrix::~Matrix() {
    if (data != NULL) {
        for (unsigned int i = 0; i < rows; ++i) {
            delete [] data[i];
        }
        delete [] data;
        data = NULL;
    }
    rows = 0;
    columns = 0;
}

Matrix& Matrix::operator=(const Matrix& m) {
    if (*this != m) {
        if (data != NULL) {
            for (unsigned int i = 0; i < rows; ++i) {
                delete [] data[i];
            }
            delete [] data;
            data = NULL;
        }
        rows = 0;
        columns = 0;
    }
    create(m.num_rows(), m.num_cols(), 0);
    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < columns; ++j) m.get(i, j, data[i][j]);
    }
    return *this;
}

//Accessors
bool Matrix::get(const unsigned int& r, const unsigned int& c, double& value) const {
    //checking for valid inputs
    if(r > rows || c > columns) {
        return false;
    }
    //setting value
    value = data[r][c];
    return true;
}

//Other Functions
bool Matrix::set(const unsigned int& r, const unsigned int& c, double value) {
    //checking bounds
    if(r > rows || c > columns) {
        return false;
    }
    //setting value
    data[r][c] = value;
    return true;
}

void Matrix::clear() {
    //deallocating memory
    for(unsigned int i = 0; i < rows; i++){
        delete[] data[i];
    }
    delete[] data;
    data = NULL;
    //setting rows and columns to zero
    rows = 0;
    columns = 0;
}

//Simple Matrix Operations
void Matrix::multiply_by_coefficient(const double& coefficient){
    for(unsigned int i = 0; i < rows; i++) {
        for(unsigned int j = 0; j < columns; j++) {
            data[i][j] = data[i][j] * coefficient;
        }
    }
}


bool Matrix::swap_row(const unsigned int& source, const unsigned int& target){
    //checking bounds
    if(source > rows || target > rows) {
        return false;
    }
    //swapping rows if in bounds
    //creating temporary row used for the swap
    double* row1 = new double[columns];
    for(unsigned int i = 0; i < columns; i++){
        row1[i] = data[source][i]; //making trow = source row in original data
        data[source][i] = data[target][i]; //making source row = target row
    }
    for(unsigned int i = 0; i < columns; i++) {
        data[target][i] = row1[i];
    }
    delete [] row1;
    row1 = NULL;
    return true;
}

void Matrix::transpose(){

    //creating temporary matrix to create transposed matrix
    double** data1 = new double*[columns];
    //adding data to data1
    for (unsigned int i = 0; i < columns; i++) {
        data1[i] = new double[rows];
        for (unsigned int j = 0; j < rows; j++){
            data1[i][j] = data[j][i];
        }
    }

    //deleting un-needed memory from original data
    for(unsigned int i = 0; i < rows; i++) {
        delete [] data[i];
    }
    delete [] data;
    data = NULL;
    //making data equal to new data found
    data = data1;
    //swapping rows and columns for other functions
    unsigned int r, c;
    r = rows;
    c = columns;
    rows = c;
    columns = r;
}

//Binary Matrix Operations
bool Matrix::add(const Matrix& m2) {
    unsigned int rows2 = m2.num_rows();
    unsigned int columns2 = m2.num_cols();
    //making sure both matrix are same dimension
    if((rows == rows2) && (columns == columns2)) {
        for(unsigned int i = 0; i < rows; i++) {
            for(unsigned int j = 0; j < columns; j++) {
                double value;
                m2.get(i,j,value);
                data[i][j] += value;
            }
        }
        return true;
    }
    else {
        return false;
    }
}

bool Matrix::subtract(const Matrix& m2) {
    unsigned int rows2 = m2.num_rows();
    unsigned int columns2 = m2.num_cols();
    //making sure both matrix are same dimension
    if((rows == rows2) && (columns == columns2)) {
        for(unsigned int i = 0; i < rows; i++) {
            for(unsigned int j = 0; j < columns; j++) {
                double value;
                m2.get(i,j,value);
                data[i][j] -= value;
            }
        }
        return true;
    }
    else {
        return false;
    }
}

//Operators
bool Matrix::operator== (const Matrix& m2) const {
    unsigned int rows2 = m2.num_rows();
    unsigned int columns2 = m2.num_cols();
    //check if dimensions are the same for both matricies
    if((rows != rows2) || (columns != columns2)) {
        return false;
    }
    else {
        for(unsigned int i = 0; i < rows; i++) {
            for(unsigned int j = 0; j < columns; j++) {
                //getting value from m2
                double value;
                m2.get(i,j,value);
                if(data[i][j] != value) {
                    return false;
                }
            }
        }
        return true;
    }
}

bool Matrix::operator!= (const Matrix& m2) const {
    unsigned int rows2 = m2.num_rows();
    unsigned int columns2 = m2.num_cols();
    //check if dimensions are the same for both matricies
    if((rows != rows2) || (columns != columns2)) {
        return true;
    }
    else {
        for(unsigned int i = 0; i < rows; i++) {
            for(unsigned int j = 0; j < columns; j++) {
                //getting value from m2
                double value;
                m2.get(i,j,value);
                if(data[i][j] != value) {
                    return true;
                }
            }
        }
        return false;
    }
}

//Harder Operations
double* Matrix::get_row(const unsigned int& r) const {
    //Checking if r is in bounds
    if(r > rows || r < 0) {
        return NULL;
    }
    else {
        //creating pointer that will hold the row info
        double* pointer = new double[columns];
        //adding whole row to pointer
        for(unsigned int i = 0; i < columns; i++) {
            pointer[i] = data[r][i];
        }
        return pointer;
    }
}

double* Matrix::get_col(const unsigned int& c) const {
    //Checking if r is in bounds
    if(c > columns || c < 0) {
        return NULL;
    }
    else {
        //creating pointer that will hold the columns info
        double* pointer = new double[rows];
        //adding whole column to pointer
        for(unsigned int i = 0; i < rows; i++) {
            pointer[i] = data[i][c];
        }
        return pointer;
    }
}

Matrix* Matrix::quarter() {
    //Creating matrix pointer that holds all four matricies
    Matrix *matrix_pointer = new Matrix[4];
    //creating row and columns value for each quarter
    unsigned int half_r = rows/2;
    unsigned int r = half_r + rows % 2;
    unsigned int half_c = columns/2;
    unsigned int c = half_c + columns % 2;
    //creating 4 matrix inside pointer
    matrix_pointer[0].create(r,c,0);
    matrix_pointer[1].create(r,c,0);
    matrix_pointer[2].create(r,c,0);
    matrix_pointer[3].create(r,c,0);
    //Upper Left
    for(unsigned int i = 0; i < r; i++) {
        for(unsigned int j = 0; j < c; j++) {
            matrix_pointer[0].set(i,j,data[i][j]);
        }
    }
    //Upper Right
    for(unsigned int i = 0; i < r; i++) {
        for(unsigned int j = 0; j < c; j++) {
            matrix_pointer[1].set(i,j,data[i][j+half_c]);
        }
    }
    //Lower Left
    for(unsigned int i = 0; i < r; i++) {
        for(unsigned int j = 0; j < c; j++) {
            matrix_pointer[2].set(i,j,data[i+half_r][j]);
        }
    }
    //Lower Right
    for(unsigned int i = 0; i < r; i++) {
        for(unsigned int j = 0; j < c; j++) {
            matrix_pointer[3].set(i,j,data[i+half_r][j+half_c]);
        }
    }

    return matrix_pointer;
}

//Private function used to create the Matricies in quarter function
//This is pretty much the same function as the constructor but allows me to use it as a dot function
void Matrix::create(const unsigned int& r, const unsigned int& c, const double& f) {
    rows = r;
    columns = c;
    fill = f;
    //if either row or column is zero it will return a 0x0 matrix
    if(rows == 0 || columns == 0) {
        data = NULL;
        delete [] data;
    }

    else {
        //creating matrix of doubles on stack
        data = new double *[rows];
        for(unsigned int i=0; i < rows; i++){
            data[i] = new double[columns];
        }

        //setting all values to fill
        for(unsigned int i=0; i < rows; i++) {
            for(unsigned int j=0; j < columns; j++){
                data[i][j] = f;
            }
        }
    }
}

//Overload operator
std::ostream& operator<< (std::ostream& out, const Matrix& m) {
    //initializing rows and columns
    unsigned int r = m.num_rows();
    unsigned int c = m.num_cols();

    //outputting to file
    //everything before the data in matrix
    out << std::endl << r << " x " << c << " matrix:" << std::endl << "[ ";
    //data in matrix
    for(unsigned int i = 0; i < r; i++) {
        for(unsigned int j = 0; j < c; j++) {
            double value;
            m.get(i, j, value);
            out << value << " ";
        }
        //printing new line if it is not last row
        if(i != r-1) {
            out << std::endl;
        }
    }
    out << "]" << std::endl;
    return out;
}
