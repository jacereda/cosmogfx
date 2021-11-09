{ pkgs ? import <nixpkgs> {}
}:
with pkgs;
{
  shellEnv =
    let
      cosmopolitan-src = fetchTarball {
        name = "cosmopolitan";
        url = "https://github.com/jacereda/cosmopolitan/archive/7df37b5.tar.gz";
        sha256 = "1pl4d5w2kmn08ysmf8xhvg5n7smal253jw1anjnwncf1na1gawrg";
      };
      cosmopolitan = callPackage cosmopolitan-src {};
      mylibs = with xorg; [ glibc libGL libX11 libXcursor libXrender libxkbcommon ];
    in
      stdenv.mkDerivation {
        name = "shell-environment";
        nativeBuildInputs = with pkgs; [ gdb clang-tools cosmopolitan ];
        buildInputs = mylibs;
        LD_LIBRARY_PATH = lib.makeLibraryPath mylibs;
      };
}
