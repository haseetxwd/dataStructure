#include <vector>
#include <iostream>
using namespace std;

class Queen {
public:
	int x;
	int y;
	explicit Queen(int xx = 0,int yy = 0):x(xx),y(yy) {};
	~Queen(){};
	bool operator==(Queen const& q)const{
		return (x == q.x)
			|| (y == q.y)
			|| (x + y == q.x + q.y)
			|| (x - y == q.x - q.y);
	}
	bool operator!=(Queen const& q) const{ return !(*this == q); }
};

int eightQueenPuzzle() {
	vector<Queen> solu;
	Queen q;
	int nSolu = 0;
	
	do{
		if (q.x >= 8 || q.y >= 8){
			q = solu.back();
			solu.pop_back();
			q.y++;
		}
		//查找冲突
//		auto result = find(solu.begin(), solu.end(), q);
		auto result = solu.begin();
		for (; result != solu.end(); ++result) {
			if (*result == q) break;
		}
		if (result == solu.end() && q.y < 8){
			solu.push_back(q);
			if (solu.size() == 8) nSolu++;//得到一个解
			q.x++;
			q.y = 0;
		}
		else {
			q.y++;
		}

	} while (solu.size());
	cout << nSolu << endl;

	return 0;
}