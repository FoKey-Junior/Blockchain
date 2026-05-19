{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    cmake
    pkg-config
    libsodium
    sqlite
    asio
    
    # Qt6 dependencies
    qt6.qtbase
    qt6.qtdeclarative
  ];

  # Make Qt plugins available in the shell environment
  shellHook = ''
    export QT_PLUGIN_PATH=${pkgs.qt6.qtbase}/${pkgs.qt6.qtbase.qtPluginPrefix}
    export QML2_IMPORT_PATH=${pkgs.qt6.qtdeclarative}/${pkgs.qt6.qtbase.qtQmlPrefix}
  '';
}
