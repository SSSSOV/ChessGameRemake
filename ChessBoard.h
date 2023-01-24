#include <cstdlib>
#include <ctime>
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include "Figure.h"
#pragma once

ref class ChessBoard {

    public: array<Figure^, 2>^ board = gcnew array<Figure^, 2>(8, 8);

    public: array<Figure^>^ figuresPlayer1;
    private: int** allPossibleCuts1;
    public: array<Figure^>^ figuresPlayer2;
    private: int** allPossibleCuts2;


    /// <summary>
    /// Constructor of board->
    /// </summary>
    public: ChessBoard() {
        //ArrangeFigures("Default");
        
    }

    /// <summary>
    /// Constructor of board->
    /// </summary>
    /// <param name="path">Path from file with level-></param>
    public: ChessBoard(System::String^ path) {
        //ArrangeFigures(path);
    }

    /// <summary>
    /// Check is the point on the board->
    /// </summary>
    /// <returns>
    /// True - the point is locate on the board->
    /// False - the point is not locate->
    /// </returns>
    private: static bool OnBoard(System::Drawing::Point^ point) {
        if (point->X < 0 || point->X > 7) return false;
        if (point->Y < 0 || point->Y > 7) return false;
        return true;
    }

    /// <summary>
    /// This method remove figure from array with figures->
    /// </summary>
    /// <param name="figures">Array with figures-></param>
    /// <param name="removeFigure">Figure to be removed-></param>
    /// <returns>Array whithout figure-></returns>
    private: static array<Figure^>^ ArrayRemove(array<Figure^>^ figures, Figure^ removeFigure) {
        bool isContain = false;
        for each(Figure^ f in figures)
            if (f == removeFigure) {
                isContain = true;
                break;
            }

        if (!isContain) return figures;

        int k = 0;
        array<Figure^>^ newFigures = gcnew array<Figure^>(figures->Length - 1);
        for each(Figure^ f in figures)
            if (f != removeFigure)
                newFigures[k++] = f;

        return newFigures;
    }

    /// <summary>
    /// This method add figure to array with figures->
    /// </summary>
    /// <param name="figures">Array with figures-></param>
    /// <param name="addFigure">Figure to be added-></param>
    /// <returns>Array whith figure-></returns>
    private: static  array<Figure^>^ ArrayAdd(array<Figure^>^ figures, Figure^ addFigure) {
        bool isContain = false;
        for each(Figure^ f in figures)
            if (f == addFigure) {
                isContain = true;
                break;
            }

        if (isContain) return figures;

        int k = 0;
        array<Figure^>^ newFigures = gcnew array<Figure^>(figures->Length + 1);
        for each(Figure^ f in figures)
            newFigures[k++] = f;
        newFigures[k] = addFigure;

        return newFigures;
    }

    /// <summary>
    /// Arrange the figures in their starting positions->
    /// </summary>
    public: void ArrangeFigures() { ArrangeFigures("Default"); }

    /// <summary>
    /// Arrange the figures in their starting positions->
    /// </summary>
    /// <param name="path">Path to file with starting positions-></param>
    public: void ArrangeFigures(System::String^ path) {
        if (path == "Default") {
            figuresPlayer1 = gcnew array<Figure^> {
                gcnew Figure("rook", 1, gcnew System::Drawing::Point(0, 0)),
                gcnew Figure("knight", 1, gcnew System::Drawing::Point(1, 0)),
                gcnew Figure("bishop", 1, gcnew System::Drawing::Point(2, 0)),
                gcnew Figure("queen", 1, gcnew System::Drawing::Point(3, 0)),
                gcnew Figure("king", 1, gcnew System::Drawing::Point(4, 0)),
                gcnew Figure("bishop", 1, gcnew System::Drawing::Point(5, 0)),
                gcnew Figure("knight", 1, gcnew System::Drawing::Point(6, 0)),
                gcnew Figure("rook", 1, gcnew System::Drawing::Point(7, 0)),
                gcnew Figure("pawn", 1, gcnew System::Drawing::Point(0, 1)),
                gcnew Figure("pawn", 1, gcnew System::Drawing::Point(1, 1)),
                gcnew Figure("pawn", 1, gcnew System::Drawing::Point(2, 1)),
                gcnew Figure("pawn", 1, gcnew System::Drawing::Point(3, 1)),
                gcnew Figure("pawn", 1, gcnew System::Drawing::Point(4, 1)),
                gcnew Figure("pawn", 1, gcnew System::Drawing::Point(5, 1)),
                gcnew Figure("pawn", 1, gcnew System::Drawing::Point(6, 1)),
                gcnew Figure("pawn", 1, gcnew System::Drawing::Point(7, 1))
            };
            figuresPlayer2 = gcnew array<Figure^> {
                gcnew Figure(L"rook", 2, gcnew System::Drawing::Point(0, 7)),
                gcnew Figure(L"knight", 2, gcnew System::Drawing::Point(1, 7)),
                gcnew Figure(L"bishop", 2, gcnew System::Drawing::Point(2, 7)),
                gcnew Figure(L"queen", 2, gcnew System::Drawing::Point(3, 7)),
                gcnew Figure(L"king", 2, gcnew System::Drawing::Point(4, 7)),
                gcnew Figure(L"bishop", 2, gcnew System::Drawing::Point(5, 7)),
                gcnew Figure(L"knight", 2, gcnew System::Drawing::Point(6, 7)),
                gcnew Figure(L"rook", 2, gcnew System::Drawing::Point(7, 7)),
                gcnew Figure(L"pawn", 2, gcnew System::Drawing::Point(0, 6)),
                gcnew Figure(L"pawn", 2, gcnew System::Drawing::Point(1, 6)),
                gcnew Figure(L"pawn", 2, gcnew System::Drawing::Point(2, 6)),
                gcnew Figure(L"pawn", 2, gcnew System::Drawing::Point(3, 6)),
                gcnew Figure(L"pawn", 2, gcnew System::Drawing::Point(4, 6)),
                gcnew Figure(L"pawn", 2, gcnew System::Drawing::Point(5, 6)),
                gcnew Figure(L"pawn", 2, gcnew System::Drawing::Point(6, 6)),
                gcnew Figure(L"pawn", 2, gcnew System::Drawing::Point(7, 6))
            };
        }
        else {
            array<System::String^>^ param;

            FILE* streamReader = fopen((const char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(path), "r");
            if (streamReader == NULL) {
                System::Windows::Forms::MessageBox::Show(L"Incorrect level file!", L"Error!");
                return;
            }

            figuresPlayer1 = gcnew array<Figure^>(0);
            figuresPlayer2 = gcnew array<Figure^>(0);

            char* line = new char[100];
            size_t len = 0;
            while (fgets(line, 100, streamReader) != NULL) {
                array<System::String^>^ lineFigure = (gcnew System::String(line))->Split(' ');
                if (int::Parse(lineFigure[0]) == 1)
                    figuresPlayer1 = ArrayAdd(figuresPlayer1, gcnew Figure(lineFigure[1], 1, gcnew System::Drawing::Point(int::Parse(lineFigure[3]), int::Parse(lineFigure[2]))));
                else if (int::Parse(lineFigure[0]) == 2)
                    figuresPlayer2 = ArrayAdd(figuresPlayer2, gcnew Figure(lineFigure[1], 2, gcnew System::Drawing::Point(int::Parse(lineFigure[3]), int::Parse(lineFigure[2]))));
            }
            fclose(streamReader);
        }
        
        board = gcnew array<Figure^, 2>(8, 8);
        for each(Figure^ f in figuresPlayer1) board[f->position->X, f->position->Y] = f;
        for each(Figure^ f in figuresPlayer2) board[f->position->X, f->position->Y] = f;
        for (int x = 0; x < 8; x++) for (int y = 0; y < 8; y++) if (board[x, y] == nullptr) board[x, y] = gcnew Figure();

        allPossibleCuts1 = new int* [8];
        for (int i = 0; i < 8; i++)
            allPossibleCuts1[i] = new int[8];
        allPossibleCuts2 = new int* [8];
        for (int i = 0; i < 8; i++)
            allPossibleCuts2[i] = new int[8];

        allPossibleCuts1 = GetPossibleAllCutsMap(1);
        allPossibleCuts2 = GetPossibleAllCutsMap(2);
    }

    /// <summary>
    /// Get map with possible cuts all figures of player->
    /// </summary>
    /// <param name="id">Id of player-></param>
    /// <returns>Map with possible cuts-></returns>
    public: int** GetPossibleAllCutsMap(int id) {
        int** cutsMap = new int*[8];
        for (int i = 0; i < 8; i++)
            cutsMap[i] = new int[8];

        int** possibleCuts = new int*[8];
        for (int i = 0; i < 8; i++)
            possibleCuts[i] = new int[8];

        array<Figure^>^ figures;

        if (id == 1) figures = (array<Figure^>^) figuresPlayer1->Clone();
        else if (id == 2) figures = (array<Figure^>^) figuresPlayer2->Clone();
        else return cutsMap;

        for each(Figure^ f in figures) {
            possibleCuts = getPossibleCuts(f->position);
            if (possibleCuts == nullptr) continue;
            cutsMap = AdditionTwoCutsMaps(cutsMap, possibleCuts);
        }
        return cutsMap;
    }

    /// <summary>
    /// Addition two cuts maps
    /// </summary>
    /// <param name="map1">First cuts map-></param>
    /// <param name="map2">Second cuts map-></param>
    /// <returns>Map after addition-></returns>
    public: static int** AdditionTwoCutsMaps(int** map1, int** map2) {
        for (int x = 0; x < 8; x++)
            for (int y = 0; y < 8; y++)
                if (map2[x][y] > 0 || map1[x][y] > 1)
                    map1[x][y] = 1;
        return map1;
    }

    /// <summary>
    /// Remove cuts map from moves map->
    /// </summary>
    /// <param name="moves">Moves map-></param>
    /// <param name="cuts">Cuts map-></param>
    /// <returns>Moves map after subtraction-></returns>
    public: static int** RemoveCutsFromMoves(int** moves, int** cuts) {
        for (int x = 0; x < 8; x++)
            for (int y = 0; y < 8; y++)
                if (cuts[x][y] > 0)
                    moves[x][y] = 0;
        return moves;
    }

    /// <summary>
    /// Add cuts map to moves map->
    /// </summary>
    /// <param name="moves">Moves map-></param>
    /// <param name="cuts">Cuts map-></param>
    /// <returns>Moves map after addition-></returns>
    public: static int** AdditionMovesCutsMaps(int** moves, int** cuts) {
        for (int x = 0; x < 8; x++)
            for (int y = 0; y < 8; y++)
                if (cuts[x][y] > 1 && moves[x][y] == 0)
                    moves[x][y] = cuts[x][y];
        return moves;
    }

    /// <summary>
    /// Checks if the map is empty->
    /// </summary>
    /// <param name="map">Checked map-></param>
    /// <returns>
    /// True - if map is empty->
    /// False - if map is not empty->
    /// </returns>
    public: static bool IsEmptyMap(int** map) {
        for (int x = 0; x < 8; x++)
            for (int y = 0; y < 8; y++)
                if (map[x][y] == 1 || map[x][y] == 2) {
                    return false;
                }
        return true;
    }

    /// <summary>
    /// Get possible moves for figure what stand in figurePoint on chess board->
    /// 1 - Can move->
    /// </summary>
    /// <param name="figurePoint">Position figure on chess board-></param>
    /// <returns>Map possible moves-></returns>
    public: int** getPossibleMoves(System::Drawing::Point^ figurePoint) {
        int** resultMap = new int*[8];
        for (int i = 0; i < 8; i++)
            resultMap[i] = new int[8];

        Figure^ figure = getFigure(figurePoint);
        int** movesMap = figure->moves;
        int moveRadius;
        System::Drawing::Point^ point;

        if (figure->isChanging) moveRadius = figure->isFirst ? figure->moveRadius1 : figure->moveRadius2;
        else moveRadius = figure->moveRadius1;

        if (figure->isFixed) {
            int movesMapSize = moveRadius * 2 + 1;

            for (int x = 0; x < movesMapSize; x++) {
                point = gcnew System::Drawing::Point(figurePoint->X - moveRadius + x, 0);
                if (!OnBoard(point)) continue;
                for (int y = 0; y < movesMapSize; y++) {
                    point->Y = figurePoint->Y - moveRadius + y;
                    if (!OnBoard(point)) continue;
                    if (movesMap[x][y] == 1 && getFigure(point)->name == "none") resultMap[point->X][point->Y] = 1;
                }
            }
        }
        else {
            int radius = 1;
            if (movesMap[0][0] == 1)
                for (point = gcnew System::Drawing::Point(figurePoint->X - 1, figurePoint->Y - 1), radius = 1; OnBoard(point) && radius <= moveRadius; point->X--, point->Y--, radius++)
                    if (getFigure(point)->name == "none") resultMap[point->X][point->Y] = 1;
                    else break;

            if (movesMap[1][0] == 1)
                for (point = gcnew System::Drawing::Point(figurePoint->X, figurePoint->Y - 1), radius = 1; OnBoard(point) && radius <= moveRadius; point->Y--, radius++)
                    if (getFigure(point)->name == "none") resultMap[point->X][point->Y] = 1;
                    else break;

            if (movesMap[2][0] == 1)
                for (point = gcnew System::Drawing::Point(figurePoint->X + 1, figurePoint->Y - 1), radius = 1; OnBoard(point) && radius <= moveRadius; point->X++, point->Y--, radius++)
                    if (getFigure(point)->name == "none") resultMap[point->X][point->Y] = 1;
                    else break;

            if (movesMap[2][1] == 1)
                for (point = gcnew System::Drawing::Point(figurePoint->X + 1, figurePoint->Y), radius = 1; OnBoard(point) && radius <= moveRadius; point->X++, radius++)
                    if (getFigure(point)->name == "none") resultMap[point->X][point->Y] = 1;
                    else break;

            if (movesMap[2][2] == 1)
                for (point = gcnew System::Drawing::Point(figurePoint->X + 1, figurePoint->Y + 1), radius = 1; OnBoard(point) && radius <= moveRadius; point->X++, point->Y++, radius++)
                    if (getFigure(point)->name == "none") resultMap[point->X][point->Y] = 1;
                    else break;

            if (movesMap[1][2] == 1)
                for (point = gcnew System::Drawing::Point(figurePoint->X, figurePoint->Y + 1), radius = 1; OnBoard(point) && radius <= moveRadius; point->Y++, radius++)
                    if (getFigure(point)->name == "none") resultMap[point->X][point->Y] = 1;
                    else break;

            if (movesMap[0][2] == 1)
                for (point = gcnew System::Drawing::Point(figurePoint->X - 1, figurePoint->Y + 1), radius = 1; OnBoard(point) && radius <= moveRadius; point->X--, point->Y++, radius++)
                    if (getFigure(point)->name == "none") resultMap[point->X][point->Y] = 1;
                    else break;

            if (movesMap[0][1] == 1)
                for (point = gcnew System::Drawing::Point(figurePoint->X - 1, figurePoint->Y), radius = 1; OnBoard(point) && radius <= moveRadius; point->X--, radius++)
                    if (getFigure(point)->name == "none") resultMap[point->X][point->Y] = 1;
                    else break;
        }

        return resultMap;
    }

    /// <summary>
    /// Get possible cuts for figure what stand in figurePoint on chess board->
    /// 2 - Can cut->
    /// 3 - Can cut, but figurePoint is empty->
    /// 4 - Can cut, but figurePoint is busy->
    /// </summary>
    /// <param name="figurePoint">Position figure on chess board-></param>
    /// <returns>Map possible cuts-></returns>
    public: int** getPossibleCuts(System::Drawing::Point^ figurePoint) {
        int** resultMap = new int*[8];
        for (int i = 0; i < 8; i++)
            resultMap[i] = new int[8];

        Figure^ figure = getFigure(figurePoint);
        int** cutsMap = figure->cuts;
        int cutRadius;
        System::Drawing::Point^ point;

        cutRadius = figure->moveRadius2;

        if (figure->isFixed) {
            int cutsMapSize = cutRadius * 2 + 1;

            for (int x = 0; x < cutsMapSize; x++) {
                point = gcnew System::Drawing::Point(figurePoint->X - cutRadius + x, 0);
                if (!OnBoard(point)) continue;
                for (int y = 0; y < cutsMapSize; y++) {
                    point->Y = figurePoint->Y - cutRadius + y;
                    if (!OnBoard(point)) continue;
                    if (cutsMap[x][y] == 1) {
                        if (getFigure(point)->name == "none") resultMap[point->X][point->Y] = 3;
                        else if (getFigure(point)->idPlayer != figure->idPlayer) resultMap[point->X][point->Y] = 2;
                        else resultMap[point->X][point->Y] = 4;
                    }
                }
            }
        }
        else {
            int radius = 1;
            if (cutsMap[0][0] == 1)
                for (point = gcnew System::Drawing::Point(figurePoint->X - 1, figurePoint->Y - 1), radius = 1; OnBoard(point) && radius <= cutRadius; point->X--, point->Y--, radius++) {
                    if (getFigure(point)->name == "none") resultMap[point->X][point->Y] = 3;
                    else {
                        if (getFigure(point)->idPlayer != figure->idPlayer) resultMap[point->X][point->Y] = 2;
                        else if (getFigure(point)->idPlayer == figure->idPlayer) resultMap[point->X][point->Y] = 4;
                        break;
                    }
                }
            if (cutsMap[1][0] == 1)
                for (point = gcnew System::Drawing::Point(figurePoint->X, figurePoint->Y - 1), radius = 1; OnBoard(point) && radius <= cutRadius; point->Y--, radius++) {
                    if (getFigure(point)->name == "none") resultMap[point->X][point->Y] = 3;
                    else {
                        if (getFigure(point)->idPlayer != figure->idPlayer) resultMap[point->X][point->Y] = 2;
                        else if (getFigure(point)->idPlayer == figure->idPlayer) resultMap[point->X][point->Y] = 4;
                        break;
                    }
                }
            if (cutsMap[2][0] == 1)
                for (point = gcnew System::Drawing::Point(figurePoint->X + 1, figurePoint->Y - 1), radius = 1; OnBoard(point) && radius <= cutRadius; point->X++, point->Y--, radius++) {
                    if (getFigure(point)->name == "none") resultMap[point->X][point->Y] = 3;
                    else {
                        if (getFigure(point)->idPlayer != figure->idPlayer) resultMap[point->X][point->Y] = 2;
                        else if (getFigure(point)->idPlayer == figure->idPlayer) resultMap[point->X][point->Y] = 4;
                        break;
                    }
                }
            if (cutsMap[2][1] == 1)
                for (point = gcnew System::Drawing::Point(figurePoint->X + 1, figurePoint->Y), radius = 1; OnBoard(point) && radius <= cutRadius; point->X++, radius++) {
                    if (getFigure(point)->name == "none") resultMap[point->X][point->Y] = 3;
                    else {
                        if (getFigure(point)->idPlayer != figure->idPlayer) resultMap[point->X][point->Y] = 2;
                        else if (getFigure(point)->idPlayer == figure->idPlayer) resultMap[point->X][point->Y] = 4;
                        break;
                    }
                }
            if (cutsMap[2][2] == 1)
                for (point = gcnew System::Drawing::Point(figurePoint->X + 1, figurePoint->Y + 1), radius = 1; OnBoard(point) && radius <= cutRadius; point->X++, point->Y++, radius++) {
                    if (getFigure(point)->name == "none") resultMap[point->X][point->Y] = 3;
                    else {
                        if (getFigure(point)->idPlayer != figure->idPlayer) resultMap[point->X][point->Y] = 2;
                        else if (getFigure(point)->idPlayer == figure->idPlayer) resultMap[point->X][point->Y] = 4;
                        break;
                    }
                }
            if (cutsMap[1][2] == 1)
                for (point = gcnew System::Drawing::Point(figurePoint->X, figurePoint->Y + 1), radius = 1; OnBoard(point) && radius <= cutRadius; point->Y++, radius++) {
                    if (getFigure(point)->name == "none") resultMap[point->X][point->Y] = 3;
                    else {
                        if (getFigure(point)->idPlayer != figure->idPlayer) resultMap[point->X][point->Y] = 2;
                        else if (getFigure(point)->idPlayer == figure->idPlayer) resultMap[point->X][point->Y] = 4;
                        break;
                    }
                }
            if (cutsMap[0][2] == 1)
                for (point = gcnew System::Drawing::Point(figurePoint->X - 1, figurePoint->Y + 1), radius = 1; OnBoard(point) && radius <= cutRadius; point->X--, point->Y++, radius++) {
                    if (getFigure(point)->name == "none") resultMap[point->X][point->Y] = 3;
                    else {
                        if (getFigure(point)->idPlayer != figure->idPlayer) resultMap[point->X][point->Y] = 2;
                        else if (getFigure(point)->idPlayer == figure->idPlayer) resultMap[point->X][point->Y] = 4;
                        break;
                    }
                }
            if (cutsMap[0][1] == 1)
                for (point = gcnew System::Drawing::Point(figurePoint->X - 1, figurePoint->Y), radius = 1; OnBoard(point) && radius <= cutRadius; point->X--, radius++) {
                    if (getFigure(point)->name == "none") resultMap[point->X][point->Y] = 3;
                    else {
                        if (getFigure(point)->idPlayer != figure->idPlayer) resultMap[point->X][point->Y] = 2;
                        else if (getFigure(point)->idPlayer == figure->idPlayer) resultMap[point->X][point->Y] = 4;
                        break;
                    }
                }
        }

        return resultMap;
    }

    /// <summary>
    /// Get possible actions for figure what stand in figurePoint on chess board->
    /// 1 - Can move->
    /// 2 - Can cut->
    /// 3 - Can cut, but figurePoint is empty->
    /// 4 - Can cut, but figurePoint is busy->
    /// If the figure is the main, then all possible cuts of the other player are subtracted from its move map->
    /// </summary>
    /// <param name="figurePoint">Position figure on chess board-></param>
    /// <returns>Map possible cuts-></returns>
    public: int** getPossibleActions(System::Drawing::Point^ figurePoint) {
        int** resultMap = new int* [8];
        for (int i = 0; i < 8; i++)
            resultMap[i] = new int[8];

        resultMap = AdditionMovesCutsMaps(getPossibleMoves(figurePoint), getPossibleCuts(figurePoint));
        if (getFigure(figurePoint)->isMain) {
            if (getFigure(figurePoint)->idPlayer == 1) resultMap = RemoveCutsFromMoves(resultMap, allPossibleCuts2);
            if (getFigure(figurePoint)->idPlayer == 2) resultMap = RemoveCutsFromMoves(resultMap, allPossibleCuts1);
        }
        return resultMap;
    }

    /// <summary>
    /// Get figure from point on the board->
    /// </summary>
    /// <param name="point">Point on the board-></param>
    /// <returns>Figure from point</returns>
    public: Figure^ getFigure(System::Drawing::Point^ point) {
        if (OnBoard(point)) 
            return board[point->X, point->Y];
        return gcnew Figure();
    }

    /// <summary>
    /// Move figure on the board from old point to new point->
    /// </summary>
    /// <param name="oldPoint">Old point of figure on the board-></param>
    /// <param name="newPoint">New point of figure on the board-></param>
    public: void MoveFigure(System::Drawing::Point^ oldPoint, System::Drawing::Point^ newPoint) {
        if (board[oldPoint->X, oldPoint->Y]->idPlayer == 1) {
            for each(Figure^ f in figuresPlayer1)
                if (f->position == oldPoint)
                    f->position = newPoint;
        }
        if (board[oldPoint->X, oldPoint->Y]->idPlayer == 2) {
            for each(Figure^ f in figuresPlayer2)
                if (f->position == oldPoint)
                    f->position = newPoint;
        }

        board[newPoint->X, newPoint->Y] = board[oldPoint->X, oldPoint->Y];
        board[newPoint->X, newPoint->Y]->isFirst = false;
        board[oldPoint->X, oldPoint->Y] = gcnew Figure();

        allPossibleCuts1 = GetPossibleAllCutsMap(1);
        allPossibleCuts2 = GetPossibleAllCutsMap(2);
    }

    /// <summary>
    /// Cut figure on the board from new point by figure from old point->
    /// </summary>
    /// <param name="oldPoint">Old point of figure on the board-></param>
    /// <param name="newPoint">New point of figure on the board-></param>
    public: void CutFigure(System::Drawing::Point^ oldPoint, System::Drawing::Point^ newPoint) {
        if (board[oldPoint->X, oldPoint->Y]->idPlayer == 1) {
            for each(Figure^ f in figuresPlayer1)
                if (f->position == oldPoint)
                    f->position = newPoint;

            for each(Figure^ f in figuresPlayer2)
                if (f->position == newPoint)
                    figuresPlayer2 = ArrayRemove(figuresPlayer2, f);
        }
        if (board[oldPoint->X, oldPoint->Y]->idPlayer == 2) {
            for each(Figure^ f in figuresPlayer2)
                if (f->position == oldPoint)
                    f->position = newPoint;

            for each(Figure^ f in figuresPlayer1)
                if (f->position == newPoint)
                    figuresPlayer1 = ArrayRemove(figuresPlayer1, f);
        }
        board[newPoint->X, newPoint->Y] = board[oldPoint->X, oldPoint->Y];
        board[newPoint->X, newPoint->Y]->isFirst = false;
        board[oldPoint->X, oldPoint->Y] = gcnew Figure();

        allPossibleCuts1 = GetPossibleAllCutsMap(1);
        allPossibleCuts2 = GetPossibleAllCutsMap(2);
    }

    /// <summary>
    /// Checks if the game is over->
    /// </summary>
    /// <returns>A line with a possible end of the game-></returns>
    public: System::String^ GameOver() {
        System::String^ message = L"";
        if (figuresPlayer1->Length == 0) {
            message = L"Player 2 won!";
        }
        else if (figuresPlayer2->Length == 0) {
            message = L"Player 1 won!";
        }
        else {
            for each(Figure^ f in figuresPlayer1) {
                if (!f->isMain) continue;
                if (IsEmptyMap(getPossibleActions(f->position)) && allPossibleCuts2[f->position->X][f->position->Y] != 0) {
                    message = "Checkmate for 1 player";
                    break;
                }
            }
            for each(Figure^ f in figuresPlayer2) {
                if (!f->isMain) continue;
                if (IsEmptyMap(getPossibleActions(f->position)) && allPossibleCuts1[f->position->X][f->position->Y] != 0) {
                    message = "Checkmate for 2 player";
                    break;
                }
            }
        }
        if (message != "")  System::Windows::Forms::MessageBox::Show(message, L"GameOver!");
        else {
            for each(Figure^ f in figuresPlayer1) {
                if (!f->isMain) continue;
                if (allPossibleCuts2[f->position->X][f->position->Y] != 0) {
                    message = "Check for 1 player";
                    break;
                }
            }
            for each(Figure^ f in figuresPlayer2) {
                if (!f->isMain) continue;
                if (allPossibleCuts1[f->position->X][f->position->Y] != 0) {
                    message = "Check for 2 player";
                    break;
                }
            }
        }
        return message;
    }
};

