{ pkgs ? import (fetchTarball {
  name = "nixpkgs";
  url = "https://github.com/NixOS/nixpkgs/archive/fa90ef8.tar.gz";
  sha256 = "0nfazdiga80nks55jd7jxg0vxv0v7pispizx9v8r0l2ik9qgx70b";
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
