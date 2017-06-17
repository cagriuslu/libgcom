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

# Import all the .c files in SRCDIR
SRCFILES=$(wildcard $(SRCDIR)/*.cc)
OBJFILES=$(patsubst $(SRCDIR)/%.cc,$(OBJDIR)/%.o,$(SRCFILES))

# Import test source file
TESTSRC=test.cc
TESTBIN=test

# Configurations
all: $(LIBDIR)/lib$(l).a

test: $(BINDIR)/$(TESTBIN)

clean:
	@$(RM) -rf $(BINDIR)
	@$(RM) -rf $(OBJDIR)
	@$(RM) -rf $(LIBDIR)

# Compile
$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	$(CP) -g -Wall -Wextra -std=c++11 -pthread -I$(INCDIR) -c $< -o $@

$(BINDIR)/$(TESTBIN): $(BINDIR) $(LIBDIR)/lib$(l).a $(TESTDIR)/$(TESTSRC)
	$(CP) -g -Wall -Wextra -std=c++11 -pthread -I$(INCDIR) -o $(BINDIR)/$(TESTBIN) $(TESTDIR)/$(TESTSRC) -L$(LIBDIR) -l$(l)

# Archive
$(LIBDIR)/lib$(l).a: $(LIBDIR) $(OBJDIR) $(OBJFILES)
	@$(AR) rcsv $(LIBDIR)/lib$(l).a $(OBJFILES)

# Mkdir
$(OBJDIR):
	@$(MKDIR) -p $(OBJDIR)
$(LIBDIR):
	@$(MKDIR) -p $(LIBDIR)
$(BINDIR):
	@$(MKDIR) -p $(BINDIR)

