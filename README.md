# worldclock
Terminal ui worldclock. 
Only works with gcc 13. clang has not implemented chrono timezones as of the date of writing this readme.

<img src="https://github.com/notshriram/worldclock/assets/49370927/8fa044c0-c1ea-41c0-8a0b-72e43d6d0c83" width="512">

## Building

```bash
git clone https://github.com/notshriram/worldclock.git
cd worldclock
cmake -Bbuild
cmake --build build
./build/worldclock
```
