{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
  pname = "cmdtree";
  version = "0.1";
  src = ./.;
  makeFlags = "PREFIX=$(out)";
  buildInputs = with pkgs; [ xorg.libX11 xorg.libXft ];
}
