//
// Created by stef on 05.05.20.
//

#include <iostream>
#include "LSystem.h"

LSystem::LSystem(int maxDepth) : mDepth(maxDepth)
{
}

void LSystem::addRule(std::string rule) {
    // determine chance
    float chance = 1.0f;
    int posOfColon = rule.find(':');
    if(posOfColon != std::string::npos) {
        std::string chanceStringFormat = rule.substr(posOfColon+1);
        chance = std::stof(chanceStringFormat);
    }
    // determine left part
    char leftPart = rule[0];
    // determine right part
    int posOfArrow = rule.find('>');
    if(posOfArrow == std::string::npos) {
        std::cerr << "ERROR: rule doesn't contain an arrow" << std::endl;
        exit(1);
    }
    std::string rightPart = rule.substr(posOfArrow+1, posOfColon);
    // check if left part already in ruleset, else add it
    if(mProdRules.count(leftPart) < 1) {
        mProdRules.insert(std::pair<char, std::vector<ProdRuleRight>>(leftPart, {}));
    }
    // now left part will certainly be in ruleset
    auto it = mProdRules.find(leftPart);
    it->second.push_back({rightPart, chance});
}

std::string LSystem::produce(std::string base) {
    std::string currString = base;
    for(int i = 0; i < mDepth; ++i) {
        currString = produceStep(currString);
    }
    return currString;
}

std::string LSystem::produceStep(std::string base) {
    std::string out;
    for(char ch : base) {
        out.append(produceChar(ch));
    }
    return out;
}

std::string LSystem::produceChar(char ch) {
    // return char if char isn't in produce rules
    if(mProdRules.count(ch) < 1) {
        return std::string(1, ch);
    }
    // do production
    auto prodRulesRight = mProdRules.find(ch)->second;
    float p = rand() / (float)RAND_MAX;
    for(int i = 0; i < prodRulesRight.size(); ++i) {
        ProdRuleRight prodRuleRight = prodRulesRight[i];
        if(prodRuleRight.chance > p) {
            p -= prodRuleRight.chance;
        }
        else {
            return prodRuleRight.value;
        }
    }
    // program should never enter this part
    std::cerr << "Error: cumulative of chances is less than 1." << std::endl;
    exit(1);
}
