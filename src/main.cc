#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "concreteability.h" // TEMPORARY FOR TESTING
#include "controller.h"
#include "display.h"
#include "game.h"
#include "player.h"
#include "textdisplay.h"
#include "viewer.h"

int main(int argc, char **argv) {
  std::cout << "start!" << std::endl;

  std::string deck1File;
  std::string deck2File;
  std::string initFile;
  bool enableGraphics;
  bool enableTesting;

  // =================== Argument parsing ===================================

  for (int i = 1; i < argc; i++) {
    std::string curArg = argv[i];
    std::cout << curArg << std::endl;

    if (curArg == "-deck1") {
      ++i;
      if (i >= argc) {
        std::cerr << "Invalid deck1 specified!" << std::endl;
        return 1;
      }
      deck1File = argv[i];
      std::cout << "DEBUG: received - " << deck1File << std::endl;
    } else if (curArg == "-deck2") {
      ++i;
      if (i >= argc) {
        std::cerr << "Invalid deck2 specified!" << std::endl;
        return 1;
      }
      deck2File = argv[i];
      std::cout << "DEBUG: received - " << deck2File << std::endl;
    } else if (curArg == "-init") {
      ++i;
      if (i >= argc) {
        std::cerr << "Invalid init specified!" << std::endl;
        return 1;
      }
      initFile = argv[i];
      std::cout << "DEBUG: received - " << initFile << std::endl;
    } else if (curArg == "-testing") {
      enableTesting = true;
      std::cout << "DEBUG: received - " << enableTesting << std::endl;
    } else if (curArg == "-graphics") {
      enableGraphics = true;
      std::cout << "DEBUG: received - " << enableGraphics << std::endl;
    } else {
      std::cerr << "Invalid argument " << curArg << "." << std::endl;
      return 1;
    }
  }

  // ====================== Read Files =========================================

  std::ifstream init{initFile};
  std::string player1, player2;

  if (!init) {
    std::cerr << "Invalid file path for init: unable to open file."
              << std::endl;
    return 1;
  }

  if (!std::getline(init, player1)) {
    std::cerr << "Invalid player1 name." << std::endl;
    return 1;
  }
  if (!std::getline(init, player2)) {
    std::cerr << "Invalid player2 name." << std::endl;
    return 1;
  }

  std::cout << "DEBUG: received - player1: " << player1
            << ", player2: " << player2 << std::endl;

  // =============== Initialize game objects ================================

  auto p1 = std::make_unique<Player>(player1, 0, 0);
  auto p2 = std::make_unique<Player>(player2, 0, 0);

  std::vector<std::unique_ptr<Player>> players;
  players.emplace_back(std::move(p1)); // transfer ownership
  players.emplace_back(std::move(p2));

  auto game = std::make_shared<Game>(std::move(players));

  // output it
  std::cout << "Init - player1: " << game->getPlayer(0)->getName() << std::endl;
  std::cout << "Init - player2: " << game->getPlayer(1)->getName() << std::endl;

  // ========== Initialize MVC ===========

  auto textDisplay = std::make_shared<TextDisplay>(std::cout);
  std::vector<std::shared_ptr<Display>>
      displays; // TODO: expand this once graphics are implemented
  displays.emplace_back(textDisplay); // for now, just text.
  auto viewer = std::make_shared<Viewer>(displays, game);

  auto controller = std::make_unique<Controller>(game, viewer);

  // ============= DEBUG: using the triggers example =============

  // ConcreteAbility is an example class to use it.
  // this stuff should probably be done in the cards.
  game->setActivePlayer(0);
  auto ta = std::make_shared<ConcreteAbility>(game.get(), 0);

  // attaching the trigger to START TURN events
  game->getTrigger(Trigger::TriggerType::TurnStart).attach(ta);

  game->startTurn(); // activates here
  game->endTurn();
  game->startTurn(); // activates here
  // ================== Game ==================

  while (game->getWinner() == -1) {
    std::string command;
    getline(std::cin, command);

    if (command == "help") {
      controller->help();
    } else if (command == "end") {

    } else if (command == "quit") {
      std::cout << "Exiting the program..." << std::endl;
      return 0;
    } else if (command == "draw") {

    } else if (command == "discard") {

    } else if (command == "attack") {

    } else if (command == "play") {

    } else if (command == "use") {

    } else if (command == "describe") {

    } else if (command == "hand") {

    } else if (command == "board") {

    } else {
      std::cerr << "Invalid input!" << std::endl;
    }
  }
}
