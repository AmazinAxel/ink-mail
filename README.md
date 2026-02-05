# Ink Mail

An email client for e-ink displays.

## Build yourself

Email server login details are hardcoded into the build process. You must compile the program yourself to enter your email server details.

## Develop using Nix

In the project directory, run `nix develop` to run the ad hoc devshell. Run `meson setup build` and then use `meson compile -C build` to build. Run your IDE instance in this devshell to have working intellisense.

## Adding icons

This process is kind of confusing so I've outlined it here if you want to add more icons:

Use `rsvg-convert -w 32 -h 32 svg/<img>.svg -o png/<img>.png` to rasterize svg images for usage. Ink Mail uses [HeroIcons](https://heroicons.com/)

Then use `gdk-pixbuf-csource --name=<png name>_png <png name>.png > <png name>_icon.h` and add `static const guint <png name>_png_len = sizeof(<png name>_png);` to the bottom of generated header file.

---

Hack Club Inkling submission
