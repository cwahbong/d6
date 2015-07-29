#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::chrono::system_clock;
using std::cerr;
using std::cout;
using std::default_random_engine;
using std::exception;
using std::endl;
using std::stoi;
using std::string;
using std::uniform_int_distribution;
using std::vector;

namespace d6 {

struct dice_6 {
  static constexpr int min() { return 1; }
  static constexpr int max() { return 6; }

  int value;
};

dice_6
roll()
{
  uniform_int_distribution<int> dist(dice_6::min(), dice_6::max());
  const unsigned seed = system_clock::now().time_since_epoch().count();
  default_random_engine eng(seed);
  return dice_6{dist(eng)};
}

string
to_string(const dice_6 &d)
{
  static const vector<string> dice_table = {
    u8"\u2680",
    u8"\u2681",
    u8"\u2682",
    u8"\u2683",
    u8"\u2684",
    u8"\u2685",
  };
  return dice_table.at(d.value - 1);
}

} // namespace d6

void
usage() {
  const string lines[] = {
    "Roll a d-6 in terminal.",
    "Usage: d6",
    "       d6 [num]",
  };
  for (const auto &line: lines) {
    cerr << line << endl;
  }
}

void
roll_dice(int num) {
  for (int i = 0; i < num; ++i) {
    cout << to_string(d6::roll());
  }
  cout << endl;
}

int
main(int argc, char ** argv)
{
  int num = 0;

  if (argc == 1) {
    num = 1;
  } else if (argc == 2) {
    try {
      num = stoi(argv[1]);
    } catch (const exception &e) {
      cerr << "\"" << argv[1] << "\" is not a valid number." << endl;
      return 2;
    }
  } else {
    usage();
    return 1;
  }

  roll_dice(num);
  return 0;
}
