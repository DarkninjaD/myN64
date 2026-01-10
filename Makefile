PROJECT_NAME = main
BUILD_DIR = build
SOURCE_DIR = src
assets_png = $(wildcard assets/*.png)

vpath %.c $(SOURCE_DIR)

all: $(PROJECT_NAME).z64
.PHONY: all

include $(N64_INST)/include/n64.mk

assets_conv = $(addprefix filesystem/,$(notdir $(assets_png:%.png=%.sprite)))

filesystem/%.sprite: assets/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	@$(N64_MKSPRITE) -f RGBA16 -o "$(dir $@)" "$<"


OBJS = $(BUILD_DIR)/$(PROJECT_NAME).o
$(BUILD_DIR)/$(PROJECT_NAME).elf: $(OBJS)
$(BUILD_DIR)/$(PROJECT_NAME).dfs : $(assets_conv)

$(PROJECT_NAME).z64: N64_ROM_TITLE = "First N64 game"
$(PROJECT_NAME).z64: $(BUILD_DIR)/$(PROJECT_NAME).dfs

clean:
	rm -rf $(BUILD_DIR) filesystem/ *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)