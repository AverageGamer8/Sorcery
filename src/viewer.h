#ifndef VIEWER_H
#define VIEWER_H

#include "display.h"
#include "game.h"
#include <memory>
#include <vector>

class Viewer {
  std::vector<std::shared_ptr<Display>> displays;
  std::shared_ptr<Game> game;

public:
  enum Command { // TODO: Add more enums with more controller commands
    PRINT,
    HELP
  };
  Viewer(std::vector<std::shared_ptr<Display>> displays,
         std::shared_ptr<Game> game);
  void display(Command command);
};

#endif
