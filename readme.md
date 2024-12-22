# KBD firmware for Corne choc v4.1 from [keebart.com](https://www.keebart.com/products/corne)

## Main highlights

- 16 Layers.
- 32 Macros.
- Sync Layer/Led/Mod states.
- Layer indicators (using the four extra keys).
- Keyboard name shows as "keebart corne v4.1" instead of "foostan corne v4".
- Also, with the foostan/keebart firmware, when my system goes to sleep, hitting anything on the keyboard aftewards will do nothing; but with this firmware it seems to work as expcted; if I hit any key the keyboard wakes up and the system too.

## How to build

## 1. Setting Up Your QMK Environment

Please see <https://docs.qmk.fm/#/newbs_getting_started> and set up 1 to 3.

## 2. Getting source files

Please get source files of `qmk/qmk_firmware` and `vial-kb/vial-qmk`

```sh
make git-submodule
```

## 3. Building firmwares

### for VIA

```sh
make qmk-clean
kb=crkbd make qmk-init
kb=crkbd kr=rev4_1/standard km=via make qmk-compile
```

A built data will be stored on `keyboards/crkbd/qmk/qmk_firmware/.build`\
Please change `kb`, `kr` and `km` when build other.

### for Vial

```sh
make vial-qmk-clean
kb=crkbd make vial-qmk-init
kb=crkbd kr=rev4_1/standard km=vial make vial-qmk-compile
```

Note: Please change `kb`, `kr` and `km` when building other kbs/models.

Also, you can simply issue instead

```sh
make vial-qmk-compile-corne41
```

A built firmware can be found at the root dir of the project.

### All cleaning and building

```sh
make update-all
```
