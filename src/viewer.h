#ifndef VIEWER_H
#define VIEWER_H

#include "display.h"
#include "game.h"
#include <memory>
#include <vector>

class Viewer {
  std::vector<std::unique_ptr<Display>> displays;
  std::shared_ptr<Game> game;

public:
    void display();
};

#endif
