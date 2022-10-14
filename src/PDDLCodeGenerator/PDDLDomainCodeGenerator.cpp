#include "PDDLDomainCodeGenerator.hh"

using namespace std;

void PDDLDomainCodeGenerator::GenerateDomainFile(PDDLDomain* domain, string domainFile) {
	ofstream file;
	file.open(domainFile);
	file << GenerateDomainString(domain);
	file.close();
}

string PDDLDomainCodeGenerator::GenerateDomainString(PDDLDomain* domain) {
	string out = "(define (domain " + domain->name + ")\n";
	out += GetRequirements(domain->requirements) + "\n";
	out += "\n";
	out += GetPredicates(domain->predicates) + "\n";
	out += "\n";
	out += GetActions(domain->actions) + "\n";
	out += "\n";
	out += "\n)\n";
	return out;
}

string PDDLDomainCodeGenerator::GetRequirements(vector<std::string> requirements) {
	string retStr = "";
	retStr += GetTabs(1) + "(:requirements\n";
	retStr += GetTabs(2);
	for (auto i : requirements) {
		retStr += " " + i;
	}
	retStr += "\n" + GetTabs(1) + ")";
	return retStr;
}

string PDDLDomainCodeGenerator::GetPredicates(vector<PDDLPredicate> predicates) {
	string retStr = "";
	retStr += GetTabs(1) + "(:predicates\n";
	retStr += GetTabs(2);
	for (auto i : predicates) {
		retStr += GetPredicate(i);
	}
	retStr += "\n" + GetTabs(1) + ")";
	return retStr;
}

string PDDLDomainCodeGenerator::GetActions(vector<PDDLAction> actions) {
	string retStr = "";
	for (auto i : actions) {
		retStr += GetAction(i) + "\n";
	}
	return retStr;
}

string PDDLDomainCodeGenerator::GetAction(PDDLAction action) {
	string retStr = GetTabs(1) + "(:action " + action.name + "\n";
	retStr += GetTabs(2) + ":parameters (\n";
	retStr += GetTabs(3) + GetPDDLArgs(action.parameters);
	retStr += "\n";
	retStr += GetTabs(2) + ")\n";
	retStr += GetTabs(2) + ":precondition (";
	if (action.preconditions.size() > 1)
		retStr += "and\n";
	else
		retStr += "\n";
	for (auto i : action.preconditions)
		retStr += GetTabs(3) + GetLiteral(i) + "\n";
	retStr += GetTabs(2) + ")\n";
	retStr += GetTabs(2) + ":effect (";
	if (action.effects.size() > 1)
		retStr += "and\n";
	else
		retStr += "\n";
	for (auto i : action.effects)
		retStr += GetTabs(3) + GetLiteral(i) + "\n";
	retStr += GetTabs(2) + ")\n";
	retStr += GetTabs(1) + ")\n";
	return retStr;
}