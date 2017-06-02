#ifndef BLOBFEATURES_H
#define BLOBFEATURES_H

class BlobFeatures
{
private:
	int type;
	double area;
	double circularity;
	double avgGrayLevel;
public:

	static const int BACKGROUND = 1;


	void setArea(double a){ area = a; };
	void setcircularity(double c){ circularity = c; };
	void setAvgGrayLevel(double a){ avgGrayLevel = a; };
	void setType(int t){ type = t; };

	double getArea() const { return area; };
	double getCircularity() const { return circularity; };
	double getAvgGrayLevel() const { return avgGrayLevel; };
	int getType() const { return type; };
};

#endif // BLOBFEATURES_H
