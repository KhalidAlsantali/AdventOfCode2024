#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <cctype>
#include <set>


using namespace std;

pair<int, int> calculateDifference(pair<int, int> first_antenna, pair<int, int> second_antenna){
    int i_diff = second_antenna.first - first_antenna.first;
    int j_diff = second_antenna.second - first_antenna.second;
    return {i_diff, j_diff};
}

vector<pair<int, int>> getAntinodes(pair<int, int> first_antenna, pair<int, int> second_antenna, pair<int, int> diff, vector<vector<char>>& map){
    vector<pair<int, int>> antinodes;
    pair<int, int> first_antinode = {(diff.first * -1) + first_antenna.first, (diff.second * -1) + first_antenna.second};
    pair<int, int> second_antinode = {diff.first + second_antenna.first, diff.second + second_antenna.second};

    if (first_antinode.first >= 0 && static_cast<size_t>(first_antinode.first) < map.size() && 
        first_antinode.second >= 0 && static_cast<size_t>(first_antinode.second) < map[0].size()) {
        antinodes.push_back(first_antinode);
    }

    if (second_antinode.first >= 0 && static_cast<size_t>(second_antinode.first) < map.size() && 
        second_antinode.second >= 0 && static_cast<size_t>(second_antinode.second) < map[0].size()) {
        antinodes.push_back(second_antinode);
    }

    return antinodes;
}

int main(){
    string input_filename = "input.txt";
    ifstream inputFile(input_filename);
    vector<vector<char>> map;
    unordered_map<char, vector<pair<int, int>>> antennas;

    string line;
    while (getline(inputFile, line)) {
        vector<char> row(line.begin(), line.end());
        map.push_back(row);
    }

    for(size_t i = 0; i < map.size(); ++i){
        for(size_t j = 0; j < map[i].size(); ++j){
            if(isalnum(map[i][j])){
                antennas[map[i][j]].push_back({i, j});
            }
        }
    }

    set<pair<int, int>> all_antinodes;
    for(const auto& [antenna, positions] : antennas){
        for(size_t i = 0; i < positions.size(); ++i){
            for(size_t j = 0; j < positions.size(); ++j){
                if(positions[i] == positions[j]){
                    continue;
                }
                pair<int, int> diff = calculateDifference(positions[i], positions[j]);
                vector<pair<int, int>> antinodes = getAntinodes(positions[i], positions[j], diff, map);
                if(!antinodes.empty()){
                    all_antinodes.insert(antinodes.begin(), antinodes.end());
                }
            }
        }
    }
    cout << "Part one answer: " << all_antinodes.size() << endl;
    return 0;
}