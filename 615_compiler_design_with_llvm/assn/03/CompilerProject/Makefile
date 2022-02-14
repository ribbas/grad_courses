CLASSPATH = .:/usr/local/lib/antlr-4.9-complete.jar
JAVA = $(shell which java)
JAVAC = $(shell which javac)
ANTLR4 = $(JAVA) -Xmx500M -cp "$(CLASSPATH)" org.antlr.v4.Tool
GRUN = $(JAVA) -Xmx500M -cp "$(CLASSPATH)" org.antlr.v4.gui.TestRig
IN_FILE_NUMS = 0 1 2 3

.PHONY: install run clean $(IN_FILE_NUMS)

install:
	@$(ANTLR4) Cminus.g4
	@$(JAVAC) Cminus*.java

run: $(IN_FILE_NUMS)
$(IN_FILE_NUMS):
	@$(GRUN) Cminus program -tree < C-Input-files/C-Input-$@.txt > C-Output-$@.txt

clean:
	@rm *.class *.tokens *.java *.interp
	@rm -rf .antlr
