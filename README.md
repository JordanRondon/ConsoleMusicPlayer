
# Music Player Console

A simple music player console application written in C/C++ that allows you to play MP3 files from a user-defined folder or the default "Music" folder.

## Features

- Play MP3 files.
- Navigate through the playlist.
- Control volume and playback.
- Easy-to-use interface.

## Requirements

- C++17 onwards
- BASS Audio Library (for MP3 playback)

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/JordanRondon/ConsoleMusicPlayer.git

2. Run the application:
   - Build and run the project in Visual Studio.

## Important Note: bass.dll Error

If the system detects an error stating that the bass.dll file could not be found, follow these steps to fix the issue:

   - Navigate to the ConsoleMusicPlayer/dependence directory within your project.
   - Copy the bass.dll file from this directory.
   - Paste the bass.dll file into the Debug folder where the .exe file is located. This is usually the same folder where your built application resides.

This step is crucial because the application relies on the bass.dll file to function correctly. If the file is missing or not in the correct location, the application will fail to load or play music.

## Usage

When you run the application, you will be prompted to choose the location of your music files. You can select the default "Music" folder in Windows environments or enter a custom path.

Once the music is loaded, you can:
- Play/Pause the track, press the p/s key.
- Skip to the next or previous track, press the n/b key.
- Adjust the volume, press the -/+ key.
- Search forward or backward, press the f/r key.