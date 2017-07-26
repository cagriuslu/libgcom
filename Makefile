# Library name
l=gcom

# Executables
CC=gcc
CP=g++
RM=rm
MKDIR=mkdir
AR=ar
LD=ld

# Directories
SRCDIR=src
OBJDIR=obj
BINDIR=bin
LIBDIR=lib
TESTDIR=test
INCDIR=include

# Import all the .cc files in SRCDIR
SRCFILES=$(wildcard $(SRCDIR)/*.cc)
OBJFILES=$(patsubst $(SRCDIR)/%.cc,$(OBJDIR)/%.o,$(SRCFILES))

# Import all the .cc files in TESTDIR
TESTSRCS=$(wildcard $(TESTDIR)/*.cc)
TESTBINS=$(patsubst $(TESTDIR)/%.cc,$(BINDIR)/%,$(TESTSRCS))

# Configurations
all: $(OBJDIR) $(LIBDIR) $(LIBDIR)/lib$(l).a

test: all $(BINDIR) $(TESTBINS)

clean:
	@$(RM) -rf $(BINDIR)
	@$(RM) -rf $(OBJDIR)
	@$(RM) -rf $(LIBDIR)

# Compile
$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	$(CP) -g -Wall -Wextra -std=c++11 -pthread -I$(INCDIR) -c $< -o $@

$(BINDIR)/%: $(TESTDIR)/%.cc
	$(CP) -g -Wall -Wextra -std=c++11 -pthread -I$(INCDIR) $< -o $@ -L$(LIBDIR) -l$(l)

# Archive
$(LIBDIR)/lib$(l).a: $(OBJFILES)
	@$(AR) rcsv $@ $(OBJFILES)

# mkdir
$(OBJDIR):
	@$(MKDIR) -p $(OBJDIR)
$(LIBDIR):
	@$(MKDIR) -p $(LIBDIR)
$(BINDIR):
	@$(MKDIR) -p $(BINDIR)

