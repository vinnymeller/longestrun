#include <gmpxx.h>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;


mpf_class biased_coin_recursion (int x, int n, float floatp) {
	float floatq = 1 - floatp;

	
	mpf_class p(floatp, 500);
	mpf_class q(floatq, 500);
	cout << q.get_prec() << endl;
	vector<vector<mpz_class> > coefs;
	for (int i = 0; i <= n; ++i) {
		vector<mpz_class> temp;
		for(int j = 0; j <= n; ++j) {
			temp.push_back(mpz_class(0));
		}
		coefs.push_back(temp);
	}	
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (j <= x) {
				mpz_bin_uiui(coefs[i][j].get_mpz_t(), i, j);
			} else {
				mpz_class summation(0);
				for (int k = 0; k <= x; ++k) {
					mpz_add(summation.get_mpz_t(), summation.get_mpz_t(), coefs[i - k - 1][j - k].get_mpz_t());
				}
				mpz_set(coefs[i][j].get_mpz_t(), summation.get_mpz_t());
			}
		}
	}
	mpf_class prob(0, 500);
	for (int i = 0; i < n; ++i) {
		mpf_class first(0, 500);
		mpf_class second(0, 500);
		mpf_pow_ui(first.get_mpf_t(), p.get_mpf_t(), i);
		mpf_pow_ui(second.get_mpf_t(), q.get_mpf_t(), (n-i));
		mpf_class convert(0, 500);
		mpf_set_z(convert.get_mpf_t(), coefs[n][i].get_mpz_t());
		mpf_mul(first.get_mpf_t(), first.get_mpf_t(), second.get_mpf_t());
		mpf_mul(first.get_mpf_t(), first.get_mpf_t(), convert.get_mpf_t());
		mpf_add(prob.get_mpf_t(), prob.get_mpf_t(), first.get_mpf_t());
	}
	return prob;
}




int main () {
	cout << setprecision(100) << biased_coin_recursion(10, 3000, 0.5) << endl;
	return 0;
}
