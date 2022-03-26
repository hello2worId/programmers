#include <string>
#include <vector>

#include <iostream>
#include <cstring>

using namespace std;

int solution(vector<string> lines) {
    int answer = 0;

    // vector<시작시간, 종료시간>>
    vector<pair<int, int>> from_to_vec;

    for(auto line : lines) {
        string time_info = line.substr(11, 12);

        string how_long = line.substr(24);
        how_long = how_long.substr(0, how_long.size()-1);

        // hour -> sec
        cout << time_info << "\n";
        auto hour = string (strtok(const_cast<char *> (time_info.c_str()), ":"));
        auto min = string (strtok(NULL, ":"));
        auto sec = string (strtok(NULL, ":"));

        auto converted_sec = stoi(hour) * 3600000 + stoi(min) * 60000 + static_cast<int>(stod(sec) * 1000);
        auto converted_how_long = static_cast<int> (stod(how_long) * 1000);
        
        from_to_vec.push_back(make_pair(converted_sec - converted_how_long + 1, converted_sec));
    }

    for(int i=0; i<from_to_vec.size(); i++) {
        
        // initialize
        int count = 0;
        // first ~ [first + 1000]
        auto lhs = from_to_vec[i].first;
        auto rhs = lhs + 1000 - 1;

        for(int j=0; j<from_to_vec.size(); j++) {
            if(from_to_vec[j].first <= rhs && from_to_vec[j].second >= lhs) {
                count++;
            }
        }

        if(count > answer) {
            answer = count;
        }
        count = 0;

        // second ~ [second + 1000]
        lhs = from_to_vec[i].second;
        rhs = lhs + 1000 - 1;
        for(int j=0; j<from_to_vec.size(); j++) {
            if(from_to_vec[j].first <= rhs && from_to_vec[j].second >= lhs) {
                count++;
            }
        }
        
        if(count > answer) {
            answer = count;
        }
        count = 0;
        

    }


    return answer;
}


int main() {
    cout << solution({"2016-09-15 01:00:04.001 2.0s", "2016-09-15 01:00:07.000 2s"}) << "\n";
    cout << solution({"2016-09-15 01:00:04.002 2.0s", "2016-09-15 01:00:07.000 2s"}) << "\n";

    return 0;
}