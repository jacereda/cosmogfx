{ pkgs ? import (fetchTarball {
  name = "nixpkgs";
  url = "https://github.com/NixOS/nixpkgs/archive/6a95c3d.tar.gz";
  sha256 = "02cfgxilzf7kmg7mdyxga7wmmkqlxcfi3c44ay4mn7xrqdwrbx3y";
}) {}
}:
with pkgs;
{
  shellEnv =
    let
#      cosmopolitan-local = callPackage ../cosmopolitan/default.nix {};
      mylibs = with xorg; [ glibc libGL libX11 libXcursor libXrender libxkbcommon ];
    in
      stdenv.mkDerivation {
        name = "shell-environment";
        nativeBuildInputs = with pkgs; [ pkg-config wayland-protocols gdb clang-tools cosmopolitan ];
        buildInputs = mylibs;
        LD_LIBRARY_PATH = lib.makeLibraryPath mylibs;
      };
}
