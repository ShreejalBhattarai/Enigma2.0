export PATH=/usr/bin:$PATH
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .

# Flash to Pico
PICO_DRIVE="/Volumes/RPI-RP2"
UF2_FILE="$HOME/Desktop/Enigma2.0/build/enigma.uf2"

echo "Waiting for Pico in BOOTSEL mode..."
while [ ! -d "$PICO_DRIVE" ]; do
    sleep 1
done

echo "Pico found! Flashing..."
cp "$UF2_FILE" "$PICO_DRIVE/"
echo "Done! Pico is running your code."