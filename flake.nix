{
  description = "Ink Mail Kindle devshell";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};

      target = "kindlehf";

      cross = pkgs.pkgsCross.${{
        kindlehf = "armv7l-hf-multiplatform";
        kindlepw2 = "armv7l-multiplatform";
      }.${target}};
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        buildInputs = with pkgs; [
          meson
          ninja
          pkg-config
          gtk2
          tinyxxd
          #cross.buildPackages.gcc
        ];
      };
    };
}
