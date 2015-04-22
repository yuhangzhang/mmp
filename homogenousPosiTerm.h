#include "../poly/poly.h"
#include <time.h>  

class homogenousPosiTerm
{
public:
	homogenousPosiTerm(int numVar, int numLab);
	void setCost(vector<int> & labels, double cost);
	void changesubcost(vector<int> & labels, int over, double change);
	void changeCost(vector<int> & labels, double change);
	double getLabel(vector<int>& labels);//return the gap between optimum and suboptimum
	double getLabelmax(vector<int>& labels);
	void editCosts(poly<double>& p);
	void changeCosts(poly<double>& p);
	void getCosts(poly<double>& p );
	void setResidual(double r);
	poly<double> getCosts();
	void plotCosts();
	double getoptimum(){return optimum;}

	double getmargin(vector<int>& labels, int over);//\min_xt\xs E(x)-E^\star, over: the location of xt\xs 

	void plotEnergyTable();

private:
	int _numVar;
	int _numLab;
	poly<double> label2costs;
	vector<int> optimizer;
	double optimum;
	double suboptimum;
};
