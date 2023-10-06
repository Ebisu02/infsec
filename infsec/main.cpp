#include <iostream>
#include <vector>
#include <ctime>
#include <unordered_map>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <stdio.h>
#include <map>

#define ll long long
#define ld long double

uint64_t power(int b, int e, int m);
ld evklid_algo(ll a, ll b); // a >= b && a > 0 && b > 0
std::vector<ll> obobs_evklid_algo(ll a, ll b);
uint64_t diffi_hellman_sh();
ld discrete_log(int p, int g, int y);
bool is_prime(uint64_t num);
std::vector<uint64_t> generate_random_prime_in_range(uint64_t lowerRange, uint64_t upperRange);
void shamir_sh(ll msg);
bool test_ferma(ll p, int k);
void el_gamal_sh();
void vernama_sh();
void rsa_sh();

int main() {
	uint64_t a = generate_random_prime_in_range(10000, 100000)[0], b = generate_random_prime_in_range(10000, 100000)[1];
	uint64_t c = a + 1, d = b + 1;
	std::vector<ll> t = obobs_evklid_algo((ll)a, (ll)b);
	std::vector<ll> t1 = obobs_evklid_algo((ll)c, (ll)d);
	std::cout << b << "\t" << a << "\t" << t[0] << "\t" << t[1] << "\t" << t[2] << "\n";
	std::cout << c << "\t" << d << "\t" << t1[0] << "\t" << t1[1] << "\t" << t1[2] << "\n";
	test_ferma(a, 10);
	setlocale(LC_ALL, "RUSSIAN");
	std::cout << "число b в степени e по модулю m: " << (ld)power(3, 544333, 765851) << "\n";
	std::vector<ll> buf = obobs_evklid_algo(22, 20);
	std::cout << buf[0] << " " << buf[1] << " " << buf[2] << "\n";
	diffi_hellman_sh();
	std::cout << "Дискретный логарифм числа 17: " << discrete_log(7685, 3, 2277);
	return 0;
}

void shamir_sh(ll msg) {
	srand(time(nullptr));
	std::vector<uint64_t> primes = generate_random_prime_in_range(msg, msg + 1000);

	std::random_device r;
	std::default_random_engine e(r());
	std::uniform_int_distribution<uint64_t> dist(msg, msg + 1000);

	uint64_t p = primes[rand() % primes.size()];

}

// generate unique key for both users
uint64_t diffi_hellman_sh() {
	srand(time(nullptr));
	uint64_t q = 0, p = 0, g = 4, xa = 0, xb = 0;
	std::cout << "Generated:\n";
	while (1) {
		std::vector<uint64_t> bq = generate_random_prime_in_range(9000, 10000);
		q = bq[rand() % bq.size()];
		p = 2 * q + 1;
		if (is_prime(p)) { break; }
	}
	std::cout << "q = " << q << "\np = " << p << "\n";

	while (power(g, q, p) == 1 && g < p - 1) {
		g++;
		std::cout << "g = " << g << "\n";
	}
	//std::cout << "g = " << g << "\n";
	  
	std::random_device r;
	std::default_random_engine e(r());
	std::uniform_int_distribution<uint64_t> dist(1000, p - 1);

	xa = dist(e);
	xb = dist(e);
	std::cout << "Secret keys:\nxa = " << xa << "\nxb = " << xb << "\n";

	uint64_t ya, yb;
	ya = power(g, xa, p);
	yb = power(g, xb, p);
	std::cout << "Open keys:\nya = " << ya << "\nyb = " << yb << "\n";
	uint64_t zab, zba;
	zab = power(yb, xa, p);
	zba = power(ya, xb, p);
	std::cout << "zab = " << zab << "\nzba = " << zba << "\n";
	// auth error: if zab != zba throw exception
	if (zab != zba) {
		std::exception e("Final keys isnt equals");
		std::cout << "\nError: " << e.what() << "\n";
		throw e;
	}
	return zba;
}

ld discrete_log(int p, int a, int y) {
	int n = sqrt(p) + 1;
	std::map<int, int> val;
	for (int i = n; i >= 1; --i) {
		val[power(a, i * n, p)] = i;
	}
	for (int j = 0; j <= n; ++j) {
		int cur = (power(a, j, p) * y) % p;
		if (val[cur]) {
			int res = val[cur] * n - j;
			if (res < p) {
				return res;
			}
		}
	}
	return -1;
}

// Функция возведения числа a в степень x по модулю p
uint64_t power(int a, int x, int p) {
	uint64_t y = 1, s = a;
	std::vector<short> sx;
	while (x > 0) {
		sx.push_back(x % 2);
		x /= 2;
	}
	
	//std::reverse(sx.begin(), sx.end());
	for (ll i = 0; i < sx.size(); ++i) {
		if (sx[i] == 1) {
			y = (y * s) % p;
		}
		s = (s * s) % p;
	}
	return y;
}

bool test_ferma(ll p, int k) {
	if (p == 2) return true;
	if (p & 1) return false;
	for (int i = 0; i < k; ++i) {
		ll a = rand() % (p - 1) + 1;
		if (evklid_algo(a, p) != 1 || power(a, p - 1, p) != 1)
			return false;
	}
	return true;
}

std::vector<uint64_t> generate_random_prime_in_range(uint64_t lowerRange, uint64_t upperRange) {
	std::vector<bool> isPrime(upperRange + 1, true);
	isPrime[0] = false;
	isPrime[1] = false;

	for (uint64_t i = 2; i * i <= upperRange; ++i) {
		if (isPrime[i]) {
			for (uint64_t j = i * i; j <= upperRange; j += i) {
				isPrime[j] = false;
			}
		}
	}

	std::vector<uint64_t> primes;
	for (uint64_t i = lowerRange; i <= upperRange; ++i) {
		if (isPrime[i]) {
			primes.push_back(i);
		}
	}
	return primes;
}

bool is_prime(uint64_t num) {
	if (num < 2) { return false; }
	for (uint64_t i = 2; i <= num / 2; ++i) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
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
