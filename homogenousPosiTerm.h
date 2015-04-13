#include "../poly/poly.h"


class homogenousPosiTerm
{
public:
	homogenousPosiTerm(int numVar, int numLab);
	void setCost(vector<int> & labels, double cost);
	void changeCost(vector<int> & labels, double change);
	double getLabel(vector<int>& labels);//return the gap between optimum and suboptimum
	void editCosts(poly<double>& p);
	void changeCosts(poly<double>& p);
	void getCosts(poly<double>& p );
	void setZero();
	poly<double> getCosts();
	void plotCosts();
private:
	int _numVar;
	int _numLab;
	poly<double> label2costs;
	vector<int> optimizer;
	double optimum;
	double suboptimum;
};
