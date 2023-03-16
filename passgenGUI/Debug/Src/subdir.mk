################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/String.c \
../Src/passgen.c \
../Src/passgen_config.c \
../Src/passgen_errtra.c \
../Src/passgen_glade.c \
../Src/passgen_gui.c \
../Src/randomize.c 

O_SRCS += \
../Src/String.o \
../Src/passgen.o \
../Src/passgen_config.o \
../Src/passgen_errtra.o \
../Src/passgen_glade.o \
../Src/passgen_gui.o \
../Src/randomize.o 

C_DEPS += \
./Src/String.d \
./Src/passgen.d \
./Src/passgen_config.d \
./Src/passgen_errtra.d \
./Src/passgen_glade.d \
./Src/passgen_gui.d \
./Src/randomize.d 

OBJS += \
./Src/String.o \
./Src/passgen.o \
./Src/passgen_config.o \
./Src/passgen_errtra.o \
./Src/passgen_glade.o \
./Src/passgen_gui.o \
./Src/randomize.o 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/opt/include -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/mirclient -I/usr/include/mircore -I/usr/include/mircookie -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libpng16 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/libxml2 -I/home/ipserc/workspace_oxigen/zhavam/Source -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Src

clean-Src:
	-$(RM) ./Src/String.d ./Src/String.o ./Src/passgen.d ./Src/passgen.o ./Src/passgen_config.d ./Src/passgen_config.o ./Src/passgen_errtra.d ./Src/passgen_errtra.o ./Src/passgen_glade.d ./Src/passgen_glade.o ./Src/passgen_gui.d ./Src/passgen_gui.o ./Src/randomize.d ./Src/randomize.o

.PHONY: clean-Src

