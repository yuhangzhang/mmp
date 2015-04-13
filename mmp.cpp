#include "mmp.h"

mmp::mmp(int width,int height,int numlabel)
{
	_width=width;
	_height=height;
	_numlabel=numlabel;




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
		//parallel_for(int(0),_k,[&](int i)
		for(int i=0;i<k+1;i++)
		{
			vector<int> vars;
			vars.reserve(k);
			for(int j=0;j<k+1;j++)
			{
				if(j!=i) vars.push_back(it->first[j]);
			}
			cliquek_1tok[k].addTerm(vars,1);
		}//);

	}

	//printf("here\n");

	for(poly< int >::TERMS::iterator it=cliquek_1tok[k].firstTerm();it!=cliquek_1tok[k].lastTerm();it++)
	{
		//if(it->second>1) 
			cliquek[k].editTerm(it->first, new homogenousPosiTerm(k,_numlabel));
		//else it->second=0;
	}

	cliquek_1tok[k].clean();


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
	cliquek_1tok = new poly< int >[k];

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

	for(int i=2;i<=_k;i++)
	{
		printf("i=%d\n",i);
		feedback(i);
	}

	for(int i=0;i<500;i++)
	{
printf("ITERATION %d ======================================\n",i);
		//plotcliquek(2);
		demand(_k);
		//plotcliquek(1);
		//plotcliquek(2);
		feedback(_k);

		for(int j=_k;j>=2;j--)
		{
			demand(j);
		}
		for(int j=2;j<=_k;j++)
		{
			feedback(j);
		}
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
					it->second[0].changeCost(vars2,it2->second/cliquek_1tok[k-1].getTerm(vars));
//printf("==%d %d\n",vars2[0],vars2[1]);getchar();
				}

				
			}

			//tempp=tempp*-1;
			//cliquek[k-1].getTerm(vars)[0].changeCosts(tempp);
		}
	}

	for(poly< homogenousPosiTerm* >::TERMS::iterator it=cliquek[k-1].firstTerm();it!=cliquek[k-1].lastTerm();it++)
	{
		it->second[0].setZero();
	}

	return;
}


void mmp::demand(int k)
{
	for(poly< homogenousPosiTerm* >::TERMS::iterator it=cliquek[k].firstTerm();it!=cliquek[k].lastTerm();it++)
	{
		vector<int> label;
		double stepsize=it->second[0].getLabel(label);
		//it->second[0].changeCost(label,stepsize);

		for(int i=0;i<k;i++) printf("%d ",it->first[i]);
		printf(": ");
		for(int i=0;i<k;i++) printf("%d ",label[i]);
		printf("\n");

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

