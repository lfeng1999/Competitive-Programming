long long modinv(long long a, long long b){ //a mod b's inverse
	if (a == 1)
		return 1;
	return b - modinv(b%a, a)*b/a;
}

/*
another way
is x^(totientfunctionof(m)) == 1 mod m
so modinv of x is
x^(totientfunctionof(m)- 1)
since x * x^(totientfunctionof(m)- 1) == 1 mod m
*/
long long totientfunction(long long a){
	long long ret = a;
	for (int i=2; i<sqrt(a); ++i){
		if (ret%i == 0){
			ret /= i;
			ret *= (i-1);
		}
	}
	return ret;
}

long long modinv2(long long a, long long b){
	return pow(a, totientfunction(b) - 1);
}
