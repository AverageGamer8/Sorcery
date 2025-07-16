#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <vector>

#include "game.h"
#include "viewer.h"

class Controller {
  std::shared_ptr<Game> game;
  std::shared_ptr<Viewer> viewer;

public:
  Controller(std::shared_ptr<Game> game, std::shared_ptr<Viewer> viewer);

  void run();
  void drawCard();

  void help();
  void end();
};

#endif