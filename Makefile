SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

ES_FRAMEWORK_SRC_DIR := es-framework
ES_FRAMEWORK_OBJ_DIR := $(OBJ_DIR)/$(ES_FRAMEWORK_SRC_DIR)

RENDIX_SRC_DIR := rendix/source
RENDIX_INC_DIR := rendix/include
RENDIX_OBJ_DIR := $(OBJ_DIR)/rendix

rendix-triangle_SRC_DIR := $(SRC_DIR)/rendix-triangle
rendix-triangle_OBJ_DIR := $(OBJ_DIR)/rendix-triangle

GLM_DIR := glm

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
RENDIX_OBJ_DIR := $(subst /,\,$(RENDIX_OBJ_DIR))
else
RM := rm -rfv
RMDIR := $(RM)
MKDIR := mkdir -p
endif

TARGETS := triangle moving-triangle square perfect-square hello-world-text vbo-triangle gstreamer-tutorial-01-hello-world gstreamer-tutorial-02-gstreamer-concepts
RENDIX_TARGETS := rendix-triangle

BINS := $(TARGETS:%=$(BIN_DIR)/%)
RENDIX_BINS := $(RENDIX_TARGETS:%=$(BIN_DIR)/%)
SRC := $(SRC_DIR)/gl-utils.c $(ES_FRAMEWORK_SRC_DIR)/esUtil.c
RENDIX_SRC := \
    $(RENDIX_SRC_DIR)/core/Application.cpp \
    $(RENDIX_SRC_DIR)/core/Engine.cpp \
    $(RENDIX_SRC_DIR)/core/ESUtilWindowSystem.cpp \
    $(RENDIX_SRC_DIR)/main_loop/ESUtilMainLoopStrategy.cpp \
    $(RENDIX_SRC_DIR)/rendering/GLESConvert.cpp \
    $(RENDIX_SRC_DIR)/rendering/GLESMesh.cpp \
    $(RENDIX_SRC_DIR)/rendering/GLESRenderer.cpp \
    $(RENDIX_SRC_DIR)/shaders/GLESShader.cpp \
    $(RENDIX_SRC_DIR)/shaders/GLESShaderProgram.cpp \
    $(RENDIX_SRC_DIR)/texturing/Texture.cpp \
    $(RENDIX_SRC_DIR)/utils/FileReader.cpp

rendix-triangle_SRC := \
    $(rendix-triangle_SRC_DIR)/RendixTriangleApplication.cpp

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ := $(OBJ:$(ES_FRAMEWORK_SRC_DIR)/%.c=$(ES_FRAMEWORK_OBJ_DIR)/%.o)
RENDIX_OBJ := $(RENDIX_SRC:$(RENDIX_SRC_DIR)/%.cpp=$(RENDIX_OBJ_DIR)/%.o)
RENDIX_OBJ_SUBDIRS := $(foreach subdir,core main_loop rendering shaders texturing utils,$(RENDIX_OBJ_DIR)/$(subdir))

rendix-triangle_OBJ := $(rendix-triangle_SRC:$(rendix-triangle_SRC_DIR)/%.cpp=$(rendix-triangle_OBJ_DIR)/%.o)

NATIVE_DISPLAY_TYPE ?= x11

CC ?= $(CROSS_COMPILE)gcc

CPPFLAGS += -MMD -MP
CFLAGS ?= -Wall -g -O0
CFLAGS += -I$(ES_FRAMEWORK_SRC_DIR) -I$(SRC_DIR) $(shell pkg-config gstreamer-1.0 --cflags)
CXXFLAGS ?= -Wall -g -O0
CXXFLAGS += -I$(RENDIX_INC_DIR) -I$(RENDIX_SRC_DIR) -I$(GLM_DIR) -I$(ES_FRAMEWORK_SRC_DIR) -I$(SRC_DIR)
LDFLAGS += $(shell pkg-config gstreamer-1.0 --libs)

ifeq ($(NATIVE_DISPLAY_TYPE), x11)
CFLAGS += -DUSE_X11
LDFLAGS += -lEGL -lGLESv2 -lm -lX11
else ifeq ($(NATIVE_DISPLAY_TYPE), fb)
CFLAGS += -DUSE_FB=$(FB_NUMBER)
LDFLAGS += -lGAL -lVSC -lm -lEGL -lGLESv2
else ifeq ($(NATIVE_DISPLAY_TYPE), drm)
CFLAGS += -DUSE_DRM $(shell pkg-config libdrm gbm --cflags)
LDFLAGS += -lEGL -lGLESv2 -lm $(shell pkg-config libdrm gbm --libs)
endif

ifneq ($(GPU_PKG_CONFIG),)
CFLAGS += $(shell pkg-config $(GPU_PKG_CONFIG) --define-prefix=$(dir $(GPU_PKG_CONFIG))../../../ --cflags)
LDFLAGS += $(shell pkg-config $(GPU_PKG_CONFIG) --define-prefix=$(dir $(GPU_PKG_CONFIG))../../../ --libs)
endif

# PHONY targets
.PHONY: all clean $(TARGETS) $(RENDIX_TARGETS)

# All PHONY target, default target
all: $(TARGETS) $(RENDIX_TARGETS)

# All PHONY targets except all, clean and rendix
$(TARGETS) $(RENDIX_TARGETS): %: $(BIN_DIR)/%

# C targets

# C linking stage target, executable C binaries
$(BINS): $(BIN_DIR)/%: $(OBJ_DIR)/%.o $(OBJ) | $(BIN_DIR)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

# C compiling stage target, main C files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# C compiling stage target, es-framework C files
$(ES_FRAMEWORK_OBJ_DIR)/%.o: $(ES_FRAMEWORK_SRC_DIR)/%.c | $(ES_FRAMEWORK_OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# CPP targets

# CPP linking stage target, main CPP files
$(RENDIX_TARGETS): %: $(BIN_DIR)/%

$(BIN_DIR)/rendix-triangle: $(RENDIX_OBJ) $(OBJ) $(rendix-triangle_OBJ) $(OBJ_DIR)/rendix-triangle.o | $(BIN_DIR)
	$(CXX) $^ -o $@ $(CXXFLAGS) $(LDFLAGS)

# CPP compiling stage target, main CPP files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# CPP compiling stage target, rendix CPP files
$(RENDIX_OBJ_DIR)/%.o: $(RENDIX_SRC_DIR)/%.cpp | $(RENDIX_OBJ_SUBDIRS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(rendix-triangle_OBJ_DIR)/%.o: $(rendix-triangle_SRC_DIR)/%.cpp | $(rendix-triangle_OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Create output directories target
$(BIN_DIR) $(OBJ_DIR) $(ES_FRAMEWORK_OBJ_DIR) $(RENDIX_OBJ_SUBDIRS) $(rendix-triangle_OBJ_DIR):
	$(MKDIR) $@

# PHONY clean target
clean:
ifeq ($(UNAME),Windows)
	if exist $(BIN_DIR) $(RMDIR) $(BIN_DIR)
	if exist $(OBJ_DIR) $(RMDIR) $(OBJ_DIR)
else
	$(RMDIR) $(BIN_DIR)
	$(RMDIR) $(OBJ_DIR)
endif

install:
	install -d $(DESTDIR)$(PREFIX)/bin
	install -m 0755 $(BIN_DIR)/triangle $(DESTDIR)$(PREFIX)/bin/triangle
	install -m 0755 $(BIN_DIR)/moving-triangle $(DESTDIR)$(PREFIX)/bin/moving-triangle
	install -m 0755 $(BIN_DIR)/square $(DESTDIR)$(PREFIX)/bin/square
	install -m 0755 $(BIN_DIR)/perfect-square $(DESTDIR)$(PREFIX)/bin/perfect-square
	install -m 0755 $(BIN_DIR)/hello-world-text $(DESTDIR)$(PREFIX)/bin/hello-world-text
	install -m 0755 $(BIN_DIR)/gstreamer-tutorial-01-hello-world $(DESTDIR)$(PREFIX)/bin/gstreamer-tutorial-01-hello-world
	install -m 0755 $(BIN_DIR)/gstreamer-tutorial-02-gstreamer-concepts $(DESTDIR)$(PREFIX)/bin/gstreamer-tutorial-02-gstreamer-concepts

# Include dependency .d files
-include $(OBJ:.o=.d)
-include $(RENDIX_OBJ:.o=.d)
-include $(rendix-triangle_OBJ:.o=.d)
