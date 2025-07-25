#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "controller/controller.h"
#include "gameModel/game.h"
#include "gameModel/player.h"
#include "narrator.h"
#include "view/display.h"
#include "view/graphicsdisplay.h"
#include "view/textdisplay.h"
#include "view/viewer.h"
#include "./argexception.h"
#include "./utils.h"

using namespace std;

const string DEFAULT_DECK_PATH = "../sorcery-asciiart/default.deck";
const int DEFAULT_PLAYER_LIFE = 20;
const int DEFAULT_PLAYER_MAGIC = 3;
const int MAX_CARDS_IN_HAND = 5;

int main(int argc, char **argv) {
    cout << "Starting game... Welcome to Sorcery!" << endl;

    string deck1FilePath;
    string deck2FilePath;
    string initFile;
    bool graphicsEnabled = false;
    bool testingEnabled = false;
    bool narrateEnabled = false;
    bool delayEnabled = false;

    // =================== Argument parsing ===================================

    for (int i = 1; i < argc; i++) {
        string curArg = argv[i];

        if (curArg == "-deck1") {
            ++i;
            if (i >= argc) {
                cerr << "Invalid deck1 specified!" << endl;
                return 1;
            }
            deck1FilePath = argv[i];
            cout << "DEBUG: received - " << deck1FilePath << endl;
        } else if (curArg == "-deck2") {
            ++i;
            if (i >= argc) {
                cerr << "Invalid deck2 specified!" << endl;
                return 1;
            }
            deck2FilePath = argv[i];
            cout << "DEBUG: received - " << deck2FilePath << endl;
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
            cout << "DEBUG: Testing Enabled." << endl;
        } else if (curArg == "-graphics") {
            graphicsEnabled = true;
            cout << "DEBUG: Graphics Enabled." << endl;
        } else if (curArg == "-narrate") {
            narrateEnabled = true;
            cout << "DEBUG: Narrator Enabled." << endl;
        } else if (curArg == "-delay") {
            delayEnabled = true;
            
            cout << "DEBUG: Text Delay Enabled." << endl;
        } else {
            cerr << "Invalid argument " << curArg << "." << endl;
            return 1;
        }
    }

    Narrator::setEnabled(narrateEnabled);
    Narrator::setDelayed(delayEnabled);

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

        Narrator::printLine();
        Narrator::announce("Two warriors have entered the arena: '" + player1Name + "' and '" + player2Name + "'.");
    } else {  // Init is provided - prompt users.
        cout << "Please enter the name of Player 1: " << endl;
        getline(cin, player1Name);
        cout << "Please enter the name of Player 2: " << endl;
        getline(cin, player2Name);
        Narrator::printLine();
        Narrator::announce("The challengers " + player1Name + " and " + player2Name + " prepare for battle.");
    }

    // =============== Initialize game objects ================================

    auto p1 = make_shared<Player>(player1Name, DEFAULT_PLAYER_LIFE, DEFAULT_PLAYER_MAGIC);
    auto p2 = make_shared<Player>(player2Name, DEFAULT_PLAYER_LIFE, DEFAULT_PLAYER_MAGIC);

    vector<shared_ptr<Player>> players;
    players.emplace_back(move(p1));  // transfer ownership
    players.emplace_back(move(p2));

    auto game = make_shared<Game>(move(players));

    auto deck1 = make_shared<Deck>(0);
    auto deck2 = make_shared<Deck>(1);

    ifstream deck1File;
    ifstream deck2File;
    if (deck1FilePath.empty()) {
        deck1File.open(DEFAULT_DECK_PATH);
    } else {
        deck1File.open(deck1FilePath);
    }
    if (deck2FilePath.empty()) {
        deck2File.open(DEFAULT_DECK_PATH);
    } else {
        deck2File.open(deck2FilePath);
    }
    deck1->loadDeck(deck1File, game.get());
    deck2->loadDeck(deck2File, game.get());

    game->getPlayer(0)->setDeck(deck1);
    game->getPlayer(1)->setDeck(deck2);

    if (!testingEnabled) {
        game->getPlayer(0)->shuffleDeck();
        game->getPlayer(1)->shuffleDeck();
        Narrator::announce("The decks are shuffled, fate now decides the order of battle.");
    }

    // Starting Hand: Draw 5 cards for both players.
    for (int i = 0; i < MAX_CARDS_IN_HAND; ++i) {
        game->getPlayer(0)->drawCard();
        game->getPlayer(1)->drawCard();
    }
    game->setActivePlayer(0);

    Narrator::announce("Both warriors draw their opening hands - " + to_string(MAX_CARDS_IN_HAND) + " cards each.");
    Narrator::announce("The arena is set. Let the battle commence!");
    Narrator::announce("Tip: For a list of commands, type 'help'.");

    // ========== Initialize MVC ===========

    auto textDisplay = make_shared<TextDisplay>(cout, delayEnabled);
    vector<shared_ptr<sorcDisplay>> displays;
    displays.emplace_back(textDisplay);
    if (graphicsEnabled) {
        try {
            auto graphicsDisplay = make_shared<GraphicsDisplay>();
            displays.emplace_back(graphicsDisplay);
            graphicsDisplay->printBoard(game.get());
        } catch(...) {
            cerr << "Unable to create XWindow." << endl;
            cerr << "Please setup XWindow before enabling graphics on next execution." << endl;
        }
    }
    auto viewer = make_shared<Viewer>(displays, game.get());

    auto controller = make_unique<Controller>(game.get(), viewer);

    // ================== Game Loop ==================

    while (game->getWinner() == -1) {
        string command;
        if ((init && getline(init, command)) || getline(cin, command)) {
            if (command.empty()) continue;
        } else {
            break;
        }
        if (command == "help") {
            controller->help();
        } else if (command == "end") {
            controller->end();
        } else if (command == "quit") {
            Narrator::announce("The battle ends as both warriors retreat... Play again next time!");
            return 0;
        } else if (command == "draw") {
            if (!testingEnabled) {
                Narrator::announce("Manual draw is available only in testing mode.");
                continue;
            }
            controller->draw();
        } else if (command.substr(0, 7) == "discard") {
            if (!testingEnabled) {
                Narrator::announce("Discarding is available only in testing mode.");
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
                int card;
                if (!parseInt(tokens[1], card)) continue;
                if (!controller->discard(card - 1)) break;
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
                int attackingMinion;
                if (!parseInt(tokens[1], attackingMinion)) continue;
                if (!controller->attack(attackingMinion - 1)) {
                    cerr << "The attack fails - invalid command provided." << endl;
                    continue;
                }
            } else if (args == 2) {
                int attackingMinion;
                if (!parseInt(tokens[1], attackingMinion)) continue;
                int receivingMinion;
                if (!parseInt(tokens[2], receivingMinion)) continue;
                if (!controller->attack(attackingMinion - 1, receivingMinion - 1)) {
                    cerr << "The attack fails - invalid command provided." << endl;
                    continue;
                }
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
                int card;
                if (!parseInt(tokens[1], card)) continue;
                if (!controller->play(card - 1, testingEnabled)) {
                    // cerr << "DEBUG: (Main) Invalid command provided to controller." << endl;
                    continue;
                }
            } else if (args == 3) {
                int card;
                if (!parseInt(tokens[1], card)) continue;
                int player;
                if (!parseInt(tokens[2], player)) continue;
                int minion;
                if (tokens[3] == "r") {
                    minion = 0;
                } else {
                    if (!parseInt(tokens[3], minion)) continue;
                }
                if (!controller->play(card - 1, player - 1, minion - 1, testingEnabled)) {
                    // cerr << "DEBUG: (Main) Invalid command provided to controller." << endl;
                    continue;
                }
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
                int minion;
                if (!parseInt(tokens[1], minion)) continue;
                if (!controller->use(minion - 1, testingEnabled)) {
                    // cerr << "DEBUG: (Main) Invalid command provided to controller." << endl;
                    continue;
                }
            } else if (args == 3) {
                int activeMinion;
                int player;
                int receivingMinion;
                if (!parseInt(tokens[1], activeMinion)) continue;
                if (!parseInt(tokens[2], player)) continue;
                if (!parseInt(tokens[3], receivingMinion)) continue;
                if (!controller->use(activeMinion - 1, player - 1, receivingMinion - 1, testingEnabled)) {
                    // cerr << "DEBUG: (Main) Invalid command provided to controller." << endl;
                    continue;
                }
            } else {
                cerr << "Invalid input: Received " << args << " arguments. Please use either 1 or 3." << endl;
                continue;
            }
        } else if (command.substr(0, 7) == "inspect") {
            stringstream cmd{command};
            string token;
            vector<string> tokens;

            while (cmd >> token) {
                tokens.emplace_back(token);
            }
            int args = tokens.size() - 1;
            if (args == 1) {
                int card;
                if (!parseInt(tokens[1], card)) continue;
                try {
                    controller->describe(card - 1);
                }
                catch (ArgException& e) {
                    cerr << e.what() << endl;
                }
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
    string loser = game->getPlayer((game->getWinner() + 1) % 2)->getName();
    string winner = game->getPlayer(game->getWinner())->getName();

    Narrator::announce("The final blow has been struck!");
    Narrator::announce(loser + " falls to their knees, defeated.");
    Narrator::announce("Victory belongs to " + winner + "!");
}
