# myN64 - Nintendo 64 Game & Engine Framework

`myN64` is a custom game framework and demonstration codebase for the Nintendo 64 (N64) hardware. Built on top of the modern open-source [libdragon](https://github.com/dragonmind/libdragon) SDK and the [Tiny3D](https://github.com/flynn/t3d) graphics library, this project features a modular screen state machine, custom font loading, audio playback, 2D sprite animations, and real-time 3D rendering.

---

## 🚀 Key Features

- **3D Rendering (Tiny3D)**: Real-time 3D model rendering with custom projection matrices, ambient lighting, and rotation animations.
- **2D Sprite Animation (Libdargon)**: Custom scissoring, scaling, blending, and color dithering leveraging the N64 Reality Coprocessor (RCP).
- **Audio Engine (Libdargon)**: Hardware-accelerated `.wav64` playback using the N64 audio mixer channel limits.
- **Custom Asset Compiler (Libdargon)**: Automatized conversion pipeline for sprites, fonts, audio, and 3D models.
- **Host-Side Unit Testing (Ceedling)**: Direct logic validation (state transitions, math, and engine state) compiled natively on host PCs using Ceedling.

---

## 📁 Directory Structure

```
Project/
├── assets/                  # Raw assets (PNGs, TTF fonts, MP3 audio, 3D GLB models)
├── filesystem/              # Compiled assets packed into the ROM's DFS archive
├── src/                     # Game source code
├── test/                    # Host-side unit test files
│   └── support/             # Mock header directories (e.g. stub libdragon.h)
├── Makefile                 # Compiles source and converts all assets for N64
└── project.yml              # Ceedling unit test configuration
```

---

## 🛠️ The Asset Pipeline (Makefile)

To build a Nintendo 64 ROM, all source assets must be converted into MIPS-friendly binary formats and packed into a DFS (Directory File System) image. The project [Makefile](file:///wsl.localhost/Ubuntu/home/zourbomb/workspace/n64dev/myN64/Makefile) automatically processes the `assets/` directory using specialized Libdragon tools.

### Sprite Conversion (`n64mksprite`)

- Converts PNG images into N64 sprites.
- **Optimization Flags**:
  - `--format CI4`: 4-bit Color Indexed mode (16-color palette) to optimize texture RAM (TMEM) footprint (used for `brew_logo`).
  - `--format I4`: 4-bit Intensity (grayscale transparency) mode (used for `dragon` logo segments).
  - `--format RGBA16`: High-fidelity 16-bit color format (used for buttons and gameplay assets).
  - `-c 2`: Enables Codec 2 (LZ4 compression) for compact ROM storage.

### 3D Models (`t3dgltf` & `mkasset`)

- Converts GLTF/GLB models to `.t3dm` (Tiny3D Model format) files and compresses them with Codec 2 (`-c 2`) compression for N64 runtime performance.

### Audio Conversion (`n64audioconv`)

- Processes MP3 tracks into standard `.wav64` format.
- **Optimization Flags**:
  - `--wav-resample 32000`: Resamples to 32kHz to standardise mixer frequencies.
  - `--wav-mono`: Downmixes stereo channels to mono, saving 50% memory size.
  - `--wav-compress 3`: Compresses using Codec 3 (VADPCM) for hardware-accelerated decompression.

### Font Conversion (`n64mkfont`)

- Converts standard TrueType TTF fonts into MIPS-aligned `.font64` files for rendering with the `rdpq_text` APIs.

---

## 💻 Build and Run Instructions

### Prerequisites

1. **Libdragon Toolchain**: Ensure you have the `libdragon` compilation toolchain installed on your Linux machine or WSL instance.
2. **Tiny3D (T3D)**: The Tiny3D library must be installed in your `$N64_INST` environment.

### Compile the ROM

To compile the game source, run the asset pipeline, and build the final MIPS ROM file:

```bash
make
```

This produces `main.z64` (the Nintendo 64 ROM).

### Cleaning Build Files

To remove all compiled object files, generated filesystem assets, and built ROMs:

```bash
make clean
```

### Running the ROM

- **Emulator**: Load the compiled `main.z64` into an emulator. [Ares](https://ares-emu.github.io/) is being used to test against.
- **Real Hardware**: Flash the `main.z64` onto a flashcart

---

## 🧪 Automated Unit Testing

Because debugging directly on an N64 emulator or physical console can be extremely difficult, this codebase is designed to run unit tests natively on a development PC.

### Testing Stack

- **Ceedling**: Build automation manager orchestrating test builds and compilations.
- **Unity**: Core assertion library providing testing macros.
- **CMock**: Mocking framework used to stub hardware interactions and cross-module calls.

### How to Run Tests

Tests require **Ruby** and a native host compiler (**GCC**). Once installed, run these from the project root:

- Run all tests:
  ```bash
  ceedling test:all
  ```
- Run a specific test module (omit the `test_` prefix and file extension):
  ```bash
  ceedling test:screenMng
  ```
- Clean test artifacts:
  ```bash
  ceedling clobber
  ```

### Toolchain Mismatch (Hardware Stubs)

When source files include `<libdragon.h>`, building on a host PC would fail due to missing N64 architectures. We bypass this using **Ceedling's pathing priority** config in [project.yml](file:///wsl.localhost/Ubuntu/home/zourbomb/workspace/n64dev/myN64/project.yml). By placing empty header files inside `test/support/`, the host compiler finds these mocks first, stubbing out MIPS-specific routines and compiling your core engine logic without errors.

For detailed guidelines and code examples, read the [Testing Strategy Guide.md](file:///wsl.localhost/Ubuntu/home/zourbomb/workspace/n64dev/myN64/Testing%20Strategy%20Guide.md).

---

## 🎨 Naming Conventions

To maintain readability and consistency across the codebase, please adhere to the following naming standards:

- **File Names**: `PascalCase` (e.g., `screenMng.c`, `introScreen.c`)
- **Functions**: `camelCase` (e.g., `screenMngInit()`, `menuInputTest()`)
- **Enums & Constants**: `SCREAMING_SNAKE_CASE` (e.g., `MAIN_MENU`, `FONT_SIXTYFOUR`, `SPINSPEED`)
- **Variables**: Standard descriptive coding styles (such as `camelCase` or `snake_case`).
