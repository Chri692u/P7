#include "PDDLState.hh"

#include "PDDLInstance.hh"

void PDDLState::DoAction(const PDDLActionInstance *action) {
    int actionEffectLength = action->action->effects.size();
    for (int i = 0; i < actionEffectLength; i++) {
        PDDLLiteral effect = action->action->effects.at(i);
        if (effect.args.size() == 1) {
            // Handle unary effect
            if (effect.value)
                unaryFacts.at(effect.predicateIndex).emplace(action->objects.at(effect.args.at(0)));
            else
                unaryFacts.at(effect.predicateIndex).erase(action->objects.at(effect.args.at(0)));
        } else {
            // Handle multi effect
            if (effect.value) {
                if (ContainsFact(effect.predicateIndex, &effect.args, &action->objects))
                    continue;
                
                multiFacts.at(effect.predicateIndex).push_back(MultiFact(&effect.args, &action->objects));
            } else {
                if (!ContainsFact(effect.predicateIndex, &effect.args, &action->objects))
                    continue;
                auto factSet = &multiFacts.at(effect.predicateIndex);
                factSet->erase(std::remove(factSet->begin(), factSet->end(), std::make_pair(&effect.args, &action->objects)), factSet->end());
            }
        }
    }
}

void PDDLState::UndoAction(const PDDLActionInstance *action) {
    int actionEffectLength = action->action->effects.size();
    for (int i = 0; i < actionEffectLength; i++) {
        PDDLLiteral effect = action->action->effects.at(i);
        if (effect.args.size() == 1) {
            // Handle unary effect
            if (!effect.value)
                unaryFacts.at(effect.predicateIndex).emplace(action->objects.at(effect.args.at(0)));
            else
                unaryFacts.at(effect.predicateIndex).erase(action->objects.at(effect.args.at(0)));
        } else {
            // Handle multi effect
            if (!effect.value) {
                if (ContainsFact(effect.predicateIndex, &effect.args, &action->objects))
                    continue;
                
                multiFacts.at(effect.predicateIndex).push_back(MultiFact(&effect.args, &action->objects));
            } else {
                if (!ContainsFact(effect.predicateIndex, &effect.args, &action->objects))
                    continue;
                auto factSet = &multiFacts.at(effect.predicateIndex);
                factSet->erase(std::remove(factSet->begin(), factSet->end(), std::make_pair(&effect.args, &action->objects)), factSet->end());
            }
        }
    }
}

std::string PDDLState::ToString(const PDDLInstance* instance)
{
    std::string temp = "State ";
    for (auto &unaryFact : unaryFacts)
    {
        if (unaryFact.second.size() > 0) {
            temp += "(";
            temp += instance->domain->predicates[unaryFact.first].name;

            for (auto objectindex : unaryFact.second) {
                temp += " " + instance->problem->objects[objectindex];
            }
            temp += ")";
        }
        

    }

    for (auto &multiFact : multiFacts) {
        for (auto &facts : multiFact.second) {
            temp += "(";
            temp += instance->domain->predicates[multiFact.first].name;
            for (auto fact : facts.fact) {
                
                temp += " " + instance->problem->objects[fact];
               
            }
            temp += ")";
        }
    }

    temp += "\n";
    return temp;
};
