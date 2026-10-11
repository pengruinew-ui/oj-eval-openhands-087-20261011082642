#include <iostream>
#include <vector>
using namespace std;

long long countBallsToLeaf(int D, long long n, int leaf_pos) {
    long long balls = n;
    
    for (int depth = 1; depth < D; depth++) {
        // Determine if we should go left or right to reach leaf_pos
        int bit = (leaf_pos >> (D - depth)) & 1;  // 0 for left, 1 for right
        
        cout << "  Depth " << depth << ": balls=" << balls << ", bit=" << bit;
        
        if (balls % 2 == 1) {
            // Odd balls go left
            if (bit == 0) {
                // This path matches where odd balls go
                balls = (balls + 1) / 2;
                cout << " -> odd matches left, new balls=" << balls << endl;
            } else {
                // This path gets even balls
                balls = balls / 2;
                cout << " -> odd goes left, this path gets even, new balls=" << balls << endl;
            }
        } else {
            // Even balls go right
            if (bit == 1) {
                // This path matches where even balls go
                balls = balls / 2;
                cout << " -> even matches right, new balls=" << balls << endl;
            } else {
                // This path gets odd balls
                balls = (balls + 1) / 2;
                cout << " -> even goes right, this path gets odd, new balls=" << balls << endl;
            }
        }
    }
    
    return balls;
}

int main() {
    int D = 4;
    long long n = 3;
    
    cout << "Testing leaf positions 8-15:" << endl;
    for (int leaf_pos = 8; leaf_pos < 16; leaf_pos++) {
        cout << "Leaf " << leaf_pos << ":" << endl;
        long long balls = countBallsToLeaf(D, n, leaf_pos);
        cout << "  Final balls: " << balls << " -> state: " << (balls % 2) << endl;
        cout << endl;
    }
    
    return 0;
}