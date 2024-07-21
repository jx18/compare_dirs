#include "utilities.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <algorithm>
namespace fs = filesystem;

bool read_file(string &dest, const string& path)
{
    ostringstream os;
    ifstream input(path);
    string line;
    if (input.is_open()) {
        while (getline(input, line)) {
            os << line << endl;
        }
        dest = os.str();
        input.close();
        return true;
    }
    return false;
}

void hash_files_in_dir(const string& dir,
                       vector<size_t>& hashes,
                       unordered_map<size_t, string>& filename_map)
{
    for (const auto& entry : fs::directory_iterator(dir)) {
        string contents;
        if (!read_file(contents, entry.path())) {
            cerr << "Error reading file " << entry.path().string() << endl;
        }
        size_t hash_value = fs::hash_value(contents);
        hashes.push_back(hash_value);
        filename_map.emplace(hash_value, entry.path().string());
    }
    sort(hashes.begin(), hashes.end());
}

void write_filenames(vector<size_t>& hashes,
                     unordered_map<size_t, string>& filename_map,
                     const string& output_filename,
                     bool append)
{
    ofstream output;
    if (append) {
        output.open(output_filename, ios::app);
    } else {
        output.open(output_filename, ios::trunc);
    }

    for (size_t h : hashes) {
        output << filename_map[h] << endl;
    }

    output.close();
}
