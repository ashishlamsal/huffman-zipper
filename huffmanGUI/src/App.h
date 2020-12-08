#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include"MyFrame.h"

/**
	This class models the Starting App
*/
class MyApp : public wxApp
{
public:
	/**
	* Function to initialize application. @refer wxWidgets documentation
	*/
	virtual bool OnInit(); 
};

