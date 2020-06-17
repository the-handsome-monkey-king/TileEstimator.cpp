/***********************
  *
  * tile_estimator.h
  *
  * @author Ryan Morehouse
  * @license MIT
  *
  * A class to contain a tile cost eitmation system.
  *
  ************************/

#ifndef TILEESTIMATOR_H
#define TILEESTIMATOR_H

#include <string>

class TileEstimator {
  private:
    // input args
    double area_w, area_h, tile_w, tile_h;
    long tile_cost, extra_tiles;
    bool reuse_subtiles;
    // calculation values
    long h_tile_count, w_tile_count;
    // output results
    long tile_count;
    long total_cost;

    void count_all_tiles();
    long count_neat_tiles();
    long count_partial_tiles();
    void calculate_cost();

  public:
    TileEstimator(
        double area_w, double area_h, 
        double tile_w, double tile_h,
        long tile_cost, long extra_tiles, 
        bool reuse_subtiles); 

    void calculate();
    long get_cost();
    long get_tile_count();
    std::string get_report();
};

#endif
