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
    Viewer(std::vector<std::shared_ptr<Display>> displays, std::shared_ptr<Game> game);
    std::vector<std::shared_ptr<Display>> getDisplays();
};

#endif
