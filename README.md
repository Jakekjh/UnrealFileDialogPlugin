# FileDialogPlugin for Unreal Engine

A cross-platform file dialog plugin for Unreal Engine, allowing users to easily open and save files using native system dialogs, as well as select folders.

## Features
- **Open Folder Dialog**: Select a folder.
- **Open File Dialog**: Select a file with customizable filters.
- **Save File Dialog**: Save a file with customizable filters.
- Support for multiple file types such as text files, PDFs, images, audio, video, and more.
- Cross-platform support for Windows (and other platforms if applicable).

## Installation

### 1. Download the Plugin
Clone or download this repository to your local machine.

### 2. Adding the Plugin to Your Unreal Project
1. Copy the `FileDialogPlugin` folder into your project's `Plugins` folder. If your project doesn't have a `Plugins` folder, create one.
2. Open your Unreal Engine project.
3. Go to **Edit > Plugins** in the Unreal Engine Editor.
4. Find the **FileDialogPlugin** in the list and enable it.
5. Restart the Unreal Engine Editor to load the plugin.

### 3. Usage

You can use the following functions in your project:

- **OpenFileDialog** – Opens a file selection dialog.
- **SaveFileDialog** – Opens a save file dialog.
- **OpenFolderDialog** – Opens a folder selection dialog.