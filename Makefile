# filestat makefile

CC				= gcc
CXX				= g++
CPPFLAGS			= -fdiagnostics-color=always -std=c++11 -Wall -Werror -g -iquote include/
LD				= $(CXX)
LDFLAGS				= -lboost_system -lboost_program_options
STRIP				= strip --strip-unneeded
RM				= rm

FILES				= main filestat
SRCDIR				= src
OBJDIR				= build

SRCEXT				= ${addsuffix .cpp,$(FILES)}
OBJEXT				= ${addsuffix .o,$(FILES)}
SRC				= ${addprefix $(SRCDIR)/,$(SRCEXT)}
OBJ				= ${addprefix $(OBJDIR)/,$(OBJEXT)}
EXE				= filestat


build/%.o: src/%.cpp
				$(CXX) $(CPPFLAGS) -c $< -o $@

all: $(EXE)

$(EXE): $(OBJ)
				$(LD) $(CPPFLAGS) -o $@ $(OBJ) $(LDFLAGS)

clean:
				$(RM) -f $(EXE) $(OBJ)

dist: $(EXE)
				$(STRIP) $(EXE)

