#include <cstdlib>
#include <ctime>
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#pragma once

ref class Figure {
    // Main fields:
    public: System::Drawing::Point^ position; // Position on board.
    public: System::String^ name; // Name of figure.
    public: int idPlayer; // Id of player.
    public: System::Drawing::Image^ image; // Image of figure.
    public: int idImage; // Id of image from sprite.
    public: bool isMain; // Main figure?
    public: bool isFirst; // First move?
    public: bool isFixed; // Fixed moves?
    public: bool isSimetrical; // Simetrical moves?
    public: bool isChanging; // Changing moves after first?
    public: bool isSame; // Cut same with moves?
    public: int moveRadius1; // Radius for first move.
    public: int moveRadius2; // Radius for another moves.
    public: int** moves; // Map of moves.
    public: int** cuts; // Map of cuts.

        // File fields:
    static System::String^ figuresPath = L"res/figures.txt"; // Path to file with figures descriptions.
    static System::String^ spritePath = L"res\\Sprite_figures.png"; // Path to file with figures images.

    // Sprite fields:
    private: System::Drawing::Image^ spriteFigures = gcnew System::Drawing::Bitmap(spritePath); // Sprite with all figures images.
    private: System::Drawing::Size^ spriteSize = gcnew System::Drawing::Size(100, 100); // Size of image for figures.

    /// <summary>
    /// Ñreating an empty figure.
    /// </summary>
    public: Figure() {
        name = L"none";
        idPlayer = 0;
    }

    /// <summary>
    /// Initializes a new figure. The image for figures gets from file using name.
    /// </summary>
    /// <param name="name">The name of figure.</param>
    /// <param name="idPlayer">The id of player.</param>
    public: Figure(System::String^ name, int idPlayer, System::Drawing::Point^ position) {
        this->name = name;
        this->idPlayer = idPlayer;
        this->position = position;
        isFirst = true;

        array<System::String^>^ param;

        FILE* streamReader = fopen((const char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(figuresPath), "r");
        if (streamReader == NULL)
            System::Windows::Forms::MessageBox::Show(L"Config file not found.\nThe settings are set by default.\n", L"Warning!");

        char* line = new char[100];
        size_t len = 0;
        bool isFound = false;
        while (fgets(line, 100, streamReader) != NULL) {
            line[strlen(line) - 1] = '\0';
            if (gcnew System::String(line) == name) {
                isFound = true;
                break;
            }
        }

        if (!isFound) {
            this->name = L"none";
            this->idPlayer = 0;
        }
        else {
            fgets(line, 100, streamReader);
            line[strlen(line) - 1] = '\0';
            idImage = int::Parse(gcnew System::String(line));

            fgets(line, 100, streamReader);
            isMain = gcnew System::String(line) == "main\n" ? true : false;

            fgets(line, 100, streamReader);
            isFixed = gcnew System::String(line) == "fixed\n" ? true : false;
            
            fgets(line, 100, streamReader);
            isSimetrical = gcnew System::String(line) == "simetrical\n" ? true : false;
            
            fgets(line, 100, streamReader);
            isChanging = gcnew System::String(line) == "changing\n" ? true : false;
            
            fgets(line, 100, streamReader);
            line[strlen(line) - 1] = '\0';
            moveRadius1 = int::Parse((gcnew System::String(line))->Split('=')[1]);
            
            if (isChanging) { 
                fgets(line, 100, streamReader);
                line[strlen(line) - 1] = '\0';
                moveRadius2 = int::Parse((gcnew System::String(line))->Split('=')[1]); 
            }
            else moveRadius2 = moveRadius1;

            if (isFixed) moves = MapReadFromSR(streamReader, moveRadius1 * 2 + 1);
            else moves = MapReadFromSR(streamReader, 3);

            fgets(line, 100, streamReader);
            isSame = gcnew System::String(line) == "same\n" ? true : false;

            if (!isSame) cuts = isFixed ? MapReadFromSR(streamReader, moveRadius2 * 2 + 1) : MapReadFromSR(streamReader, 3);
            else cuts = moves;
            if (!isSimetrical && idPlayer == 1) {
                moves = FlipYMap(moves, isFixed ? moveRadius1 * 2 + 1 : 3);
                cuts = FlipYMap(cuts, isFixed ? moveRadius2 * 2 + 1 : 3);
            }

            image = gcnew  System::Drawing::Bitmap(100, 100);
            System::Drawing::Graphics^ g = System::Drawing::Graphics::FromImage(image);
            System::Drawing::Point^ spritePoint = gcnew System::Drawing::Point(0, 0);
            spritePoint->X = 100 * idImage;
            if (idPlayer == 2) spritePoint->Y = 100;
            g->DrawImage(spriteFigures, System::Drawing::Rectangle(0, 0, spriteSize->Width, spriteSize->Height), spritePoint->X, spritePoint->Y, spriteSize->Width, spriteSize->Height, System::Drawing::GraphicsUnit::Pixel);
        }
        this->position = position;

        fclose(streamReader);
    }

    /// <summary>
    /// Reads a 2d array from the curent stream.
    /// </summary>
    /// <param name="streamReader">The curent stream.</param>
    /// <param name="sideSize">The side length of 2d array.</param>
    /// <returns>Map from stream.</returns>
    public: static int** MapReadFromSR(FILE* streamReader, const int sideSize) {
        int** map = new int*[sideSize];
        for (int i = 0; i < sideSize; i++)
            map[i] = new int[sideSize];

        for (int y = 0; y < sideSize; y++) {
            char* line= new char[100];
            fgets(line, 100, streamReader);
            line[strlen(line) - 1] = '\0';
            for (int x = 0; x < sideSize; x++) {
                map[x][y] = line[x] == '1' ? 1 : 0;
            }
        }
        return map;
    }

    /// <summary>
    /// Vertical flip array.
    /// </summary>
    /// <param name="map">2d array for flipping.</param>
    /// <param name="sideSize">Side length of 2d array.</param>
    /// <returns>Fliped map.</returns>
    public: static int** FlipYMap(int** map, int sideSize) {
        int** newMap = new int*[sideSize];
        for (int i = 0; i < sideSize; i++)
            newMap[i] = new int[sideSize];

        for (int x = 0; x < sideSize; x++)
            for (int y = 0; y < sideSize; y++) {
                newMap[x][y] = map[x][sideSize - y - 1];
            }
        return newMap;
    }
};

