# nds-test

## Description
Currently just a small demo. </br>
devkitPro installation: https://devkitpro.org/wiki/Getting_Started </br>
Great intro: https://www.patater.com/manual-git/cover.html </br>
The Bible: https://problemkaputt.de/gbatek.htm </br>
GBA Ref (pretty similar): https://gbadev.net/tonc/intro.html </br>
nds.h: https://github.com/devkitPro/libnds/blob/master/include/nds.h </br>
examples: https://github.com/devkitPro/nds-examples </br>

## Building with devkitPro

* ### How to install devkitPro (Linux)
    Generally you want to follow the [guide](https://devkitpro.org/wiki/Getting_Started) </br>
    Sample commands for fedora provided (you need pacman sadly)

    ```
    sudo dnf install pacman
    DEVKITPRO=/opt/devkitpro
    DEVKITARM=/opt/devkitpro/devkitARM
    DEVKITPPC=/opt/devkitpro/devkitPPC
    sudo pacman-key --init
    sudo pacman-key --recv BC26F752D25B92CE272E0F44F7FD5492264BB9D0 --keyserver keyserver.ubuntu.com
    sudo pacman-key --lsign BC26F752D25B92CE272E0F44F7FD5492264BB9D0
    wget https://pkg.devkitpro.org/devkitpro-keyring.pkg.tar.xz
    sudo pacman -U devkitpro-keyring.pkg.tar.xz
    
    sudo vi /etc/pacman.conf

    >Comment out [core] [community] [extra]
    #[core]
    #...
    #[community]
    #...
    #[extra]
    #...

    >Paste this
    [dkp-libs]
    Server = https://pkg.devkitpro.org/packages
    [dkp-linux]
    Server = https://pkg.devkitpro.org/packages/linux/$arch/

    >Then install the actual devkit
    sudo pacman -Sy
    sudo pacman -Sy nds-dev
    ```
* ### Building the project
    ```
    cd nds-test
    make
    ./emu/melonDS-x86_64.AppImage nds-test.nds
    ```

