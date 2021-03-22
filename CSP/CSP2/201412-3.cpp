#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<vector>
#include<set>
#define MAXLEN 5001
#define BUY 0
#define SELL 1
#define CANCEL 2
using namespace std;
struct Operation {
	bool valid = false;
	int type = -1;
	int num = 0;
	float price = 0.0;
	Operation(bool vv = false, int tt = -1, int nn = 0, float pp = 0)
		:valid(vv), type(tt), num(nn), price(pp) {}
	Operation& operator = (const Operation &op) {
		valid = op.valid;
		type = op.type;
		num = op.num;
		price = op.price;
		return *this;
	}
};
Operation op[MAXLEN];
int oplen = 0;
set<float> priceSet;

long long calc(float price)
{
	long long buyNum = 0, sellNum = 0;
	for (int i = 0; i < oplen; i++)
	{
		if (op[i].valid && op[i].type != CANCEL)
		{
			if (op[i].type == BUY && op[i].price >= price)
				buyNum += op[i].num;
			if (op[i].type == SELL && op[i].price <= price)
				sellNum += op[i].num;
		}
	}
	return min(buyNum, sellNum);
}


int main()
{
	string s;
	float price;
	int num;
	int i;

	while (cin >> s)
	{
		cin.ignore();
		if (s == "buy")
		{
			cin >> price >> num;
			cin.ignore();
			op[oplen++] = Operation(true, BUY, num, price);
			priceSet.insert(price);
		}
		else if (s == "sell")
		{
			cin >> price >> num;
			cin.ignore();
			op[oplen++] = Operation(true,SELL, num, price);
			priceSet.insert(price);
		}
		else if (s == "cancel")
		{
			cin >> i;
			cin.ignore();
			op[i-1].valid = false;
			op[oplen++] = Operation(false, CANCEL);
		}
	}
	float ansPrice = -1.0;
	long long ansNum = INT_MIN;
	for (float p : priceSet)
	{
		long long num = calc(p);
		if ((num > ansNum) || (num == ansNum && p > ansPrice))
		{
			ansPrice = p;
			ansNum = num;
		}
	}
	printf("%.2f %lld\n", ansPrice, ansNum);
	

}