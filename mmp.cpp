#include "mmp.h"

mmp::mmp(int width,int height,int numlabel)
{
	_width=width;
	_height=height;
	_numlabel=numlabel;

	currentdual = -DBL_MAX;


	return;
}

//void mmp::addunary(int id, int l, double cost)
//{
//	if(id+1%_height==0)
//	{
//		for(int i=0;i<_numlabel;i++)
//		{
//			addbinary(id-1,id,i,l,cost);
//		}
//	}
//	else
//	{
//		for(int i=0;i<_numlabel;i++)
//		{
//			addbinary(id,id+1,l,i,cost);
//		}
//	}
//	
//	return;
//
//}
//
//
//void mmp::addbinary(int id1, int id2, int l1, int l2, double cost)
//{
//	vector<int> index(2);
//	index[0] = id1;
//	index[1] = id2;
//
//	vector<int> label(2);
//	label[0] = l1;
//	label[1] = l2;
//
//	clique2.getTerm(index)[0].changeCost(label,cost);
//	
//	return;
//}

void mmp::addterm(vector<int> vars, vector<int> labs, double cost)
{
	if(cliqueraw.getTerm(vars)==0) cliqueraw.editTerm(vars,new homogenousPosiTerm(vars.size(),_numlabel));
	
	cliqueraw.getTerm(vars)[0].changeCost(labs,cost);

	return;
}

int mmp::addnodetoclique(vector<int>& vars, int node)
{
	int oldsize=vars.size();

	if(node<vars.front())
	{
		return 0;
	}
	else if(node>vars.back())
	{
		vars.push_back(node);
		return 1;
	}
	else
	{
		for(int i=0;i<vars.size();i++)
		{
			if(vars[i]==node) break;
			else if(vars[i]>node)
			{
				vars.insert(vars.begin()+i,node);
				break;
			}
		}

		if(vars.size()==oldsize) return 0;
		else return 1;
	}
}

void mmp::remnodetoclique(vector<int>& vars, int node)
{
	for(int i=0;i<vars.size();i++)
	{
		if(vars[i]==node)
		{
			vars.erase(vars.begin()+i);
			break;
		}
		else if(vars[i]>node)
		{
			break;
		}
	}

	return;
}

void mmp::growclique(int current, poly< homogenousPosiTerm* > & clique, vector<int> &vars, int csize, int numlab)
{	
	if(current%_height!=0 && addnodetoclique(vars,current-1))
	{
		if(vars.size()==csize)
		{
			if(clique.getTerm(vars)==0) clique.editTerm(vars,new homogenousPosiTerm(csize,numlab));
		}
		else
		{
			growclique(current,clique,vars,csize,numlab);
			growclique(current-1,clique,vars,csize,numlab);
		}
		remnodetoclique(vars,current-1);
	}

	if(current+_height<_width*_height && addnodetoclique(vars,current+_height))
	{
		if(vars.size()==csize)
		{
			if(clique.getTerm(vars)==0) clique.editTerm(vars,new homogenousPosiTerm(csize,numlab));
		}
		else
		{
			growclique(current,clique,vars,csize,numlab);
			growclique(current+_height,clique,vars,csize,numlab);
		}
		remnodetoclique(vars,current+_height);
	}

	if((current+1)%_height!=0 && addnodetoclique(vars,current+1))
	{
		if(vars.size()==csize) 
		{
			if(clique.getTerm(vars)==0) clique.editTerm(vars,new homogenousPosiTerm(csize,numlab));
		}
		else
		{
			growclique(current,clique,vars,csize,numlab);
			growclique(current+1,clique,vars,csize,numlab);
		}
		remnodetoclique(vars,current+1);
	}

	if(addnodetoclique(vars,current-_height))
	{
		if(vars.size()==csize) 
		{
			if(clique.getTerm(vars)==0) clique.editTerm(vars,new homogenousPosiTerm(csize,numlab));
		}
		else 			
		{
			growclique(current,clique,vars,csize,numlab);
			growclique(current-_height,clique,vars,csize,numlab);		
		}
		remnodetoclique(vars,current-_height);
	}


	return;
}

void mmp::enumerateMessage(int k)
{
	if(k>_k-1||k<=0) return;

	for(poly< homogenousPosiTerm* >::TERMS::iterator it=cliquek[k+1].firstTerm();it!=cliquek[k+1].lastTerm();it++)
	{		
		printf("K-%d %d %d\n",it->first[0],it->first[1],it->first[2]);
		//parallel_for(int(0),_k,[&](int i)
		for(int i=0;i<k+1;i++)
		{
			vector<int> vars;
			vars.reserve(k);
			for(int j=0;j<k+1;j++)
			{
				if(j!=i) vars.push_back(it->first[j]);
			}

			printf("  %d %d at %d\n",vars[0],vars[1],i);

			if(cliquek_1tok[k].getTerm(vars)==0)
			{
				cliquek_1tok[k].editTerm(vars,new vector<homogenousPosiTerm*>);
				cliquek_1tok_miss[k].editTerm(vars, new vector<int>);
			}
			cliquek_1tok[k].getTerm(vars)[0].push_back(it->second);
			cliquek_1tok_miss[k].getTerm(vars)[0].push_back(i);
		}//);

	}

	//printf("here\n");

	for(poly< vector<homogenousPosiTerm*>* >::TERMS::iterator it=cliquek_1tok[k].firstTerm();it!=cliquek_1tok[k].lastTerm();it++)
	{
		//if(it->second>1) 
			cliquek[k].editTerm(it->first, new homogenousPosiTerm(k,_numlabel));
		//else it->second=0;
	}

	//cliquek_1tok[k].clean();


	printf("%d %d-clique in total\n",cliquek[k].numTerm(),k);

	return;
}

//void mmp::enumerateBoth(int k)
//{	
//	_k = k;
//
//	poly< homogenousPosiTerm* > *cliques = new poly< homogenousPosiTerm* >[_width];
//	poly< int > *tempc = new poly< int >[_width];
//
//	parallel_for (int(0), _width, [&](int i)
//	{
//		for(int j=0;j<_height;j++)
//		{
//			growclique(i*_height+j,cliques[i],vector<int>(1,i*_height+j),k,_numlabel);
//		}
//
//		for(poly< homogenousPosiTerm* >::TERMS::iterator it=cliques[i].firstTerm();it!=cliques[i].lastTerm();it++)
//		{		
//			//parallel_for(int(0),_k,[&](int i)
//			for(int i2=0;i2<_k;i2++)
//			{
//				vector<int> vars;
//				vars.reserve(_k-1);
//				for(int j=0;j<_k;j++)
//				{
//					if(j!=i2) vars.push_back(it->first[j]);
//				}
//				tempc[vars.front()/_height].addTerm(vars,1);
//			}//);
//
//		}
//
//
//	});
//
//	//printf("here\n");
//
//	for(int i=0;i<_width;i++)
//	{
//		cliquek.expand(cliques[i]);
//		cliques[i].destroy();
//		cliquek_1tok.expand(tempc[i]);
//		tempc[i].destroy();
//	}
//
//
//
//	delete[] cliques;
//	delete[] tempc;
//
//	for(poly< int >::TERMS::iterator it=cliquek_1tok.firstTerm();it!=cliquek_1tok.lastTerm();it++)
//	{
//		if(it->second>1) 
//			cliquek_1.editTerm(it->first, new homogenousPosiTerm(_k-1,_numlabel));
//		//else it->second=0;
//	}
//
//	cliquek_1tok.clean();
//
//
//	printf("%d %d-clique in total\n",cliquek_1.numTerm(),_k-1);
//
//	printf("%d %d-clique in total\n",cliquek.numTerm(),k);
//	
//
//	return;
//}

void mmp::enumerateClique(int k)
{	
	_k = k;

	cliquek = new poly< homogenousPosiTerm* >[k+1];
	cliquek_1tok = new poly< vector<homogenousPosiTerm*>* >[k];
	cliquek_1tok_miss = new poly<vector<int>*>[k];

	poly< homogenousPosiTerm* > *cliques = new poly< homogenousPosiTerm* >[_width];

	parallel_for (int(0), _width, [&](int i)
	{
		for(int j=0;j<_height;j++)
		{
			growclique(i*_height+j,cliques[i],vector<int>(1,i*_height+j),k,_numlabel);
		}
	});

	for(int i=0;i<_width;i++)
	{
		cliquek[k].expand(cliques[i]);
		cliques[i].destroy();

	}

	delete[] cliques;



	printf("%d %d-clique in total\n",cliquek[k].numTerm(),k);
	

	return;
}



void mmp::plotcliquek(int k)
{
	for(poly< homogenousPosiTerm* >::TERMS::iterator it=cliquek[k].firstTerm();it!=cliquek[k].lastTerm();it++)
	{
		for(int i=0;i<k;i++) printf("%d ",it->first[i]);

		printf(": ");

		it->second[0].plotCosts();

		printf("\n");
	}

	return;
}

void mmp::optimize_seq()
{
	for(poly< homogenousPosiTerm* >::TERMS::iterator it=cliqueraw.firstTerm();
		it!=cliqueraw.lastTerm();it++)
	{
		vector<int> index = it->first;

		poly<double> temp;
		it->second[0].getCosts(temp);
		cliquek[index.size()].getTerm(index)[0].changeCosts(temp);
	}

	for(int i=2;i<=_k;i++)
	{
		printf("i=%d\n",i);
		feedback(i);
	}

	for(int i=0;i<10000;i++)
	{
printf("ITERATION %d ======================================\n",i);
		

		for(poly< homogenousPosiTerm* >::TERMS::iterator it=cliquek[_k].firstTerm();it!=cliquek[_k].lastTerm();it++)
		{
			vector<int> label;
			double stepsize=it->second[0].getLabel(label);
			//if(stepsize<0.001) stepsize=0.001;
			//it->second[0].changeCost(label,stepsize);

			for(int i=0;i<_k;i++) printf("%d ",it->first[i]);
			printf(": ");
			for(int i=0;i<_k;i++) printf("%d ",label[i]);
			printf("\n");
		}
		plotcliquek(_k);
	
		for(poly< homogenousPosiTerm* >::TERMS::iterator it=cliquek[_k].firstTerm();it!=cliquek[_k].lastTerm();it++)
		{
			vector<int> label;
			double stepsize=it->second[0].getLabel(label);

for(int i=0;i<_k;i++) printf("%d ",it->first[i]);
printf(": ");
for(int i=0;i<_k;i++) printf("%d ",label[i]);
printf("\n");

			for(int i=0;i<_k;i++)
			{
				vector<int> vars;
				vector<int> sublab;
				vars.reserve(_k-1);
				sublab.reserve(_k-1);

				for(int j=0;j<_k;j++)
				{
					if(j!=i) 
					{
						vars.push_back(it->first[j]);
						sublab.push_back(label[j]);
					}
				}

				cliquek[_k-1].getTerm(vars)[0].changeCost(sublab,-stepsize/_k);

				vector<int> tlabel = label;
				for(int j=0;j<_numlabel;j++)
				{
					tlabel[i]=j;
					it->second[0].changeCost(tlabel,stepsize/_k);
				}
			}

			feedback(_k);
			//printf("local done\n");
			//demand(_k);
			//feedback(_k);
		}

double tempd = currentdual;
printf("dual=%e %e\n",currentdual,tempd-dualvalue());
 
	}



	return;
}

void mmp::optimize_it()
{

	for(poly< homogenousPosiTerm* >::TERMS::iterator it=cliqueraw.firstTerm();
		it!=cliqueraw.lastTerm();it++)
	{
		vector<int> index = it->first;

		poly<double> temp;
		it->second[0].getCosts(temp);
		cliquek[index.size()].getTerm(index)[0].changeCosts(temp);
	}



	plotcliquek(1);
	for(int i=2;i<=_k;i++)
	{
		printf("i=%d\n",i);
		feedback(i);
		plotcliquek(i);
	}



	for(int i=0;i<100000;i++)
	{
//if(i%10000==0)
//{
//printf("ITERATION %d ======================================\n",i);
//plotcliquek(3);
//}
		printf("i=%d\n",i);
		plotcliquek(_k);
		instant_top();
		//plotcliquek(_k-1);
		//plotcliquek(_k);

		//getchar();

	double tempd = currentdual;

	printf("dual=%e improvement=%e\n",currentdual,dualvalue()-tempd);
	if(tempd-dualvalue()>0) getchar();
	}
	return;
}

void mmp::optimize()
{
	for(poly< homogenousPosiTerm* >::TERMS::iterator it=cliqueraw.firstTerm();
		it!=cliqueraw.lastTerm();it++)
	{
		vector<int> index = it->first;

		poly<double> temp;
		it->second[0].getCosts(temp);
		cliquek[index.size()].getTerm(index)[0].changeCosts(temp);
	}

	plotcliquek(1);
	for(int i=2;i<=_k;i++)
	{
		printf("i=%d\n",i);
		feedback(i);
		plotcliquek(i);
	}

	for(int i=0;i<10000;i++)
	{
//if(i%10000==0)
//{
//printf("ITERATION %d ======================================\n",i);
//plotcliquek(3);
//}
		//plotcliquek(_k);
		demand(_k);
		//plotcliquek(_k-1);
		//plotcliquek(_k);
		feedback(_k);
		//getchar();

double tempd = currentdual;

printf("dual=%e %e\n",currentdual,tempd-dualvalue());
if(tempd-dualvalue()>0) getchar();
	}



	return;
}

void mmp::optimize_deep()
{
	for(poly< homogenousPosiTerm* >::TERMS::iterator it=cliqueraw.firstTerm();
		it!=cliqueraw.lastTerm();it++)
	{
		vector<int> index = it->first;

		poly<double> temp;
		it->second[0].getCosts(temp);
		cliquek[index.size()].getTerm(index)[0].changeCosts(temp);
	}

	plotcliquek(1);
	for(int i=2;i<=_k;i++)
	{
		printf("i=%d\n",i);
		feedback(i);
		plotcliquek(i);
	}

	for(int i=0;i<10000;i++)
	{
//if(i%10000==0)
//{
printf("ITERATION %d ======================================\n",i);
//plotcliquek(3);
//}
		plotcliquek(_k);
		//demand(_k);
		//plotcliquek(_k-1);
		//plotcliquek(_k);
		//feedback(_k);
		//getchar();
		for(int j=_k;j>=2;j--)
		{
			demand(j);
		}
		for(int j=2;j<=_k;j++)
		{
			feedback(j);
		}

double tempd = currentdual;
printf("dual=%e improvement=%e\n",currentdual,tempd-dualvalue());
	}



	return;
}
void mmp::feedback(int k)
{
	for(poly< homogenousPosiTerm* >::TERMS::iterator it=cliquek[k].firstTerm();it!=cliquek[k].lastTerm();it++)
	{
//printf("%d %d:\n",it->first[0],it->first[1]);
		for(int i=0;i<k;i++)
		{
			vector<int> vars;
			vars.reserve(k-1);
			for(int j=0;j<k;j++)
			{
				if(j!=i) vars.push_back(it->first[j]);
			}

			poly<double> tempp;

			cliquek[k-1].getTerm(vars)[0].getCosts(tempp);



			for(poly<double>::TERMS::iterator it2 = tempp.firstTerm();
				it2!=tempp.lastTerm();it2++)
			{
				vector<int> vars2(k);
				
				for(int j=0;j<i;j++) vars2[j] = it2->first[j];
				for(int j=i;j<k;j++) vars2[j] = it2->first[j-1];
				for(int j=0;j<_numlabel;j++)
				{
					vars2[i] = j;
					it->second[0].changeCost(vars2,it2->second/cliquek_1tok[k-1].getTerm(vars)[0].size());
					//printf("size=%d\n",cliquek_1tok[k-1].getTerm(vars)[0].size());getchar();
				}
				
			}



			//tempp=tempp*-1;
			//cliquek[k-1].getTerm(vars)[0].changeCosts(tempp);
		}
	}

	for(poly< homogenousPosiTerm* >::TERMS::iterator it=cliquek[k-1].firstTerm();it!=cliquek[k-1].lastTerm();it++)
	{
		it->second[0].setResidual(0);
	}

	return;
}

void mmp::instant_top()
{
	for(poly< homogenousPosiTerm* >::TERMS::iterator it=cliquek[_k].firstTerm();it!=cliquek[_k].lastTerm();it++)
	{//for each t
		vector<int> label;
		double stepsize=it->second[0].getLabel(label);
		//printf("stepsize= %e\n",stepsize);
		//if(stepsize<0.001) stepsize=0.001;
		//it->second[0].changeCost(label,stepsize);

		//printf("label=%d %d\n",label[0],label[1])

		for(int i=0;i<_k;i++) printf("%d ",it->first[i]);
		printf(": ");
		for(int i=0;i<_k;i++) printf("%d ",label[i]);
		printf("\n");

		for(int i=0;i<_k;i++)
		{//for each s
			vector<int> vars;
			vector<int> sublab;
			vars.reserve(_k-1);
			sublab.reserve(_k-1);

			for(int j=0;j<_k;j++)
			{
				if(j!=i) 
				{
					vars.push_back(it->first[j]);
					sublab.push_back(label[j]);
					//printf("v%d=l%d\n",vars.back(),sublab.back());
				}
				
			}

			////Es = Es + Mts
			//cliquek[_k-1].getTerm(vars)[0].changeCost(sublab,-stepsize/_k);

			////Et = Et - Mts
			//vector<int> tlabel = label;
			//for(int j=0;j<_numlabel;j++)
			//{
			//	tlabel[i]=j;
			//	it->second[0].changeCost(tlabel,stepsize/_k);
			//}
			double message = stepsize;

			vector<homogenousPosiTerm*> uncles = cliquek_1tok[_k-1].getTerm(vars)[0];

			for(int k=0;k<uncles.size();k++)
			{//for each t'
				if(uncles[k]==it->second) continue;//skip youself
				
				if(message==0) break;//nothing left;

				double margin = uncles[k][0].getmargin(sublab,cliquek_1tok_miss[_k-1].getTerm(vars)[0][k])/2;

				if(margin==0) continue;
				//printf("message=%e margin=%e\n",message,margin);

				if(margin>=message)
				{
					uncles[k][0].changesubcost(sublab,cliquek_1tok_miss[_k-1].getTerm(vars)[0][k],-message);
					message = 0;
				}
				else
				{
					message-=margin;
					uncles[k][0].changesubcost(sublab,cliquek_1tok_miss[_k-1].getTerm(vars)[0][k],-margin);
				}
			//printf("one uncle\n");
			//plotcliquek(_k);getchar();
			}



			if(message<stepsize)
			{
				vector<int> tlabel = label;
				for(int j=0;j<_numlabel;j++)
				{
					tlabel[i]=j;
					it->second[0].changeCost(tlabel,stepsize-message);
				}
			}
		}


	}
 



	return;
}


void mmp::demand(int k)
{
	for(poly< homogenousPosiTerm* >::TERMS::iterator it=cliquek[k].firstTerm();it!=cliquek[k].lastTerm();it++)
	{
		vector<int> label;
		double stepsize=it->second[0].getLabel(label);
		//printf("stepsize= %e\n",stepsize);
		//if(stepsize<0.001) stepsize=0.001;
		//it->second[0].changeCost(label,stepsize);

		//for(int i=0;i<k;i++) printf("%d ",it->first[i]);
		//printf(": ");
		//for(int i=0;i<k;i++) printf("%d ",label[i]);
		//printf("\n");

		for(int i=0;i<k;i++)
		{
			vector<int> vars;
			vector<int> sublab;
			vars.reserve(k-1);
			sublab.reserve(k-1);

			for(int j=0;j<k;j++)
			{
				if(j!=i) 
				{
					vars.push_back(it->first[j]);
					sublab.push_back(label[j]);
				}
			}

			cliquek[k-1].getTerm(vars)[0].changeCost(sublab,-stepsize/k);

			vector<int> tlabel = label;
			for(int j=0;j<_numlabel;j++)
			{
				tlabel[i]=j;
				it->second[0].changeCost(tlabel,stepsize/k);
			}
		}


	}
 



	return;
}

double mmp::dualvalue()
{
	double total=0;
	for(poly< homogenousPosiTerm* >::TERMS::iterator it=cliquek[_k].firstTerm();it!=cliquek[_k].lastTerm();it++)
	{
		total+=it->second[0].getoptimum();
	}

	currentdual = total;

	return total;
}