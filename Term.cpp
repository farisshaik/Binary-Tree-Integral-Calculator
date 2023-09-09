//Faris Shaik

#include "Term.h"

#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <cmath>

bool Term::operator<(Term compare) const {      // overloaded operators for comparison in all recursive functions
    if(this->trig != 'X'){ return true;}
    else if(compare.trig != 'X'){ return false;}
    return this->exp < compare.exp;
}

bool Term::operator>(Term compare) const {
    if(this->trig != 'X'){ return false;}
    else if(compare.trig != 'X'){ return true;}
    return this->exp > compare.exp;
}

bool Term::operator==(Term compare) const {
    return (this->exp == compare.exp) and (this->trig == compare.trig);
}

Term &Term::operator+=(Term &add) {
    this->coeff += add.coeff;
    return* this;
}

Term::Term(int c, int e, char func) {       // constructor with coeff, exp, trig parameters
    coeff = c;
    exp = e;
    trig = func;
}

Term::Term() {      // default constructor
    coeff = 0;
    exp = 0;
    trig = 'X';
}

std::string Term::toString() const {                                // to string, integrates term and outputs
    int numerator = (int)coeff;
    int denominator = exp;
    if(trig == 'X'){ denominator++; }
    std::string expOut, frac, output;
    for (int i = abs(numerator * denominator); i > 1; i--) {        // simplify fractions
        if ((denominator % i == 0) and (numerator % i == 0)) {
            denominator /= i;
            numerator /= i;
        }
    }
    if(trig == 'X'){                                                // not a trig function
        double outCoeff = (double)numerator / denominator;          // divide by exp + 1 (integrating)
        int outExp = exp + 1;                                       // increase exponent by 1 (integrating)
        numerator < 0 ? numerator *= -1 : numerator;
        denominator < 0 ? denominator *= -1 : denominator;
        expOut = "x^" + std::to_string(outExp);
        frac = "(" + std::to_string(numerator) + "/" + std::to_string(denominator) + ")";           // fraction formatting
        if(numerator % denominator == 0){ frac = std::to_string(abs(numerator / denominator)); }
        if(frac == "1"){ frac = ""; }
        if(frac == "0"){ expOut = ""; }
        if(expOut == "x^1"){ expOut = "x"; }                                                                 // exponent formatting
        numerator < 0 ? numerator *= -1 : denominator < 0 ? denominator *= -1 : numerator;
        outCoeff < 0 ? output = "- " + frac + expOut : output = "+ " + frac + expOut;
        return output + " ";
    }
    else{
        double outCoeff = (double)numerator / denominator;              // trig function
        numerator < 0 ? numerator *= -1 : numerator;
        denominator < 0 ? denominator *= -1 : denominator;
        trig == 'C' ? expOut = "sin " + std::to_string(exp) + "x" : expOut = "cos " + std::to_string(exp) + "x";    // adding sin or cos to expOut
        output = "+ " + frac + expOut;
        frac = "(" + std::to_string(numerator) + "/" + std::to_string(denominator) + ")";
        if(numerator % denominator == 0){ frac = std::to_string(abs(numerator / denominator)); }                        // // fraction formatting
        if(frac == "1"){ frac = ""; }
        if(expOut.substr(3) == " 1x"){ expOut.replace(3, 6, " x"); }
        if((trig == 'C' and outCoeff < 0) or (trig == 'S' and outCoeff > 0)){ output = "- " + frac + expOut; }              // exponent formatting and checking for positive/ negative
        else{ output = "+ " + frac + expOut; }
        return output + " ";
    }
}

int Term::getExp() const {
    return exp;
}

double Term::getCoeff() const {
    return coeff;
}

char Term::getTrig() const {
    return trig;
}

void Term::setExp(int exp) {
    Term::exp = exp;
}

void Term::setCoeff(double coeff) {
    Term::coeff = coeff;
}

void Term::setTrig(char trig) {
    Term::trig = trig;
}

