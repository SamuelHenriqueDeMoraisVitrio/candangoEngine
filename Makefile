
GC=gcc
OPTIONS=-shared -fpic -o
SRC=src/main.c
SRC_TESTE=src/teste.c
OUT=candangoEngine/candango_engine.so
OUT_TESTE=teste.out
RUN_CMD=./${OUT_TESTE}
EXEC_LUA=lua
RUN_LUA=testes/teste.lua
CONCAT_LUA=${EXEC_LUA} ${RUN_LUA}
ZIP_NAME=candangoEngine.zip

all: clear comp run zip

testC: clear comp_teste run_teste

valgrind: clear
	@valgrind ${CONCAT_LUA}

run:
	@echo ""
	@echo "	Executando ..."
	@echo ""
	@${CONCAT_LUA}

run_teste:
	@echo ""
	@echo "	Executando ..."
	@echo ""
	@${RUN_CMD}
	@echo ""

comp: clear
	@echo ""
	${GC} ${SRC} ${OPTIONS} ${OUT}
	@echo ""
	@echo " 	Compilação concluida.			"
	@echo ""

comp_teste:
	@echo ""
	${GC} ${SRC_TESTE} -o ${OUT_TESTE}
	@echo ""
	@echo " 	Compilação concluida.			"
	@echo ""

clear:
	clear
	@echo ""
	@ls -lah --color=always
	@echo ""

zip:
	rm -f ${ZIP_NAME}
	zip -r ${ZIP_NAME} candangoEngine/

