#include "Main.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();

	ChessGameRemake::Main^ form = gcnew ChessGameRemake::Main();
	Application::Run(form);
	form->Show();
}