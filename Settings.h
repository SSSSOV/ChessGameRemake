#include <cstdlib>
#include <ctime>
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#pragma once

ref class Settings {

    public: System::Drawing::Color colorBlack; // Color of black fields on the board.
    public: System::Drawing::Color colorWhite; // Color of white fields on the board.
    public: System::Drawing::Color colorMove; // Color of fields on the board where the figure can moves.
    public: System::Drawing::Color colorCut; // Color of fields on the board where the figure can cuts.
    public: int theme; // Board color theme.
    public: bool PaintAllPossible; // Is it necessary to draw all possible actions.

    private: System::String^ defaultPath = L"res/cfg.txt"; // Path to the file with settings value.

    /// <summary>
    /// Constructor of setting. If the file with the value is not found, then the default values are set.
    /// </summary>
    public: Settings() {
        theme = 2;
        colorBlack = System::Drawing::Color::FromArgb(116, 150, 84);
        colorWhite = System::Drawing::Color::FromArgb(236, 238, 212);
        colorMove = System::Drawing::Color::FromArgb(248, 240, 103);
        colorCut = System::Drawing::Color::FromArgb(183, 191, 36);
        PaintAllPossible = false;
        ReadFromCfg();
    }

    /// <summary>
    /// Convert color to string.
    /// </summary>
    public: System::String^ ColorToString(System::Drawing::Color color) {
        return color.ToArgb().ToString();
    }

    /// <summary>
    /// Convert string to color.
    /// </summary>
    public: System::Drawing::Color StringToColor(System::String^ str) {
        return System::Drawing::Color::FromArgb(int::Parse(str));
    }

    /// <summary>
    /// Read file with values from default file.
    /// </summary>
    public: void ReadFromCfg() { ReadFromCfg(defaultPath); }

    /// <summary>
    /// Read file with values from file.
    /// </summary
    public: void ReadFromCfg(System::String^ path) {
        try {
            //std::ifstream streamReader((const char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(path));
            //FILE* streamReader = fopen((const char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(path), "rt");
            //std::string line;
            array<System::String^>^ param;
            
            FILE* streamReader = fopen((const char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(path), "r");
            if (streamReader == NULL) {
                System::Windows::Forms::MessageBox::Show(L"Config file not found.\nThe settings are set by default.\n", L"Warning!"); // wtf
                return;
            }
            char* line = new char[100];
            size_t len = 0;
            while (fgets(line, 100, streamReader) != NULL) {
                param = (gcnew System::String(line))->Split('=');
                if (param[0] == "colorBlack") colorBlack = StringToColor(param[1]);
                else if (param[0] == "colorWhite") colorWhite = StringToColor(param[1]);
                else if (param[0] == "colorMove") colorMove = StringToColor(param[1]);
                else if (param[0] == "colorCut") colorCut = StringToColor(param[1]);
                else if (param[0] == "theme") theme = int::Parse(param[1]);
                else if (param[0] == "paintAllPossible") PaintAllPossible = param[1] == "True";
            }
            fclose(streamReader);
        }
        catch (...) {
            System::Windows::Forms::MessageBox::Show(L"Config file not found.\nThe settings are set by default.\n", L"Warning!");
        }
    }

    /// <summary>
    /// Write settings to default file.
    /// </summary>
    public: void WriteToCfg() { WriteToCfg(defaultPath); }

    /// <summary>
    /// Write settings to file.
    /// </summary>
    public: void WriteToCfg(System::String^ path) {
        FILE* streamWriter = fopen((const char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(path), "w");

        if (streamWriter == NULL)
            System::Windows::Forms::MessageBox::Show(L"Config file not found.\nThe settings are set by default.\n", L"Warning!");

        char* line = NULL;
        size_t len = 0;
        
        fprintf_s(streamWriter, "%s", "theme=" + theme.ToString() + "\n");
        fprintf_s(streamWriter, "%s", "colorBlack=" + ColorToString(colorBlack) + "\n");
        fprintf_s(streamWriter, "%s", "colorWhite=" + ColorToString(colorWhite) + "\n");
        fprintf_s(streamWriter, "%s", "colorMove=" + ColorToString(colorMove) + "\n");
        fprintf_s(streamWriter, "%s", "colorCut=" + ColorToString(colorCut) + "\n");
        fprintf_s(streamWriter, "%s", "paintAllPossible=" + PaintAllPossible.ToString() + "\n");

        fclose(streamWriter);
    }
};

