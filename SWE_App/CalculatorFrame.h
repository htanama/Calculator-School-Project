#pragma once

#include <vector>
#include <math.h>
#include "wx/wx.h"
#include "wx/event.h"
#include "ButtonFactory.h"


class CalculatorFrame : public wxFrame
{
public:
	CalculatorFrame();	

private:
	bool mIsThereIsException = false;
	int mCountDecimalSign = 0;



	// Creating specific ID for event handler
	enum {
		CALCULATOR_TEXT_ID = 1111,
		BUTTON_CLEAR_ID = 1112,
		BUTTON_ZERO_ID = 1000,
		BUTTON_ONE_ID = 1001,
		BUTTON_TWO_ID = 1002,
		BUTTON_THREE_ID = 1003,
		BUTTON_FOUR_ID = 1004,
		BUTTON_FIVE_ID = 1005,
		BUTTON_SIX_ID = 1006,
		BUTTON_SEVEN_ID = 1007,
		BUTTON_EIGHT_ID = 1008,
		BUTTON_NINE_ID = 1009,
		BUTTON_NEGATIVE_ONE_ID = 1010,
		BUTTON_DECIMAL = 1011,
		BUTTON_PLUS = 1012,
		BUTTON_MINUS = 1013,
		BUTTON_MULTIPLY = 1014,
		BUTTON_DIVISION = 1015,
		BUTTON_EQUAL = 1016,
		BUTTON_MODULO = 1017,
		BUTTON_SIN = 1018,
		BUTTON_COS = 1019,
		BUTTON_TAN = 1020,
		BUTTON_BACKSPACE_DELETE = 1021
	};

	wxBoxSizer* mTopBoxSizer = nullptr;
	wxPanel* mTopPanel = nullptr;		
	
	wxTextCtrl* mCalculatorText = nullptr;

	// https://refactoring.guru/design-patterns/factory-method
	// Benefit: It centralizes the construction of complex objects, 
	// making the code easier to maintain and modify.
	ButtonFactory mButtonFactory;
	
	wxButton* mButtonNegativeOne = nullptr;
	wxButton* mButtonDecimal = nullptr;
	wxButton* mButtonPlus = nullptr;
	wxButton* mButtonMinus = nullptr;
	wxButton* mButtonMultiply = nullptr;
	wxButton* mButtonDivision = nullptr;
	wxButton* mButtonEqual = nullptr;
	wxButton* mButtonModule = nullptr;
	wxButton* mButtonSin = nullptr;
	wxButton* mButtonCos = nullptr;
	wxButton* mButtonTan = nullptr;
	wxButton* mButtonBackspaceDelete = nullptr;

	wxButton* mButtonZero = nullptr;
	wxButton* mButtonOne = nullptr;
	wxButton* mButtonTwo = nullptr;
	wxButton* mButtonThree = nullptr;
	wxButton* mButtonFour = nullptr;
	wxButton* mButtonFive = nullptr;
	wxButton* mButtonSix = nullptr;
	wxButton* mButtonSeven = nullptr;
	wxButton* mButtonEight = nullptr;
	wxButton* mButtonNine = nullptr;

	wxButton* mButtonClear = nullptr;


	void InitializeCalculatorGUI();
	void PerformCalculation();
	void ExceptionHandlingInvalidExpression();	
	void BackspaceOrDelete();
	void SpecialCaseOnNumberZero();
	
	
	void OnClear(wxCommandEvent& event);
	void OnZero(wxCommandEvent& event);
	void OnOne(wxCommandEvent& event);
	void OnTwo(wxCommandEvent& event);
	void OnThree(wxCommandEvent& event);
	void OnFour(wxCommandEvent& event);
	void OnFive(wxCommandEvent& event);
	void OnSix(wxCommandEvent& event);
	void OnSeven(wxCommandEvent& event);
	void OnEight(wxCommandEvent& event);
	void OnNine(wxCommandEvent& event);	
	void OnNegativeOne(wxCommandEvent& event);
	void OnDecimal(wxCommandEvent& event);
	void OnPlus(wxCommandEvent& event);
	void OnMinus(wxCommandEvent& event);
	void OnMultiply(wxCommandEvent& event);
	void OnDivision(wxCommandEvent& event);
	void OnEqual(wxCommandEvent& event);
	void OnModulo(wxCommandEvent& event);
	void OnSin(wxCommandEvent& event);
	void OnCos(wxCommandEvent& event);
	void OnTan(wxCommandEvent& event);
	void OnBackspaceDelete(wxCommandEvent& event);
		
	void OnKeyPressed(wxKeyEvent& event);

	wxDECLARE_EVENT_TABLE();
};

