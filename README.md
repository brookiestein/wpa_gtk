# WPA GUI
## Table of contents
- [What is it?](#what-is-it)
- [Dependencies](#dependencies)
  - [How to install the dependencies?](#how-to-install-the-dependencies)
- [How to install it?](#how-to-install-it)
  - [Getting the sources](#getting-the-sources)
  - [Compiling](#compiling)
    - [Note 1](#note-1)
  - [Installing](#installing)
- [Note 2](#note-2)
- [Screenshots](#screenshots)

### What is it?
This is a simple tool to connect to Wi-Fi networks that use the WPA2 protocol.

### Dependencies
```
gcc
make
wpa_supplicant
gtk+3.0
```

#### How to install the dependencies?
Depending on your distribution use the corresponding command:
| Distribution                     | Command                                              |
|:---------------------------------|------------------------------------------------------|
|Debian/Ubuntu and derivatives     |`apt install gcc make libgtk-3-dev wpasupplicant`     |
|Fedora/CentOS/RHEL                |`dnf install gcc make gtk3-devel wpa_supplicant`      |
|Gentoo/Funtoo and derivatives     |`emerge --ask gcc make gtk+ wpa_supplicant`           |
|Arch Linux/Manjaro and derivatives|`pacman -S gcc make gtk3 wpa_supplicant`              |

#### Note
**You will need root permissions.**

### How to install it?
#### Getting the sources
First get the sources using git:
```
git clone https://github.com/brookiestein/wpa_gui
```
If you don't have `git` installed on your system or simply you don't want to use it, you can download using the green button `Code` above.

#### Compiling
You already have the sources, so now you can compile it.

To do that, execute the following commands:
```
make
make clean
```
##### Note 1:
`make clean` is optional!

### Installing
If everything has gone well, you'd have it compiled, finally!

To install it, only execute this:
```
make install
```

### Note 2
For the correct working of this program, **you will need root permissions**, because the turn Wi-Fi network's configuration **will
be written to a file the which belongs to the root user.**

### Screenshots
![](screenshots/1.png)
![](screenshots/2.png)
![](screenshots/3.png)
