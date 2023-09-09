//Faris Shaik

#ifndef TERM_H
#define TERM_H

#include <string>

class Term {

private:

    int exp;
    double coeff;
    char trig;

public:

    Term();
    Term(int, int, char);
    bool operator < (Term) const;
    bool operator > (Term) const;
    bool operator == (Term) const;
    Term& operator += (Term& add);
    std::string toString() const;
    int getExp() const;
    double getCoeff() const;
    char getTrig() const;
    void setExp(int exp);
    void setCoeff(double coeff);
    void setTrig(char trig);

};


#endif //TERM_H
