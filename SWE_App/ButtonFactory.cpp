#include "ButtonFactory.h"

ButtonFactory::ButtonFactory(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size)
	: wxButton(parent, id, label, pos, size)
{
}

ButtonFactory* ButtonFactory::CreateZeroButton(wxWindow* parent, wxWindowID id)
{	
	return new ButtonFactory(parent, id, "0", wxPoint(80, 40 * 7), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreateOneButton(wxWindow* parent, wxWindowID id)
{	
	return new ButtonFactory(parent, id, "1", wxPoint(1, 40), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreateTwoButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "2", wxPoint(80, 40), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreateThreeButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "3", wxPoint(80 * 2, 40), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreateFourButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "4", wxPoint(1, 40 * 3), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreateFiveButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "5", wxPoint(80, 40 * 3), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreateSixButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "6", wxPoint(80 * 2, 40 * 3), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreateSevenButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "7", wxPoint(1, 40 * 5), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreateEightButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "8", wxPoint(80, 40 * 5), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreateNineButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "9", wxPoint(80 * 2, 40 * 5), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreateClearButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "C", wxPoint(80 * 4, 40), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreateMinusButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "-", wxPoint(80 * 3, 40 * 3), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreateDivisionButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "/", wxPoint(80 * 3, 40 * 7), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreateMultiplyButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "*", wxPoint(80 * 3, 40 * 5), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreateModuleButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "%", wxPoint(80 * 4, 40 * 3), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreatePlusButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "+", wxPoint(80 * 3, 40), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreateBackspaceDeleteButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "Backspace/Delete", wxPoint(1, 40 * 9), wxSize(160, 80));
}

ButtonFactory* ButtonFactory::CreateEqualButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "=", wxPoint(80 * 2, 40 * 9), wxSize(160, 80));
}

ButtonFactory* ButtonFactory::CreateDecimalButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, ".", wxPoint(80 * 2, 40 * 7), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreateNegativeOneButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "+/-", wxPoint(1, 40 * 7), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreateSinButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "Sin(n)", wxPoint(80 * 4, 40 * 5), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreateCosButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "Cos(n)", wxPoint(80 * 4, 40 * 7), wxSize(80, 80));
}

ButtonFactory* ButtonFactory::CreateTanButton(wxWindow* parent, wxWindowID id)
{
	return new ButtonFactory(parent, id, "Tan(n)", wxPoint(80 * 4, 40 * 9), wxSize(80, 80));
}

