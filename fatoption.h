#ifndef FATOPTION_H
#define FATOPTION_H


class FatOption
{
public:
	FatOption();
	~FatOption();

	double minCir;
	double maxCir;
	double minSize;
	double maxSize;

	bool check(double size, double cir);
};

#endif // FATOPTION_H
