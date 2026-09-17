CC=gcc

IFLAGS = -Iinclude -ID:/main/others/includes
LFLAGS = -LD:/main/others/libraries/glfw -lglfw3 -lgdi32
CFLAGS = -Wdiscarded-qualifiers $(IFLAGS) $(LFLAGS)

SOURCE_DIR=src

ODIR=obj


# Create list of object file paths from their names
_OBJ = main.o glad.o utils/file_utils.o backends/graphics/opengl_backend.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# TODO: Generate all needed folders for obj files


$(ODIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

malt.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Delete all object file if "make clean" is ran
.PHONY: clean

clean:
	rm -rf %(ODIR)/*.o