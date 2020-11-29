#include "HuffmanForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	huffmanGUI::HuffmanForm form;
	Application::Run(% form);
}
