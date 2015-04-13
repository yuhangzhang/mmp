#include "homogenousPosiTerm.h"

homogenousPosiTerm::homogenousPosiTerm(int numVar, int numLab)
{
	_numVar = numVar;
	_numLab = numLab;
	optimizer.clear();
	return;
}


void homogenousPosiTerm::setCost(vector<int> & labels, double cost)
{
	label2costs.editTerm(labels,cost);
	optimizer.clear();

	return;
}

void homogenousPosiTerm::changeCost(vector<int> & labels, double change)
{
	label2costs.addTerm(labels,change);
	optimizer.clear();
	return;
}

void homogenousPosiTerm::editCosts(poly<double>& p)
{
	label2costs = p;
	optimizer.clear();
	return;
}

void homogenousPosiTerm::changeCosts(poly<double>& p)
{
	label2costs.merge(p); 
	optimizer.clear();
	return;
}

void homogenousPosiTerm::setZero()
{
	for(poly<double>::TERMS::iterator it= label2costs.firstTerm();
		it!=label2costs.lastTerm();it++)
	{
		it->second = 0;
	}
	
	return;
}

poly<double> homogenousPosiTerm::getCosts()
{
	return label2costs;
}

void homogenousPosiTerm::getCosts(poly<double>& p)
{
	p.expand(label2costs); 
	return;
}

void homogenousPosiTerm::plotCosts()
{
	for(poly<double>::TERMS::iterator it=label2costs.firstTerm();
		it!=label2costs.lastTerm();it++)
	{
		printf("(");
		for(int i=0;i<it->first.size();i++) printf("%d ",it->first[i]);
		printf("|%f) ",it->second);
	}

	return;
}

double homogenousPosiTerm::getLabel(vector<int>& labels)
{	
	
	if(optimizer.size()>0)
	{
		//printf("optimum=%f\n",optimum);
		labels = optimizer;
		return suboptimum-optimum;
	}
	else if(label2costs.numTerm()<pow(double(_numLab),_numVar))
	{
		printf("incomplete label costs %d / %.0f | %d %d\n",label2costs.numTerm(),pow(double(_numLab),_numVar),_numLab,_numVar);
		exit(0);
	}
	//{
	//	optimizer = vector<int>(_numVar,0);
	//	optimum = 0;
	//	suboptimum = 0;
	//	labels = optimizer;
	//	return suboptimum-optimum;
	//}

	//printf("in");

	poly<double>::TERMS::iterator tempit = label2costs.firstTerm();
	optimizer = tempit->first;
	optimum = tempit->second;
	tempit++;
	suboptimum = tempit->second;

	for(poly<double>::TERMS::iterator it=label2costs.firstTerm();it!=label2costs.lastTerm();it++)
	{
		if(optimum>it->second)
		{
			suboptimum = optimum;
			optimum = it->second;
			optimizer = it->first;
		}
		else if(suboptimum>it->second && optimum<it->second)
		{
			suboptimum = it->second;
		}
	}

	labels = optimizer;


	return suboptimum-optimum;


}