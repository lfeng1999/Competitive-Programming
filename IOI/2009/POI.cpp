#include <iostream>
int ques[2000][2000];
int points[2000];
int scores[2000];
int qNum[2000];

using namespace std;

int main()
{
	int numbers[3];
	int place = 1;
	cin >> numbers[0] >> numbers[1] >> numbers[2];
	for (int i = 0; i < numbers[0]; ++i){
		for (int j = 0; j < numbers[1]; ++j)
		{
			cin >> ques[i][j];
			if (ques[i][j] == 0)
				points[j]++;
		}
	}
	for (int i = 0; i < numbers[0]; ++i){
		for (int j = 0; j < numbers[1]; ++j)
		{
			if (ques[i][j] == 1)
			{
				scores[i] += points[j];
				qNum[i]++;
			}
		}
	}

	for (int i = 0; i < numbers[0]; ++i)
	{
		if (scores[i]>scores[numbers[2] - 1])
			place++;
		else if (scores[i] == scores[numbers[2] - 1])
		{
			if (qNum[i] > qNum[numbers[2] - 1])
				place++;
			else if (qNum[i] == qNum[numbers[2] - 1])
			{
				if (i < numbers[2] - 1)
					place++;
			}
		}
	}

	cout << scores[numbers[2] - 1] << " " << place;
	return 0;
}
