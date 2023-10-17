# worldclock
Terminal ui worldclock. 
Only works with gcc 13. clang has not implemented chrono timezones as of the date of writing of this readme.

<img src="https://github.com/notshriram/worldclock/assets/49370927/d6b3cddb-d254-4284-b379-7e6752c94377" width="512">


## Building

```bash
git clone https://github.com/notshriram/worldclock.git
cd worldclock
cmake -Bbuild
cmake --build build
./build/worldclock
```
