#include <dwarfpp/spec.hpp>
#include <memory>
#include "cxx_compiler.hpp"

namespace cxxgen
{

using std::shared_ptr;
using namespace dwarf;
using dwarf::spec::type_die;

shared_ptr<type_die> 
canonicalise_type(shared_ptr<type_die> p_t,
	dwarf::tool::cxx_compiler& compiler)

}
