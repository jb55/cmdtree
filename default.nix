{ nixpkgs ? import <nixpkgs> {} }:

with nixpkgs;

stdenv.mkDerivation {
  name = "cmdtree";
  src = ./.;
  buildPhase = "make";
  installPhase = ''
    mkdir -p $out/bin
    cp ./cmdtree $out/bin
  '';
  buildInputs = [ pkgs.xorg.libX11 pkgs.xorg.libXft ];
}
