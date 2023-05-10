#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <cmath>

using namespace std;

namespace ariel{

    class Fraction{

        private:

            static const int Thousand = 1000;
            int upOfFraction;
            int downOfFraction;

            int greatestCommonDivisor(int first, int second) const {
                if (second == 0) {
                    return first;
                } 
                return greatestCommonDivisor(second, first % second);
            }
    
        public:

            Fraction(int upOfFraction , int downOfFraction);

            Fraction(float number): upOfFraction(static_cast<int>(Thousand * number)), downOfFraction(Thousand) {
                if (this->downOfFraction < 0) {
    
                    this->upOfFraction = -this->upOfFraction;
                    this->downOfFraction = -this->downOfFraction;
                }

                int gcd = greatestCommonDivisor(upOfFraction, downOfFraction);
                upOfFraction = upOfFraction/ gcd;
                downOfFraction = downOfFraction/ gcd;
                
            }
        
            Fraction():upOfFraction(0), downOfFraction(1){ 
            }
            
            /////////////////////////////////////////////////////////////////////

            static int multiply(int parameter1, int parameter2) {
                if (parameter2 > 0)
                {
                    if(parameter1 > numeric_limits<int>::max() / parameter2){
                        throw overflow_error("Error in Multiplication");
                    }
                    if(parameter1 < numeric_limits<int>::min() / parameter2){
                        throw overflow_error("Error in Multiplication");
                    }

                }            
                else if (parameter2 < 0)
                {
                    if(parameter1 < numeric_limits<int>::max() / parameter2){
                        throw overflow_error("Error in Multiplication");
                    }
                }
                else{
                    return 0;
                }
                int result = parameter1 * parameter2;
                return result;
            }

            static int add(int parameter1, int parameter2) {
                if (parameter2 > 0)
                {
                    if(parameter1 > (numeric_limits<int>::max() - parameter2)){
                        throw overflow_error("Error in Addition");
                    }                
                }
                
                if (parameter2 < 0)
                {
                    if(parameter1 < (numeric_limits<int>::min() - parameter2)){
                        throw overflow_error("Error in Addition ");
                    }
                    
                }    
                int result = parameter1 + parameter2;
                return result;
            }

            static int subtraction(int parameter1, int parameter2) {
                if (parameter2 < 0)
                {
                    if(parameter1 > numeric_limits<int>::max() + parameter2){
                        throw overflow_error("Error in Subtraction");
                    }
                }
                
                if (parameter2 > 0 )
                {
                    if(parameter1 < numeric_limits<int>::min() + parameter2){
                        throw overflow_error("Error in Subtraction overflow");
                    }
                }
                int result = (parameter1 - parameter2);
                return result ;
            }

            /////////////////////////////////////////////////////////////////////

            int getNumerator() const {
                return upOfFraction;
            }

            int getDenominator() const {
                return downOfFraction;
            }

            //////////////////////////////////////////////////////////////////////

            void reduce() {
                int gcd = greatestCommonDivisor(upOfFraction, downOfFraction);
                upOfFraction = upOfFraction/ gcd;
                downOfFraction = downOfFraction/ gcd;

                if (this->downOfFraction < 0) {
        
                this->upOfFraction = -this->upOfFraction;
                this->downOfFraction = -this->downOfFraction;
                }
            }

            //////////////////////////////////////////////////////////////////////

            Fraction& operator++();
            Fraction operator++(int);
            Fraction& operator--(); 
            Fraction operator--(int);

            //////////////////////////////////////////////////////////////////////

            Fraction operator-(const Fraction& FractionOther) const;
            Fraction operator-(const float& number) const;
            friend Fraction operator-(const float& number, const Fraction& FractionOther);

            //////////////////////////////////////////////////////////////////////

            Fraction operator+(const Fraction& FractionOther) const;
            Fraction operator+(const float& number) const;
            friend Fraction operator+(const float& number, const Fraction& FractionOther);

            //////////////////////////////////////////////////////////////////////

            Fraction operator*(const Fraction& FractionOther) const;
            Fraction operator*(const float& number)const;
            friend Fraction operator*(const float& number, const Fraction& FractionOther);

            //////////////////////////////////////////////////////////////////////

            Fraction operator/(const Fraction& FractionOther) const;
            Fraction operator/(const float& number)const;
            friend Fraction operator/(const float& number, const Fraction& FractionOther);

            //////////////////////////////////////////////////////////////////////

            bool operator==(const Fraction& FractionOther) const;
            bool operator==(const float& number)const;
            friend bool operator==(const float& number, const Fraction& FractionOther);

            //////////////////////////////////////////////////////////////////////

            bool operator<(const Fraction& FractionOther) const;
            bool operator<(const float& number)const;
            friend bool operator<(const float& number, const Fraction& FractionOther);

            ///////////////////////////////////////////////////////////////////////

            bool operator>(const Fraction& FractionOther) const;
            bool operator>(const float& number)const;
            friend bool operator>(const float& number, const Fraction& FractionOther);

            ///////////////////////////////////////////////////////////////////////

            bool operator>=(const Fraction& FractionOther) const;
            bool operator>=(const float& number)const;
            friend bool operator>=(const float& number, const Fraction& FractionOther);

            ///////////////////////////////////////////////////////////////////////

            bool operator<=(const Fraction& FractionOther) const;
            bool operator<=(const float& number)const;
            friend bool operator<=(const float& number, const Fraction& FractionOther);

            ///////////////////////////////////////////////////////////////////////

            friend ostream& operator<<(ostream& ostream, const Fraction& fraction);    
            friend istream& operator>>(istream& HeSheIt, Fraction& fraction);

            ///////////////////////////////////////////////////////////////////////

            string toString() const;

            ///////////////////////////////////////////////////////////////////////
        
    };
    
}
#endif