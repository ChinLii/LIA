#ifndef EDITABLEMODE_H
#define EDITABLEMODE_H

#include "imagemode.h"
#include "imageview.h"

class EditableMode : public ImageMode
{
public:
	EditableMode();
	~EditableMode();

	void enterOriginalMode(ImageView* iv);
	void enterProcessedMode(ImageView* iv);
	void enterEditableMode(ImageView* iv);
	void doubleLeftClick(ImageView* iv);
	void doubleRightClick(ImageView* iv);
	int code();

private:
	
};

#endif // EDITABLEMODE_H
