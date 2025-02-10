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

TARGETS := triangle moving-triangle square perfect-square hello-world-text vbo-triangle gstreamer-tutorial-01-hello-world gstreamer-tutorial-02-gstreamer-concepts

BINS := $(TARGETS:%=$(BIN_DIR)/%)
SRC := $(SRC_DIR)/gl-utils.c $(ES_FRAMEWORK_DIR)/esUtil.c

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ := $(OBJ:$(ES_FRAMEWORK_DIR)/%.c=$(ES_FRAMEWORK_OBJ_DIR)/%.o)

# x11, fb, drm, gbm, kms
NATIVE_PLATFORM ?= x11

CC ?= $(CROSS_COMPILE)gcc

CPPFLAGS += -MMD -MP -DEGL_EGLEXT_PROTOTYPES
CFLAGS ?= -Wall -g -O0
CFLAGS += -I$(ES_FRAMEWORK_DIR) -I$(SRC_DIR) $(shell pkg-config gstreamer-1.0 --cflags)
LDFLAGS += $(shell pkg-config gstreamer-1.0 --libs)

PKG_CONFIG_GPU ?=
PKG_CONFIG_LIBKMS ?=

ifeq ($(NATIVE_PLATFORM), x11)
CPPFLAGS += -DUSE_X11
LDFLAGS += -lEGL -lGLESv2 -lm -lX11
else ifeq ($(NATIVE_PLATFORM), fb)
CPPFLAGS += -DUSE_FB=$(FB_NUMBER)
LDFLAGS += -lGAL -lVSC -lm -lEGL -lGLESv2
else ifneq (,$(filter $(NATIVE_PLATFORM),drm gbm kms))
CPPFLAGS += -DUSE_DRM
CFLAGS += $(shell pkg-config libdrm --cflags)
LDFLAGS += $(shell pkg-config libdrm --libs)
ifeq ($(NATIVE_PLATFORM), gbm)
CPPFLAGS += -DUSE_GBM
CFLAGS += $(shell pkg-config gbm --cflags)
LDFLAGS += $(shell pkg-config gbm --libs)
else ifeq ($(NATIVE_PLATFORM), kms)
CPPFLAGS += -DUSE_KMS
ifneq ($(PKG_CONFIG_LIBKMS),)
CFLAGS += $(shell PKG_CONFIG_PATH= PKG_CONFIG_LIBDIR=$(PKG_CONFIG_LIBKMS)/usr/local/lib/x86_64-linux-gnu/pkgconfig PKG_CONFIG_SYSROOT_DIR=$(PKG_CONFIG_LIBKMS) pkg-config libkms --cflags)
LDFLAGS += $(shell PKG_CONFIG_PATH= PKG_CONFIG_LIBDIR=$(PKG_CONFIG_LIBKMS)/usr/local/lib/x86_64-linux-gnu/pkgconfig PKG_CONFIG_SYSROOT_DIR=$(PKG_CONFIG_LIBKMS) pkg-config libkms --libs)
else
CFLAGS += $(shell pkg-config libkms --cflags)
LDFLAGS += $(shell pkg-config libkms --libs)
endif
endif
LDFLAGS += -lEGL -lGLESv2 -lm
endif

ifneq ($(PKG_CONFIG_GPU),)
CFLAGS += $(shell pkg-config $(PKG_CONFIG_GPU) --define-prefix=$(dir $(PKG_CONFIG_GPU))../../../ --cflags)
LDFLAGS += $(shell pkg-config $(PKG_CONFIG_GPU) --define-prefix=$(dir $(PKG_CONFIG_GPU))../../../ --libs)
endif

DRM_SRC_DIR := drm
DRM_BUILD_DIR := drm_build
DRM_INSTALL_DIR := $(shell pwd)/drm_install
DRM_GIT_REPO_URL := https://gitlab.freedesktop.org/nachopitt/drm.git
LIBKMS := $(DRM_INSTALL_DIR)/usr/local/lib/x86_64-linux-gnu/libkms.so

.PHONY: all clean $(TARGETS) libkms clean-libkms

all: $(TARGETS)

$(TARGETS): %: $(BIN_DIR)/%

$(BINS): $(BIN_DIR)/%: $(OBJ_DIR)/%.o $(OBJ) | $(BIN_DIR)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(ES_FRAMEWORK_OBJ_DIR)/%.o: $(ES_FRAMEWORK_DIR)/%.c | $(ES_FRAMEWORK_OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR) $(ES_FRAMEWORK_OBJ_DIR) $(DRM_BUILD_DIR) $(DRM_INSTALL_DIR):
	$(MKDIR) $@

libkms: $(LIBKMS)

$(LIBKMS): $(DRM_BUILD_DIR) $(DRM_INSTALL_DIR)
	git clone $(DRM_GIT_REPO_URL) $(DRM_SRC_DIR)
	meson setup $(DRM_BUILD_DIR) $(DRM_SRC_DIR)
	meson compile -C $(DRM_BUILD_DIR)
	meson install -C $(DRM_BUILD_DIR) --destdir $(DRM_INSTALL_DIR)

clean:
ifeq ($(UNAME),Windows)
	if exist $(BIN_DIR) $(RMDIR) $(BIN_DIR)
	if exist $(OBJ_DIR) $(RMDIR) $(OBJ_DIR)
else
	$(RMDIR) $(BIN_DIR) $(OBJ_DIR)
endif

clean-libkms:
ifeq ($(UNAME),Windows)
	if exist $(DRM_SRC_DIR) $(RMDIR) $(DRM_SRC_DIR)
	if exist $(DRM_BUILD_DIR) $(RMDIR) $(DRM_BUILD_DIR)
	if exist $(DRM_INSTALL_DIR) $(RMDIR) $(DRM_INSTALL_DIR)
else
	$(RMDIR) $(DRM_SRC_DIR) $(DRM_BUILD_DIR) $(DRM_INSTALL_DIR)
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

-include $(OBJ:.o=.d)
