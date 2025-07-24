#include "textdisplay.h"
#include <algorithm>

#include "../cards/spell.h"
using namespace std;

const int MAX_ACTIVE_MINIONS = 5;
const int HORIZONTAL_LINE_WIDTH = 165;
const int printDelayMs = 30;

TextDisplay::TextDisplay(ostream& out, bool enablePrintDelay)
    : out{out}, enablePrintDelay{enablePrintDelay} {}

void TextDisplay::printCardTemplate(const card_template_t& cardInfo) {
    for (int i = 0; i < cardInfo.size(); ++i) {
        out << cardInfo[i];
        if (i < cardInfo.size() - 1) {
            out << endl;
            if (enablePrintDelay) {
                std::this_thread::sleep_for(std::chrono::milliseconds(printDelayMs));
            }
        }
    }
}

void TextDisplay::printHelp() {
    out << "Commands:\n\t"
        << "help -- Display this message,\n\t"
        << "end -- End the current player's turn,\n\t"
        << "quit -- End the game,\n\t"
        << "attack minion other-minion -- Orders minion to attack other-minion,\n\t"
        << "attack minion -- Orders minion to attack the opponent,\n\t"
        << "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player,\n\t"
        << "use minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player,\n\t"
        << "inspect minion -- View a minion's card and all enchantments on that minion,\n\t"
        << "hand -- Describe all cards in your hand,\n\t"
        << "board -- Describe all cards on the board."
        << endl;
}
void TextDisplay::printDescribe(Game* game, int minion) {
    auto player = game->getActivePlayer();
    auto minionCard = player->getBoard()->getMinion(minion);
    vector<card_template_t> enchs;
    printCardTemplate(getMinionInfo(minionCard)); out << endl;
    while (minionCard->getType() == "Enchantment") {
        auto ench = static_pointer_cast<Enchantment>(minionCard);
        enchs.emplace_back(getEnchantmentInfo(ench));
        minionCard = ench->getMinion();
    }
    if (!enchs.empty()) {
        reverse(enchs.begin(), enchs.end());
        printTemplatesRow(enchs);
    }
}

void TextDisplay::printHand(Game* game) {
    auto player = game->getActivePlayer();
    auto hand = player->getHand();

    vector<card_template_t> cardTemplates;
    for (int i = 0; i < hand->getSize(); ++i) {
        auto card = hand->getCardAtIndex(i);
        if (!card) {
            cerr << "DEBUG: (TextDisplay) Hand: no card at index." << endl;
            return;
        }
        card_template_t cardInfo = getCardInfo(card);
        cardTemplates.emplace_back(cardInfo);
    }
    printTemplatesRow(cardTemplates);
}

card_template_t TextDisplay::getMinionInfo(shared_ptr<Minion> minion) const {
    auto triggeredAbility = minion->getTriggeredAbility();
    auto activatedAbility = minion->getActivatedAbility();
    if (triggeredAbility) {
        return display_minion_triggered_ability(
            minion->getName(),
            minion->getCost(),
            minion->getAttack(),
            minion->getDefence(),
            triggeredAbility->getDesc());
    } else if (activatedAbility) {
        return display_minion_activated_ability(
            minion->getName(),
            minion->getCost(),
            minion->getAttack(),
            minion->getDefence(),
            minion->getActivateCost(),
            activatedAbility->getDesc());
    } else {
        return display_minion_no_ability(
            minion->getName(),
            minion->getCost(),
            minion->getAttack(),
            minion->getDefence());
    }
}

card_template_t TextDisplay::getEnchantmentInfo(shared_ptr<Enchantment> ench) const {
    if (ench->getAtkDesc().empty() || ench->getDefDesc().empty()) {
        return display_enchantment(
            ench->getEnchName(),
            ench->getEnchCost(),
            ench->getEnchDesc());
    } else {
        return display_enchantment_attack_defence(
            ench->getEnchName(),
            ench->getEnchCost(),
            ench->getEnchDesc(),
            ench->getAtkDesc(),
            ench->getDefDesc());
    }
}

card_template_t TextDisplay::getRitualInfo(shared_ptr<Ritual> ritual) const {
    return display_ritual(
            ritual->getName(),
            ritual->getCost(),
            ritual->getActivationCost(),
            ritual->getDesc(),
            ritual->getCharges());
}

card_template_t TextDisplay::getSpellInfo(shared_ptr<Spell> spell) const {
    return display_spell(
            spell->getName(),
            spell->getCost(),
            spell->getDesc());
}

card_template_t TextDisplay::getCardInfo(shared_ptr<Card> card) const {
    if (card->getType() == "Minion") return getMinionInfo(static_pointer_cast<Minion>(card));
    else if (card->getType() == "Spell") return getSpellInfo(static_pointer_cast<Spell>(card));
    else if (card->getType() == "Ritual") return getRitualInfo(static_pointer_cast<Ritual>(card));   
    else if (card->getType() == "Enchantment") return getEnchantmentInfo(static_pointer_cast<Enchantment>(card));
    else {
        return CARD_TEMPLATE_BORDER;
    }
}
void TextDisplay::printTemplatesRow(vector<card_template_t> cardTemplates) const {
    if (cardTemplates.empty()) {
        cerr << "DEBUG: TextDisplay: empty template given to print" << endl;  // todo exception
        return;
    }
    int height = cardTemplates[0].size();  // NOTE: take first element of templates vector as height of card!
    // assumes all card have same or greater height.
    for (int line = 0; line < height; ++line) {
        for (int card = 0; card < cardTemplates.size(); ++card) {
            out << cardTemplates[card][line];
        }
        if (line < height - 1) {
            out << endl;
            if (enablePrintDelay) {
                std::this_thread::sleep_for(std::chrono::milliseconds(printDelayMs));
            }
        }
    }
    cout << endl;
}

vector<card_template_t> TextDisplay::getBoardMinionsRow(shared_ptr<Player> player) {
    vector<card_template_t> cardTemplates;

    auto board = player->getBoard();
    int numMinions = board->getMinions().size();
    for (int i = 0; i < numMinions; ++i) {
        auto minion = board->getMinion(i);
        card_template_t cardInfo = getMinionInfo(minion);
        cardTemplates.emplace_back(cardInfo);
    }
    for (int i = 0; i < MAX_ACTIVE_MINIONS - numMinions; ++i) {
        cardTemplates.emplace_back(CARD_TEMPLATE_BORDER);
    }
    return cardTemplates;
}

vector<card_template_t> TextDisplay::getBoardPlayerRow(shared_ptr<Player> player) {
    vector<card_template_t> cardTemplates;
    if (player->hasRitual()) {
        auto ritual = player->getBoard()->getRitual();
        card_template_t ritualInfo = getCardInfo(static_pointer_cast<Card>(ritual));
        cardTemplates.emplace_back(ritualInfo);
    } else {
        cardTemplates.emplace_back(CARD_TEMPLATE_BORDER);
    }
    cardTemplates.emplace_back(CARD_TEMPLATE_EMPTY);
    card_template_t player1Info = display_player_card(
        0,
        player->getName(),
        player->getLife(),
        player->getMagic());
    cardTemplates.emplace_back(player1Info);
    cardTemplates.emplace_back(CARD_TEMPLATE_EMPTY);
    if (!player->isGraveyardEmpty()) {
        auto minion = player->getGraveyard()->getTopMinion();
        card_template_t graveyardInfo = getCardInfo(static_pointer_cast<Card>(minion));
        cardTemplates.emplace_back(graveyardInfo);
    } else {
        cardTemplates.emplace_back(CARD_TEMPLATE_BORDER);
    }
    return cardTemplates;
}

void TextDisplay::printHorizontalBorder() const {
    for (int i = 0; i < HORIZONTAL_LINE_WIDTH; i++) {
        cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
}

card_template_t TextDisplay::buildVerticalCardBorder() const {
    card_template_t col;
    int cardHeight = CARD_TEMPLATE_EMPTY.size();
    for (int i = 0; i < cardHeight; i++) {
        col.emplace_back(EXTERNAL_BORDER_CHAR_UP_DOWN);
    }
    return col;
}
void TextDisplay::printBoard(Game* game) {
    cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
    printHorizontalBorder();
    cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT;
    cout << endl;

    card_template_t verticalBorder = buildVerticalCardBorder();

    auto player1 = game->getPlayer(0);
    auto player2 = game->getPlayer(1);
    vector<card_template_t> row1Templates = getBoardPlayerRow(player1);
    vector<card_template_t> row2Templates = getBoardMinionsRow(player1);
    vector<card_template_t> row3Templates = getBoardMinionsRow(player2);
    vector<card_template_t> row4Templates = getBoardPlayerRow(player2);
    row1Templates.insert(row1Templates.begin(), verticalBorder);
    row1Templates.emplace_back(verticalBorder);
    row2Templates.insert(row2Templates.begin(), verticalBorder);
    row2Templates.emplace_back(verticalBorder);
    row3Templates.insert(row3Templates.begin(), verticalBorder);
    row3Templates.emplace_back(verticalBorder);
    row4Templates.insert(row4Templates.begin(), verticalBorder);
    row4Templates.emplace_back(verticalBorder);

    printTemplatesRow(row1Templates);
    printTemplatesRow(row2Templates);
    printCardTemplate(CENTRE_GRAPHIC);
    cout << endl;
    printTemplatesRow(row3Templates);
    printTemplatesRow(row4Templates);

    cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
    printHorizontalBorder();
    cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT;
    cout << endl;
}