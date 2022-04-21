#include <iostream>
#include <utility>
#include <algorithm>
#include <limits>
#include <vector>
#include <set>
#include <optional>
#include <map>

using namespace std;

struct SubTree {
    set<pair<int, int>> edges;
    int max_delay_path = 0; // max delay from start to t[i]
    int cost_sum = 0; // total cost
};

// rating of solution according to the task scoring system
struct Rating {
    int level;
    int sum;
    bool operator<(const Rating& other) const {
        return level < other.level || (level == other.level && sum > other.sum);
    }
};

struct Solver {
    int l, D; // l - start vertex, D - delay bound
    vector<set<int>> g; // graph
    map<pair<int, int>, pair<int, int>> edges_info; // [vertex from, to] -> [cost, delay]
    vector<int> t; // terminals
    vector<SubTree> ans; // final answer

    set<pair<int, int>> deleted_edges; // used in Solve1

    void Read(std::istream& in = std::cin) {
        int n;
        in >> n >> l;
        g.resize(n);
        int k;
        in >> k;
        t.resize(k);
        for (int& i : t)
            in >> i;
        in >> D;
        int m;
        in >> m;
        for (int i = 0; i < m; ++i) {
            int a, b, cost, delay;
            in >> a >> b >> cost >> delay;
            g[a].insert(b);
            g[b].insert(a);
            edges_info[{a, b}] = {cost, delay};
            edges_info[{b, a}] = {cost, delay};
        }
    }

    // used in Solve1
    void DeleteEdges(const SubTree& tree) {
        for (const auto& i : tree.edges)
            g[i.first].erase(i.second);
        deleted_edges = tree.edges;
    }

    // return edges which have been deleted by previous method
    void ReturnEdges() {
        for (const auto& edge : deleted_edges)
            g[edge.first].insert(edge.second);
        deleted_edges.clear();
    }

    // return simple path from start to vertex r, prev - array of parents
    static optional<set<pair<int, int>>> RestorePath(const vector<int>& prev, int r) {
        set<pair<int, int>> edges;
        while (prev[r] != -1) {
            edges.emplace(prev[r], r);
            r = prev[r];
        }
        if (edges.empty())
            return nullopt;
        return edges;
    }

    // return tree which contains all paths from l to t[i]
    optional<SubTree> RestoreTree(const vector<int>& prev) {
        SubTree tree;
        for (int i : t) {
            auto opt = RestorePath(prev, i);
            if (!opt.has_value())
                return nullopt;

            // compute path delay
            int d = 0;
            for (const auto& edge : opt.value())
                d += edges_info[edge].second;

            // add path to tree
            tree.edges.merge(move(opt.value()));
            tree.max_delay_path = max(tree.max_delay_path, d);
        }

        // compute total cost
        for (const auto& edge : tree.edges)
            tree.cost_sum += edges_info[edge].first;

        return tree;
    }

    void dfs(int v, vector<int>& prev) {
        for (auto to : g[v]) {
            if (prev[to] == -1 && to != l) {
                prev[to] = v;
                dfs(to, prev);
            }
        }
    }

    // try to build tree using DFS
    optional<SubTree> BuildTreeDfs() {
        vector<int> prev(g.size(), -1);
        dfs(l, prev);
        return RestoreTree(prev);
    }

    // Dijkstra algorithm, start from vertex l, return array of parents
    // can find min path on cost and on delay
    vector<int> Dijkstra(const vector<set<int>>& G, bool on_cost) {
        vector<int> prev(g.size(), -1);
        int INF = std::numeric_limits<int>::max();
        vector<int> d(g.size(), INF);
        d[l] = 0;
        set<pair<int, int>> q;
        q.emplace(0, l);
        while (!q.empty()) {
            int v = q.begin()->second;
            q.erase(q.begin());
            for (auto to : G[v]) {
                int len = on_cost ? edges_info[{v, to}].first : edges_info[{v, to}].second;
                if (d[v] + len < d[to]) {
                    q.erase({d[to], to});
                    d[to] = d[v] + len;
                    prev[to] = v;
                    q.emplace(d[to], to);
                }
            }
        }
        return prev;
    }

    optional<SubTree> BuildTreeDijkstraOnCost() {
        return RestoreTree(Dijkstra(g, true));
    }

    optional<SubTree> BuildTreeDijkstraOnDelay() {
        return RestoreTree(Dijkstra(g, false));
    }

    // it works like this:
    // first, we look for a path to t[0] in first subtree,
    // delete these edges in second one and also build path to t[0]
    // then do the same for t[1], t[2], ... t[k]
    // that is, we build paths to terminals one by one in each subtree
    optional<vector<SubTree>> DijkstraTogether(bool on_cost) {
        auto g1 = g;
        auto g2 = g;
        SubTree tree1, tree2;

        for (auto i : t) {
            for (int k = 0; k < 2; ++k) {
                auto opt = RestorePath(Dijkstra(g1, on_cost), i);
                if (!opt.has_value())
                    return nullopt;

                // delete edges ans compute delay
                int d = 0;
                for (auto edge: opt.value()) {
                    g2[edge.first].erase(edge.second);
                    d += edges_info[edge].second;
                }

                tree1.edges.merge(move(opt.value()));
                tree1.max_delay_path = max(tree1.max_delay_path, d);

                swap(tree1, tree2);
                swap(g1, g2);
            }
        }

        for (auto edge : tree1.edges)
            tree1.cost_sum += edges_info[edge].first;
        for (auto edge : tree2.edges)
            tree2.cost_sum += edges_info[edge].first;

        return vector<SubTree>{tree1, tree2};
    }

    // compute rating of some solution
    Rating ComputeRating(const vector<SubTree>& trees) {
        int level;
        if (trees.size() == 1) {
            int sum = trees[0].cost_sum;
            level = (trees[0].max_delay_path <= D ? 2 : 1);
            return {level, sum};
        } else if (trees.size() == 2) {
            int sum = trees[0].cost_sum + trees[1].cost_sum;
            if (trees[0].max_delay_path <= D && trees[1].max_delay_path <= D)
                level = 5;
            else if (trees[0].max_delay_path <= D || trees[1].max_delay_path <= D)
                level = 4;
            else
                level = 3;
            return {level, sum};
        }
        return {0, 0};
    }

    // use DijkstraTogether method
    void Solve() {
        // min path on cost may be better than on delay and at the same time not exceed D
        // try both variants and choose the best one
        for (auto on_cost : {true, false}) {
            auto opt = DijkstraTogether(on_cost);
            if (opt.has_value()) {
                // if answer has improved, update it
                if (ComputeRating(ans) < ComputeRating(opt.value()))
                    ans = move(opt.value());
            }
        }

        // if no solution was found, try another method
        // slightly worse than this, but always finding a solution
        if (ans.empty())
            Solve1();
    }

    // let's see all the combinations of finding trees (DFS, DijkstraOnCost, DijkstraOnDelay)
    // and choose the best
    void Solve1() {
        using ClassMethod = optional<SubTree> (Solver::*)();
        vector<ClassMethod> func {
                &Solver::BuildTreeDfs,
                &Solver::BuildTreeDijkstraOnCost,
                &Solver::BuildTreeDijkstraOnDelay
        };

        for (int i = 0; i < func.size(); ++i) {
            for (int j = 0; j < func.size(); ++j) {
                vector<SubTree> trees;

                // the first subtree always exists
                trees.push_back((this->*func[i])().value());

                // remove used edges so that there are no intersections
                DeleteEdges(trees.back());

                // if second tree found save it
                auto opt = (this->*func[j])();
                if (opt.has_value())
                    trees.push_back(opt.value());

                // return deleted edges for next iteration
                ReturnEdges();

                // update answer
                if (ComputeRating(ans) < ComputeRating(trees))
                    ans = move(trees);
            }
        }
    }

    // print final answer
    ~Solver() {
        cout << ans.size() << "\n";
        for (const auto& i : ans) {
            cout << i.edges.size() << "\n";
            for (auto& j : i.edges)
                cout << j.first << " " << j.second << "\n";
        }
    }
};

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Solver solve;
    solve.Read(cin);
    solve.Solve();

    return 0;
}