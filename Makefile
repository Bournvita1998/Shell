run: \
			modular.o \
			cd.o \
			split.o \
			execute.o \
			ls.o \
			pinfo.o \
			pwd.o \
			redirect.o \
			set.o \
			piping.o \
			unset.o
		$(CC) -g -o run $^
clean:
	@rm -f *.o run

modular.o: run.h modular.c
	$(CC) -g -c modular.c

cd.o: run.h cd.c
	$(CC) -g -c cd.c

split.o: run.h split.c
	$(CC) -g -c split.c

execute.o: run.h execute.c
	$(CC) -g -c execute.c

ls.o: run.h ls.c
	$(CC) -g -c ls.c

pinfo.o: run.h pinfo.c
	$(CC) -g -c pinfo.c

pwd.o: run.h pwd.c
	$(CC) -g -c pwd.c

redirect.o: run.h redirect.c
	$(CC) -g -c redirect.c

set.o: run.h set.c
	$(CC) -g -c set.c

unset.o: run.h unset.c
	$(CC) -g -c unset.c

piping.o: run.h piping.c
	$(CC) -g -c piping.c
