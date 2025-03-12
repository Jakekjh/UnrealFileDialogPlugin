# FileDialogPlugin for Unreal Engine

A cross-platform plugin for Unreal Engine, providing users with the ability to open, save, and select files and folders using native system dialog boxes, returning the file or folder path.

## Features
- **Open Folder Dialog**: Select a folder using a system-native dialog.
- **Open File Dialog**: Select a file with customizable filters.
- **Save File Dialog**: Save a file with customizable filters.
- Support for multiple file types including text, PDFs, images, audio, video, and more.

## Installation

### 1. Download the Plugin
Clone or download this repository to your local machine.

### 2. Adding the Plugin to Your Unreal Project
1. Copy the `FileDialogPlugin` folder into your project's `Plugins` folder. If your project doesn't have a `Plugins` folder, create one.
2. Open your Unreal Engine project.
3. Go to **Edit > Plugins** in the Unreal Engine Editor.
4. Find the **FileDialogPlugin** in the list and enable it.
5. Restart Unreal Engine Editor to load the plugin.

## File Type Filters Supported
The plugin supports various file types, which can be used in the file dialog to filter the selection. The EFileType enum defines the types of files:

- All Files: *.*
- Text Files: *.txt
- PDF Files: *.pdf
- Word Documents: *.doc, *.docx
- Image Files: *.jpg, *.jpeg, *.png, *.gif
- Audio Files: *.mp3, *.wav, *.flac
- Video Files: *.mp4, *.avi, *.mov
- Archive Files: *.zip, *.rar, *.7z
- Code Files: *.cpp, *.h, *.js
- Spreadsheet Files: *.xls, *.xlsx
- Presentation Files: *.ppt, *.pptx
- Database Files: *.mdb
- Executable Files: *.exe
These file types can be used to filter the file dialog to allow only specific types of files to be selected by the user.

## Blueprint Nodes for File Dialog Functions

![image](https://github.com/user-attachments/assets/55fc38a3-9777-4d93-8b29-387456f5b813)

## Dialog Window Screenshots

### Open File Dialog
![image](https://github.com/user-attachments/assets/fa3010df-a3c2-4380-a73c-977615ad6df6)

### Save File Dialog
![image](https://github.com/user-attachments/assets/ca9ea5b6-7604-475a-9cd1-2b9cde17dc23)

### Open Folder Dialog
![image](https://github.com/user-attachments/assets/96cc4556-45d0-4dcd-ace4-d1a3a87da4e0)


