# $@ = target file
# $< = first dependency
# $^ = all dependencies

# detect all .o files based on their .c source

CC = gcc

INCLUDE_DIR = src/include

CFLAGS = -F /Library/Frameworks -framework SDL2 -I$(INCLUDE_DIR)

C_SOURCES = $(wildcard src/lib/*.c src/*.c)

DEPS = $(wildcard $(INCLUDE_DIR)/*.h)
OBJ = ${C_SOURCES:.c=.o}

# First rule is the one executed when no parameters are fed to the Makefile

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

3D-graphics: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) src/*.bin src/*.o src/*.dis src/*.elf
	$(RM) src/*/*.bin src/*/*.o src/*/*.dis src/*/*.elf
