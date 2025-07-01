// Memory Leak Prevention
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif
///////////////////////////////////////////

#include <wx/tokenzr.h>
#include <iomanip>   // For std::fixed and std::setprecision
#include <sstream>   // For std::ostringstream
#include <string>
#include <math.h>
#include <stdexcept>
#include "CalculatorFrame.h"
#include "ButtonFactory.h"
#include "CalculatorProcessor.h"


// Event table to handle key events
wxBEGIN_EVENT_TABLE(CalculatorFrame, wxFrame)
	EVT_BUTTON(BUTTON_CLEAR_ID, CalculatorFrame::OnClear)
	EVT_BUTTON(BUTTON_ZERO_ID, CalculatorFrame::OnZero)
	EVT_BUTTON(BUTTON_ONE_ID, CalculatorFrame::OnOne)
	EVT_BUTTON(BUTTON_TWO_ID, CalculatorFrame::OnTwo)
	EVT_BUTTON(BUTTON_THREE_ID, CalculatorFrame::OnThree)
	EVT_BUTTON(BUTTON_FOUR_ID, CalculatorFrame::OnFour)
	EVT_BUTTON(BUTTON_FIVE_ID, CalculatorFrame::OnFive)
	EVT_BUTTON(BUTTON_SIX_ID, CalculatorFrame::OnSix)
	EVT_BUTTON(BUTTON_SEVEN_ID, CalculatorFrame::OnSeven)
	EVT_BUTTON(BUTTON_EIGHT_ID, CalculatorFrame::OnEight)
	EVT_BUTTON(BUTTON_NINE_ID, CalculatorFrame::OnNine)
	EVT_BUTTON(BUTTON_NEGATIVE_ONE_ID, CalculatorFrame::OnNegativeOne)
	EVT_BUTTON(BUTTON_DECIMAL, CalculatorFrame::OnDecimal)
	EVT_BUTTON(BUTTON_PLUS, CalculatorFrame::OnPlus)
	EVT_BUTTON(BUTTON_MINUS, CalculatorFrame::OnMinus)
	EVT_BUTTON(BUTTON_MULTIPLY, CalculatorFrame::OnMultiply)
	EVT_BUTTON(BUTTON_DIVISION, CalculatorFrame::OnDivision)
	EVT_BUTTON(BUTTON_EQUAL, CalculatorFrame::OnEqual)
	EVT_BUTTON(BUTTON_MODULO, CalculatorFrame::OnModulo)
	EVT_BUTTON(BUTTON_BACKSPACE_DELETE, CalculatorFrame::OnBackspaceDelete)
	EVT_BUTTON(BUTTON_SIN, CalculatorFrame::OnSin)
	EVT_BUTTON(BUTTON_COS, CalculatorFrame::OnCos)
	EVT_BUTTON(BUTTON_TAN, CalculatorFrame::OnTan)
	EVT_CHAR_HOOK(CalculatorFrame::OnKeyPressed)
wxEND_EVENT_TABLE()

CalculatorFrame::CalculatorFrame()
	:wxFrame(nullptr, wxID_ANY, "Custom Calculator", wxDefaultPosition, wxSize(420, 500))
{
	// Sets the object of the wxSizerFlags to center itsefl in the area it is given
	//  https://docs.wxwidgets.org/3.2/classwx_window.html#a4a1819eeee3f2143cdde4f329ffde787
	Center();

	InitializeCalculatorGUI();
}

void CalculatorFrame::InitializeCalculatorGUI()
{
	mCountDecimalSign = 0;
	mIsThereIsException = false;	

	mTopBoxSizer = new wxBoxSizer(wxVERTICAL);

	mTopPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(420, 400));

	mTopBoxSizer->Add(mTopPanel, wxEXPAND);

	mCalculatorText = new wxTextCtrl(mTopPanel, wxID_ANY, "0", wxDefaultPosition,
		wxSize(400, 30), wxEXPAND | wxALIGN_RIGHT);

	// Disable cursor to edit the textbox
	// mCalculatorText->SetEditable(false);

	mButtonOne = mButtonFactory.CreateOneButton(mTopPanel, BUTTON_ONE_ID);
	mButtonTwo = mButtonFactory.CreateTwoButton(mTopPanel, BUTTON_TWO_ID);
	mButtonThree = mButtonFactory.CreateThreeButton(mTopPanel, BUTTON_THREE_ID);
	mButtonPlus = mButtonFactory.CreatePlusButton(mTopPanel, BUTTON_PLUS);
	mButtonClear = mButtonFactory.CreateClearButton(mTopPanel, BUTTON_CLEAR_ID);

	mButtonFour = mButtonFactory.CreateFourButton(mTopPanel, BUTTON_FOUR_ID);
	mButtonFive = mButtonFactory.CreateFiveButton(mTopPanel, BUTTON_FIVE_ID);
	mButtonSix = mButtonFactory.CreateSixButton(mTopPanel, BUTTON_SIX_ID);
	mButtonMinus = mButtonFactory.CreateMinusButton(mTopPanel, BUTTON_MINUS);
	mButtonModule = mButtonFactory.CreateModuleButton(mTopPanel, BUTTON_MODULO);

	mButtonFour = mButtonFactory.CreateSevenButton(mTopPanel, BUTTON_SEVEN_ID);
	mButtonFive = mButtonFactory.CreateEightButton(mTopPanel, BUTTON_EIGHT_ID);
	mButtonSix = mButtonFactory.CreateNineButton(mTopPanel, BUTTON_NINE_ID);
	mButtonMultiply = mButtonFactory.CreateMultiplyButton(mTopPanel, BUTTON_MULTIPLY);
	mButtonSin = mButtonFactory.CreateSinButton(mTopPanel, BUTTON_SIN);

	mButtonNegativeOne = mButtonFactory.CreateNegativeOneButton(mTopPanel, BUTTON_NEGATIVE_ONE_ID);
	mButtonZero = mButtonFactory.CreateZeroButton(mTopPanel, BUTTON_ZERO_ID);
	mButtonDecimal = mButtonFactory.CreateDecimalButton(mTopPanel, BUTTON_DECIMAL);
	mButtonDivision = mButtonFactory.CreateDivisionButton(mTopPanel, BUTTON_DIVISION);
	mButtonCos = mButtonFactory.CreateCosButton(mTopPanel, BUTTON_COS);

	mButtonBackspaceDelete = mButtonFactory.CreateBackspaceDeleteButton(mTopPanel, BUTTON_BACKSPACE_DELETE);
	mButtonEqual = mButtonFactory.CreateEqualButton(mTopPanel, BUTTON_EQUAL);
	mButtonTan = mButtonFactory.CreateTanButton(mTopPanel, BUTTON_TAN);

	SetSizer(mTopBoxSizer);
}

void CalculatorFrame::OnClear(wxCommandEvent& event)
{
	mCalculatorText->Clear();
	mCalculatorText->SetValue('0');
	mCountDecimalSign = 0;
	mIsThereIsException = false;	
}

void CalculatorFrame::OnZero(wxCommandEvent& event)
{
	mCalculatorText->AppendText("0");
	SpecialCaseOnNumberZero();

	//std::string CalculatorStr(mCalculatorText->GetValue());

	//if (CalculatorStr[0] == '0' && CalculatorStr[1] == '.') {
	//	mCalculatorText->AppendText("0");
	//}
	//else if (CalculatorStr[0] == '0' && CalculatorStr[1] != '.') {
	//	return;
	//}
	//else {
	//	mCalculatorText->AppendText("0");
	//}
}

void CalculatorFrame::OnOne(wxCommandEvent& event)
{
	mCalculatorText->AppendText("1");
	SpecialCaseOnNumberZero();

}

void CalculatorFrame::OnTwo(wxCommandEvent& event)
{
	mCalculatorText->AppendText("2");
	SpecialCaseOnNumberZero();	
}

void CalculatorFrame::OnThree(wxCommandEvent& event)
{
	mCalculatorText->AppendText("3");
	SpecialCaseOnNumberZero();
}

void CalculatorFrame::OnFour(wxCommandEvent& event)
{
	mCalculatorText->AppendText("4");
	SpecialCaseOnNumberZero();

}

void CalculatorFrame::OnFive(wxCommandEvent& event)
{
	mCalculatorText->AppendText("5");
	SpecialCaseOnNumberZero();
}

void CalculatorFrame::OnSix(wxCommandEvent& event)
{
	mCalculatorText->AppendText("6");
	SpecialCaseOnNumberZero();
}

void CalculatorFrame::OnSeven(wxCommandEvent& event)
{
	mCalculatorText->AppendText("7");
	SpecialCaseOnNumberZero();
	
}

void CalculatorFrame::OnEight(wxCommandEvent& event)
{
	mCalculatorText->AppendText("8");
	SpecialCaseOnNumberZero();	
}

void CalculatorFrame::OnNine(wxCommandEvent& event)
{
	mCalculatorText->AppendText("9");
	SpecialCaseOnNumberZero();
}

void CalculatorFrame::OnNegativeOne(wxCommandEvent& event)
{
	wxString CalculatorText = mCalculatorText->GetValue();
	int CalculatorValue = 0;
	CalculatorText.ToInt(&CalculatorValue);
	CalculatorValue = (-1) * CalculatorValue;

	mCalculatorText->SetValue(std::to_string(CalculatorValue));
}

void CalculatorFrame::OnDecimal(wxCommandEvent& event)
{
	wxString CalculatorText = mCalculatorText->GetValue();

	for (int index = 0; index < CalculatorText.size(); ++index) {
		if (CalculatorText[index] == '.')
			++mCountDecimalSign;

		// Checking for overators inside the CalculatorText Box befor putting another decimal.
		// if you encounter operators, you can put decimal point but you cannot have decimal point next to each other.
		char Operator = CalculatorText[index];
		switch (Operator)
		{
		case '+':
			mCountDecimalSign = 0;
			break;
		case '-':
			mCountDecimalSign = 0;
			break;
		case '*':
			mCountDecimalSign = 0;
			break;
		case '/':
			mCountDecimalSign = 0;
			break;
		case '%':
			mCountDecimalSign = 0;
			break;
		}
	}

	if (mCountDecimalSign < 1) {
		mCalculatorText->AppendText(".");
		mCountDecimalSign = 0;
	}

}

void CalculatorFrame::OnPlus(wxCommandEvent& event)
{
	mCalculatorText->AppendText("+");
}

void CalculatorFrame::OnMinus(wxCommandEvent& event)
{
	mCalculatorText->AppendText("-");
}

void CalculatorFrame::OnMultiply(wxCommandEvent& event)
{
	mCalculatorText->AppendText("*");
}

void CalculatorFrame::OnDivision(wxCommandEvent& event)
{
	mCalculatorText->AppendText("/");
}

void CalculatorFrame::OnEqual(wxCommandEvent& event)
{
	// mCalculatorText->AppendText("=");	
	PerformCalculation();
}

void CalculatorFrame::OnModulo(wxCommandEvent& event)
{
	mCalculatorText->AppendText("%");
}

void CalculatorFrame::OnSin(wxCommandEvent& event)
{
	std::string CalculatorStr(mCalculatorText->GetValue());

	// Find the position of the last digit in the string (the number to replace with "Sin")
	std::size_t lastDigitPos = CalculatorStr.find_last_of("0123456789");

	if (lastDigitPos != std::string::npos) {
		// Find where the number starts (going backward from the last digit)
		std::size_t numberStart = CalculatorStr.find_last_of("+-*/", lastDigitPos);

		// If a valid operator is found before the number, calculate the number start correctly
		if (numberStart != std::string::npos) {
			numberStart++;  // Move past the operator to the actual start of the number
		}
		else {
			numberStart = 0;  // If no operator is found, the number starts from the beginning
		}

		// Extract the number to replace (substring from numberStart to lastDigitPos)
		std::string numberStr = CalculatorStr.substr(numberStart, lastDigitPos - numberStart + 1);

		if (CalculatorStr.back() == '0' || CalculatorStr.back() == '+' || CalculatorStr.back() == '-' || CalculatorStr.back() == '*' || CalculatorStr.back() == '/' || CalculatorStr.back() == '%') {
			wxMessageBox("Please press the number first before pressing the Sin");
		}
		else {
			// Replace the number with "Sin" + the number
			CalculatorStr.replace(numberStart, numberStr.length(), "Sin" + numberStr);
		}
		// Update the calculator display
		mCalculatorText->SetValue(CalculatorStr);

		// Set the cursor position at the end of the new expression
		mCalculatorText->SetInsertionPointEnd();
	}
	else {
		// If no number is found, insert "Sin" at the current cursor position
		long insertionPoint = mCalculatorText->GetInsertionPoint();
		CalculatorStr.insert(insertionPoint, "Sin");
		mCalculatorText->SetValue(CalculatorStr);
		mCalculatorText->SetInsertionPoint(insertionPoint + 3); // Move cursor after "Sin"
	}
		
	//std::string CalculatorStr(mCalculatorText->GetValue());

	//// std::string::find_first_of
	//// https://cplusplus.com/reference/string/string/find_first_of/

	//// The next three line will remove the leading zero in the front
	//std::size_t FindNumbers = CalculatorStr.find_first_of("0123456789");
	//std::string NumbersStr = CalculatorStr.substr(FindNumbers);
	//int Numbers = std::stoi(NumbersStr);

	//mCalculatorText->SetValue("Sin" + std::to_string(Numbers));

	//SpecialCaseOnNumberZero();

}

void CalculatorFrame::OnCos(wxCommandEvent& event)
{
	std::string CalculatorStr(mCalculatorText->GetValue());

	std::size_t LastDigitPos = CalculatorStr.find_last_of("0123456789");

	if (LastDigitPos != std::string::npos) {
		
		std::size_t NumberStart = CalculatorStr.find_last_of("+-*/", LastDigitPos);
		
		if (NumberStart != std::string::npos) {
			NumberStart++;  
		}
		else {
			NumberStart = 0;  
		}

		std::string NumberStr = CalculatorStr.substr(NumberStart, LastDigitPos - NumberStart + 1);	
		
		if (CalculatorStr.back() == '0' || CalculatorStr.back() == '+' || CalculatorStr.back() == '-' || CalculatorStr.back() == '*' || CalculatorStr.back() == '/' || CalculatorStr.back() == '%') {
			wxMessageBox("Please press the number first before pressing the Cos");

		}
		else {
			CalculatorStr.replace(NumberStart, NumberStr.length(), "Cos" + NumberStr);
		}

		mCalculatorText->SetValue(CalculatorStr);
		
		mCalculatorText->SetInsertionPointEnd();
	}
	else {
		
		long insertionPoint = mCalculatorText->GetInsertionPoint();
		CalculatorStr.insert(insertionPoint, "Tan");
		mCalculatorText->SetValue(CalculatorStr);
		mCalculatorText->SetInsertionPoint(insertionPoint + 3); // Move cursor after "Sin"
	}

	// Get the current insertion point (cursor position)
	// https://docs.wxwidgets.org/3.2/classwx_text_entry.html#aec1a523f158549abdef5271c55906902
	// long InsertionPoint = mCalculatorText->GetInsertionPoint();
	//std::size_t FunctionPos = CalculatorStr.find("Cos");

	//if (FunctionPos != std::string::npos) { // If "Cos" is found
	//	
	//	// Find the first digit after "Cos"
	//	// https://en.cppreference.com/w/cpp/types/size_t
	//	std::size_t FindNumbers = CalculatorStr.find_first_of("0123456789", FunctionPos + 3); // "Cos" length is 3

	//	// If a number was found after "Sin"
	//	if (FindNumbers != std::string::npos) {
	//		std::string NumbersStr = CalculatorStr.substr(FindNumbers);

	//		int Numbers = std::stoi(NumbersStr); // Convert the number part to an integer
	//		
	//		// Now set the value back to the text control, with "Sin" followed by the number
	//		mCalculatorText->SetValue("Cos" + std::to_string(Numbers));					

	//		// Remove leading zeros
	//		NumbersStr.erase(0, NumbersStr.find_first_not_of('0'));			
	//	}
	//	else {			
	//		long insertionPoint = mCalculatorText->GetInsertionPoint();
	//		CalculatorStr.insert(insertionPoint, "Cos");
	//		mCalculatorText->SetValue(CalculatorStr);
	//		mCalculatorText->SetInsertionPoint(insertionPoint + 3);
	//	}
	//	
	//}
	//


	//std::string CalculatorStr(mCalculatorText->GetValue());

	//// The next three line will remove the leading zero in the front
	//std::size_t FindNumbers = CalculatorStr.find_first_of("0123456789");
	//std::string NumbersStr = CalculatorStr.substr(FindNumbers);
	//int Numbers = std::stoi(NumbersStr);

	//mCalculatorText->SetValue("Cos" + std::to_string(Numbers));
	//SpecialCaseOnNumberZero();
}

void CalculatorFrame::OnTan(wxCommandEvent& event)
{
	std::string CalculatorStr(mCalculatorText->GetValue());

	std::size_t LastDigitPos = CalculatorStr.find_last_of("0123456789");

	if (LastDigitPos != std::string::npos) {

		std::size_t NumberStart = CalculatorStr.find_last_of("+-*/", LastDigitPos);

		if (NumberStart != std::string::npos) {
			NumberStart++;
		}
		else {
			NumberStart = 0;
		}

		std::string NumberStr = CalculatorStr.substr(NumberStart, LastDigitPos - NumberStart + 1);

		if (CalculatorStr.back() == '0' || CalculatorStr.back() == '+' || CalculatorStr.back() == '-' || CalculatorStr.back() == '*' || CalculatorStr.back() == '/' || CalculatorStr.back() == '%') {
			wxMessageBox("Please press the number first before pressing the Tan");
		}
		else {
			CalculatorStr.replace(NumberStart, NumberStr.length(), "Tan" + NumberStr);
		}

		mCalculatorText->SetValue(CalculatorStr);

		mCalculatorText->SetInsertionPointEnd();
	}
	else {

		long insertionPoint = mCalculatorText->GetInsertionPoint();
		CalculatorStr.insert(insertionPoint, "Tan");
		mCalculatorText->SetValue(CalculatorStr);
		mCalculatorText->SetInsertionPoint(insertionPoint + 3); // Move cursor after "Sin"
	}

	//std::string CalculatorStr(mCalculatorText->GetValue());

	//// The next three line will remove the leading zero in the front
	//std::size_t FindNumbers = CalculatorStr.find_first_of("0123456789");
	//std::string NumbersStr = CalculatorStr.substr(FindNumbers);
	//int Numbers = std::stoi(NumbersStr);

	//mCalculatorText->SetValue("Tan" + std::to_string(Numbers));
	//SpecialCaseOnNumberZero();
}

void CalculatorFrame::OnBackspaceDelete(wxCommandEvent& event){
	BackspaceOrDelete();
}

void CalculatorFrame::PerformCalculation()
{
	if (!mIsThereIsException) {
		try {
			// Attempt to calculate
			double result = CalculatorProcessor::GetInstance()->Calculate(mCalculatorText->GetValue());

			// Check if the result is an integer
			if (result == static_cast<int>(result)) {				 
				 mCalculatorText->SetValue(wxString::Format("%d", static_cast<int>(result)));
			}
			else {
				// Display the result
				mCalculatorText->SetValue(wxString::Format("%.9f", result));
			}
		}

		catch (const std::runtime_error& e) {
			// If there's an error (like modulus by zero), set the exception flag and display the error
			mIsThereIsException = true;
			mCalculatorText->SetValue(e.what());  // Display the exception message
			wxMessageBox("Please Clear the Calculator");
		}	
	}


	// https://wiki.wxwidgets.org/Converting_everything_to_and_from_wxString#int_to_wxString
	// wxString mystring = wxString::Format(wxT("%i"),myint);
	// wxString ConvertIntTowxString = wxString::Format(wxT("%i"), result); 

	// another solution to convert integer to wxString 
	// mCalculatorText->SetValue(std::to_string(result));

	//double result = CalculatorProcessor::GetInstance()->Calculate(mCalculatorText->GetValue());
	//mCalculatorText->SetValue(wxString::Format("%.1f", result));

	//ExceptionHandlingInvalidExpression();


	//if (!mIsThereIsException) {
	//	try {
	//		double result = CalculatorProcessor::GetInstance()->Calculate(mCalculatorText->GetValue());
	//		mCalculatorText->SetValue(wxString::Format("%0.1f", result));	

	//	}
	//	catch (const std::runtime_error& e) {
	//		mIsThereIsException = true;
	//		mCalculatorText->SetValue(e.what());
	//	}
	//}
	//
	//ExceptionHandlingInvalidExpression();



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Previous Calculator Calculation 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//wxString FindOperator = mCalculatorText->GetValue();
	//wxString NumberFormatedResult = "";
	//int IntegerResult = 0;
	//double DoubleResult = 0;

	//if (!mIsThereIsException) {
	//	for (int index = 0; index < FindOperator.length(); ++index) {

	//		// Addition
	//		if (FindOperator[index].GetValue() == '+') {

	//			wxStringTokenizer tokenizer(mCalculatorText->GetValue(), "+");

	//			double left_value = 0.0f, right_value = 0.0f;

	//			// get the first token put it onto the value_left
	//			tokenizer.GetNextToken().ToDouble(&left_value);

	//			// get the second token put it onto the value_right
	//			tokenizer.GetNextToken().ToDouble(&right_value);

	//			DoubleResult = left_value + right_value;

	//			// check if the result is double or integer
	//			if (DoubleResult == static_cast<int>(DoubleResult)) {
	//				IntegerResult = static_cast<int>(DoubleResult);
	//				mCalculatorText->AppendText(wxString::Format("%d", IntegerResult));
	//				return;
	//			}
	//			else {
	//				mCalculatorText->AppendText(wxString::Format("%.2f", DoubleResult));
	//				return;
	//			}

	//		}
	//		// Double minus signs is positive or addition 
	//		if (FindOperator[index].GetValue() == '-' && FindOperator[index + 1].GetValue() == '-') {

	//			wxStringTokenizer tokenizer(mCalculatorText->GetValue(), "-");
	//			double left_value = 0.0f, right_value = 0.0f;

	//			// get the first token put it onto the value_left
	//			tokenizer.GetNextToken().ToDouble(&left_value);

	//			wxString TempStr = tokenizer.GetNextToken(); // empty string

	//			// get the second token put it onto the value_right
	//			tokenizer.GetNextToken().ToDouble(&right_value);

	//			DoubleResult = left_value + right_value;

	//			// check if the result is double or integer
	//			if (DoubleResult == static_cast<int>(DoubleResult)) {
	//				IntegerResult = static_cast<int>(DoubleResult);
	//				mCalculatorText->AppendText(wxString::Format("%i", IntegerResult));
	//				return;
	//			}
	//			else {
	//				mCalculatorText->AppendText(wxString::Format("%.2f", DoubleResult));
	//				return;
	//			}
	//		}		

	//		// Subtraction
	//		if (FindOperator[index].GetValue() == '-') {

	//			wxStringTokenizer tokenizer(mCalculatorText->GetValue(), "-");

	//			double left_value = 0.0f, right_value = 0.0f;

	//			// get the first token put it onto the value_left
	//			tokenizer.GetNextToken().ToDouble(&left_value);

	//			// get the second token put it onto the value_right
	//			tokenizer.GetNextToken().ToDouble(&right_value);

	//			DoubleResult = left_value - right_value;

	//			// check if the result is double or integer
	//			if (DoubleResult == static_cast<int>(DoubleResult)) {
	//				IntegerResult = static_cast<int>(DoubleResult);
	//				mCalculatorText->AppendText(wxString::Format("%i", IntegerResult));
	//				return;
	//			}
	//			else {
	//				mCalculatorText->AppendText(wxString::Format("%.2f", DoubleResult));
	//				return;
	//			}
	//		}

	//		// Multiplication
	//		if (FindOperator[index].GetValue() == '*') {

	//			wxStringTokenizer tokenizer(mCalculatorText->GetValue(), "*");

	//			double left_value = 0, right_value = 0;

	//			// get the first token put it onto the value_left
	//			tokenizer.GetNextToken().ToDouble(&left_value);

	//			// get the second token put it onto the value_right
	//			tokenizer.GetNextToken().ToDouble(&right_value);

	//			DoubleResult = left_value * right_value;

	//			// check if the result is double or integer
	//			if (DoubleResult == static_cast<int>(DoubleResult)) {
	//				IntegerResult = static_cast<int>(DoubleResult);
	//				mCalculatorText->AppendText(wxString::Format("%i", IntegerResult));
	//				return;
	//			}
	//			else {
	//				mCalculatorText->AppendText(wxString::Format("%.2f", DoubleResult));
	//				return;
	//			}
	//		}

	//		// Division
	//		if (FindOperator[index].GetValue() == '/') {

	//			wxStringTokenizer tokenizer(mCalculatorText->GetValue(), "/");

	//			double left_value = 0, right_value = 0;

	//			// get the first token put it onto the value_left
	//			tokenizer.GetNextToken().ToDouble(&left_value);

	//			// get the second token put it onto the value_right
	//			tokenizer.GetNextToken().ToDouble(&right_value);

	//			try {
	//				if (right_value == 0) {
	//					throw std::runtime_error("Cannot perform division by zero undefined");
	//				}
	//				DoubleResult = left_value / right_value;

	//				// check if the result is double or integer
	//				if (DoubleResult == static_cast<int>(DoubleResult)) {
	//					IntegerResult = static_cast<int>(DoubleResult);
	//					mCalculatorText->AppendText(wxString::Format("%i", IntegerResult));
	//					return;
	//				}
	//				else {
	//					mCalculatorText->AppendText(wxString::Format("%.2f", DoubleResult));
	//					return;
	//				}
	//			}
	//			catch (const std::exception& exception) {
	//				mCalculatorText->AppendText(exception.what());					
	//				return;
	//			}

	//		}

	//		// Modulo
	//		if (FindOperator[index].GetValue() == '%') {

	//			wxStringTokenizer tokenizer(mCalculatorText->GetValue(), "%");

	//			int left_value = 0, right_value = 0;

	//			// get the first token put it onto the value_left
	//			tokenizer.GetNextToken().ToInt(&left_value);

	//			// get the second token put it onto the value_right
	//			tokenizer.GetNextToken().ToInt(&right_value);

	//			try {
	//				if (right_value == 0) {

	//					throw std::runtime_error("Cannot perform modulus by zero is undefined");
	//				}
	//			}
	//			catch (const std::exception& exception) {
	//				mCalculatorText->AppendText(exception.what());					
	//				return;
	//			}

	//			IntegerResult = left_value % right_value;

	//			mCalculatorText->AppendText(std::to_string(IntegerResult));

	//			return;
	//		}

	//		//Sin
	//		int FoundSin = FindOperator.compare(0, 3, "Sin");
	//		if (FoundSin == 0) {
	//			wxStringTokenizer tokenizer(mCalculatorText->GetValue(), " ");
	//			// The first value of tokenizer is Sin
	//			// The second value of the tokeizer is number

	//			// go through the first token so we can access the next token
	//			tokenizer.GetNextToken();

	//			double number;
	//			// get the first token put it onto the value_left
	//			tokenizer.GetNextToken().ToDouble(&number);

	//			mCalculatorText->AppendText("Rad: " + std::to_string(std::sin(number)));

	//			return;
	//		}

	//		int FoundCos = FindOperator.compare(0, 3, "Cos");
	//		if (FoundCos == 0) {
	//			wxStringTokenizer tokenizer(mCalculatorText->GetValue(), " ");
	//			// The first value of tokenizer is Sin
	//			// The second value of the tokeizer is number

	//			// go through the first token so we can access the next token
	//			tokenizer.GetNextToken();

	//			double number;
	//			// get the first token put it onto the value_left
	//			tokenizer.GetNextToken().ToDouble(&number);

	//			mCalculatorText->AppendText("Rad: " + std::to_string(std::cos(number)));

	//			return;
	//		}

	//		int FoundTan = FindOperator.compare(0, 3, "Tan");
	//		if (FoundTan == 0) {
	//			wxStringTokenizer tokenizer(mCalculatorText->GetValue(), " ");
	//			// The first value of tokenizer is Sin
	//			// The second value of the tokeizer is number

	//			// go through the first token so we can access the next token
	//			tokenizer.GetNextToken();

	//			double number;
	//			// get the first token put it onto the value_left
	//			tokenizer.GetNextToken().ToDouble(&number);

	//			mCalculatorText->AppendText("Rad: " + std::to_string(std::tan(number)));

	//			return;
	//		}
	//	}
	//}

}

void CalculatorFrame::ExceptionHandlingInvalidExpression()
{
	std::string CalculatorStr(mCalculatorText->GetValue());

	for (int index = 0; index < CalculatorStr.length(); ++index) {
		if (CalculatorStr[index] == '.' && CalculatorStr[index + 1] == '.') {
			mCalculatorText->AppendText("Invalid Expression");
			mIsThereIsException = true;
			return;
		}
		else if (CalculatorStr[index] == '+' && CalculatorStr[index + 1] == '+'){
			mCalculatorText->AppendText("Invalid Expression");
			mIsThereIsException = true;
			return;
		}else if (CalculatorStr[index] == '+' && CalculatorStr[index + 1] == '=') {
			mCalculatorText->AppendText("Invalid Expression");
			mIsThereIsException = true;
			return;
		}else if (CalculatorStr.size() < 3 && CalculatorStr[index] == '0' && CalculatorStr[index + 1] == '=') {
			mCalculatorText->AppendText("Invalid Expression");
			mIsThereIsException = true; 
			return;
		} else if (CalculatorStr.size() < 3 && CalculatorStr[index] == '1' && CalculatorStr[index + 1] == '=') {
			mCalculatorText->AppendText("Invalid Expression");
			mIsThereIsException = true;
			return;
		} else if (CalculatorStr.size() < 3 && CalculatorStr[index] == '2' && CalculatorStr[index + 1] == '=') {
			mCalculatorText->AppendText("Invalid Expression");
			mIsThereIsException = true;
			return;
		} else if (CalculatorStr.size() < 3 && CalculatorStr[index] == '3' && CalculatorStr[index + 1] == '=') {
			mCalculatorText->AppendText("Invalid Expression");
			mIsThereIsException = true;
			return;
		} else if (CalculatorStr.size() < 3 && CalculatorStr[index] == '4' && CalculatorStr[index + 1] == '=') {
			mCalculatorText->AppendText("Invalid Expression");
			mIsThereIsException = true;
			return;
		} else if (CalculatorStr.size() < 3 && CalculatorStr[index] == '5' && CalculatorStr[index + 1] == '=') {
			mCalculatorText->AppendText("Invalid Expression");
			mIsThereIsException = true;
			return;
		} else if (CalculatorStr.size() < 3 && CalculatorStr[index] == '6' && CalculatorStr[index + 1] == '=') {
			mCalculatorText->AppendText("Invalid Expression");
			mIsThereIsException = true;
			return;
		} else if (CalculatorStr.size() < 3 && CalculatorStr[index] == '7' && CalculatorStr[index + 1] == '=') {
			mCalculatorText->AppendText("Invalid Expression");
			mIsThereIsException = true;
			return;
		} else if (CalculatorStr.size() < 3 && CalculatorStr[index] == '8' && CalculatorStr[index + 1] == '=') {
			mCalculatorText->AppendText("Invalid Expression");
			mIsThereIsException = true;
			return;
		} else if (CalculatorStr.size() < 3 && CalculatorStr[index] == '9' && CalculatorStr[index + 1] == '=') {
			mCalculatorText->AppendText("Invalid Expression");
			mIsThereIsException = true;
			return;
		}

	}
	
}

void CalculatorFrame::BackspaceOrDelete()
{
	wxString StrCalculatorValue = mCalculatorText->GetValue();
	StrCalculatorValue.RemoveLast();
	try {
		if (mCalculatorText->IsEmpty()) {
			throw std::runtime_error("wxTextCtrl Text Box cannot be empty");
		}
	}
	catch (const std::exception& EmptyTextBoxException) {
		mCalculatorText->AppendText(EmptyTextBoxException.what());
		return;
	}
	
	mCalculatorText->SetValue(StrCalculatorValue);
	
	if (mCalculatorText->IsEmpty()) {
		mCalculatorText->AppendText("Text Box Cannot be Empty");		
	}
}

void CalculatorFrame::SpecialCaseOnNumberZero()
{
	std::string CalculatorStr(mCalculatorText->GetValue());
	if (CalculatorStr[0] == '0' && CalculatorStr[1] == '.') {
		mCalculatorText->AppendText("0");
	}
	else if (CalculatorStr[0] == '0' && CalculatorStr[1] != '.') {
		CalculatorStr.erase(0, 1);
	}
	mCalculatorText->SetValue(CalculatorStr);

	// Example: Sin 05 -> we need to remove zero from the textbox - String size is 6
	if (CalculatorStr.compare("Sin 0") == 0)
		mCalculatorText->SetValue("Sin ");
	if (CalculatorStr.compare("Cos 0") == 0 && CalculatorStr.size() > 5)
		mCalculatorText->SetValue("Cos ");
	if (CalculatorStr.compare("Tan 0") == 0 && CalculatorStr.size() > 5)
		mCalculatorText->SetValue("Tan ");

}

void CalculatorFrame::OnKeyPressed(wxKeyEvent& event)
{
	// wxKeyEvent
	// https://docs.wxwidgets.org/3.2/classwx_key_event.html#a460e06e32b36973a63a02958ce4528b9

	// Enum wxKeyCode
	// https://docs.wxwidgets.org/3.2/defs_8h.html#a41c4609211685cff198618963ec8f77d

	// MACROS - wxKeyEvent::GetKeyCode()
	// https://docs.wxwidgets.org/latest/defs_8h.html

	int keyCode = event.GetKeyCode();

	if (keyCode == '5' && event.ShiftDown()) {
		mCalculatorText->AppendText("%");
	}

	if (keyCode == '=' && event.ShiftDown()) {
		mCalculatorText->AppendText("+");
	}

	switch (keyCode)
	{
		// check if '0' key is pressed
	case '0':
		mCalculatorText->AppendText("0");
		break;
	case '1':
	{
		mCalculatorText->AppendText("1");
		SpecialCaseOnNumberZero();
	}break;
	case '2':
	{
		mCalculatorText->AppendText("2");
		SpecialCaseOnNumberZero();		
	}break;
	case '3':
	{
		mCalculatorText->AppendText("3");
		SpecialCaseOnNumberZero();
	}break;
	case '4':
	{
		mCalculatorText->AppendText("4");
		SpecialCaseOnNumberZero();
	}	break;
	case '5':
		if (!event.ShiftDown()) { 
			mCalculatorText->AppendText("5"); 
			SpecialCaseOnNumberZero();
		} break;
	case '6':
	{
		mCalculatorText->AppendText("6");
		SpecialCaseOnNumberZero();
	}break;
	case '7':
	{
		mCalculatorText->AppendText("7");
		SpecialCaseOnNumberZero();
	}break;
	case '8':
	{
		mCalculatorText->AppendText("8"); 
		SpecialCaseOnNumberZero();
	}	break;
	case '9':
	{
		mCalculatorText->AppendText("9");
		SpecialCaseOnNumberZero();
	}break;	
	case WXK_ADD:
		mCalculatorText->AppendText("+");
		break;
	case WXK_NUMPAD_ADD:
		mCalculatorText->AppendText("+");
		break;
	case WXK_SUBTRACT:
		mCalculatorText->AppendText("-");
		break;
	case WXK_NUMPAD_SUBTRACT:
		mCalculatorText->AppendText("-");
		break;
	case WXK_MULTIPLY:
		mCalculatorText->AppendText("*");
		break;
	case WXK_NUMPAD_MULTIPLY:
		mCalculatorText->AppendText("*");
		break;
	case '/':
		mCalculatorText->AppendText("/");
		break;
	case WXK_DIVIDE:
		mCalculatorText->AppendText("/");
		break;
	case WXK_NUMPAD_DIVIDE:
		mCalculatorText->AppendText("/");
		break;
	case '%':
		mCalculatorText->AppendText("%");
		break;
	case WXK_NUMPAD_EQUAL:
		// mCalculatorText->AppendText("=");
		PerformCalculation();
		break;
	case '=':
		if (!event.ShiftDown()) {
			//mCalculatorText->AppendText("=");
			PerformCalculation();
		}break;	
	case WXK_RETURN:
		//mCalculatorText->AppendText("=");
		PerformCalculation();
		break;
	case WXK_NUMPAD_ENTER:
		//mCalculatorText->AppendText("=");
		PerformCalculation();
		break;
	case '.':
		mCalculatorText->AppendText(".");
		break;
	case WXK_BACK: 
		BackspaceOrDelete();
		break;
	case WXK_DELETE: 
		BackspaceOrDelete();
		break;
	default:
		event.Skip();
		break;
	}
}