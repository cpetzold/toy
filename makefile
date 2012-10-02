CC=g++
CCFLAGS=-framework OpenGL -framework Cocoa -lglfw

AR=ar
ARFLAGS=rcs

INCPATH=inc
SRCPATH=src
OBJPATH=obj
LIBPATH=lib
BINPATH=bin

INC=$(SRCPATH)/mage.h
SRC=$(SRCPATH)/mage.cc
OBJS=$(OBJPATH)/mage.o $(OBJPATH)/Game.o $(OBJPATH)/Input.o
OUT=$(LIBPATH)/libmage.a

all: $(OUT)

$(OUT): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(OBJPATH)/%.o: $(SRCPATH)/%.cc $(SRCPATH)/%.h $(INC)
	$(CC) $(CCFLAGS) -c $< -o $@

.PHONY: clean cleanall

clean:
	rm -f $(OBJPATH)/*.o

cleanall: clean
	rm -f $(OUT)