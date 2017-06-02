#include "originalmode.h"
#include "imageview.h"

OriginalMode::OriginalMode()
{

}

OriginalMode::~OriginalMode()
{

}

void OriginalMode::doubleLeftClick(ImageView* iv)
{
	// do nothing
}

void OriginalMode::doubleRightClick(ImageView* iv)
{
	// do nothing
}


void OriginalMode::enterOriginalMode(ImageView* iv)
{
}

void OriginalMode::enterProcessedMode(ImageView* iv)
{
	iv->setMode(ImageView::PROCESSED_MODE);
}

void OriginalMode::enterEditableMode(ImageView* iv)
{
	iv->setMode(ImageView::EDITABLE_MODE);
}

int OriginalMode::code()
{
	return ImageView::ORIGINAL_MODE;
}