# Universal makefile for single C++ program
#
# Use gcc flag -MMD (user) or -MD (user/system) to generate dependencies among source files.
# Use make default rules for commonly used file-name suffixes and make variables names.
#
# % make [ a.out ]

########## Variables ##########

CXX = g++-14					# compiler
CXXFLAGS = -std=c++20 -g -Wall -MMD -Iview			# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

# sources (*.cc)

SOURCES = $(wildcard *.cc) \
          $(wildcard cards/*.cc) \
          $(wildcard controller/*.cc) \
          $(wildcard gameModel/*.cc) \
          $(wildcard view/*.cc)

OBJECTS = ${SOURCES:.cc=.o}		# object files forming executable
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXEC = sorcery					# executable name

########## Targets ##########

.PHONY : clean					# not file names

${EXEC} : ${OBJECTS}				# link step
	${CXX} ${CXXFLAGS} $^ -o $@		# additional object files before $^

# compile for subdirectories
cards/%.o: cards/%.cc
	${CXX} ${CXXFLAGS} -c $< -o $@

controller/%.o: controller/%.cc
	${CXX} ${CXXFLAGS} -c $< -o $@

gameModel/%.o: gameModel/%.cc
	${CXX} ${CXXFLAGS} -c $< -o $@

view/%.o: view/%.cc
	${CXX} ${CXXFLAGS} -c $< -o $@

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

# make implicitly generates rules to compile C++ files that generate .o files

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}
