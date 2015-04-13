#include "mmp.h"

//#define SIZE 4
//#define CLIQUE 4

int main(int argc, char* argv[])
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