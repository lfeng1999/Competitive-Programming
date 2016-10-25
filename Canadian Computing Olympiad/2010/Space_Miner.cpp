#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int M = 0, planet[1001][3], res[1001], radius[1001], N = 0, moves[1001][3], D = 0;
bool dug[1001];


double dist(int A[], int B[])
{
	int AB[3];
	AB[0] = A[0] - B[0];
	AB[1] = A[1] - B[1];
	AB[2] = A[2] - B[2];
	return sqrt(AB[0] * AB[0] + AB[1] * AB[1] + AB[2] * AB[2]);
}

double cos(int A[], int B[], int C[])
{
	return (dist(A, B)*dist(A, B) + dist(A, C)*dist(A, C) - dist(B, C)*dist(B, C))/(2*dist(A,B)*dist(A,C));
}

double absin(double &cos1, int A[], int B[], int C[])
{
	double sin = sqrt(1 - cos1*cos1);
	return dist(A, C)*sin;
}

double LtoP(int A[], int B[], int C[])
{
	double cos1 = cos(A, B, C);
	if (cos1 <= 0)
		return dist(A, C);
	double cos2 = cos(B, A, C);
	if (cos2 <= 0)
		return dist(B, C);
	return absin(cos1,A,B,C);
}


int main()
{
	//ifstream file("SpaceMiner.txt");
	cin >> M;
	for (int i = 0; i != M; ++i)
	{
		cin >> planet[i][0] >> planet[i][1] >> planet[i][2] >> res[i] >> radius[i];
	}
	cin >> N;
	moves[0][0] = 0;
	moves[0][1] = 0;
	moves[0][2] = 0;
	for (int i = 1; i != N+1; ++i)
	{
		cin >> moves[i][0] >> moves[i][1] >> moves[i][2];
	}
	cin >> D;
	int restotal = 0;
	for (int i = 1; i!=N+1; ++i)
	{
		for (int j = 0; j != M; ++j)
		{
			if (!dug[j])
			{
				double plandist = LtoP(moves[i - 1], moves[i], planet[j]);
				//cout << plandist << endl;
				if (radius[j] + D >= plandist)
				{
					dug[j] = true;
					restotal += res[j];
				}
			}
		}
	}
	cout << restotal << endl;
	return 0;
}