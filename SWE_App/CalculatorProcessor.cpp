#include "CalculatorProcessor.h"
#include <wx/tokenzr.h>
#include <stack>
#include <string>

CalculatorProcessor* CalculatorProcessor::onlyInstance = nullptr;

CalculatorProcessor::CalculatorProcessor()
{
    // private constructor
}

CalculatorProcessor* CalculatorProcessor::GetInstance()
{
    if (onlyInstance == nullptr)
        onlyInstance = new CalculatorProcessor();

    return onlyInstance;
}

bool CalculatorProcessor::IsOperator(const char& CharacterOperator)
{
    return CharacterOperator == '+' || CharacterOperator == '-' ||
    CharacterOperator == '*' || CharacterOperator == '/' || CharacterOperator == '%';
}

bool CalculatorProcessor::isFunction(const std::string& token)
{
    return (token == "Sin") || (token == "Cos") || (token == "tan");
}

int CalculatorProcessor::Precedence(const char& OperatorStr)
{
    if (OperatorStr == '+' || OperatorStr == '-')
        return 2;
    if (OperatorStr == '*' || OperatorStr == '/')
        return 3;

    return 0;
}

double CalculatorProcessor::ApplyOperator(const char& op, double left, double right)
{
    // Handle division by zero
    if (op == '/' && right == 0) {
        throw std::runtime_error("Cannot perform division by zero: Undefined operation.");
    }

    // Handle modulus by zero (ensure integers are used in modulus)
    if (op == '%' && static_cast<int>(right) == 0) {
        throw std::runtime_error("Cannot perform modulus by zero: Undefined operation.");
    }

    // Perform the actual operation
    if (op == '+') return left + right;
    if (op == '-') return left - right;
    if (op == '*') return left * right;
    if (op == '/') return left / right;
    if (op == '%') return static_cast<int>(left) % static_cast<int>(right);  // Modulus operation for integers

    // Throw an exception for unknown operators
    throw std::runtime_error("Unknown operator: " + std::string(1, op));
}

double CalculatorProcessor::ApplyFunctionDegree(const std::string& func, double value)
{
    double radians = value * (M_PI / 180.0);  // Convert degrees to radians

    if (func == "Sin") return std::sin(radians); // Use radians for sin
    if (func == "Cos") return std::cos(radians); // Use radians for cos
    if (func == "Tan") return std::tan(radians); // Use radians for tan

    throw std::runtime_error("Unknown function: " + func);
}

// Functions Sin, Cos, Tan in Radian	
double  CalculatorProcessor::ApplyFunction(const std::string& func, double value) {
    if (func == "Sin") return std::sin(value);
    if (func == "Cos") return std::cos(value);
    if (func == "Cos") return std::tan(value);
    throw std::runtime_error("Unknown function: " + func);
}

double CalculatorProcessor::Calculate(const wxString& CalculatorTextString)
{ 
    std::string StringBuffersCalculatorText(CalculatorTextString);

    std::stack<double> Outputs;
    std::stack<char> Operators;
    std::stack<std::string> Functions; // to store Sin, Cos, Tan

    std::string Token;
    size_t length = StringBuffersCalculatorText.length();
    size_t index = 0;

    // Shunting yard algorithm begins
    while (index < length) {
        char ch = StringBuffersCalculatorText[index];

        // Handle numbers (multi-digit and floating point)
        if (std::isdigit(ch) || ch == '.') {
            std::string TempNumber;
            while (index < length && (std::isdigit(StringBuffersCalculatorText[index]) || StringBuffersCalculatorText[index] == '.')) {
                TempNumber += StringBuffersCalculatorText[index];
                index++;
            }
            Outputs.push(std::stod(TempNumber));  // Convert string to double and push to stack
            continue;  // to skip the rest of the current iteration and move on to the next one.
        }
        // Handle functions like Sin, Cos, Tan
        else if (std::isalpha(ch)) {
            std::string TempFunc;
            while (index < length && std::isalpha(StringBuffersCalculatorText[index])) {
                TempFunc = TempFunc + StringBuffersCalculatorText[index];
                index++;
            }
            Functions.push(TempFunc);  // Push function to function stack
            continue;  // skip the rest of the current iteration and move on to the next one.
        }
        // Handle double negatives ("--") as "+"
        else if (ch == '-' && index + 1 < length && StringBuffersCalculatorText[index + 1] == '-') {
            Operators.push('+');  // Treat "--" as "+"
            index += 2;  // Skip the next "-" sign
            continue;
        }
        // Handle unary negation or subtraction
        else if (ch == '-') {
            // Handle -Sin, -Cos, -Tan
            if (Outputs.empty() || (index > 0 && !std::isdigit(StringBuffersCalculatorText[index - 1]))) {
                std::string negFunc = "-";
                index++;  // Move past the '-' character

                // Check if there's a function like Sin, Cos, Tan after the negation
                if (index < length && std::isalpha(StringBuffersCalculatorText[index])) {
                    std::string TempFunc;
                    while (index < length && std::isalpha(StringBuffersCalculatorText[index])) {
                        TempFunc += StringBuffersCalculatorText[index];
                        index++;
                    }

                    // If it's a function like Sin, Cos, Tan, process it
                    if (TempFunc == "Sin" || TempFunc == "Cos" || TempFunc == "Tan") {
                        std::string TempNumber;
                        while (index < length && (std::isdigit(StringBuffersCalculatorText[index]) || StringBuffersCalculatorText[index] == '.')) {
                            TempNumber += StringBuffersCalculatorText[index];
                            index++;
                        }

                        // Apply the function (Sin, Cos, Tan) and convert the result to a double
                        double value = std::stod(TempNumber);
                        if (TempFunc == "Sin") {
                            value = std::sin(value);
                        }
                        else if (TempFunc == "Cos") {
                            value = std::cos(value);
                        }
                        else if (TempFunc == "Tan") {
                            value = std::tan(value);
                        }

                        // Apply unary negation (-Sin5 becomes -sin(5))
                        value = -value;

                        // Push the result of the negated function to the Outputs stack
                        Outputs.push(value);
                        continue;  // to skip the rest of the current iteration and move on to the next one.
                    }
                }
            }
            else {
                // Treat it as a binary subtraction
                Operators.push(ch);  // Push the "-" operator
            }
        }
        // Handle operators (+, -, *, /, %)
        else if (IsOperator(ch)) {
            // Evaluate function first, if any, before pushing the operator, check if a function is on the stack
            if (!Functions.empty()) {
                if (Outputs.empty()) {
                    throw std::runtime_error("Invalid Expression");
                }

                std::string func = Functions.top();
                Functions.pop();

                double value = Outputs.top();
                Outputs.pop();
                Outputs.push(ApplyFunction(func, value));  // Apply function and push result
            }

            // Process operator precedence
            while (!Operators.empty() && Precedence(Operators.top()) >= Precedence(ch)) {
                if (Outputs.size() < 2) {
                    throw std::runtime_error("Invalid Expression");
                }

                char op = Operators.top();
                Operators.pop();

                double right = Outputs.top();
                Outputs.pop();
                double left = Outputs.top();
                Outputs.pop();

                Outputs.push(ApplyOperator(op, left, right)); // Apply operator and push result
            }
            Operators.push(ch);  // Push current operator
        }

        // Increment index after processing current character
        index++;
    } // Shunting yard algorithm end


     // Before applying remaining operators, apply any remaining functions
    if (!Functions.empty()) {
        if (Outputs.empty()) {
            throw std::runtime_error("Empty stack: No value to apply function.");
        }

        std::string func = Functions.top();
        Functions.pop();

        double value = Outputs.top();
        Outputs.pop();
        Outputs.push(ApplyFunction(func, value));  // Apply function before applying remaining operators
    }

    // Apply remaining operators
    while (!Operators.empty()) {
        if (Outputs.size() < 2) {
            throw std::runtime_error("Empty stack: Not enough operands for operator.");
        }

        char op = Operators.top();
        Operators.pop();

        double right = Outputs.top();
        Outputs.pop();
        double left = Outputs.top();
        Outputs.pop();

        Outputs.push(ApplyOperator(op, left, right));
    }

    if (Outputs.empty()) {
        throw std::runtime_error("Empty stack: No result to return.");
    }

    return Outputs.top();  // Final result

    // This code below is working 
    //std::string StringBuffersCalculatorText(CalculatorTextString);
    //
    //// https://www.geeksforgeeks.org/java-program-to-implement-shunting-yard-algorithm/
    //// Preprocess the input to handle double negatives ("--")
    //// std::string::npos - https://www.geeksforgeeks.org/stringnpos-in-c-with-examples/
    ////size_t pos = 0;
    ////while ((pos = StringBuffersCalculatorText.find("--", pos)) != std::string::npos) {
    ////    StringBuffersCalculatorText.replace(pos, 2, "+");
    ////    pos += 1; // Move past the newly replaced '+'
    ////}

    //std::stack<double> Outputs;
    //std::stack<char> Operators;
    //std::stack<std::string> Functions; // to store the word Sin, Cos, Tan

    //std::string Token;
    //size_t length = StringBuffersCalculatorText.length();

    //size_t index = 0;

    //// shunting yard algorithm being
    //while (index < length) { 
    //    char ch = StringBuffersCalculatorText[index];

    //    // Handle numbers (multi-digit and floating point)
    //    if (std::isdigit(ch) || ch == '.') {
    //        std::string TempNumber;
    //        while (index < length && (std::isdigit(StringBuffersCalculatorText[index]) || StringBuffersCalculatorText[index] == '.')) {
    //            TempNumber = TempNumber + StringBuffersCalculatorText[index];
    //            index++;
    //        }
    //        Outputs.push(std::stod(TempNumber));  // Convert string to double and push to stack
    //        continue;  // to skip the rest of the current iteration and move on to the next one.
    //    }
    //    // Handle functions like Sin, Cos, Tan
    //    else if (std::isalpha(ch)) {
    //        std::string TempFunc;
    //        while (index < length && std::isalpha(StringBuffersCalculatorText[index])) {
    //            TempFunc = TempFunc + StringBuffersCalculatorText[index];
    //            index++;
    //        }
    //        Functions.push(TempFunc);  // Push function to function stack
    //        continue;  // to skip the rest of the current iteration and move on to the next one.
    //    }
    //    // Handle double negatives ("--") as "+"
    //    else if (ch == '-' && index + 1 < length && StringBuffersCalculatorText[index + 1] == '-') {
    //        Operators.push('+');  // Treat "--" as "+"
    //        index = index + 2;  // Skip the next "-" sign
    //        continue;
    //    }
    //    // Handle unary negation or subtraction
    //    else if (ch == '-') {
    //        if (Outputs.empty() || (index > 0 && !std::isdigit(StringBuffersCalculatorText[index - 1]))) {
    //            std::string negNumber = "-";
    //            index++;
    //            while (index < length && (std::isdigit(StringBuffersCalculatorText[index]) || StringBuffersCalculatorText[index] == '.')) {
    //                negNumber += StringBuffersCalculatorText[index];
    //                index++;
    //            }
    //            Outputs.push(std::stod(negNumber));  // Convert to double and push to stack
    //            continue; 
    //        }
    //        else {
    //            // Treat it as a binary subtraction
    //            Operators.push(ch);  // Push the "-" operator
    //        }
    //    }
    //    // Handle operators (+, -, *, /, %)
    //    else if (IsOperator(ch)) {
    //        // Evaluate function first, if any
    //        if (!Functions.empty()) {
    //            if (Outputs.empty()) {
    //                throw std::runtime_error("Invalid Expression");
    //            }

    //            std::string func = Functions.top();
    //            Functions.pop();

    //            double value = Outputs.top();
    //            Outputs.pop();
    //            Outputs.push(ApplyFunction(func, value));  // Apply function and push result
    //        }

    //        // Process operator precedence
    //        while (!Operators.empty() && Precedence(Operators.top()) >= Precedence(ch)) {
    //            if (Outputs.size() < 2) {
    //                throw std::runtime_error("Invalid Expression");
    //            }

    //            char op = Operators.top();
    //            Operators.pop();

    //            double right = Outputs.top();
    //            Outputs.pop();
    //            double left = Outputs.top();
    //            Outputs.pop();

    //            Outputs.push(ApplyOperator(op, left, right)); // Apply operator and push result
    //        }
    //        Operators.push(ch);  // Push current operator
    //    }

    //    // Increment index after processing current character
    //    index++;
    //} // shunting yard algorithm end

    //// Preparing for calculation and performing the calculation
    //// Apply any remaining functions before processing remaining operators
    //if (!Functions.empty()) {
    //    if (Outputs.empty()) {
    //        throw std::runtime_error("Empty stack: No value to apply function.");
    //    }

    //    std::string func = Functions.top();
    //    Functions.pop();

    //    double value = Outputs.top();
    //    Outputs.pop();
    //    Outputs.push(ApplyFunction(func, value));  // Apply function before applying remaining operators
    //}

    //// Apply remaining operators
    //while (!Operators.empty()) {
    //    if (Outputs.size() < 2) {
    //        throw std::runtime_error("Empty stack: Not enough operands for operator.");
    //    }

    //    char op = Operators.top();
    //    Operators.pop();

    //    double right = Outputs.top();
    //    Outputs.pop();
    //    double left = Outputs.top();
    //    Outputs.pop();

    //    Outputs.push(ApplyOperator(op, left, right));
    //}

    //if (Outputs.empty()) {
    //    throw std::runtime_error("Empty stack: No result to return.");
    //}

    //return Outputs.top();  // Final result
    //   
    


    //std::string StringBuffersCalculatorText(CalculatorTextString);
    //
    //char Token;

    //std::stack<std::string> Operators;
    //std::stack<std::string> Outputs;
    //std::stack<std::string> Functions;
    //std::stack<int> SolutionsTypeInt;  
    //
    //// Shunting Yard Algorithm 
    //// Puting things in order base on their characteristic: numbers or operands

    //for (int index = 0; index < StringBuffersCalculatorText.size(); ++index) {
    //    //wxStringTokenizer tokenizer(CalculatorTextCtrl.GetValue(), "+");
    //    
    //    Token = StringBuffersCalculatorText[index];

    //    // https://en.cppreference.com/w/cpp/string/byte/isdigit
    //    
    //    if (std::isdigit(Token) || Token == '.') {
    //        
    //        Outputs.push(std::string(1,Token)); // put number into Output string
    //    }
    //    else { // if it is not a digit then, it is an operator
    //        
    //        // Handle the Precedence of the operator
    //        if (IsOperator(Token)) {
    //            while(!Operators.empty() && Precedence(Operators.top()[0]) >= Precedence(Token))
    //            Operators.push(std::string(1, Token));
    //        }
    //    } 
    //    // Apply special function if present (e.g. Sin, Cos, Tan)
    //    if (!Functions.empty()) {
    //        std::string func = Functions.top();
    //        Functions.pop();

    //        SolutionsTypeInt.push(ApplyFunction(func, Outputs.top()));
    //        Outputs.pop();
    //    }
    //}
    //    
    //while (!Outputs.empty()) {
    //    SolutionsTypeInt.push(std::stoi(Outputs.top()));
    //    Outputs.pop();
    //}

    //// Calculation
    //while (!Operators.empty()) {
    //    int left = 0, right = 0;

    //    right = SolutionsTypeInt.top();
    //    SolutionsTypeInt.pop();
    //    left = SolutionsTypeInt.top();
    //    SolutionsTypeInt.pop();

    //    SolutionsTypeInt.push(ApplyOperator(Operators.top()[0], left, right));
    //    Operators.pop();
    //}

    //return static_cast<double>(SolutionsTypeInt.top());
    
}