#ifndef GRID_NODE_ARRAY_H_
#define GRID_NODE_ARRAY_H_

#include <string>
#include <sstream>
#include "grid_node.h"

using namespace std;
using Coord = pair<int,int>;

// This is used to hold grid nodes for quick indexing.
template<typename CostType>
class GridNodeArray {
public:
  GridNodeArray(int w, int h):w_(w), h_(h) {
    reset();
  }

  ~GridNodeArray() {
    if (array_ != nullptr)
      delete array_;
  }

public:
  int w_ = 0;
  int h_ = 0;

public:
  void reset() {
    if (array_ != nullptr) {
      delete array_;
      array_ = nullptr;
    }
    array_ = new GridNode<CostType>[h_*w_];
    for (int i=0; i < h_; i++) {
      for (int j=0; j < w_; j++) {
          node(Coord(j, i))->x(j);
          node(Coord(j, i))->y(i);
      }
    }
  }

  GridNode<CostType> *node(Coord coord) const{
    return &array_[coord.second * w_ + coord.first];
  }

  bool off(Coord coord) const {
    if (coord.first < 0 || coord.first >= w_ ||
        coord.second < 0 || coord.second >= h_)
      return true;
    else
      return false;
  }



private:
  GridNode<CostType> *array_ {nullptr};

};


#endif /* GRID_NODE_ARRAY_H_ */
