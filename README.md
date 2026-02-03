# Ink Mail

An email client for e-ink displays.

## Build yourself

This app is designed to have hardcoded email server login details. This means you must compile the program yourself with this information.

## Develop using Nix

In the project directory, run `nix develop` to run the ad hoc devshell. Run `meson setup build` and then use `meson compile -C build` to build. Run your IDE instance in this devshell to have working intellisense.

## Adding icons

This process is kind of confusing so I've outlined it here if you want to add more icons:

Use `rsvg-convert -w 32 -h 32 svg/<img>.svg -o <img>.png` to rasterize svg images for usage. Ink Mail uses [HeroIcons](https://heroicons.com/)

Then use `gdk-pixbuf-csource --name=<png name>_png <png name>.png > <png name>_icon.h` and add `gdk-pixbuf-csource --name=<icon name>_png <icon name>.png > <icon name>_icon.h` to the bottom of generated header file.

---

Hack Club Inkling submission
