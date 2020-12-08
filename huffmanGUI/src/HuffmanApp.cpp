#include "HuffmanFrame.h"
#include "HuffmanApp.h"

bool HuffmanApp::OnInit() {
	HuffmanFrame* frame = new HuffmanFrame(NULL, NULL, "Huffman Zipper", wxPoint(50, 50), wxSize(800, 600), wxDEFAULT_FRAME_STYLE);
	frame->Show(true);

	return true;
}