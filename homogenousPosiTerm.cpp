#include "homogenousPosiTerm.h"

homogenousPosiTerm::homogenousPosiTerm(int numVar, int numLab)
{
	_numVar = numVar;
	_numLab = numLab;
	optimizer.clear();
	srand (time(NULL));

	return;
}


void homogenousPosiTerm::setCost(vector<int> & labels, double cost)
{
	label2costs.editTerm(labels,cost);
	optimizer.clear();

	return;
}

void homogenousPosiTerm:: changesubcost(vector<int> & labels, int over, double change)
{
	vector<int> flab(_numVar);
	optimizer.clear();
				
	for(int j=0;j<over;j++) flab[j] = labels[j];
	for(int j=over;j<_numVar;j++) flab[j] = labels[j-1];
	for(int j=0;j<_numLab;j++)
	{
		flab[over] = j;
		label2costs.addTerm(flab,change);
		optimizer.clear();
	}

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

void homogenousPosiTerm::setResidual(double r)
{
	for(poly<double>::TERMS::iterator it= label2costs.firstTerm();
		it!=label2costs.lastTerm();it++)
	{
		it->second = r;
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


void homogenousPosiTerm::plotEnergyTable()
{
	return;
}


void homogenousPosiTerm::plotCosts()
{
	for(poly<double>::TERMS::iterator it=label2costs.firstTerm();
		it!=label2costs.lastTerm();it++)
	{
		printf("(");
		for(int i=0;i<it->first.size();i++) printf("%d ",it->first[i]);
		printf("| %.2f) ",it->second);
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

	optimizer = label2costs.firstTerm()->first;
	optimum = label2costs.firstTerm()->second;
	suboptimum = DBL_MAX;

	for(poly<double>::TERMS::iterator it=label2costs.firstTerm();it!=label2costs.lastTerm();it++)
	{
//printf("%f search %f\n",optimum,it->second);
		if(optimum>it->second)
		{
			suboptimum = optimum;
			optimum = it->second;
			optimizer = it->first;
		}
		else if(optimum==it->second)
		{
			if(rand() % 2==0) optimizer = it->first;
		}
		else if(suboptimum>it->second && optimum<it->second)
		{
			suboptimum = it->second;
		}
//printf("sub optimum %f %f\n",suboptimum, optimum);
	}

	labels = optimizer;
	if(suboptimum==DBL_MAX) suboptimum = optimum;
//printf("")
	return suboptimum-optimum;


}

double homogenousPosiTerm::getLabelmax(vector<int>& labels)
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
		
		if(suboptimum<it->second)
		{
			suboptimum = it->second;
		}
	}

	labels = optimizer;


	return suboptimum-optimum;


}


double homogenousPosiTerm::getmargin(vector<int>& labels, int over)
{	
	if(optimizer.size()==0) getLabel(optimizer);

	double margin = DBL_MAX;

	vector<int> flabel(_numVar);


	for(int j=0;j<over;j++) flabel[j] = labels[j];
	for(int j=over;j<_numVar;j++) flabel[j] = labels[j-1];
	for(int j=0;j<_numLab;j++)
	{
		flabel[over]=j;
		if(margin>label2costs.getTerm(flabel)) margin = label2costs.getTerm(flabel);

		//printf("label=%d %d %d\n",flabel[0],flabel[1],flabel[2]);
		//printf("m=%f c=%f\n",margin,label2costs.getTerm(flabel));
		
	}

	//for(poly<double>::TERMS::iterator it = label2costs.firstTerm();it!=label2costs.lastTerm();it++) 
	//{
	//	printf("%d %d %d : %f : %d %f\n",it->first[0],it->first[1],it->first[2],it->second,flabel.size(),label2costs.getTerm(flabel));
	//}

	//printf("\n m=%f o=%f\n",margin, optimum);getchar();
	return margin-optimum;
}