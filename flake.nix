{
  description = "A classic 2d jump'n shoot game";

  inputs = {
    nixpkgs.url = "github:grumbel/nixpkgs/fix-guile-3.0";
    # nixpkgs.url = "github:NixOS/nixpkgs/nixos-22.05";
    flake-utils.url = "github:numtide/flake-utils";

    tinycmmc.url = "github:grumbel/tinycmmc";
    tinycmmc.inputs.flake-utils.follows = "flake-utils";
    tinycmmc.inputs.nixpkgs.follows = "nixpkgs";

    clanlib.url = "github:grumbel/clanlib-1.0";
    clanlib.inputs.nixpkgs.follows = "nixpkgs";
    clanlib.inputs.flake-utils.follows = "flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, tinycmmc, clanlib }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in rec {
        packages = flake-utils.lib.flattenTree {
          colorasion = pkgs.stdenv.mkDerivation {
            pname = "colorasion";
            version = "0.2.0";
            src = nixpkgs.lib.cleanSource ./.;

            nativeBuildInputs = with pkgs; [
              cmake
              pkgconfig
            ];
            buildInputs = with pkgs; [
              guile_1_8
            ] ++ [
              tinycmmc.defaultPackage.${system}
              clanlib.defaultPackage.${system}
            ];
           };
        };
        defaultPackage = packages.colorasion;
      }
    );
}
