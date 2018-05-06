# Project: ICP Project 1
# File: Makefile
# Title: Block editor
# Description: This file uses qmake to generate a Makefile 
#              and hides it behind custom targets created according to the assignment.
# Authors: Michal Pospíšil (xpospi95@stud.fit.vutbr.cz)
#          Tomáš Pazdiora (xpazdi02@stud.fit.vutbr.cz)

##### TARGETS - first target is default
compile: update
	make -f qMakefile

run: compile
	./blockeditor


update: ICP_Project.pro
	qmake -o qMakefile ICP_Project.pro

doxygen:
	doxygen doc/Doxyfile

clean:
	rm -f blockeditor *.o ui_blockeditor.h moc_blockeditor.cpp qMakefile

pack:
	zip -r xpazdi02-xpospi95.zip src res examples ICP_Project.pro Makefile README.txt README.md doc/Doxyfile
