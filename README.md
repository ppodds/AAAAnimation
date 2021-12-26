# AAAAnimation

## About

This is a term project of Assembly Language and System Programming course in NCU. It decode video with FFmpeg and plays ASCII animation with assembly.

## Installation

### Envirment

- Visual Studio 2019
  - Universal Windows Platform
  - C++ Desktop
  - Windows 10 SDK (10.0.1904)
  - Build Tools v142
- FFmpeg
  - [ffmpeg-n4.4.1-2-gcc33e73618-win64-lgpl-shared-4.4](https://github.com/BtbN/FFmpeg-Builds/releases)
- Qt
  - msvc 6.2.2
  - Windows

### Clone The Repository and Set Environment Variables

```shell
git clone https://github.com/ppodds/AAAAnimation.git
```

Environment Variables

- ffmpeg
  - `%your_project_path%\includes\ffmpeg`
- qt
  - `%your_qt_path%`
- PATH
  - `%qt%\bin;%ffmpeg%\bin%;...`
