#include "ConsoleFormatter.h"
using namespace std;
#include <iostream>
#include "ColourStruct.h"

//reference
//https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797

ConsoleFormatter::ConsoleFormatter()
{
	Bold = false;
	Italics = false;
	Underline = false;
	StrikeThrough = false;
}


void ConsoleFormatter::SetColour(ColourStyle style, ColourStruct colour)
{
	int fg = 38;
	int bg = 48;
	int styleID{};
	if (style == ColourStyle::FOREGROUND)
		styleID = fg;
	else
		styleID = bg;
	int format = 2; //5
	cout << ESCAPESEQUENCE << styleID << ARGUMENTCONCAT << format << ARGUMENTCONCAT << colour.r << ARGUMENTCONCAT << colour.g << ARGUMENTCONCAT << colour.b << COMMANDCLOSE;
}

void ConsoleFormatter::SetColour(ConsoleColour fgColour, ConsoleColour bgColour)
{
	int fgcolourToSet = GetColour(fgColour, ColourStyle::FOREGROUND);
	int bgcolourToSet = GetColour(bgColour, ColourStyle::BACKGROUND);

	cout << ESCAPESEQUENCE << fgcolourToSet << ARGUMENTCONCAT << bgcolourToSet << COMMANDCLOSE;

}

void ConsoleFormatter::SetColour(ConsoleColour fgColour)
{
	int fgcolourToSet = GetColour(fgColour, ColourStyle::FOREGROUND);
	cout << ESCAPESEQUENCE << fgcolourToSet << COMMANDCLOSE;
}

void ConsoleFormatter::SetBackGroundColour(ConsoleColour bgColour)
{

	int bgcolourToSet = GetColour(bgColour, ColourStyle::BACKGROUND);

	cout << ESCAPESEQUENCE << bgcolourToSet << COMMANDCLOSE;
}

void ConsoleFormatter::ClearConsole()
{
	cout << ESCAPESEQUENCE << "2J";
}

void ConsoleFormatter::ResetConsole()
{
	int fgcolourToSet = 0;
	int bgcolourToSet = 0;

	cout << ESCAPESEQUENCE << fgcolourToSet << ARGUMENTCONCAT << bgcolourToSet << COMMANDCLOSE;

}

void ConsoleFormatter::ResetColour()
{
	int fgcolourToSet = GetColour(ConsoleColour::DEFAULT, ColourStyle::FOREGROUND);
	int bgcolourToSet = GetColour(ConsoleColour::DEFAULT, ColourStyle::BACKGROUND);

	cout << ESCAPESEQUENCE << fgcolourToSet << ARGUMENTCONCAT << bgcolourToSet << COMMANDCLOSE;
}

void ConsoleFormatter::ResetPosition()
{
	cout << ESCAPESEQUENCE << "H";
}

void ConsoleFormatter::MoveCursorUp(int amount)
{
	//ESC[#A 	moves cursor up # lines
	cout << ESCAPESEQUENCE << amount << "A";
}

void ConsoleFormatter::MoveCursorDown(int amount)
{
	//ESC[#B 	moves cursor down # lines
	cout << ESCAPESEQUENCE << amount << "B";
}

void ConsoleFormatter::MoveCursorRight(int amount)
{
	//ESC[#C 	moves cursor right # columns
	cout << ESCAPESEQUENCE << amount << "C";
}

void ConsoleFormatter::MoveCursorLeft(int amount)
{
	//ESC[#D 	moves cursor left # columns
	cout << ESCAPESEQUENCE << amount << "D";
}

void ConsoleFormatter::SetTextMode(TextMode mode)
{
	cout << ESCAPESEQUENCE;

	int modifier = 20;
	if (mode == TextMode::BOLD)
		modifier++;

	switch (mode)
	{
	case BOLD:
		if (Bold)
			cout << TextMode::BOLD + modifier << COMMANDCLOSE;
		else
			cout << TextMode::BOLD << COMMANDCLOSE;

		Bold = !Bold;
		break;
	case ITALICS:
		if (Italics)
			cout << TextMode::ITALICS + modifier << COMMANDCLOSE;
		else
			cout << TextMode::ITALICS << COMMANDCLOSE;

		Italics = !Italics;
		break;
	case UNDERLINE:
		if (Underline)
			cout << TextMode::UNDERLINE + modifier << COMMANDCLOSE;
		else
			cout << TextMode::UNDERLINE << COMMANDCLOSE;

		Underline = !Underline;
		break;
	case STRIKETHROUGH:
		if (StrikeThrough)
			cout << TextMode::STRIKETHROUGH + modifier << COMMANDCLOSE;
		else
			cout << TextMode::STRIKETHROUGH << COMMANDCLOSE;

		StrikeThrough = !StrikeThrough;
		break;
	default:
		break;
	}
}

int ConsoleFormatter::GetColour(ConsoleColour colour, ColourStyle style)
{
	return colour + style;
}

