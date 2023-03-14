# Overview

This is a template for VEX code. I essentially took the existing 2023 code and slimmed it down to just driving code. I also added comments explaining what things do.

I put it in this separate folder because I didn't want to delete anything that was already done, but I wanted to give a reference for getting drive code up and running.

## Relevant things to know:

* The [firmware](firmware) folder contains, well, firmware. Include this too.
* The [include](include) folder contains the library files, such as PROS, okapi, and Littlev (for the auton selection GUI). You want to include these. You see this also includes [include/api.h](api.h), [include/main.h](main.h), and [include/robot_constants.hpp](robot_constants.hpp). It's up to you how you want to do robot_constants and where to put it or how to go about it, but you should also include the api and main header files in any project you make.
* In [src](src), you will see a few files and a few folders.
  * [src/main.cpp](main.cpp) is the main file that runs the robot. You will see functions for auton, initialization, and op control. There in comments in there for what each of those mean, but this is where you'll put the code for each of those. If you wanted to, you could write the entire robot code in that one file, but you probably want to have separate files for everything.
  * [src/autons.hpp](autons.hpp) and [src/autons.cpp](autons.cpp) are where the auton code is. If you have multiple autons, this is where you would write each of them. Make sure the header file has everything you write in the cpp file. You will also likely need to update the auton_selector files to include any additional autons you write.
  * [src/chassis](chassis) is significantly simplied from what was in there before, because I deleted the pathfinding code for ease. If you want to look at it, you can look at [Spin-Up\HSKY15_SpinUp\src\chassis](../../Spin-Up\HSKY15_SpinUp\src\chassis). It's complicated though, and an extra thing that's cool to have and might be useful, but for sake of this I decided to remove it.
    * TODO: test to make sure I didn't delete anything important
  * [src/scorer](scorer) is for the catapult and intake. I didn't delete anything here, but this involves using sensors, and also includes the code for how to control them, similar to the drive code. If you understand the drive code, this should make sense.
    * TODO: look into what the colors refer to

Hopefully this seems a bit more simple to follow, and a lot of this will stay relevant for any future games as well.
