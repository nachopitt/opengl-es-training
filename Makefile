SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
INSTALL_DIR := install

ES_FRAMEWORK_DIR := es-framework
ES_FRAMEWORK_OBJ_DIR := $(OBJ_DIR)/$(ES_FRAMEWORK_DIR)

ifeq '$(findstring ;,$(PATH))' ';'
UNAME := Windows
else
UNAME := $(shell uname 2>/dev/null || echo Unknown)
UNAME := $(patsubst CYGWIN%,Cygwin,$(UNAME))
UNAME := $(patsubst MSYS%,MSYS,$(UNAME))
UNAME := $(patsubst MINGW%,MSYS,$(UNAME))
endif

ifeq ($(UNAME),Windows)
RM := DEL /Q /F
RMDIR := RMDIR /Q /S
MKDIR := MKDIR
ES_FRAMEWORK_OBJ_DIR := $(subst /,\,$(ES_FRAMEWORK_OBJ_DIR))
else
RM := rm -rfv
RMDIR := $(RM)
MKDIR := mkdir -p
endif

BIN := triangle

SRC := $(SRC_DIR)/triangle.c $(ES_FRAMEWORK_DIR)/esUtil.c

INC := -I$(ES_FRAMEWORK_DIR)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ := $(OBJ:$(ES_FRAMEWORK_DIR)/%.c=$(ES_FRAMEWORK_OBJ_DIR)/%.o)

CPPFLAGS := $(INC) -MMD -MP
CFLAGS := -Wall -g -O0

LDFLAGS := -lGLESv2 -lEGL -lm -lX11

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJ) | $(BIN_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(ES_FRAMEWORK_OBJ_DIR)/%.o: $(ES_FRAMEWORK_DIR)/%.c | $(ES_FRAMEWORK_OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR) $(ES_FRAMEWORK_OBJ_DIR):
	$(MKDIR) $@

clean:
ifeq ($(UNAME),Windows)
	if exist $(BIN_DIR) $(RMDIR) $(BIN_DIR)
	if exist $(OBJ_DIR) $(RMDIR) $(OBJ_DIR)
	if exist $(INSTALL_DIR) $(RMDIR) $(INSTALL_DIR)
else
	$(RMDIR) $(BIN_DIR)
	$(RMDIR) $(OBJ_DIR)
	$(RMDIR) $(INSTALL_DIR)
endif

-include $(OBJ:.o=.d)
