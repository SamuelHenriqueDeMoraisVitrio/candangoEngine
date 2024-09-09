
GC=gcc
SRC=src/one.c
OUT=teste.out
RUN_CMD=./${OUT}

all: comp run

run:
	@echo ""
	@${RUN_CMD}
	@echo ""

comp:
	@echo ""
	${GC} ${SRC} -o ${OUT}
	@echo ""

