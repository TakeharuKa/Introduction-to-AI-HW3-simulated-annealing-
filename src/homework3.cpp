/*
 * =====================================================================================
 *
 *       Filename:  homework3.cpp
 *
 *    Description:  Homework for Introduction to AI
 *
 *        Version:  1.0
 *        Created:  04/19/2016 13:44:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jia Yueqing
 *   Organization:  Tsinghua University
 *
 * =====================================================================================
 */

#include<iostream>
#include<fstream>
#include<cmath>
#include<algorithm>
#include<map>
#include<queue>                                            /*  */
#include<stack>                                            /*  */
#include<set>
#include<ctime>
#define Debug(x) cerr << #x << "=" << x << endl
using namespace std;                                       /*  */

char name[50][10];
int n;

double x[50][2];

class sol                                       /* "sol" means solution */
{
	private:

		int ans[50];

	public:

		double dis;
		void print()
		{
			for(int i = 0; i < n; i ++)
			{
				printf("%s ", name[ans[i]]);
			}
			printf("%lf\n", dis);
		}
		double calc_dis(const int &a1, const int &a2)
		{
			return sqrt((x[a1][0] - x[a2][0]) * (x[a1][0] - x[a2][0])
			   	+ (x[a1][1] - x[a2][1]) * (x[a1][1] - x[a2][1]));
		}
		void recalc()
		{
			dis = 0;
			for(int i = 0; i < n; i ++)
				dis += calc_dis(ans[i], ans[(i + 1) % n]);
		}
		void change()
		{
			int a1 = rand() % n, a2 = rand() % n;
			swap(ans[a1], ans[a2]);
			recalc();
		}

		sol()
		{
			for(int i = 0; i < n; i ++)
				ans[i] = i;
			random_shuffle(ans, ans + n);
			cerr << "Initialization completed." << endl;
			recalc();
		}


};

const double T0 = 280, r = 0.92;
class TSP
{
	private:

		double t;
		sol A, B;

	public:
		bool possibility(const double &now)
		{
			if(now > (double(rand()) / (double(RAND_MAX) + 1.0)))
				return 1;
			return 0;
		}
		bool canchange(const double &delta)
		{
			if(delta < 0)
				return 1;
			if(possibility(exp(-delta / t)))
				return 1;
			return 0;
		}

		TSP()
		{
			static const int Lk = n * 100;
			A.print();
			t = T0;
			bool flag = 1;

			while(flag)
			{
				flag = 0;
//				cerr << exp(-1 / t) << endl;
				for(int i = 0; i < Lk; i ++)
				{
					B = A;
					B.change();
					//Debug(canchange(B.dis - A.dis));
					if(canchange(B.dis - A.dis))
					{
						if(B.dis - A.dis != 0)
							flag = 1;
						swap(A, B);
						A.print();
					}
				}
				t = t * r;
			}
		}
};

int main(int argc, char *argv[]) 
{
	srand(time(0));
	freopen(argv[1], "r", stdin);
	freopen(argv[2], "w", stdout);
	cin >> n;
	for(int i = 0; i < n; i ++)
		cin >> name[i] >> x[i][0] >> x[i][1];
	TSP a0;
}

