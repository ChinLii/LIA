#include "processedmode.h"
#include "imageview.h"

ProcessedMode::ProcessedMode()
{

}

ProcessedMode::~ProcessedMode()
{


}

void ProcessedMode::doubleLeftClick(ImageView* iv)
{
	// do nothing
}

void ProcessedMode::doubleRightClick(ImageView* iv)
{
	// do nothing
}


void ProcessedMode::enterOriginalMode(ImageView* iv)
{
	iv->setMode(ImageView::ORIGINAL_MODE);
}

void ProcessedMode::enterProcessedMode(ImageView* iv)
{
	
}

void ProcessedMode::enterEditableMode(ImageView* iv)
{
	iv->setMode(ImageView::EDITABLE_MODE);
}

int ProcessedMode::code()
{
	return ImageView::PROCESSED_MODE;
}
