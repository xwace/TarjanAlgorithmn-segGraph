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
        //已经完整搜索过，所有子节点都被dfs过的节点被标记为2
        if (color[u] == 2) {
            return;
        }

        //已搜索过一次的点，即回边，说明形成了环
        if (color[u] == 1) {
            vector<int> v;
            cyclenumber++;

            int cur = p;
            v.push_back(cur);
            //一直搜索父节点直到搜完完整环
            while (cur != u) {
                cur = par[cur];
                v.push_back(cur);
            }
            cycles.push_back(v);
            return;
        }

        //标记当前点的父节点和搜索次数
        par[u] = p;
        color[u] = 1;

        // simple dfs on graph
        for (int v: graph[u]) {
            //跳过父节点
            if (v == par[u]) {
                continue;
            }
            dfs_cycle(v, u, color, par, cyclenumber);
        }
        //完全搜索的点标记，归的时候这个节点可以跳过，节省搜索时间
        color[u] = 2;
    };

    // call DFS to mark the cycles
    dfs_cycle(adjacentRoomPairs[0].first, 0, color, par, cyclenumber);

    for (auto c: cycles) {
        auto it = c.begin() + 1;
        while (it != c.end()) {
            auto found = has_outlier(outliers, pair<int, int>{c.front(), *it});
            if (!found) {
                //找到环中的第一对点，删除，即可打断环
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
