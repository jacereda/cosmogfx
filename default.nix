with import <nixpkgs> {};
{
  shellEnv =
    let
      cosmopolitan-local = callPackage ../cosmopolitan/default.nix {};
      mylibs = with xorg; [ glibc libGL libX11 libXcursor libXrender libxkbcommon ];
    in
      stdenv.mkDerivation {
        name = "shell-environment";
        nativeBuildInputs = with pkgs; [ pkg-config wayland-protocols gdb clang-tools cosmopolitan-local ];
        buildInputs = mylibs;
        LD_LIBRARY_PATH = lib.makeLibraryPath mylibs;
      };
}
