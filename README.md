# Ink Mail

An email client for e-ink displays.

## Build yourself

Email server login details are hardcoded into the build process. You must compile the program yourself to enter your email server details.

### Prebuilt binaries

I only provide prebuilt binaries as a testing convinience. Since this program offers no way of entering or saving email logins, all my prebuilt binaries provided use a test email that I set up. You can email it at `inkling@amazinaxel.com` and use the prebuilt to preview those messages in real time. I may shut down the email in the future.

## Develop using Nix

In the project directory, run `nix develop` to run the ad hoc devshell. Run `meson setup build -Dimap=imaps://imap.youremailserverhere.com:993/INBOX -Demail=inkling@amazinaxel.com -Dpassword=password` and then build: `meson compile -C build`

Run your IDE instance in this devshell to have working intellisense.

## Adding icons

This process is kind of confusing so I've outlined it here if you want to add more icons:

Use `rsvg-convert -w 32 -h 32 svg/<img>.svg -o png/<img>.png` to rasterize svg images for usage. Ink Mail uses [HeroIcons](https://heroicons.com/)

Then use `gdk-pixbuf-csource --name=<png name>_png <png name>.png > <png name>_icon.h` and add `static const guint <png name>_png_len = sizeof(<png name>_png);` to the bottom of generated header file.

---

Hack Club Inkling submission
