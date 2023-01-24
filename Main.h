#include <cstdlib>
#include <ctime>
#include <iostream>
#include <windows.h>
#include <string>
#include "Settings.h"
#include "ChessBoard.h"
#pragma once

namespace ChessGameRemake {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ Main
	/// </summary>
	public ref class Main : public System::Windows::Forms::Form
	{
	
	public: Settings^ settings = gcnew Settings(); // Field with settings object.
	public: ChessBoard^ cb = gcnew ChessBoard(); // Field with chess.

	public: array<System::Windows::Forms::Button^, 2>^ game_field = gcnew array<System::Windows::Forms::Button^, 2>(8, 8); // 2d array with buttons.
	public:System::Media::SoundPlayer^ soundPlayer; // Controls the playback of a WAV audio file.
	public: System::Drawing::Point point_of_field = System::Drawing::Point(6, 20);
	public: int** map = new int*[8]; // Map with 
	public: int player = 0; // Id of curent move player.
	public: bool isComputer = false; // Game with computer.
	public: Point^ selectedPoint = gcnew Point(-1, -1); // Selected point.
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	public:
		Main(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			for (int x = 0; x < 8; x++)
				for (int y = 0; y < 8; y++) {
					System::Windows::Forms::Button^ button = (gcnew System::Windows::Forms::Button());
					button->Name = "button_" + x.ToString() + y.ToString();
					button->Size = System::Drawing::Size(50, 50);
					button->Location = System::Drawing::Point(x * 50 + point_of_field.X, y * 50 + point_of_field.Y);
					button->BackColor = (x + y) % 2 == 0 ? settings->colorWhite : settings->colorBlack;
					button->Click += gcnew System::EventHandler(this, &Main::OnButtonPress);
					button->BackgroundImageLayout = ImageLayout::Stretch;
					button->FlatStyle = FlatStyle::Flat;
					button->FlatAppearance->BorderSize = 0;
					game_field[x, y] = button;
					groupBox_ChessBoard->Controls->Add(button);
				}
			srand(time(NULL));
			for (int i = 0; i < 8; i++)
				map[i] = new int[8];
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~Main()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;

	private: System::Windows::Forms::ToolStripMenuItem^ gameToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ newGameToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ playerVsPlayerToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ playerVsComputerToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ loadLevelToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ settingsToolStripMenuItem;
	private: System::Windows::Forms::GroupBox^ groupBox_ChessBoard;
	private: System::Windows::Forms::Label^ label_gameOver;
	private: System::Windows::Forms::Label^ label_whichPlayer;
	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->gameToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newGameToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->playerVsPlayerToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->playerVsComputerToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadLevelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->settingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBox_ChessBoard = (gcnew System::Windows::Forms::GroupBox());
			this->label_gameOver = (gcnew System::Windows::Forms::Label());
			this->label_whichPlayer = (gcnew System::Windows::Forms::Label());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Font = (gcnew System::Drawing::Font(L"Cascadia Code SemiBold", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->gameToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(7, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(436, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// gameToolStripMenuItem
			// 
			this->gameToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->newGameToolStripMenuItem,
					this->loadLevelToolStripMenuItem, this->settingsToolStripMenuItem
			});
			this->gameToolStripMenuItem->Name = L"gameToolStripMenuItem";
			this->gameToolStripMenuItem->Size = System::Drawing::Size(47, 20);
			this->gameToolStripMenuItem->Text = L"Game";
			// 
			// newGameToolStripMenuItem
			// 
			this->newGameToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->playerVsPlayerToolStripMenuItem,
					this->playerVsComputerToolStripMenuItem
			});
			this->newGameToolStripMenuItem->Name = L"newGameToolStripMenuItem";
			this->newGameToolStripMenuItem->Size = System::Drawing::Size(193, 22);
			this->newGameToolStripMenuItem->Text = L"New game";
			// 
			// playerVsPlayerToolStripMenuItem
			// 
			this->playerVsPlayerToolStripMenuItem->Name = L"playerVsPlayerToolStripMenuItem";
			this->playerVsPlayerToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
			this->playerVsPlayerToolStripMenuItem->Size = System::Drawing::Size(298, 22);
			this->playerVsPlayerToolStripMenuItem->Text = L"Player vs. Player";
			this->playerVsPlayerToolStripMenuItem->Click += gcnew System::EventHandler(this, &Main::playerVsPlayerToolStripMenuItem_Click);
			// 
			// playerVsComputerToolStripMenuItem
			// 
			this->playerVsComputerToolStripMenuItem->Name = L"playerVsComputerToolStripMenuItem";
			this->playerVsComputerToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift)
				| System::Windows::Forms::Keys::N));
			this->playerVsComputerToolStripMenuItem->Size = System::Drawing::Size(298, 22);
			this->playerVsComputerToolStripMenuItem->Text = L"Player vs. Computer";
			this->playerVsComputerToolStripMenuItem->Click += gcnew System::EventHandler(this, &Main::playerVsComputerToolStripMenuItem_Click);
			// 
			// loadLevelToolStripMenuItem
			// 
			this->loadLevelToolStripMenuItem->Name = L"loadLevelToolStripMenuItem";
			this->loadLevelToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::L));
			this->loadLevelToolStripMenuItem->Size = System::Drawing::Size(193, 22);
			this->loadLevelToolStripMenuItem->Text = L"Load level";
			this->loadLevelToolStripMenuItem->Click += gcnew System::EventHandler(this, &Main::loadLevelToolStripMenuItem_Click);
			// 
			// settingsToolStripMenuItem
			// 
			this->settingsToolStripMenuItem->Name = L"settingsToolStripMenuItem";
			this->settingsToolStripMenuItem->Size = System::Drawing::Size(193, 22);
			this->settingsToolStripMenuItem->Text = L"Settings";
			this->settingsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Main::SeToolStripMenuItem_Click);
			// 
			// groupBox_ChessBoard
			// 
			this->groupBox_ChessBoard->Enabled = false;
			this->groupBox_ChessBoard->Location = System::Drawing::Point(12, 27);
			this->groupBox_ChessBoard->Name = L"groupBox_ChessBoard";
			this->groupBox_ChessBoard->Size = System::Drawing::Size(412, 427);
			this->groupBox_ChessBoard->TabIndex = 1;
			this->groupBox_ChessBoard->TabStop = false;
			this->groupBox_ChessBoard->Text = L"Chess board";
			// 
			// label_gameOver
			// 
			this->label_gameOver->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label_gameOver->Location = System::Drawing::Point(183, 457);
			this->label_gameOver->Name = L"label_gameOver";
			this->label_gameOver->Size = System::Drawing::Size(241, 16);
			this->label_gameOver->TabIndex = 2;
			this->label_gameOver->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label_whichPlayer
			// 
			this->label_whichPlayer->AutoSize = true;
			this->label_whichPlayer->Location = System::Drawing::Point(12, 457);
			this->label_whichPlayer->Name = L"label_whichPlayer";
			this->label_whichPlayer->Size = System::Drawing::Size(0, 16);
			this->label_whichPlayer->TabIndex = 3;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(436, 479);
			this->Controls->Add(this->label_whichPlayer);
			this->Controls->Add(this->label_gameOver);
			this->Controls->Add(this->groupBox_ChessBoard);
			this->Controls->Add(this->menuStrip1);
			this->Font = (gcnew System::Drawing::Font(L"Cascadia Code SemiBold", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
			this->Name = L"Main";
			this->Text = L"Chess Game";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::Void OnButtonPress(System::Object^ sender, System::EventArgs^ e) {
			System::Windows::Forms::Button^ button = (System::Windows::Forms::Button^)sender;

			if (button->BackColor != settings->colorMove && button->BackColor != settings->colorCut) {
				ResetButtonsColor(map);
				selectedPoint->X = -1;
			}
			if (selectedPoint->X == -1) {
				selectedPoint = gcnew Point(int::Parse(button->Name[7].ToString()), int::Parse(button->Name[8].ToString()));
				if (cb->getFigure(selectedPoint)->idPlayer != player) return;
				map = cb->getPossibleActions(selectedPoint);
				bool isNotMoveble = true;
				for (int x = 0; x < 8; x++)
					for (int y = 0; y < 8; y++) {
						if (map[x][y] == 1) game_field[x, y]->BackColor = settings->colorMove;
						if (map[x][y] == 2) game_field[x, y]->BackColor = settings->colorCut;
						if (settings->PaintAllPossible) {
							if (map[x][y] == 3) game_field[x, y]->BackColor = Color::Orange;
							if (map[x][y] == 4) game_field[x, y]->BackColor = Color::OrangeRed;
						}
						isNotMoveble = false;
					}
				if (isNotMoveble) selectedPoint->X = -1;
			}
			else {
				if (button->BackColor == settings->colorMove) {
					soundPlayer = gcnew System::Media::SoundPlayer("res/sound_move.wav");
					soundPlayer->Play();
					Point^ newPoint = gcnew Point(int::Parse(button->Name[7].ToString()), int::Parse(button->Name[8].ToString()));
					cb->MoveFigure(selectedPoint, newPoint);
					ResetButtonsColor(map);
					DrowFigure(selectedPoint);
					DrowFigure(newPoint);
					selectedPoint->X = -1;
					player = player % 2 + 1;
					label_whichPlayer->Text = player.ToString() + " player move.";
				}
				else if (button->BackColor == settings->colorCut) {
					soundPlayer = gcnew System::Media::SoundPlayer("res/sound_cut.wav");
					soundPlayer->Play();
					Point^ newPoint = gcnew Point(int::Parse(button->Name[7].ToString()), int::Parse(button->Name[8].ToString()));
					cb->CutFigure(selectedPoint, newPoint);
					ResetButtonsColor(map);
					DrowFigure(selectedPoint);
					DrowFigure(newPoint);
					selectedPoint->X = -1;
					player = player % 2 + 1;
					label_whichPlayer->Text = player.ToString() + " player move.";
				}

				label_gameOver->Text = cb->GameOver();
				if (label_gameOver->Text == "Checkmate for 2 player" || label_gameOver->Text == "Checkmate for 1 player")
					groupBox_ChessBoard->Enabled = false;

				if (isComputer && groupBox_ChessBoard->Enabled == true) {
					Sleep(rand() % 3000 + 1000);
					RandomMoveForFirstPlayer(sender, e);
				}
			}
		}
		/// <summary>
		/// Reset color for button.
		/// </summary>
		/// <param name="p">Button coordinates.</param>
		private: void ResetButtonColor(Point^ p) {
			game_field[p->X, p->Y]->BackColor = (p->X + p->Y) % 2 == 0 ? settings->colorWhite : settings->colorBlack;
		}

		/// <summary>
		/// Reset colors for buttons.
		/// </summary>
		/// <param name="map">Map of buttons.</param>
		private: void ResetButtonsColor(int** map) {
			   for (int x = 0; x < 8; x++)
				   for (int y = 0; y < 8; y++) {
					   if (map[x][y] != 0) ResetButtonColor(gcnew Point(x, y));
				   }
		}

		/// <summary>
		/// Reset color for all buttons.
		/// </summary>
		private: void ResetAllButtonsColor() {
			for (int x = 0; x < 8; x++)
				for (int y = 0; y < 8; y++) {
					ResetButtonColor(gcnew Point(x, y));
				}
		}

		/// <summary>
		/// Draw a figure on the board.
		/// </summary>
		/// <param name="p">Figure coordinates.</param>
		public: void DrowFigure(Point^ p) {
			Figure^ figure = cb->getFigure(p);
			if (figure->name != "none") game_field[p->X, p->Y]->BackgroundImage = figure->image;
			else game_field[p->X, p->Y]->BackgroundImage = nullptr;
		}

		/// <summary>
			   /// Draw all figures on the board.
			   /// </summary>
		public: void DrowAllFigures() {
		   for (int x = 0; x < 8; x++)
			   for (int y = 0; y < 8; y++) {
				   DrowFigure(gcnew Point(x, y));
			   }
		}


		/// <summary>
		/// Create a new game and unlock the board.
		/// </summary>
		/// <param name="path">Path to the file with level.</param>
		private: void NewGame() { NewGame("Default"); }

		/// <summary>
		/// Create a new game and unlock the board.
		/// </summary>
		/// <param name="path">Path to the file with level.</param>
		private: void NewGame(System::String^ path) {
			groupBox_ChessBoard->Enabled = true;
			ResetAllButtonsColor();
			cb->ArrangeFigures(path);
			DrowAllFigures();
			selectedPoint->X = -1;

			label_gameOver->Text = cb->GameOver();
			/*if (label_gameOver->Text == gcnew System::String("Checkmate for 2 player") || label_gameOver->Text == gcnew System::String("Checkmate for 1 player"))
				groupBox_ChessBoard->Enabled = false;*/
		}

		/// <summary>
		/// Open the settings form for changing settings.
		/// </summary>
		private: void SeToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			//SettingsForm sf = new(settings);
			/*sf.Owner = this;
			sf.ShowDialog();*/
			//settings.ReadFromCfg();
			ResetAllButtonsColor();
		}

		/// <summary>
		/// Do computer move for first player when player vs. computer.
		/// </summary>
		private: void RandomMoveForFirstPlayer(System::Object^ sender, System::EventArgs^ e) {
			int num_of_figure = rand() % cb->figuresPlayer1->Length;
			int amount_possible_actions = 0;
			int** possible_actions_map;
			array<Point^>^ possible_actions = gcnew array<Point^>(20);
			int count = 0;

			possible_actions_map = cb->getPossibleActions(cb->figuresPlayer1[num_of_figure]->position);
			while (ChessBoard::IsEmptyMap(possible_actions_map)) {
				num_of_figure = rand() % cb->figuresPlayer1->Length;
				possible_actions_map = cb->getPossibleActions(cb->figuresPlayer1[num_of_figure]->position);
				count++;
				if (count > 5) {
					label_gameOver->Text = "Checkmate for 1 player";
					groupBox_ChessBoard->Enabled = false;
					MessageBox::Show("Checkmate for 1 player.", "GameOver!");
					return;
				}
			}

			selectedPoint = cb->figuresPlayer1[num_of_figure]->position;

			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++) {
					if (possible_actions_map[x][y] == 1 || possible_actions_map[x][y] == 2) {
						possible_actions[amount_possible_actions] = gcnew Point(x, y);
						amount_possible_actions++;
						if (amount_possible_actions == 19) break;
					}
				}
				if (amount_possible_actions == 19) break;
			}

			   int num_of_action = rand() % amount_possible_actions;

			   Point^ randomPoint = possible_actions[num_of_action];
			   if (cb->getFigure(randomPoint)->name != "none") {
				   soundPlayer = gcnew System::Media::SoundPlayer("res/sound_cut.wav");
				   soundPlayer->Play();
				   cb->CutFigure(selectedPoint, randomPoint);
				   ResetButtonsColor(map);
				   DrowFigure(selectedPoint);
				   DrowFigure(randomPoint);
				   selectedPoint->X = -1;
				   player = player % 2 + 1;
				   label_whichPlayer->Text = player.ToString() + " player move.";
			   }
			   else {
				   soundPlayer = gcnew System::Media::SoundPlayer("res/sound_move.wav");
				   soundPlayer->Play();
				   cb->MoveFigure(selectedPoint, randomPoint);
				   ResetButtonsColor(map);
				   DrowFigure(selectedPoint);
				   DrowFigure(randomPoint);
				   selectedPoint->X = -1;
				   player = player % 2 + 1;
				   label_whichPlayer->Text = player.ToString() + " player move.";
			   }
			   label_gameOver->Text = cb->GameOver();
			   if (label_gameOver->Text == gcnew System::String("Checkmate for 2 player") || label_gameOver->Text == gcnew System::String("Checkmate for 1 player"))
				   groupBox_ChessBoard->Enabled = false;
		}

		/// <summary>
		/// Start game player vs. player.
		/// </summary>
		private: void playerVsPlayerToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			NewGame();
			isComputer = false;
			player = rand() % 2 + 1;
			label_whichPlayer->Text = player.ToString() + " player move.";
		}

		/// <summary>
		/// Start game player vs. computer.
		/// </summary>
		private: void playerVsComputerToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			NewGame();
			isComputer = true;
			player = 2;
			label_whichPlayer->Text = player.ToString() + " player move.";
		}

		/// <summary>
		/// Load level player vs. computer from file.
		/// </summary>
		private: void loadLevelToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			openFileDialog1 = gcnew OpenFileDialog();
			openFileDialog1->Filter = "txt files (*.txt)|*.txt";

			if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) NewGame(openFileDialog1->FileName);
			isComputer = true;
			player = 2;
			label_whichPlayer->Text = player.ToString() + " player move.";
		}
};
}
