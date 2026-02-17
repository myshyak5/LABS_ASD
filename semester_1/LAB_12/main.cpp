#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <filesystem>

void merge_files(const std::string& output_file, const std::vector<std::string>& temp_files) {
    std::vector<std::ifstream> file_streams;
    file_streams.reserve(temp_files.size());
    for (const auto& temp_file : temp_files) {
        file_streams.emplace_back(temp_file);
        if (!file_streams.back().is_open()) {
            std::cerr << "Error opening file: " << temp_file << std::endl;
            return;
        }
    }
    std::ofstream output(output_file);
    if (!output.is_open()) {
        std::cerr << "Error opening output file: " << output_file << std::endl;
        return;
    }
    using Element = std::pair<int, size_t>;
    std::priority_queue<Element, std::vector<Element>, std::greater<Element>> heap;
    for (size_t i = 0; i < file_streams.size(); ++i) {
        int value;
        if (file_streams[i] >> value) {
            heap.emplace(value, i);
        }
    }
    size_t counter = 0;
    const size_t total_files = file_streams.size();
    while (counter < total_files) {
        auto root = heap.top();
        heap.pop();
        output << root.first << '\n';
        int value;
        if (file_streams[root.second] >> value) {
            heap.emplace(value, root.second);
        }
        else {
            ++counter;
        }
    }
}
std::vector<std::string> create_initial_runs(const std::string& input_file, int run_size, const std::string& path) {
    std::vector<std::string> temp_files;
    std::ifstream input(input_file);
    if (!input.is_open()) {
        std::cerr << "Error opening input file: " << input_file << std::endl;
        return temp_files;
    }
    std::filesystem::create_directories(path);
    int temp_files_counter = 0;
    bool end_of_file = false;
    while (!end_of_file) {
        std::vector<int> data;
        data.reserve(run_size);
        for (int i = 0; i < run_size; ++i) {
            int value;
            if (input >> value) {
                data.push_back(value);
            }
            else {
                end_of_file = true;
                break;
            }
        }
        if (data.empty()) {
            break;
        }
        std::sort(data.begin(), data.end());
        std::string temp_filename = path + "f_" + std::to_string(temp_files_counter) + ".txt";
        std::ofstream output(temp_filename);
        if (!output.is_open()) {
            std::cerr << "Error creating temp file: " << temp_filename << std::endl;
            continue;
        }
        for (size_t i = 0; i < data.size(); ++i) {
            output << data[i];
            if (i < data.size() - 1) {
                output << '\n';
            }
        }
        temp_files.push_back(temp_filename);
        temp_files_counter++;
    }
    return temp_files;
}
void external_multiphase_sort(const std::string& path, int run_size) {
    std::string input_file = path + "input1.txt";
    std::string output_file = path + "output.txt";
    std::string temp_path = path + "Temp_files_linear//";
    auto temp_files = create_initial_runs(input_file, run_size, temp_path);
    merge_files(output_file, temp_files);
    // for (const auto& temp_file : temp_files) {
    //     std::filesystem::remove(temp_file);
    // }
    // std::filesystem::remove(temp_path);
}
int main() {
    std::string path = "..//..//";
    int run_size = 90;
    external_multiphase_sort(path, run_size);
    return 0;
}