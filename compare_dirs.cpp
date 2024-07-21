#include "utilities.h"
#include <algorithm>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " " << "directory_path_a"
                  << " directory_path_b" << endl;
        return 1;
    }

    // Calculate hashes of files in dir_a and dir_b
    vector<size_t> a_all, b_all;
    unordered_map<size_t, string> filename_map_a, filename_map_b;
    hash_files_in_dir(argv[1], a_all, filename_map_a);
    hash_files_in_dir(argv[2], b_all, filename_map_b);

    // Files in dir_a only
    vector<size_t> a_only;
    set_difference(a_all.begin(), a_all.end(),
                   b_all.begin(), b_all.end(),
                   inserter(a_only, a_only.begin()));
    write_filenames(a_only, filename_map_a, "a_only");

    // Files in dir_b only
    vector<size_t> b_only;
    set_difference(b_all.begin(), b_all.end(),
                   a_all.begin(), a_all.end(),
                   inserter(b_only, b_only.begin()));
    write_filenames(b_only, filename_map_b, "b_only");

    // Files in both dir_a and dir_b
    vector<size_t> common;
    set_intersection(b_all.begin(), b_all.end(),
                     a_all.begin(), a_all.end(),
                     inserter(common, common.begin()));
    write_filenames(common, filename_map_a, "common");
    write_filenames(common, filename_map_b, "common", true);
}
