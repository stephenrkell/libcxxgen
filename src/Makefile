CXXFLAGS += -std=c++11 -g -fPIC -I../include/cxxgen

CPP_SRC := $(wildcard *.cpp)

default: libcxxgen.so

CPP_DEPS := $(patsubst %.cpp,.%.d,$(CPP_SRC))

DEPS := $(CPP_DEPS)

$(CPP_DEPS): .%.d : %.c
	$(CXX) -MM $(CXXFLAGS) "$<"  > "$@"

-include $(DEPS)

libcxxgen.so: cxxgen.o cxx_compiler.o
	$(CXX) $(CXXFLAGS) -shared -o "$@" "$<" $(LDFLAGS) $(LDLIBS)

clean: 
	rm -f *.o *.so .*.d
