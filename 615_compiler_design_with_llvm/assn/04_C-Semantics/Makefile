# Makefile
# Sabbir Ahmed
# 2/28/22
# Makefile for setting up and running ANTLR4 to generate the tree and
# token files from the grammar file

OUTPUT=output
GENERATED=generated

CXX=$(shell which c++)
CXXARGS=-c -I /usr/include/antlr4-runtime -I $(GENERATED) -std=c++11	
LDARGS=-g
LIBS=/usr/lib/x86_64-linux-gnu/libantlr4-runtime.a

CLASSPATH = .:/usr/local/lib/antlr-4.9-complete.jar
JAVA = $(shell which java)
JAVAC = $(shell which javac)
ANTLR4 = $(JAVA) -Xmx500M -cp "$(CLASSPATH)" org.antlr.v4.Tool
GRUN = $(JAVA) -Xmx500M -cp "$(CLASSPATH)" org.antlr.v4.gui.TestRig

GRAMMAR=Cminus
SRC=$(GRAMMAR).cpp

ANTLRGEN=BaseListener Lexer Listener Parser Visitor
OBJS=$(addsuffix .o,$(addprefix $(OUTPUT)/$(GRAMMAR),$(ANTLRGEN)))
GSOURCES=$(addsuffix .cpp,$(addprefix $(GENERATED)/$(GRAMMAR),$(ANTLRGEN)))

.precious: $(GSOURCES)

all: $(GRAMMAR)

$(GRAMMAR): dirs antlr4 $(SRC) $(OBJS)
	$(CXX) $(CXXARGS) $(SRC) -o $(OUTPUT)/$(GRAMMAR).o 
	$(CXX) $(LDARGS) $(OUTPUT)/$(GRAMMAR).o $(OBJS) $(LIBS) -o $(GRAMMAR)

antlr4: $(GENERATED)/.generated;
 
$(GENERATED)/.generated: $(GRAMMAR).g4
	$(ANTLR4) -Dlanguage=Cpp -visitor -o $(GENERATED) $(GRAMMAR).g4
	@touch $(GENERATED)/.generated

$(OUTPUT)/%.o : $(GENERATED)/%.cpp
	$(CXX) $(CXXARGS) $< -o $@

$(GENERATED)/%.cpp: $(GENERATED)/.generated;

dirs:; mkdir -p $(OUTPUT) $(GENERATED) 

TEST:=$(shell find test -name '*.c')
.PHONY: test
test:
	@for i in $(TEST); do \
		echo "<< $$i >>"; \
		./$(GRAMMAR) $$i; \
	done

clean:
	@rm -rf $(OUTPUT) $(GENERATED)
	@rm -rf .antlr
	@rm -f $(GRAMMAR)

