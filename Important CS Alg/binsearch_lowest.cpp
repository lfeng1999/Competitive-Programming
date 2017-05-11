#include <bits/stdc++.h>

using namespace std;

int arr[100010];

int main(){
	int n = 100000; //length of the array... 0 indexed. 0->n-1 are the positions with values

	int L = -1, R = n-1; //L -> R represents the range that is descending
	while (R - L > 1){
		int mid = (L+R)/2; //note that it never checks -1 so... we're safe
		if (arr[mid+1] <= arr[mid]) //Check if mid-> mid+1 is part of descending chain  
			L = mid;  //It is part of the chain. We take 1 # below the start of the chain just like how (-1) is 1 below 0
		else R = mid; //It's not part of the descending chain. but L -> mid might be
	}
	//R is the position with the answer
}