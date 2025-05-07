#include <iostream>
#include <limits>
using namespace std;

const int MAX_SIZE = 10;

class OBST {
private:
    float weight[MAX_SIZE][MAX_SIZE] = {0};
    float cost[MAX_SIZE][MAX_SIZE] = {0};
    int root[MAX_SIZE][MAX_SIZE] = {0};

    struct TreeNode {
        int data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
    };

    TreeNode* rootNode = nullptr;

    void initializeMatrices(int n) {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                weight[i][j] = cost[i][j] = 0;
                root[i][j] = 0;
            }
        }
    }

public:
    void calculateWeights(int n, float unsucc[], float succ[]) {
        for (int i = 0; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                float w = unsucc[i];
                for (int k = i + 1; k <= j; k++) {
                    w += unsucc[k] + succ[k];
                }
                weight[i][j] = w;
            }
        }
    }

    void calculateCosts(int n) {
        for (int length = 1; length <= n; length++) {
            for (int i = 0; i <= n - length; i++) {
                int j = i + length;
                if (i == j) {
                    cost[i][j] = 0;
                    continue;
                }

                float minCost = numeric_limits<float>::max();
                int bestRoot = i + 1;
                for (int k = i + 1; k <= j; k++) {
                    float currentCost = cost[i][k - 1] + cost[k][j];
                    if (currentCost < minCost) {
                        minCost = currentCost;
                        bestRoot = k;
                    }
                }

                cost[i][j] = minCost + weight[i][j];
                root[i][j] = bestRoot;
            }
        }
    }

    TreeNode* constructTree(int i, int j, float keys[]) {
        if (i == j) return nullptr;
        int rootIndex = root[i][j];
        TreeNode* node = new TreeNode(keys[rootIndex - 1]);
        node->left = constructTree(i, rootIndex - 1, keys);
        node->right = constructTree(rootIndex, j, keys);
        return node;
    }

    void displayMatrices(int n) {
        cout << "\nWeight, Cost, and Root Matrices:\n";
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                cout << "w(" << i << "," << j << "): " << weight[i][j] << " cost(" << i << "," << j << "): " << cost[i][j] << " root(" << i << "," << j << "): " << root[i][j] << endl;
            }
        }
    }

    void buildOBST() {
        int n;
        cout << "Enter total number of keys: ";
        cin >> n;

        float keys[MAX_SIZE];
        cout << "Enter keys (sorted order): ";
        for (int i = 0; i < n; i++) {
            cin >> keys[i];
        }

        float succ[MAX_SIZE] = {0}, unsucc[MAX_SIZE] = {0};
        cout << "Enter successful probabilities: ";
        for (int i = 1; i <= n; i++) {
            cin >> succ[i];
        }

        cout << "Enter unsuccessful probabilities:\n";
        for (int i = 0; i <= n; i++) {
            cout << "Enter unsuccessful probability for " << i << ": ";
            cin >> unsucc[i];
        }

        initializeMatrices(n);
        calculateWeights(n, unsucc, succ);
        calculateCosts(n);
        displayMatrices(n);

        rootNode = constructTree(0, n, keys);
        cout << "\nOBST constructed successfully!\n";
    }

    ~OBST() {
        clearTree(rootNode);
    }

private:
    void clearTree(TreeNode* node) {
        if (node) {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }
};

int main() {
    OBST obst;
    obst.buildOBST();
    return 0;
}
