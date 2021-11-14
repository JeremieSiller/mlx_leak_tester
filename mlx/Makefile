# Makefile
# Copyright (c) jsiller (jsiller@student.42heilbronn.de)
# This file is part of mlx_leak_tester (based on mlx by Ecole 42),
# forked at 12th of November 2021
# See LICENSE file for more details about the conditions this file is released under.
# file from mlx and edited by jsiller

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c leaks.c
SRC+= mlx_png.c mlx_mouse.m
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2
CFLAGS+=-w
ifeq ($(PROTECT_VALUE), undefined)
CFLAGS+= -D PROTECT_VALUE=$(PROTECT_VALUE)
endif
COUNT=0
# add to match string put with X11 in size and position
CFLAGS+= -DSTRINGPUTX11

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
BLACK = "\033[38;2;52;52;52m"
UP = "\033[A"
CUT = "\033[K"
COUNT_SRC := 9

%.o : %.c
	@tput civis;
	@if [ $(COUNT) -eq 0 ] ; then\
		printf $(Y)"Compiling $(NOM):\n";\
		fi;
	@cc $(CFLAGS) -DSTRINGPUTX11 -c -o $@ $< || tput cnorm
	@$(eval COUNT := $(shell ls -R | grep -E "\.o" | wc -w))
	@$(eval COUNT := $(shell echo $$(($(COUNT)+1))))
	@if [ $(COUNT) -ne $$(($(COUNT_SRC) + 1)) ]; then\
		printf "\r"; \
		x=0 ; \
		while [ $$x -ne $(COUNT) ]; do \
			printf $(G)"▇"; \
			let "x+=1"; \
		done ; \
		y=0; \
		for x in $(SRC); do \
			let "y+=1"; \
		done ; \
		x=$(COUNT); \
		while [ $$x -ne $$y ] ; do \
			printf " "; \
			let "x+=1"; \
		done; \
		x=$(COUNT); \
		let "x*=100"; \
		printf $(X)"| "; \
		printf "%d" $$((x / y)); \
		printf "%%"; \
	else \
		printf $(G)"▇"; \
	fi

%.o : %.m
	@tput civis;
	@if [ $(COUNT) -eq 0 ] ; then\
		printf $(Y)"Compiling $(NOM):\n";\
		fi;
	@cc $(CFLAGS) -DSTRINGPUTX11 -c -o $@ $< || tput cnorm
	@$(eval COUNT := $(shell ls -R | grep -E "\.o" | wc -w))
	@$(eval COUNT := $(shell echo $$(($(COUNT)+1))))
	@printf "\r"; \
	x=0 ; \
	while [ $$x -ne $(COUNT) ]; do \
		printf $(G)"▇"; \
		let "x+=1"; \
	done ; \
	y=0; \
	for x in $(SRC); do \
		let "y+=1"; \
	done ; \
	x=$(COUNT); \
	while [ $$x -ne $$y ] ; do \
		printf " "; \
		let "x+=1"; \
	done; \
	x=$(COUNT); \
	let "x*=100"; \
	printf $(X)"| "; \
	printf "%d" $$((x / y)); \
	printf "%%";

internal-all: $(NOM)

all:
	@bash -c "trap 'trap - SIGINT SIGTERM ERR; tput cnorm --normal; exit 1' SIGINT SIGTERM ERR; $(MAKE) internal-all"

$(NOM):	$(OBJ)
	@ar -rc $(NOM) $(OBJ)
	@ranlib $(NOM)
	@echo
	@tput cnorm

internal-clean:
	@$(eval OBJ := $(shell find $(PWD) | grep -E "\.o" ))
	@tput civis;\
		size=0; \
		for d in $(OBJ); do\
			let "size+=1";\
		done;\
		y=0;\
		for x in $(OBJ); do\
			let "y+=1"; \
			i=0; \
			printf "\r";\
			while [ $$i -ne $$y ]; do \
				printf $(G)"▇"; \
				let "i+=1"; \
			done; \
			while [ $$i -ne $$size ]; do \
				let "i+=1"; \
				printf " "; \
			done; \
			printf $(X)"| ";\
			printf $$((y * 100 / i)); \
			printf "%%";\
			sleep 0.05; \
			rm -f $$x; \
		done;\
		printf $(X)"\n";\
		tput cnorm --normal

clean:
	@printf $(Y)"Cleaning object-files and removing $(NOM):\n"
	@bash -c "trap 'trap - SIGINT SIGTERM ERR; tput cnorm --normal; exit 1' SIGINT SIGTERM ERR; $(MAKE) internal-clean"
	@rm -f $(NOM)

re: clean all
