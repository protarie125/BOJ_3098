#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

using vi = vector<int>;
using si = set<int>;
using misi = map<int, si>;

misi adj{};
int solve(int mx, int ct, int k, vi& added) {
	if (mx == ct) {
		return k;
	}

	auto nct = int{ ct };
	auto next = misi{ adj };
	for (const auto& [k, v] : adj) {
		for (const auto& f : v) {
			for (const auto& x : adj[f]) {
				if (k == x) {
					continue;
				}

				if (next[k].end() == next[k].find(x) &&
					next[x].end() == next[x].find(k)) {
					next[k].insert(x);
					next[x].insert(k);
					++nct;
				}
			}
		}
	}

	adj = misi{ next };

	added.push_back(nct - ct);
	return solve(mx, nct, k + 1, added);
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	for (int i = 1; i <= n; ++i) {
		adj[i] = si{};
	}

	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;

		adj[a].insert(b);
		adj[b].insert(a);
	}

	const auto& mx = n * (n - 1) / 2;
	auto ct = int{ m };

	auto added = vi{};
	auto k = solve(mx, ct, 0, added);

	cout << k << '\n';
	for (const auto& x : added) {
		cout << x << '\n';
	}

	return 0;
}