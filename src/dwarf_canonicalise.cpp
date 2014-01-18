#include <dwarfpp/adt.hpp>
#include "cxx_compiler.hpp"

namespace cxxgen
{

using std::dynamic_pointer_cast;
using boost::optional;
using std::shared_ptr;
using std::string;
using std::ostringstream;
using std::pair;
using std::make_pair;
using std::endl;
using std::cerr;
using std::clog;
using std::vector;
using namespace dwarf;
using namespace dwarf::lib;
using dwarf::spec::type_die;

shared_ptr<type_die> 
canonicalise_type(shared_ptr<type_die> p_t,
	dwarf::tool::cxx_compiler& compiler)
{
	using std::clog;
	
	auto p_ds = &p_t->get_ds();
	
	typedef std::map<
		std::pair<dwarf::spec::abstract_dieset *, dwarf::tool::cxx_compiler *>,
		std::map< dwarf::tool::cxx_compiler::base_type, spec::abstract_dieset::iterator >
	> canonicalisation_cache_t;

	/* This is like get_concrete_type but stronger. We try to find
	 * the first instance of the concrete type in *any* compilation unit.
	 * Also, we deal with base types, which may be aliased below the DWARF
	 * level. */

	auto concrete_t = p_t->get_concrete_type();
	clog << "Canonicalising concrete type " << concrete_t->summary() << endl;
	if (!concrete_t) goto return_concrete; // void is already canonicalised
	else
	{
		//Dwarf_Off concrete_off = concrete_t->get_offset();
		auto opt_ident_path = concrete_t->ident_path_from_cu();
		if (!opt_ident_path) clog << "No name path, so cannot canonicalise further." << endl;
		if (opt_ident_path)
		{
			/* Instead of doing resolve_all_visible and then taking the first,
			 * we want to  */

			//auto resolved_all = p_ds->toplevel()->resolve_all_visible(
			//	opt_ident_path->begin(), opt_ident_path->end()
			//);
			auto p_resolved = p_ds->toplevel()->resolve_visible(
				opt_ident_path->begin(), opt_ident_path->end());
			clog << "Name path: ";
			for (auto i_part = opt_ident_path->begin();
				 i_part != opt_ident_path->end(); ++i_part)
			{
				if (i_part != opt_ident_path->begin()) clog << " :: ";
				clog << *i_part;
			}
			clog << endl;
			/*if (resolved_all.size() == 0)*/ if(!p_resolved) clog << "BUG: failed to resolve this name path." << endl;
			//assert(resolved_all.size() > 0);

			/* We choose the first one that is not a declaration
			 * when we concrete + dedeclify it.
			 * If they are all declarations, we choose the first one.
			 * If there are none, it is an error.
			 */

			shared_ptr<type_die> first_non_decl;
			shared_ptr<type_die> first_concrete;
			//for (auto i_resolved = resolved_all.begin();
			//	i_resolved != resolved_all.end(); ++i_resolved)
			//{
			do
			{
				if (dynamic_pointer_cast<type_die>(p_resolved))
				{
					auto temp_concrete_t = dynamic_pointer_cast<type_die>(p_resolved)
						->get_concrete_type();
					if (!first_concrete) first_concrete = temp_concrete_t;
					auto with_data_members
					 = dynamic_pointer_cast<spec::with_data_members_die>(temp_concrete_t);
					if (with_data_members)
					{
						// we do another canonicalisation here: find the defn of a decl
						auto defn = with_data_members->find_my_own_definition();
						if (defn && (!defn->get_declaration() || !*defn->get_declaration())) 
						{
							first_non_decl = defn;
							break;
						}
					}
				}
			} while (0); // FIXME
			if (first_non_decl) concrete_t = first_non_decl;
			else concrete_t = first_concrete;

			/*else*/ /* not resolved*/ goto return_concrete; // FIXME: we could do more here
		}
		else goto return_concrete; // FIXME: we could do more here
	}

return_concrete:
	//clog << "Most canonical concrete type is " << concrete_t->summary() << endl;
	static canonicalisation_cache_t cache;
	/* Now we handle base types. */
	if (concrete_t->get_tag() != DW_TAG_base_type) return concrete_t;
	else
	{
		/* To canonicalise base types, we have to use the compiler's 
		 * set of base types (i.e. the base types that it considers distinct). */
		auto base_t = dynamic_pointer_cast<base_type_die>(concrete_t);
		assert(base_t);
		auto compiler_base_t = dwarf::tool::cxx_compiler::base_type(base_t);
		auto& our_cache = cache[make_pair(p_ds, &compiler)];
		auto found_in_cache = our_cache.find(compiler_base_t);
		if (found_in_cache == our_cache.end())
		{
			/* Find the first visible named base type that is identical to base_t. */
			auto visible_grandchildren_seq
			 = p_ds->toplevel()->visible_grandchildren_sequence();
			auto i_vis = visible_grandchildren_seq->begin();
			for (;
				i_vis != visible_grandchildren_seq->end();
				++i_vis)
			{
				auto vis_as_base = dynamic_pointer_cast<base_type_die>(*i_vis);
				if (vis_as_base
					&& vis_as_base->get_name()
					&& dwarf::tool::cxx_compiler::base_type(vis_as_base)
						== compiler_base_t)
				{
					auto result = our_cache.insert(
						make_pair(
							compiler_base_t,
							vis_as_base->iterator_here()
						)
					);
					assert(result.second);
					found_in_cache = result.first;
					break;
				}
			}
			assert(i_vis != visible_grandchildren_seq->end());
		}
		assert(found_in_cache != our_cache.end());
		auto found_as_type = dynamic_pointer_cast<type_die>(*found_in_cache->second);
		assert(found_as_type);
		//cerr << "Canonicalised base type " << concrete_t->summary() 
		//	<< " to " << found_as_type->summary() 
		//	<< " (in compiler: " << compiler_base_t << ")" << endl;
		return found_as_type;
	}
}

}
