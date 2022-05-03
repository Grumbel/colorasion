{
  description = "A classic 2d jump'n shoot game";

  inputs = {
    nixpkgs.url = "github:grumbel/nixpkgs/fix-guile-3.0";
    # nixpkgs.url = "github:NixOS/nixpkgs/nixos-21.11";
    flake-utils.url = "github:numtide/flake-utils";

    tinycmmc.url = "gitlab:grumbel/cmake-modules";
    tinycmmc.inputs.flake-utils.follows = "flake-utils";
    tinycmmc.inputs.nixpkgs.follows = "nixpkgs";

    clanlib.url = "gitlab:grumbel/clanlib-1.0";
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
            postFixup = ''
                wrapProgram $out/bin/colorasion \
                  --prefix LIBGL_DRIVERS_PATH ":" "${pkgs.mesa.drivers}/lib/dri" \
                  --prefix LD_LIBRARY_PATH ":" "${pkgs.mesa.drivers}/lib"
            '';
            nativeBuildInputs = [
              pkgs.cmake
              pkgs.pkgconfig
              pkgs.makeWrapper
              tinycmmc.defaultPackage.${system}
            ];
            buildInputs = [
              clanlib.defaultPackage.${system}
              pkgs.guile_1_8
            ];
           };
        };
        defaultPackage = packages.colorasion;
      });
}
