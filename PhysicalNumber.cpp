#include <iostream>
#include <stdexcept>
#include "PhysicalNumber.h"

using namespace std;
using ariel::Dimension, ariel::PhysicalNumber;

bool ariel::notEquals(const Dimension& alpha ,const Dimension& beta){
    if(alpha!=beta) return true;
    return false;
}

ariel::PhysicalNumber::PhysicalNumber(double amount, Unit some_unit){
    _unit = some_unit;
    _amount = amount;
}

ostream& ariel::operator<<(ostream& os, const PhysicalNumber& num) {
    return os<<num._amount<<type[int(num._unit)];
}

    //Input operator, example: istringstream input("700[kg]"); input >> a;
istream& ariel::operator>> (istream& is, PhysicalNumber& num){
   std::ios::pos_type firstset = is.tellg();
        double x;
        std::string temp;

        if (!(is>>x))  {
            auto err = is.rdstate();
            is.clear(); 
            is.seekg(firstset); 
            is.clear(err); 
            return is;
        }

        is >>temp;
           int i = 0;
           bool b = false;
           while (i<9) {
               i++;
               if (i==9) 
                {
                    auto errorState = is.rdstate();
                    is.clear(); 
                    is.seekg(firstset);
                    is.clear(errorState); 
                    return is;
                }
                if(temp.compare(type[i])==0)
                {
                    num._unit=Unit(i);
                    i = 9;
                    b = true;
                }
            }
   num._amount = x;
   return is;
}

const PhysicalNumber ariel::PhysicalNumber::operator+(const PhysicalNumber& other)const {
        if ((int(other._unit)/3)!=(int(this->_unit))/3) throw std::runtime_error("different units");
        
        double curr_yahas = yahas[int(other._unit)]/yahas[int(this->_unit)];
        return PhysicalNumber(other._amount*curr_yahas+this->_amount,this->_unit);
}
const PhysicalNumber ariel::PhysicalNumber::operator-(const PhysicalNumber& other)const {
    if ((int(other._unit)/3)!=(int(this->_unit))/3) throw std::runtime_error("different units");
        
        double curr_yahas = yahas[int(other._unit)]/yahas[int(this->_unit)];
        return PhysicalNumber(this->_amount-other._amount*curr_yahas,this->_unit);
}

PhysicalNumber& PhysicalNumber::operator+=(const PhysicalNumber& other){
    if ((int(other._unit)/3)!=(int(this->_unit))/3) throw std::runtime_error("different units");
        
        double curr_yahas = yahas[int(other._unit)]/yahas[int(this->_unit)];
        this->_amount = other._amount*curr_yahas+this->_amount;
        return *this;
}

PhysicalNumber& PhysicalNumber::operator-=(const PhysicalNumber& other){
    if ((int(other._unit)/3)!=(int(this->_unit))/3) throw std::runtime_error("different units");
        
        double curr_yahas = yahas[int(other._unit)]/yahas[int(this->_unit)];
        this->_amount = this->_amount-other._amount*curr_yahas;
        return *this;
}

//the unary+
const PhysicalNumber ariel::PhysicalNumber::operator+()const {
    return PhysicalNumber(this->_amount, this->_unit);
}
//the unary-
const PhysicalNumber ariel::PhysicalNumber::operator-()const {
    return PhysicalNumber(-1*(this->_amount), this->_unit);
}

bool ariel::operator==(const PhysicalNumber& first,const PhysicalNumber& second){
    if ((int(first._unit)/3)!=(int(second._unit))/3) throw std::runtime_error("the units dont match (==)");
    return ((first._amount * yahas[int(first._unit)] == (second._amount * yahas[int(second._unit)])));
}

bool ariel::operator!=(const PhysicalNumber& first,const PhysicalNumber& second) {
    if ((int(first._unit)/3)!=(int(second._unit))/3) throw std::runtime_error("the units dont match (!=)");
    return ((first._amount * yahas[int(first._unit)] != (second._amount * yahas[int(second._unit)])));
}

bool ariel::operator>(const PhysicalNumber& first,const PhysicalNumber& second){
    if ((int(first._unit)/3)!=(int(second._unit))/3) throw std::runtime_error("the units dont match (>)");
    double x,y;
    x = first._amount * yahas[int(first._unit)];
    y = second._amount * yahas[int(second._unit)];
    if(x>y) return true;
    return false;
}

bool ariel::operator<(const PhysicalNumber& first,const PhysicalNumber& second){
    if ((int(first._unit)/3)!=(int(second._unit))/3) throw std::runtime_error("the units dont match (<)");
    double x,y;
    x = first._amount * yahas[int(first._unit)];
    y = second._amount * yahas[int(second._unit)];
    if(x<y) return true;
    return false;
}

bool ariel::operator>=(const PhysicalNumber& first,const PhysicalNumber& second){
    if ((int(first._unit)/3)!=(int(second._unit))/3) throw std::runtime_error("the units dont match (>=)");
    double x,y;
    x = first._amount * yahas[int(first._unit)];
    y = second._amount * yahas[int(second._unit)];
    if(x>=y) return true;
    return false;
}

bool ariel::operator<=(const PhysicalNumber& first,const PhysicalNumber& second){
    if ((int(first._unit)/3)!=(int(second._unit))/3) throw std::runtime_error("the units dont match (<=>=)");
    double x,y;
    x = first._amount * yahas[int(first._unit)];
    y = second._amount * yahas[int(second._unit)];
    if(x<=y) return true;
    return false;
}

const PhysicalNumber PhysicalNumber::operator++(int){
    PhysicalNumber a(this->_amount,this->_unit);
    this->_amount= this->_amount+1;
    return a;
}

const PhysicalNumber PhysicalNumber::operator--(int){
    PhysicalNumber a(this->_amount,this->_unit);
    this->_amount= this->_amount-1;
    return a;
}

PhysicalNumber& PhysicalNumber::operator++(){
    this->_amount = this->_amount + 1;
    return *this;
}

PhysicalNumber& PhysicalNumber::operator--(){
    this->_amount = this->_amount - 1;
    return *this;
}
