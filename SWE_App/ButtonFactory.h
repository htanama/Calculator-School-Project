#pragma once

#include <wx/wx.h>
#include <wx/button.h>

class ButtonFactory : public wxButton
{
private:

	
		
	// The methods may be static.
	// Inside the ButtonFactory, you will create functions that facilitate creating each button. 
	// Your Button Factory should have one method for generically creating buttons based off of parameters 
	// and multiple methods for creating each specific button.

public:
	
	ButtonFactory() = default;
	ButtonFactory(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	

	static ButtonFactory* CreateZeroButton(wxWindow* parent, wxWindowID id);
	static ButtonFactory* CreateOneButton(wxWindow* parent, wxWindowID id);
	static ButtonFactory* CreateTwoButton(wxWindow* parent, wxWindowID id);
	static ButtonFactory* CreateThreeButton(wxWindow* parent, wxWindowID id);
	static ButtonFactory* CreateFourButton(wxWindow* parent, wxWindowID id);
	static ButtonFactory* CreateFiveButton(wxWindow* parent, wxWindowID id);
	static ButtonFactory* CreateSixButton(wxWindow* parent, wxWindowID id);
	static ButtonFactory* CreateSevenButton(wxWindow* parent, wxWindowID id);
	static ButtonFactory* CreateEightButton(wxWindow* parent, wxWindowID id);
	static ButtonFactory* CreateNineButton(wxWindow* parent, wxWindowID id);

	static ButtonFactory* CreateClearButton(wxWindow* parent, wxWindowID id);
	static ButtonFactory* CreateMinusButton(wxWindow* parent, wxWindowID id);
	static ButtonFactory* CreateDivisionButton(wxWindow* parent, wxWindowID id);
	static ButtonFactory* CreateMultiplyButton(wxWindow* parent, wxWindowID id);
	static ButtonFactory* CreateModuleButton(wxWindow* parent, wxWindowID id);	
	static ButtonFactory* CreatePlusButton(wxWindow* parent, wxWindowID id);
	static ButtonFactory* CreateBackspaceDeleteButton(wxWindow* parent, wxWindowID id);
	static ButtonFactory* CreateEqualButton(wxWindow* parent, wxWindowID id);


	static ButtonFactory* CreateDecimalButton(wxWindow* parent, wxWindowID id);
	static ButtonFactory* CreateNegativeOneButton(wxWindow* parent, wxWindowID id);
	static ButtonFactory* CreateSinButton(wxWindow* parent, wxWindowID id);
	static ButtonFactory* CreateCosButton(wxWindow* parent, wxWindowID id);
	static ButtonFactory* CreateTanButton(wxWindow* parent, wxWindowID id);
		
};

