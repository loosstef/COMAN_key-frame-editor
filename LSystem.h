//
// Created by stef on 05.05.20.
//

#ifndef PROJECT_LSYSTEM_H
#define PROJECT_LSYSTEM_H

#include <vector>
#include <map>
#include <string>

struct ProdRuleRight {
    std::string value;
    float chance;
};

//struct ProdRulesRight {
//    std::vector<ProdRuleRight> prodRules;
//};

class LSystem {
public:
    LSystem(int maxDepth);
    void addRule(std::string rule);
    std::string produce(std::string base);
private:
    std::string produceStep(std::string base);
    std::string produceChar(char ch);
    std::map<char, std::vector<ProdRuleRight>> mProdRules;
    int mDepth;
};


#endif //PROJECT_LSYSTEM_H
