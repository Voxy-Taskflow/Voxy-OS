# Voxy OS

**Voxy OS** is a simple, hobbyist operating system built from scratch for educational purposes. It is currently in the early stages of development and is focused on learning how operating systems work at the fundamental level.

---

## Features Implemented So Far

### ✅ Basic Terminal
- Character input from keyboard
- Handles alphabet, number, space, enter, caps lock, and backspace
- Cursor system implemented using hardware cursor logic (ports 0x3D4 and 0x3D5)
- Arrow key support (up, down, left, right)

### ✅ Basic Command System
- Input buffer stores typed characters
- Compares typed string with known commands

### 🧪 Work-in-Progress Commands
- `help`: Currently under development
- `ver`: Will eventually display Voxy OS version info
- `install`: Placeholder for future OS installer functionality

---

## Next Goals
- Set up a basic file system and allow the kernel to read from a disk image
- Add support for reading files and storing system configuration or command data
- Eventually move toward a more interactive desktop environment and app installer

---

## Development Goals
The goal of Voxy OS is not just to build an OS, but to **learn by building**, understand how each part works, and gain deep system-level knowledge.

---

Stay tuned for more updates as the project evolves!

