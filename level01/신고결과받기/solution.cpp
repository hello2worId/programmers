#include <iostream>

#include <string>
#include <cstring>
#include <vector>

#include <map>
#include <set>
#include <algorithm>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer;

    // 신고자 -> 악플러
    map<string, set<string>> who_report_him;

    // 악플러 <- 신고자
    map<string, set<string>> he_reported_by_whom;
    
    for(const auto id : id_list) {
        who_report_him.insert(make_pair(id, set<string>()));
    }

    for(auto rep : report) {
        auto rep_c = const_cast<char *> (rep.c_str());

        auto token = strtok(rep_c, " ");
        string reporter(token);

        token = strtok(NULL, " ");
        string reported(token);

        who_report_him[reporter].insert(reported);
        he_reported_by_whom[reported].insert(reporter);
    }

    // <name, set> => string : him reported over k
    vector<string> transformed;
    std::transform(he_reported_by_whom.begin(), he_reported_by_whom.end(), std::back_inserter(transformed), 
        [k](const pair<std::string, std::set<std::string>>& info){
            auto name = info.first;
            auto size = info.second.size();

            if(size >= k) {
                return name;
            } else {
                string undefined_name("");
                return undefined_name;
            }
        });

    // <name, set> => <name, count>
    map<string, int> name_with_count;

    for(auto itr = who_report_him.begin(); itr != who_report_him.end(); itr++) {
        auto who = itr->first;
        auto report_person = itr->second;
        int count = 0;

        for(auto person : report_person) {
            auto res = find(transformed.begin(), transformed.end(), person);

            if(res != transformed.end()) {
                count++;
            }
        }

        name_with_count[who] = count;
    }

    for(const auto name : id_list) {
        answer.push_back(name_with_count[name]);
    }

    return answer;
}



int main() {
    auto res = solution({"muzi", "frodo", "apeach", "neo"}, {"muzi frodo","apeach frodo","frodo neo","muzi neo","apeach muzi"}, 2);

    for(auto r : res) {
        cout << r << " ";
    }
    cout << "\n";

    return 0;
}


