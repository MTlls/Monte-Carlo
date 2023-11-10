# PROGRAMA
	PROG = monteCarlo
	OBJS = labMonteCarlo.o utils.o

# Compilador
	CC = gcc -Wall
	override CFLAGS += -Wall -O3

# Lista de arquivos para distribuição
DISTFILES = *.c *.h README.md Makefile
DISTDIR = `basename ${PWD}`

.PHONY: all debug clean purge dist

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

all: $(PROG)

debug: CFLAGS += -g -D_DEBUG_
debug: all

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

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
