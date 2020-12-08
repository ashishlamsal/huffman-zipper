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
#include "Compressor.h"
#include "Decompressor.h"
/**
* This class models the frame to be rendered on the App
*/
class MyFrame1 : public wxFrame
{
private:
	wxDECLARE_EVENT_TABLE(); 
	Compressor compression;		/**<	Compressor object*/
	Decompressor decompression;	/**<	Decompressor object*/
	std::string inputPath;		/**<	Path to the browsed file/directory*/
	int selection;				/**<	selection=0 for file selection, 1 for dir selection*/

	/**
	 * This is an event handling function for 'choose' button click event.
	 * @params: wxCommandEvent&
	 * @returns:void
	 * On radio selecting any item(file/folder) on 'Choose', it sets MyFrame::selection accordingly
	 * selection = 1 for folder
	 * selection = 0 for file
	 */
	void OnChooseClick(wxCommandEvent& event); //{ event.Skip(); }
	
	/**
	 * This is an event handling function for 'compress' button click event.
	 * @params: wxCommandEvent&
	 * @returns:void
	 * On clicking compress button, it calls @see compress()
	 */
	void OnCompressClick(wxCommandEvent& event); //{ event.Skip(); }
	
	/**
	 * This is an event handling function for 'decompress' button click event.
	 * @params: wxCommandEvent&
	 * @returns:void
	 * On clicking decompress button, it calls @see decompress()
	 */
	void OnDecompressClick(wxCommandEvent& event); //{ event.Skip(); }
	
	/**
	 * This function takes the file/directory path and performs compression on it.
	 * @params: std::string
	 * @returns:void
	 * On implementation level, it calls @see Compression::compress()s
	 */
	void compress(std::string);
	
	/**
	 * This function takes the file path of the compress file and performs decompression on it.
	 * @params: std::string
	 * @returns:void
	 * On implementation level, it calls @see Deompression::decompress()
	 */
	void decompress(std::string);
	/**
	 * This function toogles widget between filePicker and dirPicker based on selection of MyFrame::m_radioBox3.
	 * @params: None
	 * @returns:void
	 */
	void tooglePicker();
	
	/**
	 * This function clears the input of browse widgets.
	 * @params: None
	 * @returns:void
	 */
	void clearBrowse();

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

public:

	MyFrame1(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500, 448), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MyFrame1();
};