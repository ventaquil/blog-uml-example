CC := gcc
RM := rm
STRIP := strip

CFLAGS := -Wall -Wextra -fPIC

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:src/%.c=obj/%.o)
EXECUTABLE := init

.PHONY: default
default: $(EXECUTABLE)

.PHONY: all
all: $(EXECUTABLE)

.PHONY: clean
clean: clean-$(EXECUTABLE) clean-obj

.PHONY: clean-$(EXECUTABLE)
clean-$(EXECUTABLE):
	$(RM) -f $(EXECUTABLE)

.PHONY: clean-obj
clean-obj:
	$(RM) -rf obj

$(EXECUTABLE): $(OBJS)
	$(CC) -static $(CFLAGS) $^ -o$@
	$(STRIP) $@

obj:
	mkdir obj

$(OBJS): obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -o$@ -c $<
