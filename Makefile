SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

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

TARGETS := triangle moving-triangle square perfect-square hello-world-text gstreamer-tutorial-01-hello-world gstreamer-tutorial-02-gstreamer-concepts

BINS := $(TARGETS:%=$(BIN_DIR)/%)
SRC := $(SRC_DIR)/gl-utils.c $(ES_FRAMEWORK_DIR)/esUtil.c

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ := $(OBJ:$(ES_FRAMEWORK_DIR)/%.c=$(ES_FRAMEWORK_OBJ_DIR)/%.o)

NATIVE_DISPLAY_TYPE ?= x11

CC ?= $(CROSS_COMPILE)gcc

CPPFLAGS += -MMD -MP
CFLAGS ?= -Wall -g -O0
CFLAGS += -I$(ES_FRAMEWORK_DIR) -I$(SRC_DIR) $(shell pkg-config gstreamer-1.0 --cflags)
LDFLAGS ?= $(shell pkg-config gstreamer-1.0 --libs)

ifeq ($(NATIVE_DISPLAY_TYPE), x11)
CFLAGS += -DUSE_X11
LDFLAGS += -lEGL -lGLESv2 -lm -lX11
else
ifeq ($(NATIVE_DISPLAY_TYPE), fb)
CFLAGS += -DUSE_FB=$(FB_NUMBER)
LDFLAGS += -lGAL -lVSC -lm -lEGL -lGLESv2
else
CFLAGS += -DUSE_DRM
LDFLAGS += -lEGL -lGLESv2 -lm
endif
endif

ifneq ($(GPU_PKG_CONFIG),)
CFLAGS += $(shell pkg-config $(GPU_PKG_CONFIG) --define-prefix=$(dir $(GPU_PKG_CONFIG))../../../ --cflags)
LDFLAGS += $(shell pkg-config $(GPU_PKG_CONFIG) --define-prefix=$(dir $(GPU_PKG_CONFIG))../../../ --libs)
endif

.PHONY: all clean $(TARGETS)

all: $(TARGETS)

$(TARGETS): %: $(BIN_DIR)/%

$(BINS): $(BIN_DIR)/%: $(OBJ_DIR)/%.o $(OBJ) | $(BIN_DIR)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

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
else
	$(RMDIR) $(BIN_DIR)
	$(RMDIR) $(OBJ_DIR)
endif

-include $(OBJ:.o=.d)
