#include "editablemode.h"
#include "imageview.h"

EditableMode::EditableMode()
{

}

EditableMode::~EditableMode()
{

}

void EditableMode::doubleLeftClick(ImageView* iv)
{
	iv->clickOnImage(1);
}

void EditableMode::doubleRightClick(ImageView* iv)
{
	iv->clickOnImage(2);
}

void EditableMode::enterOriginalMode( ImageView* iv )
{
	iv->setMode(ImageView::ORIGINAL_MODE);
}

void EditableMode::enterProcessedMode( ImageView* iv )
{
	iv->setMode(ImageView::PROCESSED_MODE);
}

void EditableMode::enterEditableMode( ImageView* iv )
{

}

int EditableMode::code()
{
	return ImageView::EDITABLE_MODE;
}