#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#define ll long long
#define ld long double

int power(int b, int e, int m);
ld evklid_algo(ll a, ll b); // a >= b && a > 0 && b > 0
std::vector<ll> obobs_evklid_algo(ll a, ll b);
int diffi_hellman(int p, int g, int a, int b); // return a vector<int>[2] where { SecretKeyA, SecretKeyB }
ld discrete_log(int p, int g, int y);
ld fast_pow(ll num, ll deg);

int main() {
	std::cout << (ld)power(2, 2, 5) << "\n";
	std::vector<ll> buf = obobs_evklid_algo(28, 19);
	std::cout << buf[0] << " " << buf[1] << " " << buf[2] << "\n";
	std::cout << "Shared key - " << diffi_hellman(101, 2, 4, 3) << "\n";
	std::cout << "The discrete log is: " << discrete_log(17, 3, 13);
	return 0;
}

ld discrete_log(int p, int g, int y) {
	int m = ceil(sqrt(p - 1));
	std::unordered_map<int, int> baby_steps;
	for (int i = 0, j = y % p; i < m; ++i) {
		baby_steps.insert({ j, i });
		j = (j * g) % p;
	}
	int gm = power(g, m, p);
	int giant_step = 1;
	for (int i = 0; i < m; ++i) {
		if (baby_steps.find(giant_step) != baby_steps.end()) {
			int j = baby_steps[giant_step];
			return i * m + j;
		}
		giant_step = (giant_step * gm) % p;
	}
	return -1;
}

// Функция возведения числа b в степень e по модулю m
int power(int b, int e, int m) {
	int res = 1;
	for (int i = 0; i < e; i++) {
		res *= b;
		res %= m;
	}
	return res;
}

int diffi_hellman(int p, int g, int a, int b) {
	int ka = power(g, a, p);
	int kb = power(g, b, p);
	int sa = power(kb, a, p);
	int sb = power(ka, b, p);
	if (sa == sb) return sa;
	else {
		std::cout << "Error occured. The shared secret key does not match\n";
		return -1;
	}
}

std::vector<ll> obobs_evklid_algo(ll a, ll b) {
	std::vector<ll> u = { a, 1, 0 };
	std::vector<ll> v = { b, 0, 1 };
	std::vector<ll> t = { 0, 0, 0 };
	ll q = 0;
	while (v[0] != 0) {
		q = u[0] / v[0];
		t[0] = u[0] % v[0];
		t[1] = u[1] - q * v[1];
		t[2] = u[2] - q * v[2];
		u = v;
		v = t;
	}
	return u;
}

ld evklid_algo(ll a, ll b) {
	ll r;
	while (b != 0) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

ld fast_pow(ll num, ll deg) {
	ld result = 1;
	if (deg < 0) {
		while (deg) {
			if (deg % 2 == 0) {
				deg /= 2;
				num *= num;
			}
			else {
				deg++;
				result *= num;
			}
		}
		return 1 / result;
	}
	while (deg) {
		if (deg % 2 == 0) {
			deg /= 2;
			num *= num;
		}
		else {
			deg--;
			result *= num;
		}
	}
	return result;
}