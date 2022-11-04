# Mackie of the Unicorn
[![Build Status](https://ci.sjoerdscheffer.nl/buildStatus/icon?job=MOTU-macOS%2Fmaster&subject=macOS%20build)](https://ci.sjoerdscheffer.nl/job/MOTU-macOS/job/master/)
[![Build Status](https://ci.sjoerdscheffer.nl/buildStatus/icon?job=MOTU-Windows%2Fmaster&subject=Windows%20build)](https://ci.sjoerdscheffer.nl/job/MOTU-Windows/job/master/)

Use control surfaces to control a MOTU AVB DSP mixer.

This project is in development and not ready for production use. It doesn't have a functional CLI or GUI at this point.

These are the goals for the first release (checked goals are implemented):

- [x] Support a single Mackie Control unit
- [ ] Control channel faders
- [x] Control channel mutes
- [x] Control channel solos
- [ ] Control channel pan
- [ ] Show channel names on the scribble strip
- [x] macOS support
- [x] Windows support
- [x] Integration tests using mocked MIDI and HTTP devices
- [ ] Graphical user interface
- [ ] Commandline interface
- [ ] Control stereo channels using a single channel strip
- [x] Bank between 8 channels
- [ ] Documentation
