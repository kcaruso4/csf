#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include "calc.h"


using std::map;
using std::string;
using std::cout;
using std::endl;
using std::stringstream;
using std::vector;

struct Calc {
};

class CalcImpl : public Calc {
    public:
        CalcImpl() {};

        ~CalcImpl() {};

        int evalExpr(const char *expr, int &result) {
            vector<string> sepEx;
            stringstream s(expr);
            string tok;
            while (s >> tok) {
                sepEx.push_back(tok);
            }
            if (sepEx.size() == 0) {

                return 0;
            }
            else if (sepEx.size() == 1) {
                return single(sepEx, result);
            }
            else if (sepEx.size() == 3) {
                return triple(sepEx, result);
            }
            else if (sepEx.size() == 5) {
                return five(sepEx, result);
            }
            else {

                return 0;
            }
        }

    private:

        map<string, int> vars;

        /* Converts a given string to an integer */
        int convertToInt(string str) {
            stringstream ss(str);
            int val;
            ss >> val;
            return val;
        }

        /* Checks to see if the string passed in is only made of char A-Z or a-z */
        bool checkValidVar(string name) {
            for (unsigned int i = 0; i < name.length(); i++) {
                if (name[i] >= 65 && name[i] <= 90) {
                    continue;
                }
                else if (name[i] >= 97 && name[i] <= 122) {
                    continue;
                }
                else {
                    return false;
                }
            }
            return true;
        }

        /* Checks if the given string is only made of chars 0-9 */
        bool checkValidNum(string name) {
            if (!(name[0] == 45 || (name[0] >= 48 && name[0] <= 57))) {
                return false;
            }
            for (unsigned int i = 1; i < name.length(); i++) {
                if (name[i] >= 48 && name[i] <= 57) {
                    continue;
                }
                else {
                    return false;
                }
            }
            return true;
        }

        /* Checks to see if the given string is a valid op */
        bool checkValidOp(string op) {
            if (op.length() == 1) {
                if (op == "-" || op == "+" || op == "*" || op == "/") {
                    return true;
                }
                else {
                    return false;
                }
            }
            return false;
        }

        /* This function checks to make sure the operation is valid (not divide by zero)
        * and computes the value and saves it
        */
        int compute(int first, string op, int second, int &result) {
            if (second == 0 && op == "/") {
                return 0;
            }
            else if (op == "+") {
                result = first + second;
                return 1;
            }
            else if (op == "-") {
                result = first - second;
                return 1;
            }
            else if (op == "*") {
                result = first * second;
                return 1;
            }
            else {
                result = first / second;
                return 1;
            }
        }

        /* Is called when there is only one operand in the calculator expression
        * Checks to see if the one operand is a valid var name or integer val
        * If it's an integer, sets the result to the value. If it's a valid var name
        * checks to see if the value is saved in the map and if it is will set the result
        * to the stored value. If neither of those are true will print to system error "Error"
        */
        int single(vector<string> ops, int &result) {
            string first = ops[0];
            //if the only op  is a number
            if (checkValidNum(first)) {
                result = convertToInt(first);
                return 1;
            }
            //if the only op is a variable name
            else if (checkValidVar(first)) {
                if (vars.count(first) > 0) {
                    result = vars[first];
                    return 1;
                }
                //if not contained in map then error
                else {
                    return 0;
                }
            }
            //error if otherwise
            else {
                return 0;
            }
        }
        /* This function handles two cases: operand op operand or var = operand
        * it will first check to see if the first value in the vector is a number
        * if it is a number it will check to see if the other vector elements satisfy
        * the required conditions and will compute accordingly. Else the function will
        * follow the second situation and compute accordingly
        */
        int triple(vector<string> ops, int &result) {
            //Checks to see if the first element is a valid number
            if (checkValidNum(ops[0])) {
                int firstNum = convertToInt(ops[0]);
                int secondNum;
                //check to see if the operation is valid
                if (!checkValidOp(ops[1])) {
                    return 0;
                }
                //checks to see if the second operand is a valid number
                if (checkValidNum(ops[2])) {
                    secondNum = convertToInt(ops[2]);
                }
                else if (checkValidVar(ops[2])) {
                    if (vars.count(ops[2]) > 0) {
                        secondNum = vars[ops[2]];
                    }
                    else {
                        return 0;
                    }
                }
                else {
                    return 0;
                }
                return compute(firstNum, ops[1], secondNum, result);
            }
            //checks to see if the first value is a valid variable name
            else if (checkValidVar(ops[0])) {
                //checks to see if we are setting the variable to a value
                if (ops[1] == "=") {
                    //checks to make sure the second operand is a valid number
                    if (checkValidNum(ops[2])) {
                        vars[ops[0]] = convertToInt(ops[2]);
                        result = vars[ops[0]];
                        return 1;
                    }
                    //checks to see if the second operand is a value
                    else if (checkValidVar(ops[2])) {
                        if (vars.count(ops[2]) > 0) {
                            vars[ops[0]] = vars[ops[2]];
                            result = vars[ops[0]];
                            return 1;
                        }
                        else {
                            return 0;
                        }
                    }
                    else {
                        return 0;
                    }
                }
                //checks to see if the operand is a valid operator
                else if (checkValidOp(ops[1])) {
                    //checks to make sure the variable is mapped to
                    int secondNum;
                    if (vars.count(ops[0]) > 0) {
                        //checks to see if the second operand is a valid number
                        if (checkValidNum(ops[2])) {
                            secondNum = convertToInt(ops[2]);
                        }
                        //checks to see if the second operand is a valid variable
                        else if (checkValidVar(ops[2])) {
                            //checks to see if the variable is mapped to
                            if (vars.count(ops[2]) > 0) {
                                secondNum = vars[ops[2]];
                            }
                            else {
                                return 0;
                            }
                        }
                        else {
                            return 0;
                        }
                        return compute(vars[ops[0]], ops[1], secondNum, result);
                    }
                    else {
                        return 0;
                    }
                }
                else {
                    return 0;
                }
            }
            else {
                return 0;
            }

        }

        int five(vector<string> ops, int &result) {
            //checks if the first element in the vector is a valid var name
            if (checkValidVar(ops[0])) {
                //checks to see if the second operand is the = symbol
                if (ops[1] == "=") {
                    int firstNum;
                    int secondNum;
                    //check to see if the next operand is a literal int
                    if (checkValidNum(ops[2])) {
                        firstNum = convertToInt(ops[2]);
                        //checks to make sure op is a valid operand
                    }
                    //checks to see if variable is a valid name
                    else if (checkValidVar(ops[2])) {
                        //checks to make sure the variable is contained in the map
                        if (vars.count(ops[2]) > 0) {
                            firstNum = vars[ops[2]];
                        }
                        else {
                            return 0;
                        }
                    }
                    else {
                        return 0;
                    }
                    //checks to see if the op is a valid op
                    if (!checkValidOp(ops[3])) {
                        return 0;
                    }
                    //checks to see if the second value is a literal int
                    if (checkValidNum(ops[4])) {
                        secondNum = convertToInt(ops[4]);
                    }
                    //checks to see if the second valu is a valid variable
                    else if (checkValidVar(ops[4])) {
                        if (vars.count(ops[4]) > 0) {
                            secondNum = vars[ops[4]];
                        }
                        else {
                            return 0;
                        }
                    }
                    else {
                        return 0;
                    }
                    compute(firstNum, ops[3], secondNum, result);
                    vars[ops[0]] = result;
                    return 1;
                }
                else {
                    return 0;
                }
            }
            else {
                return 0;
            }
        }
};

extern "C" struct Calc *calc_create(void) {
    return new CalcImpl();
}

extern "C" void calc_destroy(struct Calc *calc) {
    CalcImpl *obj = static_cast<CalcImpl *>(calc);
    delete obj;
}

extern "C" int calc_eval(struct Calc *calc, const char *expr, int *result) {
    CalcImpl *obj = static_cast<CalcImpl *>(calc);
    return obj->evalExpr(expr, *result);
}
