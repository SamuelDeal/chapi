all: chapi

.PHONY: all clean clean_tmp clear deps

SRCS = $(shell find . -type f -name '*.cpp')
OBJS = $(SRCS:.cpp=.o)

CPPFLAGS += -std=c++11 -Wall -O3
LDFLAGS += -lpthread -Wall -O3
LIBS +=
CC = 'g++'
LINKER = 'g++'

DEPS := $(patsubst %.o,%.d,$(OBJS))

clear: clean

clean: clean_tmp
	@$(RM) -rf chapi
	@echo "all cleaned"

clean_tmp:
	@$(RM) -rf $(OBJS) $(DEPS)
	@echo "temporary files cleaned"

%.o: %.cpp
	$(CC) -D_REENTRANT -c $(CPPFLAGS) -o $@ $<

chapi: $(OBJS)
	$(LINKER) -o $@ $^ $(LIBS) $(LDFLAGS)

deps: $(SOURCES)
	$(CC) -MD -E $(SOURCES) > /dev/null

-include $(DEPS)