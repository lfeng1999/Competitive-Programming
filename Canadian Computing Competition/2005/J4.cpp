#include <iostream>

using namespace std;

int main()
{
	bool grid[22][22];
	for (int i = 0; i != 22; ++i)
	for (int j = 0; j != 22; ++j)
	{
		grid[i][j] = false;
	}
	int length = 0, width = 0;
	int rectx = 0, recty = 0, steps=0;
	cin >> length >> width;
	cin >> rectx >> recty >> steps;
	for (int i = 0; i != 22; ++i)
	{
		grid[i][0] = true;
		grid[0][i] = true;
	}
	for (int j = 0; j != 22; ++j)
	{
		grid[width+1][j] = true;
		grid[j][length+1] = true;
	}
	for (int i = 0; i != rectx; ++i)
	for (int j = 0; j != recty; ++j)
	{
		grid[j + 1][i + 1] = true;
		grid[width-j][i + 1] = true;
		grid[width - j][length - i] = true;
		grid[j+1][length - i] = true;
	}
	int xpos = rectx + 1, ypos = 1;
	grid[ypos][xpos] = true;
	for (int i = 0; i != steps; ++i)
	{
		if (grid[ypos-1][xpos] && !grid[ypos][xpos + 1])
			++xpos;
		else if (grid[ypos][xpos+1] && !grid[ypos + 1][xpos])
			++ypos;
		else if (!grid[ypos][xpos - 1])
			--xpos;
		else if (!grid[ypos - 1][xpos])
			--ypos;
		grid[ypos][xpos] = true;
	}
	cout << xpos << endl << ypos;
	return 0;
}