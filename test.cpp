#include "mmp.h"

//#define SIZE 4
//#define CLIQUE 4

int main1(int argc, char* argv[])
{
	//mmp test(SIZE,SIZE,2);
	//test.enumerateBoth(CLIQUE);

	int SIZE=atoi(argv[1]);
	int CLIQUE=atoi(argv[2]);

	mmp test2(SIZE,SIZE,2);
	test2.enumerateClique(CLIQUE);

	for(int i=CLIQUE-1;i>0;i--)
	test2.enumerateMessage(i);


	for(int i=0;i<SIZE*SIZE;i++)
	{
		test2.addterm(vector<int>(1,i),vector<int>(1,0),0);
		if(i%2==0) test2.addterm(vector<int>(1,i),vector<int>(1,1),-1.3);
		else test2.addterm(vector<int>(1,i),vector<int>(1,1),1.2);
	}

	vector<int> index(2);
	vector<int> labs(2);

	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			if(j+1<SIZE)
			{
				index[0] = i*SIZE+j;
				index[1] = i*SIZE+j+1;
				labs[0]=0;
				labs[1]=0;
				test2.addterm(index,labs,0);
				labs[0]=0;
				labs[1]=1;
				test2.addterm(index,labs,2);
				labs[0]=1;
				labs[1]=0;
				test2.addterm(index,labs,2);
				labs[0]=1;
				labs[1]=1;
				test2.addterm(index,labs,0);
			}
			
			if(i+1<SIZE)
			{
				index[0] = i*SIZE+j;
				index[1] = i*SIZE+j+SIZE;
				labs[0]=0;
				labs[1]=0;
				test2.addterm(index,labs,0);
				labs[0]=0;
				labs[1]=1;
				test2.addterm(index,labs,2);
				labs[0]=1;
				labs[1]=0;
				test2.addterm(index,labs,2);
				labs[0]=1;
				labs[1]=1;
				test2.addterm(index,labs,0);
			}
		}
	}

	test2.optimize();
	printf("optimize done\n");

	test2.plotcliquek(1);
	test2.plotcliquek(2);

	//test.clique3in4();
	//test.plotcliquek_1();
	

	return 0;
}

int main2()
{
	mmp test2(4,1,2);
	test2.enumerateClique(3);
	test2.enumerateMessage(2);
	test2.enumerateMessage(1);


	vector<int> index(2);
	vector<int> labs(2);

	test2.addterm(vector<int>(1,0),vector<int>(1,0),2);
	test2.addterm(vector<int>(1,0),vector<int>(1,1),0);
	test2.addterm(vector<int>(1,1),vector<int>(1,0),0);
	test2.addterm(vector<int>(1,1),vector<int>(1,1),0);
	test2.addterm(vector<int>(1,2),vector<int>(1,0),0);
	test2.addterm(vector<int>(1,2),vector<int>(1,1),0);
	test2.addterm(vector<int>(1,3),vector<int>(1,0),0);
	test2.addterm(vector<int>(1,3),vector<int>(1,1),1);

	index[0]=0;
	index[1]=1;
	labs[0]=0;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=0;labs[1]=1;test2.addterm(index,labs,1);
	labs[0]=1;labs[1]=0;test2.addterm(index,labs,1);
	labs[0]=1;labs[1]=1;test2.addterm(index,labs,0);

	index[0]=1;
	index[1]=2;
	labs[0]=0;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=0;labs[1]=1;test2.addterm(index,labs,1);
	labs[0]=1;labs[1]=0;test2.addterm(index,labs,1);
	labs[0]=1;labs[1]=1;test2.addterm(index,labs,0);

	index[0]=2;
	index[1]=3;
	labs[0]=0;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=0;labs[1]=1;test2.addterm(index,labs,1);
	labs[0]=1;labs[1]=0;test2.addterm(index,labs,1);
	labs[0]=1;labs[1]=1;test2.addterm(index,labs,0);

	test2.optimize();
	printf("optimize done\n");

	test2.plotcliquek(1);
	test2.plotcliquek(2);

}

int main3()
{
	
	mmp test2(2,2,2);
	test2.enumerateClique(3);
	//test2.enumerateMessage(3);
	test2.enumerateMessage(2);
	test2.enumerateMessage(1);


	vector<int> index(2);
	vector<int> labs(2);

	test2.addterm(vector<int>(1,0),vector<int>(1,0),0);
	test2.addterm(vector<int>(1,0),vector<int>(1,1),6);
	test2.addterm(vector<int>(1,1),vector<int>(1,0),0);
	test2.addterm(vector<int>(1,1),vector<int>(1,1),6);
	test2.addterm(vector<int>(1,2),vector<int>(1,0),0);
	test2.addterm(vector<int>(1,2),vector<int>(1,1),0);
	test2.addterm(vector<int>(1,3),vector<int>(1,0),0);
	test2.addterm(vector<int>(1,3),vector<int>(1,1),0);

	index[0]=0;
	index[1]=1;
	labs[0]=0;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=0;labs[1]=1;test2.addterm(index,labs,0);
	labs[0]=1;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=1;labs[1]=1;test2.addterm(index,labs,-6);

	index[0]=0;
	index[1]=2;
	labs[0]=0;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=0;labs[1]=1;test2.addterm(index,labs,0);
	labs[0]=1;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=1;labs[1]=1;test2.addterm(index,labs,-6);

	index[0]=1;
	index[1]=3;
	labs[0]=0;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=0;labs[1]=1;test2.addterm(index,labs,0);
	labs[0]=1;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=1;labs[1]=1;test2.addterm(index,labs,-6);

	index[0]=2;
	index[1]=3;
	labs[0]=0;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=0;labs[1]=1;test2.addterm(index,labs,0);
	labs[0]=1;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=1;labs[1]=1;test2.addterm(index,labs,6);

	test2.optimize_it();
	printf("optimize done\n");

	//test2.plotcliquek(1);
	//test2.plotcliquek(2);
	//test2.plotcliquek(3);
}

int main44()
{
	mmp test2(2,2,2);
	test2.enumerateClique(2);
	//test2.enumerateMessage(3);
	//test2.enumerateMessage(2);
	test2.enumerateMessage(1);


	vector<int> index(2);
	vector<int> labs(2);

	test2.addterm(vector<int>(1,0),vector<int>(1,0),0);
	test2.addterm(vector<int>(1,0),vector<int>(1,1),0);
	test2.addterm(vector<int>(1,1),vector<int>(1,0),0);
	test2.addterm(vector<int>(1,1),vector<int>(1,1),0);
	test2.addterm(vector<int>(1,2),vector<int>(1,0),0);
	test2.addterm(vector<int>(1,2),vector<int>(1,1),0);
	test2.addterm(vector<int>(1,3),vector<int>(1,0),0);
	test2.addterm(vector<int>(1,3),vector<int>(1,1),0);

	index[0]=0;
	index[1]=1;
	labs[0]=0;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=0;labs[1]=1;test2.addterm(index,labs,0);
	labs[0]=1;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=1;labs[1]=1;test2.addterm(index,labs,0);

	index[0]=0;
	index[1]=2;
	labs[0]=0;labs[1]=0;test2.addterm(index,labs,1);
	labs[0]=0;labs[1]=1;test2.addterm(index,labs,0);
	labs[0]=1;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=1;labs[1]=1;test2.addterm(index,labs,0);

	index[0]=1;
	index[1]=3;
	labs[0]=0;labs[1]=0;test2.addterm(index,labs,1);
	labs[0]=0;labs[1]=1;test2.addterm(index,labs,0);
	labs[0]=1;labs[1]=0;test2.addterm(index,labs,1);
	labs[0]=1;labs[1]=1;test2.addterm(index,labs,1);

	index[0]=2;
	index[1]=3;
	labs[0]=0;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=0;labs[1]=1;test2.addterm(index,labs,0);
	labs[0]=1;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=1;labs[1]=1;test2.addterm(index,labs,1);

	printf("optimize start\n");
	test2.optimize_it();
	printf("optimize done\n");

	//test2.plotcliquek(1);
	//test2.plotcliquek(2);
	//test2.plotcliquek(3);
}

int main4()
{
	printf("started\n");
	mmp test2(5,1,2);
	test2.enumerateClique(3);
	//test2.enumerateMessage(3);
	test2.enumerateMessage(2);
	test2.enumerateMessage(1);


	vector<int> index(2);
	vector<int> labs(2);

	test2.addterm(vector<int>(1,0),vector<int>(1,0),0);
	test2.addterm(vector<int>(1,0),vector<int>(1,1),0.1);
	test2.addterm(vector<int>(1,1),vector<int>(1,0),0);
	test2.addterm(vector<int>(1,1),vector<int>(1,1),0);
	test2.addterm(vector<int>(1,2),vector<int>(1,0),0);
	test2.addterm(vector<int>(1,2),vector<int>(1,1),0);
	test2.addterm(vector<int>(1,3),vector<int>(1,0),0);
	test2.addterm(vector<int>(1,3),vector<int>(1,1),0);
	test2.addterm(vector<int>(1,4),vector<int>(1,0),20);
	test2.addterm(vector<int>(1,4),vector<int>(1,1),0);


	index[0]=0;
	index[1]=1;
	labs[0]=0;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=0;labs[1]=1;test2.addterm(index,labs,2);
	labs[0]=1;labs[1]=0;test2.addterm(index,labs,2);
	labs[0]=1;labs[1]=1;test2.addterm(index,labs,0);

	index[0]=1;
	index[1]=2;
	labs[0]=0;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=0;labs[1]=1;test2.addterm(index,labs,2);
	labs[0]=1;labs[1]=0;test2.addterm(index,labs,2);
	labs[0]=1;labs[1]=1;test2.addterm(index,labs,0);

	index[0]=2;
	index[1]=3;
	labs[0]=0;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=0;labs[1]=1;test2.addterm(index,labs,2);
	labs[0]=1;labs[1]=0;test2.addterm(index,labs,2);
	labs[0]=1;labs[1]=1;test2.addterm(index,labs,0);

	index[0]=3;
	index[1]=4;
	labs[0]=0;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=0;labs[1]=1;test2.addterm(index,labs,2);
	labs[0]=1;labs[1]=0;test2.addterm(index,labs,2);
	labs[0]=1;labs[1]=1;test2.addterm(index,labs,0);

	test2.optimize_it();
	printf("optimize done\n");

	//test2.plotcliquek(1);
	//test2.plotcliquek(2);
	//test2.plotcliquek(3);
	return 0;
}

int main5()
{
	printf("started\n");
	mmp test2(4,1,2);
	test2.enumerateClique(2);
	//test2.enumerateMessage(3);
	//test2.enumerateMessage(2);
	test2.enumerateMessage(1);


	vector<int> index(2);
	vector<int> labs(2);

	test2.addterm(vector<int>(1,0),vector<int>(1,0),2);
	test2.addterm(vector<int>(1,0),vector<int>(1,1),0);
	test2.addterm(vector<int>(1,1),vector<int>(1,0),0);
	test2.addterm(vector<int>(1,1),vector<int>(1,1),3);
	test2.addterm(vector<int>(1,2),vector<int>(1,0),5);
	test2.addterm(vector<int>(1,2),vector<int>(1,1),5);
	test2.addterm(vector<int>(1,3),vector<int>(1,0),0);
	test2.addterm(vector<int>(1,3),vector<int>(1,1),4);

	index[0]=0;
	index[1]=1;
	labs[0]=0;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=0;labs[1]=1;test2.addterm(index,labs,10);
	labs[0]=1;labs[1]=0;test2.addterm(index,labs,10);
	labs[0]=1;labs[1]=1;test2.addterm(index,labs,0);

	index[0]=1;
	index[1]=2;
	labs[0]=0;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=0;labs[1]=1;test2.addterm(index,labs,10);
	labs[0]=1;labs[1]=0;test2.addterm(index,labs,10);
	labs[0]=1;labs[1]=1;test2.addterm(index,labs,0);

	index[0]=2;
	index[1]=3;
	labs[0]=0;labs[1]=0;test2.addterm(index,labs,0);
	labs[0]=0;labs[1]=1;test2.addterm(index,labs,10);
	labs[0]=1;labs[1]=0;test2.addterm(index,labs,10);
	labs[0]=1;labs[1]=1;test2.addterm(index,labs,0);

	test2.optimize_it();
	printf("optimize done\n");

	//test2.plotcliquek(1);
	test2.plotcliquek(2);
	//test2.plotcliquek(3);
	return 0;
}