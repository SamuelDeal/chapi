all: chapi

.PHONY: all clean clean_tmp clear deps

SRCS = $(shell find . -type f -name '*.cpp')
OBJS = $(SRCS:.cpp=.o)

CPPFLAGS_SPECIFIC += -std=c++11 -Wall -O3 -lwiringPi -lrt
LDFLAGS_SPECIFIC += -lpthread -Wall -O3 -lwiringPi -lrt
LIBS +=
CXX = g++

DEPS := $(patsubst %.o,%.d,$(OBJS))

clear: clean

clean: clean_tmp
	@$(RM) -rf chapi
	@echo "all cleaned"

clean_tmp:
	@$(RM) -rf $(OBJS) $(DEPS)
	@echo "temporary files cleaned"

%.o: %.cpp
	$(CXX) -D_REENTRANT -c $(CPPFLAGS) -c $(CPPFLAGS_SPECIFIC) -o $@ $<

chapi: $(OBJS)
	$(CXX) -o $@ $^ $(LIBS) $(LDFLAGS) $(LDFLAGS_SPECIFIC)

deps: $(SOURCES)
	$(CXX) -MD -E $(SOURCES) > /dev/null

-include $(DEPS)
