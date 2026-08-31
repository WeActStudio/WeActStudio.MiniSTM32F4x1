## About

A KiCad symbol and footprint for the WeAct Studio BlackPill v3+ modules. Both define 44 pins: two 20-pin module headers plus a 4-pin Serial Wire Debug (SWD) header. If you don't need SWD, the standard KiCad `DIP-40_W15.24mm` footprint can be used instead.

## Files

- `WeAct-BlackPillv3.kicad_sym` — symbol library
- `WeAct.pretty/` — footprint library, containing `WeAct-BlackPill_DIP-40_W15.24mm-SWD.kicad_mod`

## Pinout

| #  | Signal |   | #  | Signal |
|----|--------|---|----|--------|
| 1  | PB12   |   | 40 | 5V*    |
| 2  | PB13   |   | 39 | GND*   |
| 3  | PB14   |   | 38 | 3V3*   |
| 4  | PB15   |   | 37 | PB10   |
| 5  | PA8    |   | 36 | PB2    |
| 6  | PA9    |   | 35 | PB1    |
| 7  | PA10   |   | 34 | PB0    |
| 8  | PA11   |   | 33 | PA7    |
| 9  | PA12   |   | 32 | PA6    |
| 10 | PA15   |   | 31 | PA5    |
| 11 | PB3    |   | 30 | PA4    |
| 12 | PB4    |   | 29 | PA3    |
| 13 | PB5    |   | 28 | PA2    |
| 14 | PB6    |   | 27 | PA1    |
| 15 | PB7    |   | 26 | PA0    |
| 16 | PB8    |   | 25 | NRST   |
| 17 | PB9    |   | 24 | PC15   |
| 18 | 5V*    |   | 23 | PC14   |
| 19 | GND*   |   | 22 | PC13   |
| 20 | 3V3*   |   | 21 | VBAT   |

\* 5V, GND, and 3V3 are each broken out twice, once at either end of the board — 18↔40, 19↔39, 20↔38. Each pair is already tied together on the module. In the symbol the duplicates are marked invisible and overlayed on top of their counterparts, so each rail appears as a single pin. Leaving a duplicate unconnected is electrically fine, but the Design Rules Checker (DRC) will flag it as unconnected; either exclude the warning or run a trace between the pair.

**SWD header** (pins 41–44): `3V3, SWDIO, SWCLK, GND`

### Alternate Functions

Every GPIO pin lists the available peripheral alternate functions pulled from the STM32F411CEU6 datasheet. Right-click a pin in the schematic and choose **Assign Alternate Function** to relabel it. The pin's associated label and electrical type will change to match the underlying peripheral. This allows the schematic to match external tooling like STM32 HALs and utilities.

For example, pin 1 (`PB12`) can be relabeled as any of: `I2C2_SMBA`, `I2S2_WS`, `I2S3_CK`, `I2S4_WS`, `SPI2_NSS`, `SPI3_SCK`, `SPI4_NSS`, or `TIM1_BKIN`. The pin number and footprint pad stay fixed at 1; only the pin label and electrical type change.

If your module uses the STM32F401 then some alternate functions will be different.

### System Pins

Reset, boot mode select, the onboard blue LED, and the user button are all broken out on the module:

| #  | Signal      | Function          |
|----|-------------|-------------------|
| 22 | PC13        | Status LED (blue) |
| 25 | NRST        | Reset             |
| 26 | PA0         | User key          |
| 36 | BOOT1 (PB2) | Boot select       |

`BOOT1` must be held low while BOOT0 is being sampled during the MCU boot sequence. After that it can be used as a normal GPIO pin.

### USB

| # | Signal | Function |
|---|--------|----------|
| 8 | PA11   | USB D-   |
| 9 | PA12   | USB D+   |

The BlackPill's USB connector D- and D+ data lines are broken out to PA11 and PA12 on the module. If you plan to use the USB connector on the module then these pins will be unusable. You can also route these pins as a 90 Ω differential pair to your own USB connector.

### Power

VBUS from the USB connector on the BlackPill passes through a diode to power the +5V rail. An onboard 500 mA LDO then generates the 3.3V rail from the +5V rail.

### Optional SPI Flash

The BlackPill has an optional SPI flash chip on the bottom of the module. It is connected to the SPI2 peripheral on the microcontroller, which maps to pins 1–4 on the module. The SPI flash is generally not installed on most modules, so it's safe to use these pins as GPIO.

| # | Signal | Alternate Function |
|---|--------|--------------------|
| 1 | PB12   | SPI2_NSS           |
| 2 | PB13   | SPI2_SCK           |
| 3 | PB14   | SPI2_MISO          |
| 4 | PB15   | SPI2_MOSI          |

## Usage

These files can be added as a new library or imported into a library you already maintain.

### Add as a New Library

1. Copy (or `git clone`) this `KiCAD` folder somewhere on disk — it can stay where it is, or be vendored into a project.
2. **Preferences → Manage Symbol Libraries**, add a new row — Nickname `WeAct`, Library Path pointing at `WeAct-BlackPillv3.kicad_sym`, Library Type `KiCad`.
3. **Preferences → Manage Footprint Libraries**, add a new row — Nickname `WeAct`, Library Path pointing at the `WeAct.pretty` folder (footprint libraries are folders, not individual `.kicad_mod` files), Library Type `KiCad`.
4. Use **Global Libraries** if you want this available in every project, or **Project Specific Libraries** to scope it to one project only — that writes to the project's `sym-lib-table` / `fp-lib-table` instead of the global tables in your KiCad config directory.

Use the nickname `WeAct` for both. The symbol's `Footprint` field already points at `WeAct:WeAct-BlackPill_DIP-40_W15.24mm-SWD`, so the footprint links automatically once the library tables resolve. Under a different nickname you'll need to reassign the footprint manually.

### Import into an Existing Library

If you'd rather fold this part into a library you already maintain instead of keeping it as its own library:

1. In the **Symbol Editor**, select `WeActBlackPillV3`, then **File → Save a Copy...** and choose your existing target symbol library.
2. In the **Footprint Editor**, select `WeAct-BlackPill_DIP-40_W15.24mm-SWD`, then **File → Save a Copy...** into your existing footprint library.
3. Update the copied symbol's `Footprint` field to `<your-library-nickname>:WeAct-BlackPill_DIP-40_W15.24mm-SWD` if the nickname differs from `WeAct`.

Both editors open standalone from the KiCad launcher with no project loaded. Neither has an "open file" command — libraries are reached through the library tables, so add them with **File → Add Library...** first, or use **File → Import Symbol...** / **Import Footprint...** to pull in a single file.
