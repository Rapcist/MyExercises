#include"matrix.hpp"
#include "rational.cpp" //replace with .hpp when get used to Cmake's building
#include <cstddef>
#include <fstream>
#include <stdexcept>
#include<iostream>

using namespace std;
using namespace Math;
template<typename T>
void initMatrix(Matrix<T> & ob,int k = 0);

int main(){

    Matrix<Rational> one{3,3};
    ifstream fin("G:/Codes/matrix/input.txt");

    for(size_t i{0};i < 3; ++i){
        for(size_t j{0}; j < 3; ++j){
            fin>>one(i,j);
            //cout<<one(i,j);
        }
    }
    one.printMatrix();
    //initMatrix(one, 3);
    //two.printMatrix();
    //auto t {one * two};
    // t.printMatrix();
    // cout<<determinat(one);
    //one(0,1) = 3;
    //one(1,1) = 1;
    //one.printMatrix();
    //one = transposition(one);
    //one.printMatrix();
    //inverseMatrix(one);
    //auto invone {inverseMatrix(one)};
    //invone.printMatrix();
    //cout<<invone.getHeight();
    //(one * invone).printMatrix();
    /*for(size_t i{0}; i < one.getWidth(); ++i){
        for(size_t j{0}; j < one.getHeight();++j){
            auto minor {additionalMinor(one,i,j)};
            cout<<determinat(one);
        }
    }*/
    //auto minor {additionalMinor(one,0,0)};
    //minor.printMatrix();
    
    try{
    //cout<<determinant(one)<<endl;
    auto inv {inverseMatrix(one)};
    inv.printMatrix();
    auto tmp {inv * one};
    tmp.printMatrix();
    }catch(const invalid_argument & er){
        cerr<<er.what();
    }
    catch(const logic_error & er){
        cerr<<er.what();
    }
    //(one * inv).printMatrix();
    for(int i {0}; i < 10 ; ++i){
        cout<<fibNumber(i)<<' ';
    }
    return 0;
}
template<typename T>
void initMatrix(Matrix<T>& ob, int k)
{
    for(size_t i{0}; i < ob.getWidth(); ++i){
       for(size_t j{0}; j < ob.getHeight();++j){
           ob(i,j) = i+j+k;
       }
    }
}