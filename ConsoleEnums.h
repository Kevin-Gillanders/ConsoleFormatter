#pragma once

enum ConsoleColour {
	               //FG      BG
	DEFAULT        = 39, //  49
	BLACK          = 30, //  40
	RED            = 31, //  41
	GREEN          = 32, //  42
	YELLOW         = 33, //  43
	BLUE           = 34, //  44
	MAGENTA        = 35, //  45
	CYAN           = 36, //  46
	WHITE          = 37, //  47
	BRIGHT_BLACK   = 90, //  100
	BRIGHT_RED     = 91, //  101
	BRIGHT_GREEN   = 92, //  102
	BRIGHT_YELLOW  = 93, //  103
	BRIGHT_BLUE    = 94, //  104
	BRIGHT_MAGENTA = 95, //  105
	BRIGHT_CYAN    = 96, //  106
	BRIGHT_WHITE   = 97, //  107
};

enum ColourStyle {
	FOREGROUND = 0,
	BACKGROUND = 10,
};

enum TextMode {

	BOLD = 1, //22
	ITALICS = 3, //23
	UNDERLINE = 4, //24
	STRIKETHROUGH = 9,  //29
};