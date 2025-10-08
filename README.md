## Task for: Rendering iOS Simulator on IntelliJ IDEA and Android Studio

More information on the internship position can be found at the [following link](https://internship.jetbrains.com/projects/1654).

### Compiling the program

**Linux**

```shell
cc -o solution main.c 
# My solution uses the <dlfcnh.h> header, which may not be linked automatically on some linux distributions. In case of an error, try following.
cc -o solution main.c -ldl
# Run the program
./solution
```


### Sidenote

Thanks to JetBrains for organizing an interesting challenge
