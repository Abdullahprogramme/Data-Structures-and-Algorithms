#include <iostream>
#include <stdexcept>
#include "Task1.cpp"

using namespace std;

template <typename T>
class ExamRoom {
    private:
        Set<T> seats;
        int capacity;
        bool isRoomEmpty;

        // Returns the distance to the nearest occupied seat from the given seat
        int getDistance(int seat) {
            if (isRoomEmpty) return capacity;

            int left = seat - 1;
            int right = seat + 1;
            int distance = 0;

            while (left >= 0 || right < capacity) {
                distance++;
                if (left >= 0 && seats.contains(left)) break;
                if (right < capacity && seats.contains(right)) break;
                left--;
                right++;
            }

            return distance;
        }

    public:
        ExamRoom(int n) : capacity(n), isRoomEmpty(true) {}

        int seat() {
            if (seats.size() == 0) {
                seats.add(0);
                isRoomEmpty = false;
                return 0;
            }

            int maxDist = 0;
            int seatToAssign = 0;

            // Get first occupied seat
            int first = seats.select(0);
            if (first != 0) {
                maxDist = first;
                seatToAssign = 0;
            }

            // Check all gaps between occupied seats
            for (int i = 1; i < seats.size(); ++i) {
                int left = seats.select(i - 1);
                int right = seats.select(i);
                int dist = (right - left) / 2;

                if (dist > maxDist) {
                    maxDist = dist;
                    seatToAssign = left + dist;
                }
            }

            // Check distance from last occupied seat to end
            int last = seats.select(seats.size() - 1);
            if (capacity - 1 - last > maxDist) {
                seatToAssign = capacity - 1;
            }

            seats.add(seatToAssign);
            return seatToAssign;
        }
    
        void leave(int p) {
            if (seats.contains(p)) {
                seats.remove(p);
                if (seats.rank(p) == 0 && seats.select(0) == p && seats.rank(p) == seats.select(seats.rank(p))) {
                    isRoomEmpty = true;
                }
            } else {
                throw invalid_argument("Seat " + to_string(p) + " is not occupied.");
            }
        }    
};

int main() {
    ExamRoom<int> examRoom(10);

    int seat1 = examRoom.seat(); // Student sits at seat 0
    cout << "Student seated at: " << seat1 << endl;
    // {S, _, _, _, _, _, _, _, _, _}

    int seat2 = examRoom.seat(); // Student sits at seat 9
    cout << "Student seated at: " << seat2 << endl;
    // {S, _, _, _, _, _, _, _, _, S}

    int seat3 = examRoom.seat(); // Student sits at seat 4
    cout << "Student seated at: " << seat3 << endl;
    // {S, _, _, _, S, _, _, _, _, S}

    int seat4 = examRoom.seat(); // Student sits at seat 2
    cout << "Student seated at: " << seat4 << endl;
    // {S, _, S, _, S, _, _, _, _, S}

    examRoom.leave(4); // Student leaves seat 4
    cout << "Student left from seat: 4" << endl;
    // {S, _, S, _, _, _, _, _, _, S}

    int seat5 = examRoom.seat(); // Student sits at seat 5
    cout << "Student seated at: " << seat5 << endl;
    // {S, _, S, _, S, _, _, _, _, S}

    return 0;
}