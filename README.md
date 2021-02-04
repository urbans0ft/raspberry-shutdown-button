# Raspberry Pi Button Shutdwon 

![Example Setup Sketch](img/example_setup.png)

## Preface

1. Compile
2. Use

## Compilation

```
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.68.tar.gz
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

## Usage

```
./shutdown
```

