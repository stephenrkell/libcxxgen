#ifndef CXXGEN_TOKENS_HPP_
#define CXXGEN_TOKENS_HPP_

#include <string>

namespace cxxgen
{

using std::string;

string escape(const string& s);

inline string literal(const string& contents)
{
	return "\"" + escape(contents) + "\"";
}

} // end namespace cxxgen

#endif
