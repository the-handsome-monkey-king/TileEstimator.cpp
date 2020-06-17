/*********************************
*
*  TileEstimator.cpp
*
*  @author Ryan Morehouse
*  @license MIT
*
*  A class to containa tile cost estimation system.
*
  **********************************/

#include <stdexcept>
#include <math.h>
#include <string>
#include <sstream>
#include "TileEstimator.h"

TileEstimator::TileEstimator( 
    double area_w, double area_h, double tile_w, double tile_h,
    long tile_cost, long extra_tiles, bool reuse_subtiles)
{
  // validate
  if(area_w <= 0 || area_h <= 0 || tile_w <= 0 || tile_h <=0)
    throw std::invalid_argument("Invalid area and tile measurements.");
  if(tile_cost <= 0)
    throw std::invalid_argument("Invalid tile cost.");
  if(extra_tiles < 0)
    throw std::invalid_argument("Invalid extra tiles count.");

  this->area_w = area_w;
  this->area_h = area_h;
  this->tile_w = tile_w;
  this->tile_h = tile_h;
  this->tile_cost = tile_cost;
  this->extra_tiles = extra_tiles;
  this->reuse_subtiles = reuse_subtiles;

  this->h_tile_count = 0;
  this->w_tile_count = 0;
  this->tile_count = 0;
  this->total_cost = 0;
}

void TileEstimator::calculate() {
  this->count_all_tiles();
  this->calculate_cost();
}

void TileEstimator::count_all_tiles() {
  // start with any extra desired tiles
  this->tile_count += this->extra_tiles;

  // count whole tiles required
  this->h_tile_count = static_cast<long>(this->area_h / this->tile_h);
  this->w_tile_count = static_cast<long>(this->area_w / this->tile_w);
  this->tile_count += static_cast<long>(
      this->h_tile_count * this->w_tile_count);

  // if tiles fit snug, stop counting
  if(std::fmod(this->area_w, this->tile_w) == 0 && 
     std::fmod(this->area_h, this->tile_h) == 0) 
  {
    return;
  }

  // otherwise count partial tiles
  this->tile_count += this->count_partial_tiles();
}

long TileEstimator::count_partial_tiles() {
  if(!reuse_subtiles)
    return (this->h_tile_count + this->w_tile_count + 1);

  // otherwise count tiles needed for partial tile use
  long count = 0;

  // reamining width
  double remaining_width = this->area_w;
  remaining_width -= this->tile_w * floor(this->area_w / this->tile_w);
  double tile_divisor = this->tile_w / remaining_width;
  count += static_cast<long>(ceil(this->h_tile_count / tile_divisor));

  // remaining height
  double remaining_height = this->area_h;
  remaining_height -= this->tile_h * floor(this->area_h / this->tile_h);
  tile_divisor = this->tile_h / remaining_height;
  count += static_cast<long>(ceil(this->w_tile_count / tile_divisor));

  // add a corner piece just in case
  count++;
  return count;
}

void TileEstimator::calculate_cost() {
  this->total_cost = this->tile_cost * this->tile_count;
}

long TileEstimator::get_cost() {
  return this->total_cost;
}

long TileEstimator::get_tile_count() {
  return this->tile_count;
}

std::string TileEstimator::get_report() {
  std::ostringstream ss;
  ss << "Tile Count: " << this->tile_count << "\n";
  ss << "Tiles Estimated: " << this->tile_count - this->extra_tiles << "\n";
  ss << "Extra Tiles Specified: " << this->extra_tiles << "\n";
  long dollars = this->total_cost / 100;
  long cents = this->total_cost % 100;
  ss << "Final Cost: $" << dollars << ".";
  if(cents == 0)
    ss << "00\n";
  else
    ss << cents << "\n";
  return ss.str();
}

