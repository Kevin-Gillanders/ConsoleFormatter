#pragma once
#include <string>
#include <vector>

class QRCodeMaker
{
public:
	std::vector<bool> CreateQRCode(std::string data);
};