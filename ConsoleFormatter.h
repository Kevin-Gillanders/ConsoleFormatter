#pragma once
#include "ConsoleEnums.h"
#include "ColourStruct.h"
#include <string>

class ConsoleFormatter
{
	const std::string ESCAPESEQUENCE = "\x1b[";
	const std::string ARGUMENTCONCAT = ";";
	const std::string COMMANDCLOSE = "m";
	bool Bold;
	bool Italics;
	bool Underline;
	bool StrikeThrough;
	const int COLOURSTYLEDISTANCE = 10;
public:
	ConsoleFormatter();
	void SetColour(ColourStyle style, ColourStruct colour);
	void SetColour(ConsoleColour fgColour, ConsoleColour bgColour);
	void SetColour(ConsoleColour fgColour);
	void SetBackGroundColour(ConsoleColour bgColour);
	void ClearConsole();
	void ResetPosition();
	void MoveCursorUp(int amount);
	void MoveCursorDown(int amount);
	void MoveCursorLeft(int amount);
	void MoveCursorRight(int amount);
	void ResetConsole();
	void ResetColour();
	void SetTextMode(TextMode mode);
	int GetColour(ConsoleColour colour, ColourStyle style);
};