// card.cpp
// Author: Yusen Liu
// Implementation of the classes defined in card.h

#include "card.h"

// Helper function to convert value string to numeric rank for comparison
int Card::getValueRank() const {
    if (value == "a") return 1;
    else if (value == "j") return 11;
    else if (value == "q") return 12;
    else if (value == "k") return 13;
    else {
        // Handle numeric values 2-10
        return stoi(value);
    }
}

// Default constructor
Card::Card() : suit(' '), value("") {}

// Constructor with suit and value
Card::Card(char s, const string& v) : suit(s), value(v) {}

// Get suit rank for comparison (c=0, d=1, s=2, h=3)
static int getSuitRank(char suit) {
    switch(suit) {
        case 'c': return 0;
        case 'd': return 1;
        case 's': return 2;
        case 'h': return 3;
        default: return -1;
    }
}

// Less than operator
bool Card::operator<(const Card& other) const {
    int thisSuitRank = getSuitRank(suit);
    int otherSuitRank = getSuitRank(other.suit);
    
    if (thisSuitRank != otherSuitRank) {
        return thisSuitRank < otherSuitRank;
    }
    
    // Same suit, compare by value
    return getValueRank() < other.getValueRank();
}

// Greater than operator
bool Card::operator>(const Card& other) const {
    return other < *this;
}

// Equal operator
bool Card::operator==(const Card& other) const {
    return suit == other.suit && value == other.value;
}

// Less than or equal operator
bool Card::operator<=(const Card& other) const {
    return *this < other || *this == other;
}

// Greater than or equal operator
bool Card::operator>=(const Card& other) const {
    return *this > other || *this == other;
}

// Not equal operator
bool Card::operator!=(const Card& other) const {
    return !(*this == other);
}

// Output stream operator
ostream& operator<<(ostream& os, const Card& card) {
    os << card.suit << " " << card.value;
    return os;
}

// Input stream operator
istream& operator>>(istream& is, Card& card) {
    is >> card.suit >> card.value;
    return is;
}

// Get suit
char Card::getSuit() const {
    return suit;
}

// Get value
string Card::getValue() const {
    return value;
}
