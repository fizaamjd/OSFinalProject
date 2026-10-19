# Architecture

Main.c creates the GTK shell. Utilities are independent C programs launched through gnome-terminal using fork and exec. RAM, disk and core budgets are counters, not OS-enforced quotas. User Mode and Kernel Mode are UI labels; this is not a bootable kernel or privilege boundary.
