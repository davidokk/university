#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
using namespace std;

// author Davyd Hutsko
// the names of the variables are the same as in the problem

struct Server {
  int id, cpu, mem, p;
  friend istream& operator>>(istream& is, Server& s) {
    return is >> s.id >> s.cpu >> s.mem >> s.p;
  }
};

struct Event {
  int cpu, mem;
};

int a, b, q, n;

// class of expansion

// t - time at which the expansion is made
// price - total expansion cost including a, b and p[i]
// cpu_d, mem_d - increase in parameters cpu and mem
// servers [id, count] - the number of servers for each id

struct Extension {
  int t;
  long long price, cpu_d, mem_d;
  map<int, long long> servers;

  Extension& operator+=(const Extension& e) {
    price += e.price - a;
    cpu_d += e.cpu_d;
    mem_d += e.mem_d;
    for (auto& i : e.servers)
      servers[i.first] += i.second;
    return *this;
  }

  friend ostream& operator<<(ostream& os, const Extension& e) {
    os << e.t << " " << e.servers.size() << " ";
    for (const auto& s : e.servers)
      os << s.first << " " << s.second << " ";
    return os;
  }
};

// we take the given cpu and mem using one type of server
Extension CalcExtension(const vector<Server>& servers, int time, long long cpu, long long mem) {
  if (cpu <= 0 && mem <= 0)
    return Extension{time, a};
  int S;
  long long K;
  long long PRICE;
  // we go through all the servers to choose the best one
  for (int s = 0; s < q; ++s) {
    long long k;
    if (cpu <= 0)
      k = mem / servers[s].mem + (mem % servers[s].mem != 0);
    else if (mem <= 0)
      k = cpu / servers[s].cpu + (cpu % servers[s].cpu != 0);
    else
      k = max(cpu / servers[s].cpu + (cpu % servers[s].cpu != 0),
              mem / servers[s].mem + (mem % servers[s].mem != 0));
    long long price = a + b * k + servers[s].p * (n - time) * k;
    if (s == 0 || price < PRICE) {
      K = k;
      PRICE = price;
      S = s;
    }
  }
  Extension e{time};
  e.servers[servers[S].id] = K;
  e.price = PRICE;
  e.cpu_d = K * servers[S].cpu;
  e.mem_d = K * servers[S].mem;
  return e;
}

int main() {

  cin.tie(0);
  cout.tie(0);
  ios_base::sync_with_stdio(false);

  int testId;
  cin >> testId;

  int p, delta;
  cin >> a >> b >> p >> delta;

  cin >> q;
  vector<Server> servers(q);
  for (auto& i : servers)
    cin >> i;

  cin >> n;
  vector<Event> events(n);
  for (auto& i : events)
    cin >> i.cpu >> i.mem;

  // final answer
  vector<Extension> EXTENSION;
  long long TOTAL_PRICE = 0;

  for (int t = 0; t < 2; t++) {
    vector<Extension> extension;
    extension.reserve(n / delta + 100);
    long long total_price = 0;

    // storage requirements
    long long need_cpu = 0, need_mem = 0;
    // real storage parameters
    long long cur_cpu = 0, cur_mem = 0;

    int j;
    for (int i = 0; i < n; i = j) {

      // here we skip those those moments of time when our current parameters cover the requirements
      // else do expansion at time 0, delta, 2 * delta, ...
      // we need to choose the best of the two, because such an answer is not always optimal (loop through t)
      if (t) {
        while (cur_cpu * p / 100.0 > need_cpu + events[i].cpu + 1 &&
            cur_mem * p / 100.0 > need_mem + events[i].mem + 1 && i < n) {
          need_cpu += events[i].cpu;
          need_mem += events[i].mem;
          ++i;
        }
      }

      // calculate the maximum requirements for the next delta time
      long long max_cpu = 0, max_mem = 0;

      for (j = i; j < min(n, i + delta); ++j) {
        need_cpu += events[j].cpu;
        max_cpu = max(max_cpu, need_cpu);
        need_mem += events[j].mem;
        max_mem = max(max_mem, need_mem);
      }

      // parameters which we are missing
      long long cpu = max_cpu * 100 / p + (max_cpu % p != 0) - cur_cpu;
      long long mem = max_mem * 100 / p + (max_mem % p != 0) - cur_mem;

      if (cpu < 0 && mem < 0)
        continue;

      // try to take one type of server
      Extension ans = CalcExtension(servers, i, cpu, mem);

      // idea:
      // since the CalcExtension function cannot use more than one server
      // let's try to take cpu by itself and mem by itself and accumulate these expansions

      // to increase the accuracy, divide the cpu that we need into d segments
      // the more the number of segments, the more the number of worked out situations
      // when choosing d we take into account the complexity of the algorithm and some constant
      // calculate the step and try to take the parameters (step, 0), (2 * step, 0), ... (cpu, 0)
      // and unambiguously choose the remainder
      long long N = 1'000'000;
      long long d = N * delta / n / q;
      long long step = cpu / d + 1;
      for (long long k = step; k <= cpu; k += step) {
        Extension l = CalcExtension(servers, i, k, 0);
        // take the remainder
        Extension l1 = CalcExtension(servers, i, max(0ll, cpu - l.cpu_d), max(0ll, mem - l.mem_d));
        l += l1;
        // update the answer
        if (l.price < ans.price)
          ans = move(l);
      }

      // the same thing, just try to take mem at once and then the remaining cpu
      step = mem / d + 1;
      for (long long k = step; k <= mem; k += step) {
        Extension r = CalcExtension(servers, i, 0, k);
        Extension r1 = CalcExtension(servers, i, max(0ll, cpu - r.cpu_d), max(0ll, mem - r.mem_d));
        r += r1;
        if (r.price < ans.price)
          ans = move(r);
      }

      extension.push_back(ans);

      // updating the current parameters of storage
      cur_cpu += extension.back().cpu_d;
      cur_mem += extension.back().mem_d;
      total_price += extension.back().price;
    }

    // once again: t decides whether to skip time where expansions are not needed
    // update the answer
    if (t == 0 || total_price < TOTAL_PRICE) {
      TOTAL_PRICE = total_price;
      EXTENSION = move(extension);
    }
  }

  cout << TOTAL_PRICE << endl;
  cout << EXTENSION.size() << endl;
  for (auto& e : EXTENSION)
    cout << e << endl;

  return 0;
}