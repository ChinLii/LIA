#ifndef IMAGEMODE_H
#define IMAGEMODE_H


class ImageView;

class ImageMode
{
public:
	ImageMode();
	~ImageMode();

	virtual void enterOriginalMode(ImageView* iv) = 0;
	virtual void enterProcessedMode(ImageView* iv) = 0;
	virtual void enterEditableMode(ImageView* iv) = 0;
	virtual void doubleLeftClick(ImageView* iv) = 0;
	virtual void doubleRightClick(ImageView* iv) = 0;
	virtual int code() = 0;



private:
	
};

#endif // IMAGEMODE_H
