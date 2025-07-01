#pragma once

#include <wx/wx.h>

// All string parsing and calculations will be performed inside the ProcessorSingleton.
// https://refactoring.guru/design-patterns/singleton/cpp/example

class CalculatorProcessor
{
public:
	static CalculatorProcessor* GetInstance();
	double Calculate(const wxString& CalculatorTextString);
	
protected:
	CalculatorProcessor();

private:	
	// Singleton object can only be created once or instantiated once. 
	// will be gobaly accessible, we need to use static when we instantiate the object, 
	// so they can be access by all the other objecs.
	static CalculatorProcessor* onlyInstance;
	bool mIsThereIsException = false;

	bool IsOperator(const char& CharacterOperator);

	// Check if the string is a function like Sin
	bool isFunction(const std::string& token);

	int Precedence(const char& OperatorStr);

	// Function to evaluate a single operator
	double ApplyOperator(const char& op, double left, double right);

	// Convert Trig Function Sin, Cos Tan from Radian to Degree
	double ApplyFunctionDegree(const std::string& func, double value);

	// Trig Function in Radian
	double ApplyFunction(const std::string& func, double value);	

};