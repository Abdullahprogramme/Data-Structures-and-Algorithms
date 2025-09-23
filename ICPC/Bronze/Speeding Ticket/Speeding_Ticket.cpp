#include <vector>
#include <stdio.h>
#include <utility>

using namespace std;

int main() {
    freopen("speeding.in", "r", stdin);

    int N, M;
    scanf("%d %d", &N, &M);

    vector<pair<int, int>> road_segments(N);
    vector<pair<int, int>> bessie_segments(M);

    for (int i = 0; i < N; i++) {
        int length, speed_limit;
        scanf("%d %d", &length, &speed_limit);
        road_segments[i] = {length, speed_limit};
    }

    for (int i = 0; i < M; i++) {
        int length, speed;
        scanf("%d %d", &length, &speed);
        bessie_segments[i] = {length, speed};
    }

    int max_over_speed = 0;
    int road_index = 0, bessie_index = 0;

    while (road_index < N && bessie_index < M) {
        int road_length = road_segments[road_index].first;
        int road_speed_limit = road_segments[road_index].second;
        int bessie_length = bessie_segments[bessie_index].first;
        int bessie_speed = bessie_segments[bessie_index].second;

        int segment_length = min(road_length, bessie_length);
        if (bessie_speed > road_speed_limit) {
            max_over_speed = max(max_over_speed, bessie_speed - road_speed_limit);
        }

        road_segments[road_index].first -= segment_length;
        bessie_segments[bessie_index].first -= segment_length;

        if (road_segments[road_index].first == 0) {
            road_index++;
        }
        if (bessie_segments[bessie_index].first == 0) {
            bessie_index++;
        }
    }
    
    printf("%d\n", max_over_speed);
    return 0;
}