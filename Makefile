# PROGRAMA
	PROG = monteCarlo
	OBJS = labMonteCarlo.o utils.o

# Compilador
	CC = gcc -Wall -g
	override CFLAGS += -Wall -O3 -lm -mavx -march=native -D_RET_ -D_MC_
	LFLAGS = -lm
# Lista de arquivos para distribuição
DISTFILES = *.c *.h README.md Makefile *.sh
DISTDIR = `basename ${PWD}`

.PHONY: all debug clean purge dist

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

all: $(PROG)

debug: CFLAGS += -g -D_DEBUG_
debug: all

mc: CFLAGS := $(filter-out -D_RET_,$(CFLAGS))
mc: all

ret: CFLAGS := $(filter-out -D_MC_,$(CFLAGS))
ret: all

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	@echo "Limpando ...."
	@rm -f *~ *.bak *.tmp core

purge: clean
	@echo "Faxina ...."
	@rm -f  $(PROG) *.o *.out a.out $(DISTDIR) $(DISTDIR).tar

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
