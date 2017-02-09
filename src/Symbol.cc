#include "Symbol.h"

#include <sstream>

/*** EPSILON ***/

bool Epsilon::equals(Symbol const& other) const {
    return this == &other;
}
    
std::size_t Epsilon::hash() const {
    return 1;
}

std::string Epsilon::to_string() const {
    return "\\eps";
}

Symbol * Epsilon::clone() const {
    return &(this->get());
}

/*** Bottom ***/

bool Bottom::equals(Symbol const& other) const {
    if (dynamic_cast<Bottom const *> (&other)) {
        return true;
    }
    return false;
}

std::size_t Bottom::hash() const {
    return 2;
}   

std::string Bottom::to_string() const {
    return "\\b_0";
}

Symbol * Bottom::clone() const {
    return new Bottom;
}

/*** Character ***/
    
Character::Character(char c) : c(c) {}   

bool Character::equals(Symbol const& other) const {
    if (Character const *obj = dynamic_cast<Character const *> (&other)) {
        return c == obj->c;
    }
    return false;
}

std::size_t Character::hash() const {
    return std::hash<char>{}(c);
}   

std::string Character::to_string() const {
    return std::string(1, c);
}

Symbol * Character::clone() const {
    return new Character(c);
}

/*** Identifier ***/

Identifier::Identifier(std::string identifier) : identifier(identifier) {}   

bool Identifier::equals(Symbol const& other) const {
    if (Identifier const *obj = dynamic_cast<Identifier const *> (&other)) {
        return identifier == obj->identifier;
    }
    return false;
}

std::size_t Identifier::hash() const {
    return std::hash<std::string>{}(identifier);
}

std::string Identifier::to_string() const {
    return identifier;
}

Symbol * Identifier::clone() const {
    return new Identifier(identifier);
}

/*** SymbolString ***/

void SymbolString::append(Symbol *s) {
    string.push_back(s->clone());
}

Symbol * SymbolString::symbol_at(std::size_t i) const {
    return string.at(i);
}

std::size_t SymbolString::length() const {
    return string.size();
}

bool SymbolString::equals(SymbolString const& other) const {
    if (length() != other.length())
        return false;

    for (std::size_t i = 0; i < length(); i++) {
        if (!symbol_at(i)->equals(*(other.symbol_at(i))))
            return false;
    }

    return true;
}

std::size_t SymbolString::hash() const {
    return std::hash<std::string>{}(to_string());
}

std::string SymbolString::to_string() const {
    std::stringstream ss;

    ss << "\"";
    for (auto it = string.begin(); it != string.end(); it++) {
        ss << **it;
    }
    ss << "\"";

    return ss.str();
}

SymbolString * SymbolString::clone() const {
    SymbolString *clone = new SymbolString;

    for (auto it = string.begin(); it != string.end(); it++) {
        clone->append(*it);
    }

    return clone;
}

SymbolString::~SymbolString() {
    for (auto it = string.begin(); it != string.end(); it++) {
        delete *it;
    }
}
