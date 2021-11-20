{ pkgs ? import <nixpkgs> {}
}:
with pkgs;
{
  shellEnv =
    let
      cosmopolitan-src = fetchTarball {
        name = "cosmopolitan";
        url = "https://github.com/jacereda/cosmopolitan/archive/200fd7a55.tar.gz";
        sha256 = "0jbvsmqrqnwlc9981wlwl6nyyf16mf54k6iwyshw7qzy676g2xd9";
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
