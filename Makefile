# -------------------------------------------------
# Project Metadata
# -------------------------------------------------
ROMNAME := main
ROMTITLE := "First N64 Game"

# -------------------------------------------------
# ROM Metadata
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
# Assets Discovery
# -------------------------------------------------

# Find general assets in the root assets directory
assets_png = $(wildcard $(ASSETS_DIR)/*.png)
assets_ttf = $(wildcard $(ASSETS_DIR)/*.ttf)

# Find core logo assets under assets/core/
IMAGE_LIST = $(wildcard $(ASSETS_DIR)/core/*.png)
MODEL_LIST = $(wildcard $(ASSETS_DIR)/core/*.glb)
SOUND2_LIST = $(wildcard $(ASSETS_DIR)/core/*.mp3)

# -------------------------------------------------
# Create Filesystem Destination Mappings
#   We use `subst` instead of `notdir` to preserve
#   the folder structure (e.g. assets/core/ -> filesystem/core/)
# -------------------------------------------------
ASSETS_CONV += $(subst $(ASSETS_DIR),$(FILESYSTEM_DIR),$(assets_png:%.png=%.sprite))
ASSETS_CONV += $(subst $(ASSETS_DIR),$(FILESYSTEM_DIR),$(assets_ttf:%.ttf=%.font64))
ASSETS_CONV += $(subst $(ASSETS_DIR),$(FILESYSTEM_DIR),$(IMAGE_LIST:%.png=%.sprite))
ASSETS_CONV += $(subst $(ASSETS_DIR),$(FILESYSTEM_DIR),$(MODEL_LIST:%.glb=%.t3dm))
ASSETS_CONV += $(subst $(ASSETS_DIR),$(FILESYSTEM_DIR),$(SOUND2_LIST:%.mp3=%.wav64))

# ------------------------------------------------------------------------------
# Asset-Specific Compilation Flags
# ------------------------------------------------------------------------------
# These rules specify additional parameters for building individual asset files.
#
# - MKSPRITE_FLAGS: Options for n64mksprite tool.
#   - --format CI4: Compress texture to 4-bit Color Indexed format (16 colors) to save RAM.
#   - --format I4: Compress to 4-bit Intensity format (grayscale transparency).
#   - --format RGB16:
#   - -c 2: Compress using Codec 2 (LZ4 compression) for smaller ROM size.
#
# - AUDIOCONV_FLAGS: Options for n64audioconv tool.
#   - --wav-resample 32000: Resample audio files to 32kHz to standardise playback.
#   - --wav-mono: Convert stereo files to mono (saves 50% space, ideal for simple audio).
#   - --wav-compress 3: Compress using Codec 3 (VADPCM) for hardware-accelerated playback.
# ------------------------------------------------------------------------------

filesystem/btnGame.sprite: MKSPRITE_FLAGS = --format RGBA16
filesystem/spaceship.sprite: MKSPRITE_FLAGS = --format RGBA16
filesystem/core/brew_logo.sprite: MKSPRITE_FLAGS += --format CI4 -c 2
filesystem/core/dragon1.sprite: MKSPRITE_FLAGS += --format I4 -c 2
filesystem/core/dragon2.sprite: MKSPRITE_FLAGS += --format I4 -c 2
filesystem/core/dragon3.sprite: MKSPRITE_FLAGS += --format I4 -c 2
filesystem/core/dragon4.sprite: MKSPRITE_FLAGS += --format I4 -c 2

filesystem/core/dragon.wav64: AUDIOCONV_FLAGS += --wav-resample 32000 --wav-mono --wav-compress 3

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
# Import external Libraries
# Libdragons & Tiny3D
# -------------------------------------------------
include $(N64_INST)/include/n64.mk
include $(N64_INST)/include/t3d.mk

# -------------------------------------------------
# Build Rules
# -------------------------------------------------

## -------------------------------------------------
## Main Rule
## -------------------------------------------------
all: $(ROMNAME).z64

# Tells libdragon that the final ROM requires the compiled filesystem
$(ROMNAME).z64: $(BUILD_DIR)/$(ROMNAME).dfs

# Tells libdragon what goes into the ELF and the DFS
$(BUILD_DIR)/$(ROMNAME).elf: $(OBJS)
$(BUILD_DIR)/$(ROMNAME).dfs: $(ASSETS_CONV) | $(FILESYSTEM_DIR)

# make filesystem dir in case it doesn't exits.
$(FILESYSTEM_DIR):
	@mkdir -p $@

## -------------------------------------------------
## Asset Rule
## -------------------------------------------------

# Rule to convert PNG images to N64 sprite format.
$(FILESYSTEM_DIR)/%.sprite: $(ASSETS_DIR)/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	$(N64_MKSPRITE) $(MKSPRITE_FLAGS) -o $(dir $@) "$<"


# Rule to convert 3D GLB/GLTF models to t3dm (Tiny3D Model format) and compress it.
$(FILESYSTEM_DIR)/%.t3dm: $(ASSETS_DIR)/%.glb
	@mkdir -p $(dir $@)
	@echo "    [T3D-MODEL] $@"
	$(T3D_GLTF_TO_3D) $(T3DM_FLAGS) "$<" $@
	$(N64_BINDIR)/mkasset -c 2 -o $(dir $@) $@

# Rule to convert audio files (.mp3) to N64 wav64 format.
$(FILESYSTEM_DIR)/%.wav64: $(ASSETS_DIR)/%.mp3
	@mkdir -p $(dir $@)
	@echo "    [SFX] $@"
	$(N64_AUDIOCONV) $(AUDIOCONV_FLAGS) -o $(dir $@) "$<"

# Rule to convert TTF fonts to N64 font64 format.
$(FILESYSTEM_DIR)/%.font64: $(ASSETS_DIR)/%.ttf
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	@$(N64_MKFONT) $(MKFONT_FLAGS) -o "$(dir $@)" "$<"

## -------------------------------------------------
## Clean rule
##   remove all build artifacts
## -------------------------------------------------
clean:
	rm -rf $(BUILD_DIR) $(FILESYSTEM_DIR) *.z64

.PHONY: all clean