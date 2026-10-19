# CustomOS

A C and GTK 3 desktop simulator for Ubuntu, with utility apps, process inspection, task launching and simulated resource budgets.

[![Verify](https://github.com/fizaamjd/OSFinalProject/actions/workflows/verify.yml/badge.svg)](https://github.com/fizaamjd/OSFinalProject/actions/workflows/verify.yml)

## Overview

Main.c creates the GTK shell. Utilities are independent C programs launched through gnome-terminal using fork and exec. RAM, disk and core budgets are counters, not OS-enforced quotas. User Mode and Kernel Mode are UI labels; this is not a bootable kernel or privilege boundary.

## Getting started

```sh
git clone https://github.com/fizaamjd/OSFinalProject.git
cd OSFinalProject
make
make check
```

Install prerequisites first:

```sh
sudo apt-get install build-essential libgtk-3-dev pkg-config gnome-terminal
make
./my_os
```

## Included applications

Calculator, calendar, text editor, file manager, clock, Minesweeper and Tic-Tac-Toe. Original filenames such as `Calender.c` and `MinSweeper.c` are retained. Three console helpers demonstrate resource inputs; they do not allocate host RAM, disk or CPU capacity.

## Limits and safe execution

This is a GTK desktop teaching project running on Ubuntu, not a standalone OS. UI modes do not implement CPU privilege rings, a custom scheduler or preemptive context switching. The host Linux kernel schedules spawned processes. Process cancellation and file operations affect the host; use a disposable VM and never run as root. Compile from source rather than trusting historical checked-in binaries.

## Live demo video

https://github.com/user-attachments/assets/77cb4711-2194-43ed-afe5-c23c3a4e1224

[Original project demonstration and LinkedIn post](https://lnkd.in/p/d_2DEMH8). The edited presentation uses footage from that original demonstration.

## Maintenance

- [Architecture](docs/architecture.md)
- [Configuration](docs/configuration.md)
- [Verification](docs/testing.md)
- [Contributing](CONTRIBUTING.md)
- [Security](SECURITY.md)
- [Support](SUPPORT.md)
- [License scope](docs/license-scope.md)

Original coursework history and contributors are preserved.
