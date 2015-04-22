#include "homogenousPosiTerm.h"
#include <ppl.h>

using namespace Concurrency;

class mmp
{
public:
	mmp(int width,int height,int numlabel);
	void addterm(vector<int> vars, vector<int> labs, double cost);
	//void addunary(int id, int l, double cost);
	//void addbinary(int id1, int id2, int l1, int l2, double cost);
	void enumerateClique(int k);
	//void enumerateBoth(int k);
	void enumerateMessage(int k);
	void plotcliquek(int k);

	void optimize_it();//instant top
	void optimize();
	void optimize_deep();
	void optimize_seq();
	double dualvalue();

	void instant_top();//

private:
	double currentdual;
	poly< homogenousPosiTerm* > cliqueraw;
	poly< homogenousPosiTerm* > *cliquek;

	void feedback(int k);//k-1 feed all it has evenly to k
	void demand(int k); //k ask k-1 for what it needs.
	
 

	poly< vector<homogenousPosiTerm*>* > *cliquek_1tok;//what k-clique share this k-1 clique
	poly< vector<int>* > *cliquek_1tok_miss;

	int _k;
	int _width;
	int _height;
	int _numlabel;
	void remnodetoclique(vector<int>& vars, int node);
	int addnodetoclique(vector<int>& vars, int node);
	void growclique(int current, poly< homogenousPosiTerm* > & clique, vector<int> &vars, int csize, int numlab);
};
