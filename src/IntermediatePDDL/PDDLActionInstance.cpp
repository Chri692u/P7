#include "PDDLActionInstance.hh"

std::string PDDLActionInstance::ToString(const PDDLProblem * problem, const PDDLDomain * domain)
{
    //Print action
    std::string temp = action->name + "(";
    for (int i = 0; i < objects.size(); i++)
    {
        temp += problem->objects[objects[i]];
        if (i + 1 < objects.size()) 
        {
            temp += " ";
        }
    }
    temp += ")\n";

    temp += "precondition(" + LiteralsToString(action->preconditions, domain, problem);
    temp += "effect(" + LiteralsToString(action->effects, domain, problem);

    return temp;
}

std::string PDDLActionInstance::LiteralsToString(std::vector<PDDLLiteral> literals, const PDDLDomain* domain, const PDDLProblem* problem)
{
    std::string temp;
    for (int i = 0; i < literals.size(); i++)
    {
        temp += "(";
        PDDLLiteral literal = literals[i];

        if (!literal.value) {
            temp += "not ";
        }
        auto predicate = domain->predicates[literal.predicateIndex];
        temp += predicate.name + " ";
        //temp += objectnames[literal.predicateIndex] + " ";

        for (int i = 0; i < literal.args.size(); i++)
        {
            temp += problem->objects[objects[literal.args[i]]];
            if (i + 1 < literal.args.size()) 
            {
                temp += " ";
            }
        }
        temp += ")";

        if (i + 1 < literals.size()) 
        {
            temp += " ";
        }
    }
    temp += ")\n";
    return temp;
}