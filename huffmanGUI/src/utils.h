/**
 * @file utils.h
 *
 */
#pragma once
#include "HuffmanFrame.h"

enum {
	ID_ChooseButtonClick = 1,
	ID_CompressButtonClick,
	ID_DecompressClick
};

wxBEGIN_EVENT_TABLE(HuffmanFrame, wxFrame)
EVT_MENU(ID_CompressButtonClick, HuffmanFrame::OnCompressClick)
wxEND_EVENT_TABLE()
