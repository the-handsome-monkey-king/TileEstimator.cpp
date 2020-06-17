/***************************
*
*  test_estimator.cpp
*
*  @author Ryan Morehouse
*  @license  MIT
*
*  Test the functionality of the TileEstimator class.
*
  **************************/


#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include "TileEstimator.h"

double get_double(std::string *prompt) {
  double d;
  while(true) {
    std::cout << *prompt << ": ";
    if (std::cin >> d)
      return d;
    else {
      std::cout << "Invalid input, try again.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
  }
}

double get_positive_double(std::string *prompt) {
  double d = get_double(prompt);
 while(d < 0) {
    std::cout << "Input must be positive. Please try again.\n";
    d = get_double(prompt);
  }
  return d;
}

long get_long(std::string *prompt) {
  long l;
  while(true) {
    std::cout << *prompt << ": ";
    if (std::cin >> l)
      return l;
    else {
      std::cout << "Invalid input, try again.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
  }
}

long get_positive_long(std::string *prompt) {
  int l = get_long(prompt);
  while(l< 0) {
    std::cout << "Input must be positive. Please try again.\n";
    l = get_long(prompt);
  }
  return l;
}

bool get_bool(std::string *prompt) {
  char c;
  while(true) {
    std:: cout << *prompt << ": ";
    if (std::cin >> c) {
      if(c == 'y' || c == 'Y')
        return true;
      else if(c == 'n' || c == 'N')
        return false;
      else {
        std::cout << "Input y or n, please try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
      }
    }
  }
}

int main() {
  // user variables
  double area_w, area_h, tile_w, tile_h;
  long tile_cost, extra_tiles;
  bool reuse_subtiles;

  // get user variables
  std::string prompt = "Please enter the area width";
  area_w = get_positive_double(&prompt);

  prompt = "Please enter the area height";
  area_h = get_positive_double(&prompt);

  prompt = "Please enter the tile width";
  tile_w = get_positive_double(&prompt);

  prompt = "Please enter the tile height";
  tile_h = get_positive_double(&prompt);

  prompt = "Please enter the cost per tile\n";
  std::ostringstream ss;
  ss << "Please enter the cost per tile without decimal:\n";
  ss << "(Example: enter $1.00 as 100, $5 as 500, etc): ";
  prompt = ss.str();
  tile_cost = get_positive_long(&prompt);

  prompt = "Please enter extra tiles beyond estimate, or 0";
  extra_tiles = get_positive_long(&prompt);

  prompt = "Do you want to split tiles into multiple subtiles";
  reuse_subtiles = get_bool(&prompt);
  
  try {
    TileEstimator te(area_w, area_h, tile_w, tile_h, tile_cost, extra_tiles,
        reuse_subtiles);
    te.calculate();
    std::cout << te.get_report();
  } catch (std::invalid_argument) {
    std::cout << "One of the inputs was invalid. Please try again.\n";
  }

  return 0;
}

