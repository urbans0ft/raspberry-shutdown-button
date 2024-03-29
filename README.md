# Raspberry Pi Button Shutdown 

![Example Setup Sketch](img/example_setup.png)

## Usage

To install the shutdown daemon with the configuration shown in the sketch
above use the [latest release](https://github.com/urbans0ft/raspberry-shutdown-button/releases/latest) and execute the following command.

```
sudo ./shutdown -I
```

The Rraspberry Pi will now shutdown immediately if the button connected
to pin number 5 is pressed longer than ~3sec. To customize time and pin
have a look at the development section below.

## Development

### Build

```
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.68.tar.gz
tar xvzf bcm2835-1.68.tar.gz
cd bcm2835-1.68
./configure
make
sudo make check
sudo make install
cd ..
git clone https://github.com/urbans0ft/raspberry-shutdown-button.git
cd raspberry-shutdown-button
make release PIN_NO=Pin05 SAFETY_DELAY=3000ms POLL_DELAY=500ms
```

### Customize

To customize build in debug mode by omiting `release` in `make release` (see example below).

```
make clean
make PIN_NO=Pin05 SAFETY_DELAY=3000ms POLL_DELAY=500ms
```

- `PIN_NO`  
  The (physical/board) pin number (*not* GPIO) the button is wired to (default: `Pin05`).
- `SAFETY_DELAY`  
  The minimum time to press the button before shutting down (default: `3000ms`).
- `POLL_DELAY`  
  The intervall to check for _LOW_/_HIGH_ events on `PIN_NO`.
  
> The debug mode is quite verbose. Do not use a debug build for service installation!

### Test

To test without installing simply use `sudo ./shutdown` without any command line arguments.

