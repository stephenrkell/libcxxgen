#ifndef DWARFPP_CXX_COMPILER_HPP_
#define DWARFPP_CXX_COMPILER_HPP_

#include <dwarfpp/lib.hpp>

namespace dwarf
{
	namespace tool
	{
		using namespace dwarf::lib;
		using boost::optional;
		using std::string;
		using std::vector;
		using std::pair;
		using std::multimap;
		using std::endl;
		using dwarf::core::iterator_base;
		
		class abstract_c_compiler
		{
		protected:
			static const char * base_typename_equivs_schar[];
			static const char * base_typename_equivs_uchar[];
			static const char * base_typename_equivs_sshort[];
			static const char * base_typename_equivs_ushort[];
			static const char * base_typename_equivs_sint[];
			static const char * base_typename_equivs_uint[];
			static const char * base_typename_equivs_slong[];
			static const char * base_typename_equivs_ulong[];
			static const char * base_typename_equivs_slonglong[];
			static const char * base_typename_equivs_ulonglong[];
			static const char * base_typename_equivs_wchar_t[];
			static const char * base_typename_equivs_float[];
			static const char * base_typename_equivs_double[];
			static const char * base_typename_equivs_long_double[];
		
			static inline const char **get_equivalence_class_in(const char ** const *classes,
				const char *name)
			{
				for (const char ** const* p_equiv = &classes[0]; *p_equiv != NULL; ++p_equiv)
				{
					for (const char **p_el = p_equiv[0]; *p_el != NULL; ++p_el)
					{
						if (string(*p_el) == name) return p_equiv[0];
					}
				}
				return nullptr;
			}
		public:
			static const char **const base_typename_equivs[];
			static const char **const *base_typename_equivs_end;
			
			inline static const char **get_equivalence_class_ptr(const char *name)
			{
				return get_equivalence_class_in(base_typename_equivs, name);
			}
		};
		
		class abstract_cxx_compiler : abstract_c_compiler // private inheritance
		{
		protected:
			static const char *base_typename_equivs_bool[];
		public:
			static const char **const base_typename_equivs[];
			static const char **const *base_typename_equivs_end;
			inline static const char **get_equivalence_class_ptr(const char *name)
			{
				return get_equivalence_class_in(base_typename_equivs, name);
			}
		};
		
		class cxx_compiler : public abstract_cxx_compiler
		{
			/* Mainly as support for dwarfhpp, this class supports discovering
			 * some DWARF-related properties of a C++ compiler. In particular,
			 * it discovers the range of base type encodings available through
			 * the compiler's implementations of C++ primitive types. */

			vector<string> compiler_argv;
			
		public:
			// build a map of base types: 
			// <byte-size, encoding, bit-offset = 0, bit-size = byte-size * 8 - bit-offset>
			struct base_type
			{
				Dwarf_Unsigned byte_size;
				Dwarf_Unsigned encoding;
				Dwarf_Unsigned bit_offset;
				Dwarf_Unsigned bit_size;
				bool operator<(const base_type& arg) const
				{
					return byte_size < arg.byte_size
					|| (byte_size == arg.byte_size && encoding < arg.encoding)
					|| (byte_size == arg.byte_size && encoding == arg.encoding && bit_offset < arg.bit_offset)
					|| (byte_size == arg.byte_size && encoding == arg.encoding && bit_offset == arg.bit_offset && bit_size < arg.bit_size);
				}
				bool operator==(const base_type& arg) const
				{
					return byte_size == arg.byte_size
					&&	encoding == arg.encoding
					&&	bit_offset == arg.bit_offset
					&&	bit_size == arg.bit_size;
				}
				base_type(const iterator_base& p_d);
				friend std::ostream& operator<<(std::ostream& s, const base_type& c);
			}; 

		protected:
			/* An equivalence class is an array of pointers to const char*. */
			typedef const char ** equiv_class_ptr_t;
			equiv_class_ptr_t find_equiv_class(const string& name) const;
			multimap<base_type, pair<string, equiv_class_ptr_t > > base_types; // map a 4-tuple to its name(s)
			string m_producer_string;
			//struct base_type dwarf_base_type(const dwarf::encap::Die_encap_base_type& d);
			//static const string dummy_return;
			void discover_base_types();
			static vector<string> parse_cxxflags();
		public:
			cxx_compiler(const vector<string>& argv);
			
			static vector<string>
			default_compiler_argv(bool use_cxxflags = true);
			
			typedef multimap<base_type, pair< string, equiv_class_ptr_t > >::iterator base_type_name_iterator;
			
			pair<base_type_name_iterator, base_type_name_iterator> 
			names_for_base_type(const base_type& arg)
			{ return base_types.equal_range(arg); }
			
			cxx_compiler();
			
			string get_producer_string() const { return m_producer_string; }
			
			std::ostream& print(std::ostream& out, const spec::abstract_def& s);

		}; // end class cxx_compiler
		std::ostream& operator<<(std::ostream& s, const cxx_compiler::base_type& c);
	}
}

#endif
