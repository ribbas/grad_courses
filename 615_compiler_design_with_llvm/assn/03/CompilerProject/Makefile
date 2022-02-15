CLASSPATH = .:/usr/local/lib/antlr-4.9-complete.jar
JAVA = $(shell which java)
JAVAC = $(shell which javac)
ANTLR4 = $(JAVA) -Xmx500M -cp "$(CLASSPATH)" org.antlr.v4.Tool
GRUN = $(JAVA) -Xmx500M -cp "$(CLASSPATH)" org.antlr.v4.gui.TestRig
IN_FILE_NUMS = Input-0 Input-1 Input-2 Input-3

.PHONY: install run clean $(IN_FILE_NUMS)

install:
	@$(ANTLR4) Cminus.g4
	@$(JAVAC) Cminus*.java

run: $(IN_FILE_NUMS)
$(IN_FILE_NUMS):
	@$(GRUN) Cminus program -tree < C-Input-files/C-$@.txt > C-$@-Tree.txt
	@$(GRUN) Cminus program -tokens < C-Input-files/C-$@.txt > C-$@-Tokens.txt

clean:
	@rm *.class *.tokens *.java *.interp
	@rm -rf .antlr
