#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <QObject>
#include <string>
#include <cctype>

class StringHelper : public QObject
{
public:
	StringHelper(QObject *parent);
	~StringHelper();

	static std::string stringToLower(std::string str);
private:
	
};

#endif // STRINGHELPER_H
