#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "HuffmanFrame.h"

/**
 *	This class models the Starting App
 */
class HuffmanApp : public wxApp {
public:
	/**
	 * Function to initialize application. @refer wxWidgets documentation
	 */
	virtual bool OnInit(); 
};

