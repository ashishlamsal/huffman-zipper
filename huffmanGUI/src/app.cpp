#include "MyFrame.h"
#include"App.h"

bool MyApp::OnInit()
{
	MyFrame1* frame = new MyFrame1(NULL, NULL, "Hello world", wxPoint(50, 50), wxSize(450, 340), wxDEFAULT_FRAME_STYLE);
	frame->Show(true);

	return true;
}