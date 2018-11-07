#include <box_nesting/Algorithm.hpp>
#include <box_nesting/Parser.hpp>
#include <box_nesting/version.hpp>

#include <cstdlib>
#include <iostream>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  auto boxes = BoxNesting::Parser::getBoxes(std::cin);

  BoxNesting::Algorithm boxNestingAlgorithm;

  std::cout << boxNestingAlgorithm.runAlgorithm(boxes) << std::endl;

  return EXIT_SUCCESS;
}
