#include <stdio.h>
#include <vector>

using namespace std;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int N;
        scanf("%d", &N);
        vector<int> sleep_times(N);
        
        int total_sum = 0;
        for (int i = 0; i < N; ++i) {
            scanf("%d", &sleep_times[i]);
            total_sum += sleep_times[i];
        }
        
        int max_segments = 1;  // At least we can have 1 segment (all elements combined)
        
        // Try all possible number of segments from N down to 1
        for (int k = N; k >= 1; k--) {
            if (total_sum % k != 0) continue;  // Sum must be divisible by number of segments
            
            int target_sum = total_sum / k;
            int current_sum = 0;
            int segments_formed = 0;
            bool valid = true;
            
            for (int i = 0; i < N; i++) {
                current_sum += sleep_times[i];
                
                if (current_sum == target_sum) {
                    segments_formed++;
                    current_sum = 0;
                } else if (current_sum > target_sum) {
                    valid = false;
                    break;
                }
            }
            
            if (valid && segments_formed == k) {
                max_segments = k;
                break;  // Found the maximum, no need to check smaller k
            }
        }
        
        // Minimum modifications = N - max_segments
        printf("%d\n", N - max_segments);
    }
    
    return 0;
}