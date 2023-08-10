from typing import List, Tuple
'''
Trajan算法求无向图的桥
'''

class Tarjan:
    # 求无向连通图的桥
    @staticmethod
    def getCuttingPointAndCuttingEdge(edges: List[Tuple]):
        link, dfn, low = {}, {}, {}# link为字典邻接表
        global_time = [0]
        for a, b in edges:
            if a not in link:
                link[a] = []
            if b not in link:
                link[b] = []
            link[a].append(b)#无向图
            link[b].append(a)#无向图
            dfn[a], dfn[b] = 0x7fffffff, 0x7fffffff
            low[a], low[b] = 0x7fffffff, 0x7fffffff

        cutting_points, cutting_edges = [], []

        def dfs(cur, prev, root):
            global_time[0] += 1
            dfn[cur], low[cur] = global_time[0], global_time[0]
            
            #print("cur next root: ",cur,prev,root)

            children_cnt = 0
            flag = False
            for next in link[cur]:
                if next != prev:
                    if dfn[next] == 0x7fffffff:
                        children_cnt += 1
                        dfs(next, cur, root)

                        if cur != root and low[next] >= dfn[cur]:
                            flag = True
                        
                        low[cur] = min(low[cur], low[next])

                        if low[next] > dfn[cur]:
                            cutting_edges.append([cur, next] if cur < next else [next, cur])
                    else:
                        low[cur] = min(low[cur], dfn[next])

            if flag or (cur == root and children_cnt >= 2):
                cutting_points.append(cur)

        dfs(edges[0][0], None, edges[0][0])
        return cutting_points, cutting_edges


class Solution:
    def criticalConnections(self, n: int, connections: List[List[int]]) -> List[List[int]]:
        edges = [(a, b) for a, b in connections]
        cutting_dots, cutting_edges = Tarjan.getCuttingPointAndCuttingEdge(edges)
        return [[a, b] for a, b in cutting_edges]


connections = [[4,3],[4,5],[3,5],[5,6]]
n = 4
s = Solution()
result = s.criticalConnections(n,connections)
print("result",result)














转换成c++代码
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    vector<pair<int,int>> vec;
    vec.emplace_back(7,1);
    vec.emplace_back(7,4);
    vec.emplace_back(7,2);
    vec.emplace_back(4,3);
    vec.emplace_back(3,6);
    vec.emplace_back(3,11);
    vec.emplace_back(6,11);
    vec.emplace_back(6,8);
    vec.emplace_back(11,9);
    vec.emplace_back(9,5);
    vec.emplace_back(9,10);
    vec.emplace_back(5,10);


    for (int i = (int) vec.size() - 1; i >= 1; i--) {
        bool repeat = any_of(vec.begin(), vec.begin() + i, [&](pair<int, int> other) {
            return (vec[i].first == other.first and vec[i].second == other.second) or
                   (vec[i].first == other.second and vec[i].second == other.first);
        });

        if (repeat) vec.erase(vec.begin() + i);
    }

    map<int,vector<int>>link;
    map<int,int>dfn,low;
    int global_time{0};

    for (auto e: vec) {
        link[e.first].emplace_back(e.second);
        link[e.second].emplace_back(e.first);
        dfn[e.first]= 0x7fffffff;
        dfn[e.second] = 0x7fffffff;
        low[e.first] = 0x7fffffff;
        low[e.second]  = 0x7fffffff;
    }

    vector<pair<int,int>>cutting_edges;
    vector<int>cutting_points;

    function<void(int, int, int)> dfs = [&](int cur, int prev, int root) {
        global_time += 1;
        dfn[cur] = global_time;
        low[cur] = global_time;

        printf("cur next root: %d,%d,%d \n", cur, prev, root);
        printf("dfn: %d, low: %d\n", dfn[cur], low[cur]);

        int children_cnt = 0;
        auto flag = false;

        for (auto next: link[cur]) {
            if (next != prev) {
                if (dfn[next] == 0x7fffffff) {
                    children_cnt += 1;
                    dfs(next, cur, root);

                    if (cur != root and low[next] >= dfn[cur]) {
                        flag = true;
                    }

                    low[cur] = min(low[cur], low[next]);

                    if (low[next] > dfn[cur]) {
                        if (cur > next) swap(cur, next);
                        cutting_edges.emplace_back(cur, next);
                    }
                } else {
                    low[cur] = min(low[cur], dfn[next]);
                }
            }
        }

        if (flag or (cur == root and children_cnt >= 2))
            cutting_points.emplace_back(cur);
    };

    dfs(vec[0].first, 0, vec[0].first);

    for (auto e: cutting_edges) cout << "edge: " << e.first << " " << e.second << endl;





