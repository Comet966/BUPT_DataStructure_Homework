using namespace std;
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
    using namespace std;

// 并查集（带路径压缩和按秩合并）
    class UnionFind {
    private:
        unordered_map<int, int> parent;
        unordered_map<int, int> rank;
    public:
        UnionFind() {}

        int find(int x) {
            if (parent.find(x) == parent.end()) {
                parent[x] = x;
                rank[x] = 0;
            }
            if (parent[x] != x) {
                parent[x] = find(parent[x]);  // 路径压缩
            }
            return parent[x];
        }

        void unite(int x, int y) {
            int px = find(x), py = find(y);
            if (px == py) return;
            if (rank[px] < rank[py]) {
                parent[px] = py;
            } else {
                parent[py] = px;
                if (rank[px] == rank[py]) rank[px]++;
            }
        }
    };

    vector<vector<int>> labelConnectedComponents(const vector<vector<int>>& image) {
        if (image.empty() || image[0].empty()) return {};

        int rows = image.size();
        int cols = image[0].size();

        vector<vector<int>> labels(rows, vector<int>(cols, 0));  // 结果标签矩阵
        UnionFind uf;
        unordered_map<int, int> nextLabel;  // 记录每个根标签对应的最终编号
        int labelCounter = 1;               // 从 1 开始编号

        // 第一遍扫描：分配临时标签并记录等价关系
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (image[i][j] == 0) continue;

                int current = 0;
                vector<int> neighbors;

                // 只看上和左（四连通）
                if (i > 0 && image[i-1][j] == 1) neighbors.push_back(labels[i-1][j]);
                if (j > 0 && image[i][j-1] == 1) neighbors.push_back(labels[i][j-1]);

                if (neighbors.empty()) {
                    // 全新连通域
                    current = labelCounter++;
                } else {
                    // 取最小标签作为当前标签
                    current = neighbors[0];
                    for (int nb : neighbors) {
                        if (nb < current) current = nb;
                    }
                    // 合并所有相邻标签
                    for (int nb : neighbors) {
                        if (nb != current) uf.unite(current, nb);
                    }
                }
                labels[i][j] = current;
            }
        }

        // 第二遍扫描：将所有等价标签替换为最终编号（从 1 开始连续）
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (labels[i][j] == 0) continue;
                int root = uf.find(labels[i][j]);
                if (nextLabel.find(root) == nextLabel.end()) {
                    nextLabel[root] = labelCounter++;
                }
                labels[i][j] = nextLabel[root];
            }
        }

        // 如果没有连通域，labelCounter-1 就是实际使用的最大编号
        return labels;
    }

// 打印矩阵（带对齐）
    void printMatrix(const vector<vector<int>>& mat) {
        for (const auto& row : mat) {
            for (int v : row) {
                if (v == 0) cout << " . ";
                else cout << " " << v << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    int main() {
        // 题目给出的测试数据（7行，长度不完全一致，补齐为 9 列）
        vector<vector<int>> image = {
                {1,0,1,0,1,0,1,0,1},
                {1,0,1,0,1,1,0,0,0},
                {1,0,1,1,0,0,1,0,0},
                {1,0,0,1,1,1,0,0,1},
                {1,1,1,1,1,1,1,1,1},
                {0,0,1,0,0,0,0,0,1},
                {1,1,1,1,1,1,1,1,1}
        };

        cout << "原始图像（1 为黑色）：\n";
        printMatrix(image);

        vector<vector<int>> result = labelConnectedComponents(image);

        cout << "四连通域标记结果（每个数字代表一个连通域）：\n";
        printMatrix(result);

        return 0;
    }


