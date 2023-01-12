{
  description = "シミュレーション物理の実験プログラム + レポート";
  inputs = { 
    nixpkgs = { url = "github:NixOS/nixpkgs/nixpkgs-unstable"; };
    flake-utils = { url = "github:numtide/flake-utils"; };
    satyxin.url = "github:SnO2WMaN/satyxin";
  };
  outputs = { self, satyxin, nixpkgs, flake-utils } @ inputs:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [ 
            satyxin.overlay
          ];
        };
      in rec {
        packages = rec {
          satysfiDist = pkgs.satyxin.buildSatysfiDist {
            packages = [
              "fss"
            ];
          };
          main = pkgs.satyxin.buildDocument {
            inherit satysfiDist;
            satysfiLocal = ./.satysfi/local;
            name = "main";
            src = ./report/week1;
            entrypoint = "main.saty";
            output = "main.pdf";
          };
        };
      }
    );
}
