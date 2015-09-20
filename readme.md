Flame Thrower Control from Across the World
==============

Imagine you have a flame thrower and you want to control it from across the world. I have this problem all the time. And if it falls over, it should probably turn off. This example shows how to use the [SparkFun ESP8266 Thing](https://www.sparkfun.com/products/13231) to connect to a mobile app via Blynk. It also reads a the[ LSM9DS1 IMU](https://www.sparkfun.com/products/13284) to see if you're upside down and controls a [solid state relay (SSR)](https://www.sparkfun.com/products/13015) to turn on/off a very large load (up to 380VAC @ 30A!).

![ESP8266 with relay and accelerometer](https://raw.githubusercontent.com/nseidle/World_Control_Of_SSR/master/SparkFun_Thing_SSR_Setup.jpg "SparkFun ESP8266 Thing with accelerometer and SSR")

Ok, no flame thrower but you get the idea. The SSR can control very large loads including sparkers, lights, generators, motors, pumps, you name it. This demo is interesting because it pushes data out to the internet (the Blynk servers) so you can control and get data from the Thing located anywhere in the world. You don't need a direct connection from phone to board.

![Blynk app with button and indicator](https://raw.githubusercontent.com/nseidle/World_Control_Of_SSR/master/Relay-Control.png)

[Blynk](http://www.blynk.cc) is an easy to use app builder that connects the ESP8266 to a server and your cell phone to a server so that they can coomunicate across networks and from anywhere in the world. It's currently free but they may charge for some of the more advanced widgets someday.

![Blynk app notification](https://raw.githubusercontent.com/nseidle/World_Control_Of_SSR/master/UpsideDownFlameCannon.png)

You can do push notifications as well. It's good to know when your flame cannon has been shut off. 

License Information
-------------------
The **code** is beerware; if you see me (or any other SparkFun employee) at the local, and you've found our code helpful, please buy us a round!

Please use, reuse, and modify these files as you see fit. Please maintain attribution to SparkFun Electronics and release anything derivative under the same license.

Distributed as-is; no warranty is given.

- Your friends at SparkFun.
