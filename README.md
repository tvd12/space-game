# Space Game
Demo for [ezyfox-sever](https://youngmonkeys.org/ezyfox-sever/)

# Thanks
[www.raywenderlich.com](https://www.raywenderlich.com/2728-cocos2d-x-tutorial-for-ios-and-android-space-game)

# Download
Download completed source [here](https://resources.tvd12.com/space-game-1.0.0.zip)

# Guide
[Use embedded ezyfox-server](https://youngmonkeys.org/use-embedded-server/)
[Use ezyfox cpp client sdk](https://youngmonkeys.org/ezyfox-cpp-client-sdk/)
[User to ezydata-mongodb](https://youngmonkeys.org/introduce-to-ezymongo/)

# Build issues
1. Argument value 10880 is outside the valid range [0, 255]
Replace cocos2d/external/bullet/include/bullet/LinearMath/btVector3.h line 42:
```cpp
#define BT_SHUFFLE(x,y,z,w) ((w)<<6 | (z)<<4 | (y)<<2 | (x))
```
with new one:
```cpp
#define BT_SHUFFLE(x, y, z, w) (((w) << 6 | (z) << 4 | (y) << 2 | (x)) & 0xff)
```
refer: https://discuss.cocos2d-x.org/t/xcode-11-ios-13-cocos-not-running/46825/4
2. xcode 12 linking error
Exclude `arm64`, refer [this guild](https://stackoverflow.com/questions/63607158/xcode-12-building-for-ios-simulator-but-linking-in-object-file-built-for-ios)

# Run
```bash
gradle wrapper
```
```bash
gradle build
```