#include "sequence_gen.h"

void process_input(const std::string & input_filename, std::string & s1,
                   std::string & s2, std::vector<int> & insert_pos1,
                   std::vector<int> & insert_pos2) {
  std::ifstream input(input_filename, std::ios_base::in);
  int pos;

  input >> s1;
  while (input >> pos) { insert_pos1.push_back(pos); }

  input.clear();

  input >> s2;
  while (input >> pos) { insert_pos2.push_back(pos); }

  input.close();
}


void generate_string(std::string & s, const std::vector<int> & insert_pos) {
  // allocate string of final size * 2
  s.reserve((size_t) pow(2, insert_pos.size() + 1) * s.size());
//  cout << "[generate_string] reserve string capacity of " <<  s.capacity() << endl;
  for (int pos: insert_pos) {
    s.insert(s.begin() + pos + 1, s.begin(), s.end());    // potential risk!
  }
}

std::unordered_map<char, std::unordered_map<char, int>>
construct_mismatch_cost() {
  return {
    {'A', {
            {'A', 0},   {'C', 110}, {'G', 48},  {'T', 94}}
    },
    {'C', {
            {'A', 110}, {'C', 0},   {'G', 118}, {'T', 48}}
    },
    {'G', {
            {'A', 48},  {'C', 118}, {'G', 0},   {'T', 110}}
    },
    {'T', {
            {'A', 94},  {'C', 48},  {'G', 110}, {'T', 0}}
    }
  };
}

void print_mismatch_cost(
  std::unordered_map<char, std::unordered_map<char, int>> & cost) {
  std::cout << "[print_mismatch_cost] cost table:\n";
  std::string s = "ACGT";
  for (char i: s) {
    for (char j: s) {
      std::cout << "\t" << cost[i][j];
    }
    std::cout << "\n";
  }
}

