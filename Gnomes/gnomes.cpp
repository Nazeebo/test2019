#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

struct Quality {
    int min;
    int max;

    Quality(int min_, int max_) {
        min = min_;
        max = max_;
    }

    Quality() = default;

    int getMax() { return (max > 0) ? max : min; }
};

vector<std::string> split(const string &s, char delimiter) {
    vector<std::string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}


void putQualityInMap(map<char, Quality> &chart, const string &line) {
    char qualityName = line[0];
    int min;
    int max = -1;

    int range = line.find('-');
    if (range > 0) {
        min = stol(line.substr(2, range - 2));
        max = stol(line.substr(range + 1, line.size() - 1));
    } else {
        string smin = line.substr(2, line.size());
        min = (isdigit(smin[0])) ? stol(smin) : chart[smin[0]].getMax();
    }

    chart.insert(pair<char, Quality>(qualityName, Quality(min, max)));
}

bool isHeWorthy(const map<char, Quality> &bouncer, map<char, Quality> visitor) {
    for (const auto quality: bouncer) {
        int visitorsValue = visitor[quality.first].min;
        if (quality.second.max != -1) {
            if (visitorsValue > quality.second.max || visitorsValue < quality.second.min)
                return false;
        } else if (visitorsValue < quality.second.min)
            return false;
    }

    return true;
}

int main() {
    string lineBouncer, lineVisitor;

    ifstream in("input.txt");

    if (in.is_open()) {
        getline(in, lineBouncer);
        getline(in, lineVisitor);
    }
    in.close();

    map<char, Quality> face_control;
    vector<string> qualitiesBouncer(split(lineBouncer, ' '));

    for (const auto &qual :qualitiesBouncer)
        putQualityInMap(face_control, qual);

    vector<string> qualitiesVisitor(split(lineVisitor, ' '));

    map<char, Quality> visitor;
    for (const auto &qual :qualitiesVisitor)
        putQualityInMap(visitor, qual);

    cout << ((isHeWorthy(face_control, visitor)) ? "true" : "false") << endl;

    return 0;
}