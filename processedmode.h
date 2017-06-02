#ifndef PROCESSEDMODE_H
#define PROCESSEDMODE_H

#include "imagemode.h"

class ImageView;

class ProcessedMode : public ImageMode
{
public:
	ProcessedMode();
	~ProcessedMode();
	void enterOriginalMode(ImageView* iv);
	void enterProcessedMode(ImageView* iv);
	void enterEditableMode(ImageView* iv);
	void doubleLeftClick(ImageView* iv);
	void doubleRightClick(ImageView* iv);
	int code();

private:
	
};

#endif // PROCESSEDMODE_H
