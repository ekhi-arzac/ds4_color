# DS4 Color

This project aims to explore the Dualshock 4's color "registers"

https://github.com/ekhi-arzac/ds4_color/assets/105313706/d0522734-e5b8-4586-a2a6-3e0800f2ea69

## How to run Linux

First of all, you need a Dualshock 4, and it needs to be connected to the PC via USB.

You need to install the following programs:

- GCC compiler
- Make

In order to run this project, we first need to figure out what is the _hidraw port_ of our controller (don't worry, we just need to get a number).

Open up a bash terminal and type the following

> [!WARNING]  
> You should never blindly paste a bash command, specially with sudo.

```bash
sudo dmesg | grep -i "Sony" | grep -i "hidraw"
```

If everything went well you will get the following output:

```bash
[    4.716324] playstation 0003:054C:05C4.0008: hidraw7: USB HID v1.11 Gamepad [Sony Computer Entertainment Wireless Controller] on usb-0000:00:14.0-12/input0
[ 2724.318756] playstation 0003:054C:05C4.0009: hidraw7: USB HID v1.11 Gamepad [Sony Computer Entertainment Wireless Controller] on usb-0000:00:14.0-12/input0
```

The word hidraw will be highlighted in red, and next to it we will have a number. REMEMBER THIS NUMBER.

Now we need to clone the project and change the source file so it works with our machine:

```bash
git clone ...
cd ...
```

Go to `src/ds4_color.c` and change line 11:

```c
#define HIDRAW_DEVICE "/dev/hidrawX" // CHANGE X WITH THE NUMBER WE GOT EARLIER
```

Now simply compile and run:

```bash
make
sudo ./ds4_color
```

As for now, I have no intentions to port this to windows, however the code should not change much.
