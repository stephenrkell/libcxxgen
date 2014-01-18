CXXFLAGS += -std=c++11 -g -fPIC -I../include/cxxgen

CPP_SRC := $(wildcard *.cpp)
CC_SRC := $(wildcard *.cc)

LDLIBS += -ldwarfpp

default: libcxxgen.so

CPP_DEPS := $(patsubst %.cpp,.%.d,$(CPP_SRC))
CC_DEPS := $(patsubst %.cc,.%.d,$(CC_SRC))

DEPS := $(CPP_DEPS) $(CC_DEPS)

$(CPP_DEPS): .%.d : %.cpp
	$(CXX) -MM $(CXXFLAGS) "$<"  > "$@"
$(CC_DEPS): .%.d : %.cc
	$(CXX) -MM $(CXXFLAGS) "$<"  > "$@"

-include $(DEPS)

libcxxgen.so: $(patsubst %.cpp,%.o,$(CPP_SRC)) $(patsubst %.cc,%.o,$(CC_SRC))
	$(CXX) $(CXXFLAGS) -shared -o "$@" $+ $(LDFLAGS) $(LDLIBS)

clean: 
	rm -f *.o *.so .*.d
