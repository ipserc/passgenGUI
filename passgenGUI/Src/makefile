#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = gcc

# define any compile-time flags
#------ CFLAGS += -Wall -fopenmp -g $(shell pkg-config --cflags gtk+-3.0 gmodule-2.0 glib-2.0 libxml-2.0)  
CFLAGS += -Wall -fopenmp -g $(shell pkg-config --cflags gtk+-3.0 glib-2.0 libxml-2.0 libconfig) 
#$(shell xml2-config --cflags)

# define any directories containing header files other than /usr/include
#
# INCLUDES = -I/home/newhall/include  -I../include
INCLUDES += -I/opt/include
#INCLUDES += -include jsmnRipper.h -include jsmn.h

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
# LFLAGS = -L/home/newhall/lib  -L../lib
# Removed cause gmodule is dumping core LFLAGS += $(shell pkg-config --libs gtk+-3.0 gmodule-2.0 glib-2.0 libxml-2.0)
LFLAGS += $(shell pkg-config --libs gtk+-3.0 glib-2.0 libxml-2.0 libconfig)
LFLAGS += -L../lib -L/opt/lib


# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
# LIBS = -lmylib -lm -ljsmnRipper -llist
LIBS += -lz -lm

# define the C source files
# SRCS = emitter.c error.c init.c lexer.c main.c symbol.c parser.c

SRCS =  randomize.c \
		passgen_errtra.c \
		passgen_config.c \
		passgen_glade.c \
		passgen_status.c \
		passgen_gui_AboutDialog.c \
		passgen_gui_Status.c \
		passgen_gui_PasswordLength.c \
		passgen_gui_PasswordRules.c \
		passgen_gui_Password.c \
		passgen_gui_MenuBar.c \
		passgen_gui.c \
		passgen_params.c \
		passgen.c 

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.c=.o)

# define the executable file 
MAIN = passgen

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: all glade depend clean

all:	$(MAIN)
	@echo
	@echo ===========================================
	@echo  $(MAIN) has been compiled... 
	@echo  Compilation:`date`
	@echo ===========================================
	@echo

glade:
	./gladec.sh ../Glade/passgen.glade
	make
	
$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
	./gladec.sh ../Glade/passgen.glade
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
# DO NOT DELETE

randomize.o: randomize.h /usr/include/stdio.h /usr/include/stdlib.h
randomize.o: /usr/include/time.h /usr/include/features.h
randomize.o: /usr/include/stdc-predef.h /usr/include/string.h
randomize.o: /usr/include/strings.h
passgen_errtra.o: /usr/include/errno.h /usr/include/features.h
passgen_errtra.o: /usr/include/stdc-predef.h /usr/include/stdio.h
passgen_errtra.o: /usr/include/stdlib.h /usr/include/time.h passgen_errtra.h
passgen_config.o: passgen_config.h /usr/include/stdio.h
passgen_config.o: /usr/include/libconfig.h
passgen_config.o: /usr/include/asm-generic/errno-base.h /usr/include/errno.h
passgen_config.o: /usr/include/features.h /usr/include/stdc-predef.h
passgen_config.o: /usr/include/stdlib.h /usr/include/string.h
passgen_config.o: /usr/include/strings.h passgen_errtra.h passgen_gui.h
passgen_config.o: /usr/include/getopt.h /usr/include/ctype.h
passgen_config.o: /usr/include/libgen.h /usr/include/signal.h
passgen_config.o: /usr/include/math.h passgen_glade.h
passgen_config.o: passgen_gui_AboutDialog.h passgen_gui_PasswordLength.h
passgen_config.o: passgen_gui_PasswordRules.h passgen_status.h
passgen_config.o: passgen_gui_Password.h passgen_gui_MenuBar.h
passgen_config.o: passgen_gui_Status.h
passgen_status.o: passgen_status.h /usr/include/errno.h
passgen_status.o: /usr/include/features.h /usr/include/stdc-predef.h
passgen_status.o: /usr/include/stdio.h /usr/include/stdlib.h
passgen_status.o: /usr/include/string.h /usr/include/strings.h
passgen_status.o: /usr/include/getopt.h /usr/include/ctype.h
passgen_status.o: /usr/include/libgen.h /usr/include/signal.h
passgen_status.o: passgen_config.h /usr/include/libconfig.h
passgen_status.o: /usr/include/asm-generic/errno-base.h passgen_errtra.h
passgen_status.o: passgen_gui.h /usr/include/math.h passgen_glade.h
passgen_status.o: passgen_gui_AboutDialog.h passgen_gui_PasswordLength.h
passgen_status.o: passgen_gui_PasswordRules.h passgen_gui_Password.h
passgen_status.o: passgen_gui_MenuBar.h passgen_gui_Status.h
passgen_gui_AboutDialog.o: passgen_gui_AboutDialog.h /usr/include/errno.h
passgen_gui_AboutDialog.o: /usr/include/features.h /usr/include/stdc-predef.h
passgen_gui_AboutDialog.o: /usr/include/stdio.h /usr/include/stdlib.h
passgen_gui_AboutDialog.o: /usr/include/string.h /usr/include/strings.h
passgen_gui_AboutDialog.o: /usr/include/getopt.h /usr/include/ctype.h
passgen_gui_AboutDialog.o: /usr/include/libgen.h /usr/include/signal.h
passgen_gui_AboutDialog.o: /usr/include/math.h passgen_errtra.h
passgen_gui_AboutDialog.o: passgen_config.h /usr/include/libconfig.h
passgen_gui_AboutDialog.o: /usr/include/asm-generic/errno-base.h
passgen_gui_AboutDialog.o: passgen_gui.h passgen_glade.h
passgen_gui_AboutDialog.o: passgen_gui_PasswordLength.h
passgen_gui_AboutDialog.o: passgen_gui_PasswordRules.h passgen_status.h
passgen_gui_AboutDialog.o: passgen_gui_Password.h passgen_gui_MenuBar.h
passgen_gui_AboutDialog.o: passgen_gui_Status.h
passgen_gui_Status.o: passgen_gui_Status.h /usr/include/errno.h
passgen_gui_Status.o: /usr/include/features.h /usr/include/stdc-predef.h
passgen_gui_Status.o: /usr/include/stdio.h /usr/include/stdlib.h
passgen_gui_Status.o: /usr/include/string.h /usr/include/strings.h
passgen_gui_Status.o: /usr/include/getopt.h /usr/include/ctype.h
passgen_gui_Status.o: /usr/include/libgen.h /usr/include/signal.h
passgen_gui_Status.o: passgen_errtra.h passgen_glade.h passgen_config.h
passgen_gui_Status.o: /usr/include/libconfig.h
passgen_gui_Status.o: /usr/include/asm-generic/errno-base.h passgen_gui.h
passgen_gui_Status.o: /usr/include/math.h passgen_gui_AboutDialog.h
passgen_gui_Status.o: passgen_gui_PasswordLength.h
passgen_gui_Status.o: passgen_gui_PasswordRules.h passgen_status.h
passgen_gui_Status.o: passgen_gui_Password.h passgen_gui_MenuBar.h
passgen_gui_PasswordLength.o: passgen_gui_PasswordLength.h
passgen_gui_PasswordLength.o: /usr/include/errno.h /usr/include/features.h
passgen_gui_PasswordLength.o: /usr/include/stdc-predef.h /usr/include/stdio.h
passgen_gui_PasswordLength.o: /usr/include/stdlib.h /usr/include/string.h
passgen_gui_PasswordLength.o: /usr/include/strings.h /usr/include/getopt.h
passgen_gui_PasswordLength.o: /usr/include/ctype.h /usr/include/libgen.h
passgen_gui_PasswordLength.o: /usr/include/signal.h passgen_errtra.h
passgen_gui_PasswordLength.o: passgen_glade.h passgen_config.h
passgen_gui_PasswordLength.o: /usr/include/libconfig.h
passgen_gui_PasswordLength.o: /usr/include/asm-generic/errno-base.h
passgen_gui_PasswordLength.o: passgen_gui.h /usr/include/math.h
passgen_gui_PasswordLength.o: passgen_gui_AboutDialog.h
passgen_gui_PasswordLength.o: passgen_gui_PasswordRules.h passgen_status.h
passgen_gui_PasswordLength.o: passgen_gui_Password.h passgen_gui_MenuBar.h
passgen_gui_PasswordLength.o: passgen_gui_Status.h
passgen_gui_PasswordRules.o: passgen_gui_PasswordRules.h /usr/include/errno.h
passgen_gui_PasswordRules.o: /usr/include/features.h
passgen_gui_PasswordRules.o: /usr/include/stdc-predef.h /usr/include/stdio.h
passgen_gui_PasswordRules.o: /usr/include/stdlib.h /usr/include/string.h
passgen_gui_PasswordRules.o: /usr/include/strings.h /usr/include/getopt.h
passgen_gui_PasswordRules.o: /usr/include/ctype.h /usr/include/libgen.h
passgen_gui_PasswordRules.o: /usr/include/signal.h passgen_errtra.h
passgen_gui_PasswordRules.o: passgen_config.h /usr/include/libconfig.h
passgen_gui_PasswordRules.o: /usr/include/asm-generic/errno-base.h
passgen_gui_PasswordRules.o: passgen_gui.h /usr/include/math.h
passgen_gui_PasswordRules.o: passgen_glade.h passgen_gui_AboutDialog.h
passgen_gui_PasswordRules.o: passgen_gui_PasswordLength.h
passgen_gui_PasswordRules.o: passgen_gui_Password.h passgen_gui_MenuBar.h
passgen_gui_PasswordRules.o: passgen_gui_Status.h passgen_status.h
passgen_gui_Password.o: passgen_gui_Password.h /usr/include/errno.h
passgen_gui_Password.o: /usr/include/features.h /usr/include/stdc-predef.h
passgen_gui_Password.o: /usr/include/stdio.h /usr/include/stdlib.h
passgen_gui_Password.o: /usr/include/string.h /usr/include/strings.h
passgen_gui_Password.o: /usr/include/getopt.h /usr/include/ctype.h
passgen_gui_Password.o: /usr/include/libgen.h /usr/include/signal.h
passgen_gui_Password.o: passgen_errtra.h passgen_glade.h passgen_config.h
passgen_gui_Password.o: /usr/include/libconfig.h
passgen_gui_Password.o: /usr/include/asm-generic/errno-base.h passgen_gui.h
passgen_gui_Password.o: /usr/include/math.h passgen_gui_AboutDialog.h
passgen_gui_Password.o: passgen_gui_PasswordLength.h
passgen_gui_Password.o: passgen_gui_PasswordRules.h passgen_status.h
passgen_gui_Password.o: passgen_gui_MenuBar.h passgen_gui_Status.h
passgen_gui_MenuBar.o: passgen_gui_MenuBar.h /usr/include/errno.h
passgen_gui_MenuBar.o: /usr/include/features.h /usr/include/stdc-predef.h
passgen_gui_MenuBar.o: /usr/include/stdio.h /usr/include/stdlib.h
passgen_gui_MenuBar.o: /usr/include/string.h /usr/include/strings.h
passgen_gui_MenuBar.o: /usr/include/getopt.h /usr/include/ctype.h
passgen_gui_MenuBar.o: /usr/include/libgen.h /usr/include/signal.h
passgen_gui_MenuBar.o: passgen_config.h /usr/include/libconfig.h
passgen_gui_MenuBar.o: /usr/include/asm-generic/errno-base.h passgen_errtra.h
passgen_gui_MenuBar.o: passgen_gui.h /usr/include/math.h passgen_glade.h
passgen_gui_MenuBar.o: passgen_gui_AboutDialog.h passgen_gui_PasswordLength.h
passgen_gui_MenuBar.o: passgen_gui_PasswordRules.h passgen_status.h
passgen_gui_MenuBar.o: passgen_gui_Password.h passgen_gui_Status.h
passgen_gui.o: passgen_gui.h /usr/include/errno.h /usr/include/features.h
passgen_gui.o: /usr/include/stdc-predef.h /usr/include/stdio.h
passgen_gui.o: /usr/include/stdlib.h /usr/include/string.h
passgen_gui.o: /usr/include/strings.h /usr/include/getopt.h
passgen_gui.o: /usr/include/ctype.h /usr/include/libgen.h
passgen_gui.o: /usr/include/signal.h /usr/include/math.h passgen_errtra.h
passgen_gui.o: passgen_config.h /usr/include/libconfig.h
passgen_gui.o: /usr/include/asm-generic/errno-base.h passgen_glade.h
passgen_gui.o: passgen_gui_AboutDialog.h passgen_gui_PasswordLength.h
passgen_gui.o: passgen_gui_PasswordRules.h passgen_status.h
passgen_gui.o: passgen_gui_Password.h passgen_gui_MenuBar.h
passgen_gui.o: passgen_gui_Status.h
passgen_params.o: passgen_params.h /usr/include/errno.h
passgen_params.o: /usr/include/features.h /usr/include/stdc-predef.h
passgen_params.o: /usr/include/stdio.h /usr/include/stdlib.h
passgen_params.o: /usr/include/string.h /usr/include/strings.h
passgen_params.o: /usr/include/getopt.h /usr/include/ctype.h
passgen_params.o: /usr/include/libgen.h /usr/include/signal.h
passgen_params.o: /usr/include/time.h
passgen.o: passgen.h /usr/include/errno.h /usr/include/features.h
passgen.o: /usr/include/stdc-predef.h /usr/include/stdio.h
passgen.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/strings.h
passgen.o: /usr/include/getopt.h /usr/include/ctype.h /usr/include/libgen.h
passgen.o: /usr/include/signal.h /usr/include/time.h randomize.h
passgen.o: passgen_errtra.h passgen_gui_PasswordLength.h passgen_glade.h
passgen.o: passgen_config.h /usr/include/libconfig.h
passgen.o: /usr/include/asm-generic/errno-base.h passgen_gui.h
passgen.o: /usr/include/math.h passgen_gui_AboutDialog.h
passgen.o: passgen_gui_PasswordRules.h passgen_status.h
passgen.o: passgen_gui_Password.h passgen_gui_MenuBar.h passgen_gui_Status.h
passgen.o: passgen_params.h
