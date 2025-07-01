#pragma warning(disable : 4996)

// Memory Leak Prevention
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

/////////////////////////////////////////

#include "CalculatorFrame.h"
#include "SWE_App.h"



wxIMPLEMENT_APP(SWE_App);

// wxApp::OnInit() in wxWidget is acting as the entry point in wxWidget
bool SWE_App::OnInit() {

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // allocation number to track down memory leak
    // change the -1 with the Dumping objects ->{ number }
    _CrtSetBreakAlloc(-1);

    CalculatorFrame* calculator_frame = new CalculatorFrame(); // heap
    calculator_frame->Show();

    return true;
}