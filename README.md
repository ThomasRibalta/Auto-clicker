# Autoclicker for macOS

## Description

This project is an autoclicker developed in C with a graphical user interface using GTK+3. The application allows you to automate clicks at the current mouse location at a user-specified interval. It also provides the ability to start and stop the autoclicker via buttons in the GUI or by pressing the `q` or `Escape` keys to stop.

## Features

- **Customizable Interval:** The user can set the interval between each click in milliseconds.
- **Graphical User Interface:** A simple interface allows you to start and stop the autoclicker.
- **Easy Activation/Deactivation:** Start the autoclicker after a 3-second delay and stop it by pressing a button or the `q` or `Escape` keys.

## Prerequisites

- **macOS** (the code is specifically designed for macOS)
- **Homebrew** (to install necessary dependencies)
- **GTK+3** (for the graphical interface)

## Installation

1. **Clone the repository:**

   ```bash
   git clone https://github.com/ThomasRibalta/Auto-clicker.git
   cd autoclicker-macos
   ```

2. **Compilation and Installation:**

   This project uses a `Makefile` to automate the compilation process and manage dependencies.

   - To compile the program and install dependencies (Homebrew and GTK+3 if needed), run:

     ```bash
     make
     ```

   - If Homebrew is not installed, it will be automatically installed. Similarly, GTK+3 will be installed if necessary.

3. **Run the application:**

   Once the compilation is complete, you can run the autoclicker with the following command:

   ```bash
   ./autoclicker.exe
   ```

## Usage

1. **Click Interval:** Enter the desired interval between clicks in milliseconds in the text field.
2. **Start the Autoclicker:** Click the "Click to activate" button. The autoclicker will start after a 3-second delay.
3. **Stop the Autoclicker:** Click the "Stop" button or press the `q` or `Escape` keys to stop the autoclicker.

## Cleanup

To remove the generated executable, use:

```bash
make clean
```

## Contribution

Contributions are welcome! Feel free to submit issues and pull requests to improve the project.
