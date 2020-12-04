

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "noname.h"

Compressor compression;
//compression.compressFile(INPUT_FILE_PATH);
//compression.compressFolder(DIRECTORY);
//compression.compressFiles({ "./src/input1.txt", "./src/small-text.txt" });

//-----------------------Decompression-------------------------//
Decompressor decompression;
//decompression.decompressFile("./src/input1.huf");
//decompression.decompressFile(COMPRESSED_FILE_PATH);


enum {
	ID_ChooseButtonClick = 1,
	ID_CompressButtonClick,
	ID_DecompressClick
};

wxBEGIN_EVENT_TABLE(MyFrame1, wxFrame)
EVT_MENU(ID_CompressButtonClick, MyFrame1::OnCompressClick)
wxEND_EVENT_TABLE()

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

bool MyApp::OnInit()
{
	MyFrame1* frame = new MyFrame1(NULL, NULL, "Hello world", wxPoint(50, 50), wxSize(450, 340), wxDEFAULT_FRAME_STYLE);
	frame->Show(true);
	return true;
}

void MyFrame1::OnCompressClick(wxCommandEvent& event) {
	try {

		this->m_textCtrl1->Clear();
		this->m_textCtrl1->AppendText("Compressing ...");
		auto inputFilePath = this->m_filePicker1->GetPath();
		std::string inputFilePathString = inputFilePath.ToStdString();
		this->m_textCtrl1->AppendText(inputFilePathString);
		compression.compressFile(inputFilePathString);
		this->m_textCtrl1->AppendText("Compression Successful");
	}
	catch (std::exception& err) {
		wxLogMessage(err.what());
		this->m_textCtrl1->Clear();
	}
	wxString str = this->m_textCtrl1->GetValue();
}
void MyFrame1::OnChooseClick(wxCommandEvent& event) {
	tooglePicker();
}
void MyFrame1::OnDecompressClick(wxCommandEvent& event) {
	try {
		this->m_textCtrl1->Clear();
		this->m_textCtrl1->AppendText("Decompressing ...");
		auto compressedFilePath = this->m_filePicker1->GetPath();
		std::string compressedFilePathString = compressedFilePath.ToStdString();
		this->m_textCtrl1->AppendText(compressedFilePathString);
		decompression.decompressFile(compressedFilePathString);
		this->m_textCtrl1->AppendText("Depression Successful");
	}
	catch (std::exception& err) {
		wxLogMessage(err.what());
		this->m_textCtrl1->Clear();
	}
}


wxIMPLEMENT_APP(MyApp);




///////////////////////////////////////////////////////////////////////////

void MyFrame1::tooglePicker() {
	int selection = this->m_radioBox3->GetSelection();
	if (!selection) {
		this->m_filePicker1->Show();
		this->m_dirPicker1->Hide();
	}
	else {
		this->m_filePicker1->Hide();
		this->m_dirPicker1->Show();
	}

}

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxString m_radioBox3Choices[] = { wxT("File"), wxT("Folder") };
	int m_radioBox3NChoices = sizeof( m_radioBox3Choices ) / sizeof( wxString );
	m_radioBox3 = new wxRadioBox( this, wxID_ANY, wxT("Choose"), wxDefaultPosition, wxDefaultSize, m_radioBox3NChoices, m_radioBox3Choices, 1, wxRA_SPECIFY_ROWS );
	m_radioBox3->SetSelection( 1 );
	bSizer1->Add( m_radioBox3, 0, wxALL, 5 );
	

	m_filePicker1 = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE);
	bSizer1->Add(m_filePicker1, 0, wxALL | wxEXPAND, 5);
	
	m_dirPicker1 = new wxDirPickerCtrl(this, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE);
	bSizer1->Add(m_dirPicker1, 0, wxALL | wxEXPAND, 5);

	tooglePicker();
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button1 = new wxButton( this, ID_CompressButtonClick, wxT("Compress"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_button1, 1, wxALL, 5 );
	
	m_button2 = new wxButton( this, wxID_ANY, wxT("Decompress"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_button2, 1, wxALL, 5 );
	
	
	bSizer1->Add( bSizer2, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_textCtrl1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_textCtrl1, 3, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_button3 = new wxButton( this, wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_button3, 0, wxALL, 5 );
	
	
	bSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_button4 = new wxButton( this, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_button4, 0, wxALL, 5 );
	
	m_button5 = new wxButton( this, wxID_ANY, wxT("About"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_button5, 0, wxALL, 5 );
	
	m_button6 = new wxButton( this, wxID_ANY, wxT("Quit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_button6, 0, wxALL, 5 );
	
	
	bSizer3->Add( bSizer4, 0, wxEXPAND, 5 );
	
	
	bSizer1->Add( bSizer3, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_radioBox3->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( MyFrame1::OnChooseClick ), NULL, this );
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::OnCompressClick ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::OnDecompressClick ), NULL, this );
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_radioBox3->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( MyFrame1::OnChooseClick ), NULL, this );
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::OnCompressClick ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::OnDecompressClick ), NULL, this );
	
}
