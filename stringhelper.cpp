#include "stringhelper.h"

StringHelper::StringHelper(QObject *parent)
	: QObject(parent)
{

}

StringHelper::~StringHelper()
{

}

std::string StringHelper::stringToLower(std::string str)
{
	for (int i = 0; str[i]; i++)
		str[i] = std::tolower(str[i]);

	return str;
}