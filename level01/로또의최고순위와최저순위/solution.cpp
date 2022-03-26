#include <string>
#include <vector>

#include <algorithm>

using namespace std;

vector<int> solution(vector<int> lottos, vector<int> win_nums) {
    // first  : how_many[매칭되는 숫자 + 0의 갯수]
    // second : how_many[매칭되는 숫자]
    vector<int> answer;

    int how_many[7] = {6, 6, 5, 4, 3, 2, 1};

    int zero_count      = 0;
    int matched_count   = 0;

    for(auto num : lottos) {
        if(num == 0) {
            zero_count++;
            continue;
        }

        auto pos = find(win_nums.begin(), win_nums.end(), num);
        if(pos != win_nums.end()) {
            matched_count++;
        }
    }

    answer.push_back(how_many[matched_count + zero_count]);
    answer.push_back(how_many[matched_count]);


    return answer;
}