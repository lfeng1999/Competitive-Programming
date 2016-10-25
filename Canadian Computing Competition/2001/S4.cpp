#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

int X[11];
int Y[11];

int main()
{
	int N = 0;
	cin >> N;
	for (int i = 0; i != N; ++i)
		cin >> X[i] >> Y[i];
	double maxd = 0;
	for (int i = 0; i != N; ++i)
	{
		for (int j = i + 1; j != N; ++j)
		{
			for (int k = j + 1; k != N; ++k)
			{
				double a = sqrt((X[i] - X[j])*(X[i] - X[j]) + (Y[i] - Y[j])*(Y[i] - Y[j]));
				double b = sqrt((X[k] - X[j])*(X[k] - X[j]) + (Y[k] - Y[j])*(Y[k] - Y[j]));
				double c = sqrt((X[i] - X[k])*(X[i] - X[k]) + (Y[i] - Y[k])*(Y[i] - Y[k]));
				double s = (a + b + c) / 2;
				if (a*a + b*b < c*c)
					maxd = max(maxd, c/2);
				else if (c*c + b*b < a*a)
					maxd = max(maxd, a/2);
				else if (a*a + c*c < b*b)
					maxd = max(maxd, b/2);
				else if (s != 0 && s!=a && s !=b && s!=c)
				{
					maxd = max(maxd, (a*b*c)/(4*sqrt(s*(s-a)*(s-b)*(s-c))));
				}
			}
		}
	}
	maxd *= 2;
	//printf("%.2lf", maxd);
	cout << setprecision(2) << fixed << maxd;
	return 0;
}