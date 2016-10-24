#include <iostream>
using namespace std;
 
int main() {
	int number,count,counted=0;
	int num=1;
	cin >> number;
	while (counted < number){
		count=0;
		num++;
		for (int a=1; a<=num; a++){
			if (num%a==0){
				count++;
			}
		}
		if (count==2){
			cout << num;
			cout << '\n';
			counted++;
		}
	}
	return 0;
}