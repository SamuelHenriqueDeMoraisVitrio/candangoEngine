
GC=gcc
OPTIONS=-shared -fpic -o
SRC=src/main.c
OUT=candangoEngine/candango_engine.so
RUN_CMD=./${OUT}
EXEC_LUA=lua
RUN_LUA=testes/teste.lua
CONCAT_LUA=${EXEC_LUA} ${RUN_LUA}

all: clear run

valgrind: clear
	@valgrind ${CONCAT_LUA}

run:
	@echo ""
	@echo "	Executando ..."
	@echo ""
	@${CONCAT_LUA}

comp: clear
	@echo ""
	${GC} ${SRC} ${OPTIONS} ${OUT}
	@echo ""
	@echo " 	Compilação concluida.			"
	@echo ""

clear:
	clear
	@echo ""
	@ls -lah --color=always
	@echo ""
