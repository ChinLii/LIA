#ifndef ORIGINALMODE_H
#define ORIGINALMODE_H

#include "imagemode.h"

class ImageView;

class OriginalMode : public ImageMode
{
public:
    OriginalMode();
    ~OriginalMode();
	void enterOriginalMode(ImageView* iv);
	void enterProcessedMode(ImageView* iv);
	void enterEditableMode(ImageView* iv);
	void doubleLeftClick(ImageView* iv);
	void doubleRightClick(ImageView* iv);
	int code();

private:
    
};

#endif // ORIGINALMODE_H
