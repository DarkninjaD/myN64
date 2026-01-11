# -------------------------------------------------
# Project metadata
# -------------------------------------------------
ROMNAME := main
ROMTITLE := "First N64 Game"

# -------------------------------------------------
# ROM metadata
# -------------------------------------------------
$(ROMNAME).z64: N64_ROM_TITLE := $(ROMTITLE)

# -------------------------------------------------
# Directories
# -------------------------------------------------
BUILD_DIR := build
SRC_DIR := src
ASSETS_DIR := assets
FILESYSTEM_DIR := filesystem

# -------------------------------------------------
# Assets
#   Find all assets and convert
# -------------------------------------------------
assets_png = $(wildcard $(ASSETS_DIR)/*.png)
assets_ttf = $(wildcard $(ASSETS_DIR)/*.ttf)

assets_conv = \
	$(addprefix $(FILESYSTEM_DIR)/, $(notdir $(assets_png:%.png=%.sprite))) \
	$(addprefix $(FILESYSTEM_DIR)/, $(notdir $(assets_ttf:%.ttf=%.font64)))


# -------------------------------------------------
# Source discovery & Create Objects
#    aka Convert `src/foo/bar.c` to `build/src/foo/bar.o`
# -------------------------------------------------
SRC = \
	$(wildcard $(SRC_DIR)/*.c) \
	$(wildcard $(SRC_DIR)/*/*.c) \
	$(wildcard $(SRC_DIR)/*/*/*.c)

OBJS = $(SRC:%.c=$(BUILD_DIR)/%.o)

# -------------------------------------------------
# import libdragons make dependencies
# -------------------------------------------------
include $(N64_INST)/include/n64.mk

# -------------------------------------------------
# The Main rule
# -------------------------------------------------
all: $(ROMNAME).z64

# -------------------------------------------------
# Tell libdragon to build with assets
# -------------------------------------------------
$(ROMNAME).z64: $(BUILD_DIR)/$(ROMNAME).dfs

# -------------------------------------------------
# Tell libdragon what to build with objects
# -------------------------------------------------
$(BUILD_DIR)/$(ROMNAME).elf: $(OBJS)
$(BUILD_DIR)/$(ROMNAME).dfs: $(assets_conv)

# -------------------------------------------------
# Asset rule
#   use mksprite to create compatible N64 sprites
# -------------------------------------------------
$(FILESYSTEM_DIR)/%.sprite: $(ASSETS_DIR)/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	@$(N64_MKSPRITE) -f RGBA16 -o "$(dir $@)" "$<"

# -------------------------------------------------
# Font rule
#   use mkfont to create compatible N64 sprites
# -------------------------------------------------
$(FILESYSTEM_DIR)/%.font64: $(ASSETS_DIR)/%.ttf
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	@$(N64_MKFONT) -o "$(dir $@)" "$<"
# -------------------------------------------------
# Clean rule
#   remove all build artifacts
# -------------------------------------------------
clean:
	rm -rf $(BUILD_DIR) $(FILESYSTEM_DIR) *.z64

.PHONY: all clean