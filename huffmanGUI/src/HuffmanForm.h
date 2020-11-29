#pragma once
//#include "Compressor.h"
//#include "Decompressor.h"

namespace huffmanGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for HuffmanForm
	/// </summary>
	public ref class HuffmanForm : public System::Windows::Forms::Form
	{
	public:
		HuffmanForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~HuffmanForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ buttonCompress;
	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->buttonCompress = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// buttonCompress
			// 
			this->buttonCompress->Location = System::Drawing::Point(257, 429);
			this->buttonCompress->Name = L"buttonCompress";
			this->buttonCompress->Size = System::Drawing::Size(217, 104);
			this->buttonCompress->TabIndex = 0;
			this->buttonCompress->Text = L"Compress";
			this->buttonCompress->UseVisualStyleBackColor = true;
			this->buttonCompress->Click += gcnew System::EventHandler(this, &HuffmanForm::buttonCompress_Click);
			// 
			// HuffmanForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(868, 612);
			this->Controls->Add(this->buttonCompress);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.1F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Margin = System::Windows::Forms::Padding(8, 7, 8, 7);
			this->MaximizeBox = false;
			this->Name = L"HuffmanForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Huffman Zipper";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void buttonCompress_Click(System::Object^ sender, System::EventArgs^ e) {
		//Compressor compression;
		//compression.compressFile("../src/input1.txt");
		Application::Exit();
	}
	};
}
