#include <string>
#include <sstream>

namespace cxxgen
{

using std::string;
using std::ostringstream;

string escape(const string& s)
{
	ostringstream str;
	for (auto i = s.begin(); i != s.end(); ++i)
	{
		char c = *i;
		switch (c)
		{
			case '\0': c = '0'; goto write_escape;
			case '\b': c = 'b'; goto write_escape;
			case '\r': c = 'r'; goto write_escape;
			case '\n': c = 'n'; goto write_escape;
			case '\t': c = 't'; goto write_escape;
			case '\f': c = 'f'; goto write_escape;
			case '\a': c = 'a'; goto write_escape;
			case '\v': c = 'v'; goto write_escape;
			/* we don't generate \0xxx or \xXX */
			case '"':
			case '\\': 
			write_escape:
				str << (string("\\") + c); break;
			default:
				str << *i; break;
		}
	}
	return str.str();
}

}
