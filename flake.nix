{
  description = "Ink Mail Kindle devshell";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.11";

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      devShells.${system}.default = pkgs.mkShell {
        buildInputs = with pkgs; [
          # For build
          meson
          ninja
          pkg-config
          gtk2
          tinyxxd

          # Fix warnings
          gtk-engine-murrine
          gnome-themes-extra
        ];
        
        # Export themes to fix adwaita warning
        shellHook = ''
          export GTK_PATH="${pkgs.gtk-engine-murrine}/lib/gtk-2.0:${pkgs.gnome-themes-extra}/lib/gtk-2.0"
        '';
      };
    };
}
