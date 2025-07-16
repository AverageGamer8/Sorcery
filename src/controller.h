#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <vector>

#include "game.h"

class Controller {
  std::unique_ptr<Game> game;
  std::vector<std::unique_ptr<Viewer>> viewer;

public:
  Controller(unique_ptr<Game> game, unique_ptr<Viewer> viewer);
};

#endif