// card.h
// Author: Yusen Liu
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

using namespace std;

class Card {
private:
    char suit;      // 'c', 'd', 's', 'h'
    string value;   // "a", "2", ..., "10", "j", "q", "k"
    
    // Helper function to convert value to numeric rank for comparison
    int getValueRank() const;
    
public:
    // Constructors
    Card();
    Card(char s, const string& v);
    
    // Comparison operators
    bool operator<(const Card& other) const;
    bool operator>(const Card& other) const;
    bool operator==(const Card& other) const;
    bool operator<=(const Card& other) const;
    bool operator>=(const Card& other) const;
    bool operator!=(const Card& other) const;
    
    // Input/Output operators
    friend ostream& operator<<(ostream& os, const Card& card);
    friend istream& operator>>(istream& is, Card& card);
    
    // Getters
    char getSuit() const;
    string getValue() const;
};

#endif
