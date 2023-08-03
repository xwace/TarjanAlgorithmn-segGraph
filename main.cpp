//wxw20230803去环
void breakUpCycles(vector<pair<int, int>> &adjacentRoomPairs) {

    const int N = 100000;
    int par[N];
    int color[N];
    int cyclenumber = 0;
    vector<int> graph[N];
    vector<vector<int>> cycles;
    vector<pair<int, int>> outliers;

    for (auto room: adjacentRoomPairs) {
        graph[room.first].push_back(room.second);
        graph[room.second].push_back(room.first);
    }

    auto has_outlier = [](vector<pair<int, int>> &vec, pair<int, int> b) -> bool {
        return any_of(vec.begin(), vec.end(), [&](pair<int, int> a) {
            return (a.first == b.first and a.second == b.second) or (a.first == b.second and a.second == b.first);
        });
    };

    function<void(int u, int p, int color[], int par[], int &cyclenumber)> dfs_cycle;
    dfs_cycle = [&](int u, int p, int color[], int par[], int &cyclenumber) {
        if (color[u] == 2) {
            return;
        }

        if (color[u] == 1) {
            vector<int> v;
            cyclenumber++;

            int cur = p;
            v.push_back(cur);

            while (cur != u) {
                cur = par[cur];
                v.push_back(cur);
            }
            cycles.push_back(v);
            return;
        }
        par[u] = p;

        color[u] = 1;

        // simple dfs on graph
        for (int v: graph[u]) {

            if (v == par[u]) {
                continue;
            }
            dfs_cycle(v, u, color, par, cyclenumber);
        }

        color[u] = 2;
    };

    // call DFS to mark the cycles
    dfs_cycle(adjacentRoomPairs[0].first, 0, color, par, cyclenumber);

    for (auto c: cycles) {
        auto it = c.begin() + 1;
        while (it != c.end()) {
            auto found = has_outlier(outliers, pair<int, int>{c.front(), *it});
            if (!found) {
                outliers.emplace_back(c.front(), *it);
                break;
            } else it++;
        }
    }

    //断开环
    for (int j = (int) adjacentRoomPairs.size() - 1; j >= 0; j--) {
        if (has_outlier(outliers, adjacentRoomPairs[j]))
            adjacentRoomPairs.erase(adjacentRoomPairs.begin() + j);
    }
}



int main(){
    vector<pair<int,int>> vec;
    vec.emplace_back(12,11);
    vec.emplace_back(15,11);
    vec.emplace_back(12,15);
    vec.emplace_back(13,15);
    vec.emplace_back(11,13);

    breakUpCycles(vec);
    for(auto v:vec) cout<<"result: "<<v.first<<" "<<v.second<<endl;
}
