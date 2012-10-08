CC=cc
AR=ar
ARFLAGS=rcs

INCPATH=inc
SRCPATH=src
OBJPATH=obj
LIBPATH=lib
BINPATH=bin

CCFLAGS=-I$(INCPATH) -Wall

SRC=$(wildcard $(SRCPATH)/*.cc)
OBJS=$(patsubst $(SRCPATH)%.cc, $(OBJPATH)%.o, $(SRC))
INC=$(SRCPATH)/mage.h
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