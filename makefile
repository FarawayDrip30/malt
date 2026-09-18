CC=gcc

IFLAGS = -Iinclude -ID:/main/others/includes
LFLAGS = -LD:/main/others/libraries/glfw -lglfw3 -lgdi32
CFLAGS = -Wdiscarded-qualifiers $(IFLAGS) $(LFLAGS)

SOURCE_DIR=src

ODIR=obj


# Create list of object file paths from their names
_OBJ = main.o glad.o utils/file_utils.o backends/graphics/opengl_backend.o backends/graphics/graphics_handler.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SOURCE_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

malt.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean

# Delete all object file if "make clean" is ran
clean:
	rm -f $(ODIR)/*.o