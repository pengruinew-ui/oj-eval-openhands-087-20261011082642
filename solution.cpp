#include <iostream>
#include <vector>
using namespace std;

// Simulate the path of a single ball through the tree
int simulateBallPath(int D, long long ball_num, vector<bool>& switches) {
    int node = 1;  // Start at root (1-indexed)
    
    // Tree has D-1 levels of switches, balls fall to level D
    for (int depth = 1; depth < D; depth++) {
        if (!switches[node]) {
            // Switch is closed, open it and go left
            switches[node] = true;
            node = node * 2;  // Go to left child
        } else {
            // Switch is open, close it and go right
            switches[node] = false;
            node = node * 2 + 1;  // Go to right child
        }
    }
    
    return node;  // Return the position at level D
}

int findLastBallPosition(int D, long long n) {
    // For finding just the last ball position, we can use a more efficient method
    // without simulating all balls
    int position = 1;  // Start at root
    
    // Tree has D-1 levels of switches
    for (int depth = 1; depth < D; depth++) {
        if (n % 2 == 1) {
            // Odd-numbered ball at this node goes left
            position = position * 2;
            n = (n + 1) / 2;
        } else {
            // Even-numbered ball at this node goes right
            position = position * 2 + 1;
            n = n / 2;
        }
    }
    
    return position;
}



vector<int> getLeafStates(int D, long long n) {
    // Use simulation for small n, mathematical approach for large n
    if (n <= 1000000) {  // Threshold for simulation
        // Simulation approach (works correctly but slow for large n)
        int total_switches = (1 << D) - 1;
        vector<bool> switches(total_switches + 1, false);
        vector<bool> leaf_visited(1 << (D - 1), false);
        
        for (long long ball = 1; ball <= n; ball++) {
            int final_pos = simulateBallPath(D, ball, switches);
            int leaf_index = final_pos - (1 << (D - 1));
            if (leaf_index >= 0 && leaf_index < (1 << (D - 1))) {
                leaf_visited[leaf_index] = true;
            }
        }
        
        vector<int> leaf_states;
        for (int i = 0; i < (1 << (D - 1)); i++) {
            leaf_states.push_back(leaf_visited[i] ? 1 : 0);
        }
        return leaf_states;
    } else {
        // For large n, use a different approach
        // Since the simulation approach is too slow, let me try to optimize it
        // by understanding that we only need to know if each leaf gets an odd or even number of balls
        
        vector<int> leaf_states;
        for (int leaf_pos = (1 << (D - 1)); leaf_pos < (1 << D); leaf_pos++) {
            // Simulate just the parity (odd/even) for this leaf
            long long balls = n;
            bool odd_parity = false;
            
            for (int depth = 1; depth < D; depth++) {
                // Determine the path to this leaf
                int bit = (leaf_pos >> (D - 1 - depth)) & 1;
                
                if (balls % 2 == 1) {
                    // Odd number of balls
                    if (bit == 0) {
                        // This path gets the odd balls
                        odd_parity = !odd_parity;
                        balls = (balls + 1) / 2;
                    } else {
                        // This path gets the even balls
                        balls = balls / 2;
                    }
                } else {
                    // Even number of balls
                    if (bit == 1) {
                        // This path gets the even balls
                        balls = balls / 2;
                    } else {
                        // This path gets the odd balls
                        odd_parity = !odd_parity;
                        balls = (balls + 1) / 2;
                    }
                }
            }
            
            leaf_states.push_back(odd_parity ? 1 : 0);
        }
        
        return leaf_states;
    }
}

int main() {
    int D;
    long long n;
    cin >> D >> n;
    
    // Find last ball position (using efficient method)
    int last_pos = findLastBallPosition(D, n);
    
    // Get leaf states (need to simulate for this)
    vector<int> leaf_states = getLeafStates(D, n);
    
    // Output results
    cout << last_pos << endl;
    for (int i = 0; i < leaf_states.size(); i++) {
        if (i > 0) cout << " ";
        cout << leaf_states[i];
    }
    cout << endl;
    
    return 0;
}