.PHONY : clean
default: build_main

PWD!=pwd
DOCKER=docker run --rm --user="$$(id -u):$$(id -g)" --net=none -v "$(PWD)/note:/tmp" -w=/tmp neitex\:latex

gen_listings: program/main.cpp
	cp program/main.cpp note/attachments/program.cpp

build_main: note/*.tex gen_listings
	$(DOCKER) latexmk -pdflatex='pdflatex -shell-escape -interaction=nonstopmode -synctex=1 %O %S;' -pdf note.tex

note.pdf: build_main
	cp note/note.pdf note.pdf


pvc:
	$(DOCKER) latexmk -pdflatex='pdflatex -shell-escape -interaction=nonstopmode -synctex=1 %O %S;' -pvc -pdf note.tex

clean:
	rm note.pdf || true
#	rm note/attachments/*.gen || true
	$(DOCKER) latexmk -C

# How to use gen_listings:
# 1. make sure ur program is in program/main.cpp relative to Makefile
# 2. first line should be a comment that looks something like that:
#    // defined snippets: |<snippet_1>,<snippet_2>...
# 3. each snippet must be defined in the comment above and surrounded by these comments:
#
#    //begin:<snippet_1>
#    int main(){
#      ...
#    }
#    //end:<snippet_1>
#
# 4. snippets will be generated to note/attachments under names <snippet_name>.gen
#
# Make sure to uncomment relative lines in clean and build_main
