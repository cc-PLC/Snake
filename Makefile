# Disable built-in rules
MAKECFLAGS += --no-builtin-rules

# Tell `make` that these are pure rules, not files.
.PHONY : all clean debug release routine check-directories

# `.SILENT:` is obsolete since `@` is more flexible

# Define the compiler
CC := g++
# Define the linker driver
LD := g++

CFLAGS		:= -std=c++11
LDFLAGS		:= -mconsole

LIBRARIES	:= 


# The directories
DIR_SRC := ./src
DIR_OBJ := ./obj

# The directories to be created
DIRS := $(DIR_OBJ)

# The files
EXECUTABLE	:= Snake.1.3.exe
SRCS		:= $(wildcard $(DIR_SRC)/*.cpp)
OBJS		:= $(patsubst $(DIR_SRC)/%.cpp,$(DIR_OBJ)/%.o,$(SRCS))
OBJS		:= $(filter-out $(DIR_OBJ)/main.o,$(OBJS))


# MAKE SURE YOU `CLEAN` BEFORE CHANGING MODE!!!

# ==== Release mode (default) ====
release:	CFLAGS	+= -O3 -DRELEASE_MODE
release:	LDFLAGS	+= -O3 -s -static -static-libgcc -static-libstdc++
release:	routine
# ========== Debug mode ==========
debug:		CFLAGS	+= -g -Wall
debug:		routine
# ================================

routine: check-directories $(EXECUTABLE)

check-directories:
	@for %%d in ($(DIRS)) do ( \
		if not exist "%%d" ( \
			mkdir "%%d" \
		) \
	)

$(EXECUTABLE): $(DIR_OBJ)/main.o $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBRARIES)

$(DIR_OBJ)/main.o: $(DIR_SRC)/main.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.cpp $(DIR_SRC)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-del /F /Q $(EXECUTABLE) 2>NUL
	-rmdir /S /Q "$(DIR_OBJ)" 2>NUL
