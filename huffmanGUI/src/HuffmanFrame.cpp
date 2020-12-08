#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <regex>
#include <chrono>
#include <fstream>

#include "HuffmanFrame.h"
#include "HuffmanApp.h"
#include "utils.h"

void HuffmanFrame::OnCompressClick(wxCommandEvent& event) {
	try {
		this->m_textCtrl1->Clear();
		wxStreamToTextRedirector redirect(m_textCtrl1);
		if (!selection) {
			inputPath = this->m_filePicker1->GetPath().ToStdString();
		}
		else {
			inputPath = this->m_dirPicker1->GetPath().ToStdString();

		}
		compress(inputPath);
		clearBrowse();

	}
	catch (std::exception& err) {
		wxLogMessage(err.what());
		this->m_textCtrl1->Clear();
	}
	wxString str = this->m_textCtrl1->GetValue();
}

void HuffmanFrame::OnChooseClick(wxCommandEvent& event) {
	tooglePicker();
}


void HuffmanFrame::OnDecompressClick(wxCommandEvent& event) {
	try {
		this->m_textCtrl1->Clear();
		wxStreamToTextRedirector redirect(m_textCtrl1);
		if (selection) {
			throw std::exception("Please select a valid compressed file");
		}
		this->m_textCtrl1->Clear();
		inputPath = this->m_filePicker1->GetPath().ToStdString();
		decompress(inputPath);
		clearBrowse();
	}
	catch (std::exception& err) {
		wxLogMessage(err.what());
		this->m_textCtrl1->Clear();
	}
}

void HuffmanFrame::compress(std::string input) {
	if (!selection)
		compression.compressFile(input);
	else
		compression.compressFolder(input);
}


void HuffmanFrame::decompress(std::string input) {
	decompression.decompressFile(input);
}


void HuffmanFrame::tooglePicker() {
	selection = this->m_radioBox3->GetSelection();
	if (!selection) {
		this->m_filePicker1->Show();
		this->m_dirPicker1->Hide();

	}
	else {
		this->m_filePicker1->Hide();
		this->m_dirPicker1->Show();

	}
}

void HuffmanFrame::clearBrowse() {
	this->m_filePicker1->SetPath(wxT(""));
	this->m_dirPicker1->SetPath(wxT(""));
}

wxIMPLEMENT_APP(HuffmanApp);

HuffmanFrame::HuffmanFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxString m_radioBox3Choices[] = { wxT("File"), wxT("Folder") };
	int m_radioBox3NChoices = sizeof(m_radioBox3Choices) / sizeof(wxString);
	m_radioBox3 = new wxRadioBox(this, wxID_ANY, wxT("Choose"), wxDefaultPosition, wxDefaultSize, m_radioBox3NChoices, m_radioBox3Choices, 1, wxRA_SPECIFY_ROWS);
	m_radioBox3->SetSelection(1);
	bSizer1->Add(m_radioBox3, 0, wxALL, 5);


	m_filePicker1 = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE);
	bSizer1->Add(m_filePicker1, 0, wxALL | wxEXPAND, 5);

	m_dirPicker1 = new wxDirPickerCtrl(this, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE);
	bSizer1->Add(m_dirPicker1, 0, wxALL | wxEXPAND, 5);

	tooglePicker();

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);

	m_button1 = new wxButton(this, ID_CompressButtonClick, wxT("Compress"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(m_button1, 1, wxALL, 5);

	m_button2 = new wxButton(this, wxID_ANY, wxT("Decompress"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(m_button2, 1, wxALL, 5);


	bSizer1->Add(bSizer2, 0, wxALIGN_CENTER_HORIZONTAL | wxEXPAND, 5);

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxHORIZONTAL);

	
	m_textCtrl1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	bSizer3->Add(m_textCtrl1, 3, wxALL | wxEXPAND, 5);


	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxVERTICAL);

	m_button3 = new wxButton(this, wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_button3, 0, wxALL, 5);


	bSizer4->Add(0, 0, 1, wxEXPAND, 5);

	m_button4 = new wxButton(this, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_button4, 0, wxALL, 5);

	m_button5 = new wxButton(this, wxID_ANY, wxT("About"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_button5, 0, wxALL, 5);

	m_button6 = new wxButton(this, wxID_ANY, wxT("Quit"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_button6, 0, wxALL, 5);


	bSizer3->Add(bSizer4, 0, wxEXPAND, 5);


	bSizer1->Add(bSizer3, 1, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	m_radioBox3->Connect(wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(HuffmanFrame::OnChooseClick), NULL, this);
	m_button1->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(HuffmanFrame::OnCompressClick), NULL, this);
	m_button2->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(HuffmanFrame::OnDecompressClick), NULL, this);
}

HuffmanFrame::~HuffmanFrame() {
	// Disconnect Events
	m_radioBox3->Disconnect(wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(HuffmanFrame::OnChooseClick), NULL, this);
	m_button1->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(HuffmanFrame::OnCompressClick), NULL, this);
	m_button2->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(HuffmanFrame::OnDecompressClick), NULL, this);
}
