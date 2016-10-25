#include <iostream>
#include <stack>


using namespace std;

int main()
{
	int T = 0;
	int N = 4;
	int temp = 0;
	int num = 1;
	cin >> T;

	for (int k = 0; k != T; ++k)
	{

		cin >> N;
		stack<int> mount;
		stack<int> branch;
		stack<int> lake;
		int end = 1;
		int n = 1;
		for (int i = 0; i != N; ++i)
		{
			cin >> temp;
			mount.push(temp);
		}
		while (true)
		{
			if ((!mount.empty()) && mount.top() == n)
			{
				//cout << mount.top() << endl;
				lake.push(mount.top());
				++n;
				mount.pop();
			}
			else if ((!branch.empty()) && branch.top() == n)
			{
				//cout << branch.top() << endl;
				lake.push(branch.top());
				++n;
				branch.pop();
			}
			else if (!mount.empty())
			{
				//cout << mount.top() << endl;
				branch.push(mount.top());
				mount.pop();
			}
			else if (branch.empty() && mount.empty())
				break;
			else if (mount.empty())
			{
				cout << "N" << endl;
				end = 0;
				break;
			}
		}
		if (end)
		{
			cout << "Y" << endl;
		}
		while (!mount.empty())
			mount.pop();
		while (!branch.empty())
			branch.pop();
		while (!lake.empty())
			lake.pop();
	}
	return 0;
}