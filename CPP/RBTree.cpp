#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main(){
	ordered_set<int> X;
	X.insert(5);
	X.insert(3);

	cout << X.order_of_key(4) << endl; // the number of elements in the s less than 2
	cout << *X.find_by_order(0) << endl; // print the 0-th smallest number in s(0-based)

	return 0;
}