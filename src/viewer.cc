#include "viewer.h"

Viewer::Viewer(std::vector<std::shared_ptr<Display>> displays, std::shared_ptr<Game> game) 
    : displays{displays}, game{game} {}

std::vector<std::shared_ptr<Display>> Viewer::getDisplays() { return displays; }