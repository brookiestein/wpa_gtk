CC 	:= gcc
CFLAGS 	:= -O2 -pipe -march=native -m64 -std=c99 -Wall -Wextra -Iincludes
CFLAGS 	+= $(shell pkg-config --cflags --libs gtk+-3.0)
TARGET 	:= wpagtk
PREFIX 	:= /usr/local/bin
SHARE 	:= /usr/share
COPY 	:= cp -f -r
MOVE 	:= mv -f
REMOVE 	:= rm -f -r
MKDIR 	:= mkdir -p
OBJ_DIR := objects
RES 	:= resources

SOURCES := src/main.c \
	src/show_message.c \
	src/leave.c \
	src/clear_fields.c \
	src/get_info.c \
	src/get_help.c \
	src/save_and_connect.c

OBJECTS := ${SOURCES:.c=.o}

all : mkobjs $(OBJECTS)
	$(CC) $(SOURCES) $(CFLAGS) -o $(TARGET)
	@$(MOVE) $(OBJECTS) $(OBJ_DIR)

.PHONY : mkobjs
mkobjs :
	@$(MKDIR) $(OBJ_DIR)

.PHONY : clean
clean :
	@echo "Cleaning..."
	@$(REMOVE) $(OBJ_DIR)
	@echo "Cleaning finished."

.PHONY : install
install : sure_environment
	@echo "Installing..."
	@$(COPY) $(TARGET) $(PREFIX)
	@$(COPY) $(RES) $(SHARE)/$(TARGET)
	@echo "Installation finished."

.PHONY : sure_environment
sure_environment :
	@$(MKDIR) $(PREFIX)
	@$(MKDIR) $(SHARE)/$(TARGET)

.PHONY : uninstall
uninstall :
	@echo "Uninstalling..."
	@$(REMOVE) $(PREFIX)/$(TARGET)
	@$(REMOVE) $(SHARE)/$(TARGET)
	@echo "Uninstallation finished."
