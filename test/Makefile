use_curses=1
FLAGS+=-DUSING_MAKEFILE
ifeq ($(use_curses),0)
    FLAGS+=-DNO_NCURSES
else
    LIBS+=-lcurses
endif
all: test test2 test test3 test4


%: %.c
	gcc $< -w -o $@ $(FLAGS) $(LIBS)