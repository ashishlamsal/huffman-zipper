#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/radiobox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/filepicker.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/frame.h>
#include <huffmanHeader.h>

///////////////////////////////////////////////////////////////////////////







///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame 
{
	private:
	
		void OnChooseClick(wxCommandEvent& event); //{ event.Skip(); }
		void OnCompressClick(wxCommandEvent& event); //{ event.Skip(); }
		void OnDecompressClick(wxCommandEvent& event); //{ event.Skip(); }
		wxDECLARE_EVENT_TABLE();
		void tooglePicker();
	protected:
		wxRadioBox* m_radioBox3;
		wxFilePickerCtrl* m_filePicker1;
		wxDirPickerCtrl* m_dirPicker1;
		wxButton* m_button1;
		wxButton* m_button2;
		wxTextCtrl* m_textCtrl1;
		wxButton* m_button3;
		wxButton* m_button4;
		wxButton* m_button5;
		wxButton* m_button6;
		
		// Virtual event handlers, overide them in your derived class
		
	
	public:
		
		MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,448 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MyFrame1();
	
};

