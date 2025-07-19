#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "concreteability.h"  // TEMPORARY FOR TESTING
#include "controller/controller.h"
#include "gameModel/game.h"
#include "gameModel/player.h"
#include "view/display.h"
#include "view/textdisplay.h"
#include "view/viewer.h"

using namespace std;

const string DEFAULT_DECK_PATH = "../sorcery-asciiart/default.deck";

int main(int argc, char **argv) {
    cout << "Starting game... Welcome to Sorcery!" << endl;

    string deck1File;
    string deck2File;
    string initFile;
    bool graphicsEnabled;
    bool testingEnabled;

    // =================== Argument parsing ===================================

    for (int i = 1; i < argc; i++) {
        string curArg = argv[i];
        // cout << curArg << endl;

        if (curArg == "-deck1") {
            ++i;
            if (i >= argc) {
                cerr << "Invalid deck1 specified!" << endl;
                return 1;
            }
            deck1File = argv[i];
            cout << "DEBUG: received - " << deck1File << endl;
        } else if (curArg == "-deck2") {
            ++i;
            if (i >= argc) {
                cerr << "Invalid deck2 specified!" << endl;
                return 1;
            }
            deck2File = argv[i];
            cout << "DEBUG: received - " << deck2File << endl;
        } else if (curArg == "-init") {
            ++i;
            if (i >= argc) {
                cerr << "Invalid init specified!" << endl;
                return 1;
            }
            initFile = argv[i];
            cout << "DEBUG: initFile received - " << initFile << endl;
        } else if (curArg == "-testing") {
            testingEnabled = true;
            cout << "DEBUG: testingEnabled received - " << testingEnabled << endl;
        } else if (curArg == "-graphics") {
            graphicsEnabled = true;
            cout << "DEBUG: graphics received - " << graphicsEnabled << endl;
        } else {
            cerr << "Invalid argument " << curArg << "." << endl;
            return 1;
        }
    }

    // ====================== Read Files =========================================

    // Get player names:
    string player1Name, player2Name;
    ifstream init;
    if (!initFile.empty()) {
        init.open(initFile);

        if (!init) {
            cerr << "Invalid file path for init: unable to open file."
                 << endl;
            return 1;
        }

        if (!getline(init, player1Name)) {
            cerr << "Invalid player1 name." << endl;
            return 1;
        }
        if (!getline(init, player2Name)) {
            cerr << "Invalid player2 name." << endl;
            return 1;
        }

        cout << "DEBUG: received - player1: " << player1Name
             << ", player2: " << player2Name << endl;
    } else {  // Init is provided - prompt users.
        
        cout << "Please enter name of Player 1: ";
        cin >> player1Name;
        cout << "Please enter name of Player 2: ";
        cin >> player2Name;
    }

    // =============== Initialize game objects ================================

    auto p1 = make_unique<Player>(player1Name, 0, 0);
    auto p2 = make_unique<Player>(player2Name, 0, 0);

    vector<unique_ptr<Player>> players;
    players.emplace_back(move(p1));  // transfer ownership
    players.emplace_back(move(p2));

    auto deck1 = make_shared<Deck>(0);
    auto deck2 = make_shared<Deck>(1);

    ifstream defaultDeck1{DEFAULT_DECK_PATH};
    ifstream defaultDeck2{DEFAULT_DECK_PATH};
    deck1->loadDeck(defaultDeck1);
    deck2->loadDeck(defaultDeck2);

    players[0]->setDeck(deck1);
    players[1]->setDeck(deck2);

    if (!testingEnabled) {
        players[0]->shuffleDeck();
        players[1]->shuffleDeck();
    }

    auto game = make_shared<Game>(move(players));

    // output it
    cout << "DEBUG: (Main) Init - player1: " << game->getPlayer(0)->getName() << endl;
    cout << "DEBUG: (Main) Init - player2: " << game->getPlayer(1)->getName() << endl;

    // ========== Initialize MVC ===========

    auto textDisplay = make_shared<TextDisplay>(cout);
    vector<shared_ptr<Display>> displays;  // TODO: expand this once graphics are implemented
    displays.emplace_back(textDisplay);    // for now, just text.
    auto viewer = make_shared<Viewer>(displays, game);

    auto controller = make_unique<Controller>(game, viewer);

    // ============= DEBUG: using the triggers example =============

    // ConcreteAbility is an example class to use it.
    // this stuff should probably be done in the cards.
    game->setActivePlayer(0);
    auto ta = make_shared<ConcreteAbility>(game.get(), 0);

    // attaching the trigger to START TURN events
    game->getTrigger(Trigger::TriggerType::TurnStart).attach(ta);

    game->startTurn();  // activates here
    game->endTurn();
    game->startTurn();  // activates here

    // ================== Game Loop ==================

    while (game->getWinner() == -1) {
        string command;
        if (init) {
            if (!getline(init, command)) {  // First, get commands from initFile, if any.
                getline(cin, command);
            }
        } else {
            getline(cin, command);
        }
        cout << "DEBUG: received command: " << command << endl;
        if (command == "help") {
            controller->help();
        } else if (command == "end") {
            controller->end();
        } else if (command == "quit") {
            cout << "Exiting the program..." << endl;
            return 0;
        } else if (command == "draw") {
            if (!testingEnabled) {
                cout << "Invalid input: Testing Mode is not enabled." << endl;
                continue;
            }
            controller->draw();
        } else if (command.substr(0, 7) == "discard") {
            if (!testingEnabled) {
                cout << "Invalid input: Testing Mode is not enabled." << endl;
                continue;
            }

            stringstream cmd{command};
            string token;
            vector<string> tokens;

            while (cmd >> token) {  // Reading in all the args
                tokens.emplace_back(token);
            }
            int args = tokens.size() - 1;
            if (args == 1) {
                int card = stoi(tokens[1]);
                controller->discard(card);
            } else {
                cerr << "Invalid input: Received " << args << " arguments. Please use 1." << endl;
                continue;
            }
        } else if (command.substr(0, 6) == "attack") {
            stringstream cmd{command};
            string token;
            vector<string> tokens;

            while (cmd >> token) {
                tokens.emplace_back(token);
            }
            int args = tokens.size() - 1;
            if (args == 1) {
                int attackingMinion = stoi(tokens[1]);
                controller->attack(attackingMinion);
            } else if (args == 2) {
                int attackingMinion = stoi(tokens[1]);
                int receivingMinion = stoi(tokens[2]);
                controller->attack(attackingMinion, receivingMinion);
            } else {
                cerr << "Invalid input: Received " << args << " arguments. Please use either 1 or 2." << endl;
                continue;
            }
        } else if (command.substr(0, 4) == "play") {
            stringstream cmd{command};
            string token;
            vector<string> tokens;

            while (cmd >> token) {
                tokens.emplace_back(token);
            }
            int args = tokens.size() - 1;
            if (args == 1) {
                int card = stoi(tokens[1]);
                controller->play(card);
            } else if (args == 3) {
                int card = stoi(tokens[1]);
                int player = stoi(tokens[2]);
                int minion = stoi(tokens[3]);
                // cout << "DEBUG: card " << card << ", player: " << player << ", minion " << minion << endl;
                controller->play(card, player, minion);
            } else {
                cerr << "Invalid input: Received " << args << " arguments. Please use either 1 or 3." << endl;
                continue;
            }
        } else if (command.substr(0, 3) == "use") {
            stringstream cmd{command};
            string token;
            vector<string> tokens;

            while (cmd >> token) {
                tokens.emplace_back(token);
            }
            int args = tokens.size() - 1;
            if (args == 1) {
                int minion = stoi(tokens[1]);
                controller->use(minion);
            } else if (args == 3) {
                int activeMinion = stoi(tokens[1]);
                int player = stoi(tokens[2]);
                int receivingMinion = stoi(tokens[3]);
                controller->use(activeMinion, player, receivingMinion);
            } else {
                cerr << "Invalid input: Received " << args << " arguments. Please use either 1 or 3." << endl;
                continue;
            }
        } else if (command.substr(0, 8) == "describe") {
            stringstream cmd{command};
            string token;
            vector<string> tokens;

            while (cmd >> token) {
                tokens.emplace_back(token);
            }
            int args = tokens.size() - 1;
            if (args == 1) {
                int card = stoi(tokens[1]);
                controller->describe(card);
            } else {
                cerr << "Invalid input: Received " << args << " arguments. Please use 1." << endl;
                continue;
            }
        } else if (command == "hand") {
            controller->hand();
        } else if (command == "board") {
            controller->board();
        } else {
            cerr << "Invalid input: Command not recognised!" << endl;
            continue;
        }
    }
}
