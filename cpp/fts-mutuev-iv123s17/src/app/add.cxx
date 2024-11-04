#include <cstring>
#include <cxxopts.hpp>
#include <iostream>
#include <libmath/addition.hxx>
#include <string>

int main(int argc, char** argv) {
  cxxopts::Options options("addition");

  double x = 0;
  double y = 0;

  try {
    options.add_options()(
        "first", "First term", cxxopts::value<double>()->default_value("0"))(
        "second", "Second term", cxxopts::value<double>()->default_value("0"));

    const auto result = options.parse(argc, argv);

    if (result.count("first") != 1 || result.count("second") != 1) {
      std::cout << options.help() << "\n";
      return 0;
    }

    const auto first = result["first"].as<double>();
    const auto second = result["second"].as<double>();
    x = first;
    y = second;

    const double output = mathfunctions::add(x, y);

    std::cout << "Addition of " << x << " and " << y << " is " << output
              << std::endl;
  } catch (const std::exception& error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }
}
