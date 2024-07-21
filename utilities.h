#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

/*
 * Read file contents into a string
 * 
 * @param[out] dest     the string to store the file contents in
 * @param[in]  path     the path of the file
*/
bool read_file(string &dest, const string& path);

/*
 * Calculate hash values of all files in a directory
 * 
 * @param[in]   dir           the path of the directory
 * @param[out]  hashes        the hash values of all the files
 * @param[out]  filename_map  map of a file's hash value to the file path
*/
void hash_files_in_dir(const string& dir,
                       vector<size_t>& hashes,
                       unordered_map<size_t, string>& filename_map);

/*
 * Write filenames with the given hash values to output file
 * 
 * @param[out]  hashes          the hash values of the files
 * @param[out]  filename_map    map of a file's hash value to the file path
 * @param[in]   output_filename the path of the output file
 * @param[in]   append          whether to append to the output_filename or not
*/
void write_filenames(vector<size_t>& hashes,
                     unordered_map<size_t, string>& filename_map,
                     const string& output_filename,
                     bool append=false);

#endif /* UTILITIES_H */