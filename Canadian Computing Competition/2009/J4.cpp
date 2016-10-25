#include <iostream>
#include <string>

using namespace std;


int main()
{
	string words[7];
	words[0] = "WELCOME";
	words[1] = "TO";
	words[2] = "CCC";
	words[3] = "GOOD";
	words[4] = "LUCK";
	words[5] = "TODAY";
	words[6] = "IDGAFABOUTHTIS RAGE QUIT";
	int W = 26;
	cin >> W;
	int tword = 0;
	int last = 0;
	while (tword <= 5)
	{
		int size = 0;
		size = words[tword].length();
		++tword;
		int wordcount = 1;
		while (tword <= 5 && size + 1 + words[tword].length() <= W)
		{
			size += 1 + words[tword].length();
			++tword;
			++wordcount;
		}

		string sentence[20];
		int totlen = 0;
		for (int i = 0; i != wordcount; ++i)
		{
			sentence[i * 2] = words[last + i];
			totlen += words[last + i].length();
			if (i != wordcount - 1)
			{
				sentence[i * 2 + 1] = ".";
				++totlen;
			}
		}

		int track = 0;
		while (totlen < W)
		{
			if (wordcount != 1)
			{
				sentence[track * 2 + 1] += ".";
				++track;
				track = track % (wordcount - 1);
				++totlen;
			}
			else
			{
				sentence[1] += ".";
				++totlen;
			}
		}


		for (int i = 0; i != wordcount; ++i)
		{
			cout << sentence[i * 2];
			cout << sentence[i * 2 + 1];
		}
		cout << endl;
		last += wordcount;

	}
	return 0;
}