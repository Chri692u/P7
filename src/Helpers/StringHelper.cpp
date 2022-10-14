#include "StringHelper.hh"

using namespace std;

void StringHelper::RemoveCharacter(string* buffer, char character) {
	buffer->erase(remove(buffer->begin(), buffer->end(), character), buffer->end());
}

string StringHelper::RemoveCharacter(string buffer, char character) {
    string newBuffer = buffer;
    StringHelper::RemoveCharacter(&newBuffer, character);
    return newBuffer;
}

void StringHelper::Trim(string* buffer) {
    string::const_iterator it = buffer->begin();
    int from = 0;
    int length = buffer->size();

    while (it != buffer->end() && isspace(*it)) {
        it++;
        from++;
    }

    string::const_reverse_iterator rit = buffer->rbegin();
    while (rit.base() != it && isspace(*rit)) {
        rit++;
        length--;
    }

    *buffer = buffer->substr(from, length - from);
}

string StringHelper::Trim(string buffer) {
    string newBuffer = buffer;
    StringHelper::Trim(&newBuffer);
    return newBuffer;
}

std::string StringHelper::StringFormat(const std::string fmt_str, ...) {
    int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while (1) {
        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
        strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
        else
            break;
    }
    return std::string(formatted.get());
}

