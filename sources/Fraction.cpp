#include "Fraction.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <limits>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

namespace ariel{  

    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////  

    Fraction::Fraction(int numerator, int denominator) {
        if (!denominator) {
            throw invalid_argument("Denominator is zero.");
        }

        this->upOfFraction = numerator / greatestCommonDivisor(numerator, denominator);
        this->downOfFraction = denominator / greatestCommonDivisor(numerator, denominator);

        if (this->downOfFraction < 0) {
            
            this->upOfFraction = -this->upOfFraction;
            this->downOfFraction = -this->downOfFraction;
        }
    }
    
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////

    Fraction& Fraction::operator++() {// ++a
        this->upOfFraction = this->upOfFraction + this->downOfFraction;
        reduce();
        Fraction& result = *this;
        return result;
    }

    Fraction Fraction::operator++(int) { //a++
        Fraction param(this->upOfFraction, this->downOfFraction);
        ++(*this);
        return param;
    }

    Fraction& Fraction::operator--() {
        this->upOfFraction = this->upOfFraction - this->downOfFraction;
        reduce();
        Fraction& result = *this;
        return result;
    }

    Fraction Fraction::operator--(int) {
        Fraction param(this->upOfFraction, this->downOfFraction);
        --(*this);
        return param; 
    }

    //////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////

    Fraction Fraction::operator+(const Fraction& other) const {

        int other1 = other.downOfFraction;
        int mult1 = multiply(this->upOfFraction, other1);
        int other2 = other.upOfFraction;
        int mult2 = multiply(other2, this->downOfFraction);
    
        return Fraction(add(mult1, mult2), multiply(downOfFraction, other.downOfFraction));
    }

    Fraction Fraction::operator+(const float& number) const{
        Fraction One = *this;
        Fraction Two(number);
        return One + Two;
    }

    Fraction operator+(const float& number, const Fraction& FractionOther){

        Fraction One(number);
        Fraction Two = FractionOther;
        return One + Two;
    }
    /////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////

    Fraction Fraction::operator-(const Fraction& other) const {

        int other1 = other.downOfFraction;
        int mult1 = multiply(this->upOfFraction, other1);
        int other2 = other.upOfFraction;
        int mult2 = multiply(other2, this->downOfFraction);

        return Fraction(subtraction(mult1, mult2), multiply(downOfFraction, other.downOfFraction));
    }
    Fraction Fraction::operator-(const float& number) const{
        Fraction One = *this;
        Fraction Two(number);
        return One - Two;
    }

    Fraction operator-(const float& number, const Fraction& FractionOther){
        Fraction One(number);
        Fraction Two = FractionOther;
        return One - Two;
    }


    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////

    Fraction Fraction::operator*(const Fraction& other) const {

        return Fraction(multiply(upOfFraction, other.upOfFraction), multiply(downOfFraction, other.downOfFraction));
    }

    Fraction Fraction:: operator*(const float& number) const{

        Fraction One = *this;
        Fraction Two(number);
        return One *Two;

    }
    Fraction operator*(const float& number, const Fraction& FractionOther){

        Fraction One(number);
        Fraction Two = FractionOther;
        return One * Two;
    }

    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////

    Fraction Fraction::operator/(const Fraction& other) const {
        if (!other.upOfFraction)
            throw runtime_error("denominator is zero");

        return Fraction(multiply(upOfFraction, other.downOfFraction), multiply(downOfFraction, other.upOfFraction));
    }

    Fraction Fraction:: operator/(const float& number) const{
        if (!number)
            throw runtime_error("denominator is zero");

        Fraction One = *this;
        Fraction Two(number);
        return One /Two;

    }

    Fraction operator/(const float& number, const Fraction& FractionOther){
        if (!FractionOther.upOfFraction)
            throw runtime_error("denominator is zero");

        Fraction One(number);
        Fraction Two = FractionOther;
        return One / Two;
    }

    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////

    bool Fraction:: operator==(const Fraction& other) const {
        bool upOf= (this->upOfFraction == other.upOfFraction);
        bool downOf= (this->downOfFraction == other.downOfFraction);
        return upOf == true && downOf == true;
    }

    bool Fraction:: operator==(const float& number) const{
        Fraction One = *this;
        Fraction Two(number);
        return One == Two;
    }

    bool operator==(const float& number, const Fraction& FractionOther){
        
        Fraction One(number);
        Fraction Two = FractionOther;
        return One == Two;
    }

    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////

    bool Fraction::operator<(const Fraction& other) const {
        float upUpdate = static_cast<float>(upOfFraction);
        float upUpdatOther = static_cast<float>(other.upOfFraction);
        return (upUpdate / downOfFraction) < (upUpdatOther / other.downOfFraction);
    }

    bool Fraction:: operator<(const float& number) const{
        Fraction One = *this;
        Fraction Two(number);
        return One < Two;
    }

    bool operator<(const float& number, const Fraction& FractionOther){
        Fraction One(number);
        Fraction Two = FractionOther;
        return One < Two;
    }

    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////


        bool Fraction::operator>(const Fraction& other) const {
        float upUpdate = static_cast<float>(upOfFraction);
        float upUpdatOther = static_cast<float>(other.upOfFraction);
        return (upUpdate / downOfFraction) > (upUpdatOther / other.downOfFraction);
    }

    bool Fraction::operator>(const float& number) const{
        Fraction One = *this;
        Fraction Two(number);
        return One > Two;
    }

    bool operator>(const float& number, const Fraction& FractionOther){
        Fraction One(number);
        Fraction Two = FractionOther;
        return One > Two;
    }

    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    
    bool Fraction::operator>=(const Fraction& other) const {

        return (*this > other)|| (*this == other);
    }

    bool Fraction::operator>=(const float& number)const {
        Fraction One = *this;
        Fraction Two(number);
        return One >= Two;
    }

    bool operator>=(const float& number, const Fraction& FractionOther){
        Fraction One(number);
        Fraction Two = FractionOther;
        return One >= Two;
    }

    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////

    bool Fraction::operator<=(const Fraction& other) const {
        return (*this < other) || (*this == other);
    }

    bool Fraction::operator<=(const float& number) const {
        Fraction One = *this;
        Fraction Two(number);
        return One <= Two;
    }

    bool operator<=(const float& number, const Fraction& FractionOther){
        Fraction One(number);
        Fraction Two = FractionOther;
        return One <= Two;
    }   

    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////

    std::ostream& operator<<(std::ostream& ostream, const Fraction& fraction) {
        int down = fraction.downOfFraction;
        int up = fraction.upOfFraction;
        return (ostream << up << '/' << down);
    }
            
    std::istream& operator>>(std::istream& HeSheIt, Fraction& fraction) {//??
        int up = 0, down = 0;
        HeSheIt >> up >> down;

        if (down == 0 || HeSheIt.fail() == true){
            throw runtime_error("Error");
        }

        else if (down >0){
            fraction.upOfFraction = up;
            fraction.downOfFraction = down;
            fraction.reduce();
        }
        else{
            fraction.upOfFraction = -up;
            fraction.downOfFraction = -down;
        }

        return HeSheIt;
    }

    //////////////////////////////////////////////////////////////////////////////////

    std::string Fraction::toString() const {
        std::ostringstream oss;
        oss << upOfFraction << "/" << downOfFraction;
        return oss.str();
    }

    //////////////////////////////////////////////////////////////////////////////////
}