# 3D-graphics
---

![](https://github.com/BjorneEk/3d-graphics/blob/teapot-2.png?raw=true)
**A program that reads obj files and renders them in a window.**

The goal with the project was to render a [Utah-teapot](https://graphics.cs.utah.edu/teapot/) in a window using only code written myself. I was mostly successful in doing this however i had to do some research and learn about projection matrices as well as freshen up on cross products.

---

The program is fairly limited in the files it can parse and it will not be able to render all .obj files. For a file to function it cannot contain normal data and the faces must be triangles. see the example below for a simple cube.

***This file works:***
```
o Cube
v 0.0 0.0 0.0
v 0.0 0.0 1.0
v 0.0 1.0 0.0
v 0.0 1.0 1.0
v 1.0 0.0 0.0
v 1.0 0.0 1.0
v 1.0 1.0 0.0
v 1.0 1.0 1.0
f 1 3 5
f 3 7 5
f 5 7 6
f 7 8 6
f 6 8 2
f 8 4 2
f 2 4 1
f 4 3 1
f 3 4 8
f 8 7 3
f 2 1 5
f 5 6 2
```

***This file does not:***
```
o Cube
v 0.0 0.0 0.0
v 0.0 0.0 1.0
v 0.0 1.0 0.0
v 0.0 1.0 1.0
v 1.0 0.0 0.0
v 1.0 0.0 1.0
v 1.0 1.0 0.0
v 1.0 1.0 1.0
f 1 3 5 7
f 5 7 6 8
f 6 8 2 4
f 2 4 1 3
f 3 4 8 7
f 2 1 5 6
```

The lines begining with a 'f' in a .obj file represents a face and they have to be in the format `f P1 P2 P3` and not `f P1 P2 P3 ... Pn` or `f P1/N1 P2/N2 P3/N3`.

---

## **Usage**

```
$ ./3D-graphics <filename.obj>
$ ./3D-graphics <filename.obj> rand (for random colors)
$ ./3D-graphics <filename.obj> <FOREGROUND_COLOR> (RED, GREEN, BLUE)
$ ./3D-graphics <filename.obj> <FOREGROUND_COLOR> <BACKGROUND_COLOR>
$ ./3D-graphics <filename.obj> <FOREGROUND_RGB> (1,0.7,0.3) values between 1 and 0
$ ./3D-graphics <filename.obj> <FOREGROUND_RGB> <BACKGROUND_RGB>
```
### **controlls**

| Key              | Action, enable/dissable |
|:----------------:|:-----------------------:|
|H                 |         wireframe       |
|J                 |    render with color    |
|L                 |    render with light    |
|k                 |dissable triangle sorting|
|W/UP              |   move light source up  |
|A/LEFT            |  move light source left |
|S/DOWN            |  move light source down |
|D/RIGHT           | move light source right |
|left mouse        |      rotate object      |
|SHIFT+ left mouse |       move object       |
| scroll wheel     |   move object in Z dir  |


![](https://github.com/BjorneEk/3d-graphics/blob/rendered-cow.png?raw=true)
