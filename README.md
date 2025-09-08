## Task for: Rendering iOS Simulator on IntelliJ IDEA and Android Studio

More information on the internship position can be found at the [following link](https://internship.jetbrains.com/projects/1654).

### How to compile the final executable

Once you wrote the `main.c` file, please test your solution by compiling the program with:

**macOS**
```shell
cc main.c -lrender -L. -framework Cocoa -framework AudioToolbox
```

**Linux**
```shell
cc main.c -lrender -L. -lX11 -lasound
```
### Bonus

Already providing a functioning program is a huge step. However, if you like "challenges", are you able to activate the program's animation? :)
