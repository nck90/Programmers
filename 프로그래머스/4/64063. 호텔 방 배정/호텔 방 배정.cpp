#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<long long, long long> room;

long long GetEmptyRoom(long long n) {
    if (room[n] == 0) return n;
    return room[n] = GetEmptyRoom(room[n]);
}

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;

    for (auto num : room_number) {
        long long emptyRoom = GetEmptyRoom(num);
        answer.push_back(emptyRoom);
        room[emptyRoom] = emptyRoom + 1;
    }
    return answer;
}
