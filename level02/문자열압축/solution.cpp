#include <string>
#include <vector>

using namespace std;

int solution(string s) {
    int curr_len = s.size();
    int answer = s.size();

    // From [1] To [s.size / 2]
    for(int len = 1; len <= s.size()/2; len++) {
        
        // initialize
        curr_len = s.size();
        int how_many = 0;

        for(int pos = 0; pos < s.size() - len; pos += len) {

            string compared = s.substr(pos, len);

            while(true) {
                // next string is same
                if(compared.compare(s.substr(pos+len, len)) == 0) {
                    how_many++;
                    pos += len;
                
                // next string is not same and how_many is not zero
                } else if(how_many != 0) {
                    curr_len = curr_len - (len * how_many) + to_string(how_many+1).size();
                    how_many = 0;

                    break;

                // next string is not same and how_many is zero
                } else {
                    break;
                }
            }
        }

        // renew answer
        if(curr_len < answer)
            answer = curr_len;

    }


    return answer;
}