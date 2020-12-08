/**
 * @file utils.h
 *
 */
#pragma once
#include"MyFrame.h"


enum {
	ID_ChooseButtonClick = 1,
	ID_CompressButtonClick,
	ID_DecompressClick
};

wxBEGIN_EVENT_TABLE(MyFrame1, wxFrame)
EVT_MENU(ID_CompressButtonClick, MyFrame1::OnCompressClick)
wxEND_EVENT_TABLE()
