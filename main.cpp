//Faris Shaik

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <sstream>
#include <cstdlib>

#include "Node.h"
#include "BinTree.h"
#include "Term.h"

using namespace std;

int main() {

    void standardizeInput(string&);                         // pass in string to remove all spaces, then add them back in a consistent manner
    string definiteAnswer(vector<Term>, pair<int, int>);    // returns integral suffix with definite integral bounds and calculated value (ex. ", 1|4 = 35.250")
    pair<int, int> termCoeffExp(string&);                   // returns pair of ints for COEFF and EXPONENT values in a regular term of integral
    pair<int, int> trigCoeffs(string&);                     // returns pair of ints for COEFF and EXPONENT values in a trigonometric term of integral

    string filename, in;
    bool definite;
    pair<int, int> bounds;
    ifstream reader;

    cout << "Enter input filename:" << endl;                // prompt user for filename and open file
    cin >> filename;
    //filename = "/Users/faris/Code/CS2337/project3/test.txt";
    reader.open(filename);

    if(reader){                                             // if reader opened successfully
        while(getline(reader, in)){
            BinTree<Term> eqn;
            string integral;
            if(in[0] == '|'){ definite = false; }           // if first char is |, then definite
            else{
                bounds.first = atoi(in.substr(0, in.find('|')).c_str());                                 // assign upper and lower bounds of equation
                bounds.second = atoi(in.substr(in.find('|')+1, in.find(' ')).c_str());
                definite = true;                                                                                    // set DEFINITE boolean to true
            }

            standardizeInput(in);                                                                                // call function so input string can have consistent spacing

            while(!in.empty()){                                                                                     // when coeff and exp are found, term is removed from input string
                char termType;                                                                                      // char X for regular term, C for cosine, S for sin
                if(in[0] == ' '){ in.erase(0, 1); }
                if(in.substr(0, in.find(' ')).find("cos") != string::npos ){ termType = 'C'; }
                else if(in.substr(0, in.find(' ')).find("sin") != string::npos ){ termType = 'S'; }
                else{ termType = 'X'; }
                pair<int, int> termData;                                                                            // pair of ints for COEFFICIENT and EXPONENT values
                termType == 'X' ? termData = termCoeffExp(in) : termData = trigCoeffs(in);
                Term inTerm(termData.first, termData.second, termType);                                             // new term with values determined above
                eqn.insert(inTerm);                                                                              // insert into BST
            }

            for(auto currTerm: eqn.inOrderTraversal()) { integral += currTerm.toString(); }                   // inorder traversal of BST and add to integral output string

            // formatting if negative and/or parenthesis out front
            integral[0] == '-' ? integral[2] == '(' ? integral.replace(0, 3, "(-") : integral.replace(0,2, "-") : integral.erase(0, 2);

            // print integral and bounds/ value (if definite) or "+C" if indefinite
            definite ? cout << integral.erase(integral.size()-1) << definiteAnswer(eqn.inOrderTraversal(), bounds) << endl : cout << integral << "+ C" << endl;

        }
    }
    else{
        cout << "Unable to open " << filename << endl;                                                               // file did not open
    }

    return 0;
}

string definiteAnswer(vector<Term> terms, pair<int, int> bounds){   // returns integral suffix with definite integral bounds and calculated value (ex. ", 1|4 = 35.250")
    double upperSum = 0;
    double lowerSum = 0;
    for(auto i: terms){
        lowerSum += (i.getCoeff())/(i.getExp()+1) * pow(bounds.first, i.getExp()+1);   // calculated value of upper bound integral
        upperSum += (i.getCoeff())/(i.getExp()+1) * pow(bounds.second, i.getExp()+1);  // calculated value of lower bound integral
    }

    double outIntegral = (round(1000.0*(upperSum-lowerSum)))/1000.0 ;                                // get the different of the two sums
    std::stringstream stream;
    stream << ", " << bounds.first << "|" << bounds.second << " = " << std::fixed << std::setprecision(3) << outIntegral; // round to 3 digits
    return stream.str();
}

void standardizeInput(string& in) {        // pass in string to remove all spaces, then add them back in a consistent manner
    bool modify;
    string out;
    in = in.substr(in.find(' '));
    while(in.find(' ') != string ::npos){ // remove all the spaces in the string
        int i = static_cast<int>(in.find(' '));
        in.replace(i, 1, "");
    }
    for(char c:in){                                         // go character by character
        if(c == '+'){ out += ' '; }                         // space between adding different terms
        else if(c == '-' and !modify){ out += " -"; }       // if minus (and not part of current term) add space and minus
        else if(c == 'd'){                                  // if 'dx' has been reached
            in = out;
            if(in[0]==' '){in = in.substr(1);}         // return all terms and exit
            return;
        }
        else{ out += c; }                                   // add current character to out
        modify = (c == '-' or c == '+' or c == '^');        // making sure - is not part of term
    }
}

pair<int, int> termCoeffExp(string& in){                                    // returns pair of ints for COEFF and EXPONENT values in a regular term of integral
    pair<int, int> out;
    string temp;
    int coeff, exp;
    if(in[0]==' '){ in.erase(0,1); }
    temp = in.substr(0, in.find(' '));
    if(temp.find('x') != string::npos){
        coeff = atoi(temp.substr(0,temp.find('x')).c_str());     // coeff = value before x
        if(coeff == 0){ coeff = 1; }                                        // cover all special cases (like no coeff and negative)
        if(temp[0] == '-' and temp[1] == 'x'){ coeff = -1; }
        temp.erase(0,temp.find('x')+2);
        exp = atoi(temp.substr(0,temp.size()).c_str());
        if(exp == 0){ exp = 1; }
    }
    else{
        coeff = atoi(temp.substr(0,temp.size()).c_str());           // if constant term
        exp = 0;                                                            // set coeff, and exp = 0
    }
    in.erase(0, in.find(' '));                                   // remove currently parsed term so next term can be parsed from zero index
    out.first = coeff;
    out.second = exp;
    return out;
}

pair<int, int> trigCoeffs(string& in){                                      // returns pair of ints for COEFF and EXPONENT values in a trigonometric term of integral
    pair<int, int> out;
    string temp;
    int coeff, exp;
    if(in[0]==' '){ in.erase(0,1); }
    temp = in.substr(0, in.find(' '));
    temp.find('c') != string::npos ? temp.insert(temp.find('s')+1, " ") : temp.insert(temp.find('n')+1, " ");   // insert space after sin/cos for easier parsing
    if(temp.substr(0, 2) == "-s" or temp.substr(0, 2) == "-c"){ coeff = -1; }                                            // set coeff for -sin / -cos
    else if(!isdigit(temp[1])){ coeff = 1; }                                                                                          // if second char is not digit, coeff is 1
    else{ coeff = atoi(temp.substr(0, temp.find(' ') - 3).c_str()); }                                                         // find coeff
    isdigit(temp[temp.find(' ')+1]) ? exp = atoi(temp.substr(temp.find(' ')+1, temp.find('x')).c_str()) : exp = 1;   // exp value is value before x
    out.first = coeff;
    out.second = exp;
    in.erase(0, in.find(' '));                                                                                                // remove currently parsed term so next term can be parsed from zero index
    return out;
}