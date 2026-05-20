# Project Faulken Assets

WindowUI can load optional static assets from these folders:

- `images/`: BMP files shown with `ui->showImage("name")`, for example `images/zero_east.bmp`.
- `sounds/`: WAV files played by game sound IDs, for example `sounds/item.wav`, `sounds/error.wav`, or `sounds/terminal.wav`.

If a sound file is missing, WindowUI plays a generated fallback tone. ConsoleUI still uses the terminal bell.
