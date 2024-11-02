# Knock-Knock-Contraption
Inspired  by The Controversy Surrounding [Sam and Colby's Conjuring House YouTube Video](https://youtu.be/U5lR8GdcJyo?t=1618), I developed this prop for a Halloween event, similar to my Ghost Box trick from last year. It was designed to simulate the event host communicating with ghosts, with the ghosts responding back through a series of knocks. This idea came to me when I used my critical thinking skills to figure out how the couple working at the Conjuring House might be communicating with ghosts and causing a series of knocks to occur. 

To create the knocks, the Wemos D1 Mini acts as an access point and creates a web server. By connecting to the device and heading to the IP address 192.168.4.1, a webpage loads with two buttons on it, giving you the ability to control the knocking wirelessly. The two buttons are labeled "Yes" and "No." Pressing "Yes" results in two knocks, while pressing "No" results in one knock. This simulates how ghost hunting shows communicate with ghosts, asking yes or no questions and having the ghosts respond with knocks. The wireless control enhances the illusion, making it seem as if a ghostly force is responsible for the knocking. It's great because, in this day and age, people are always on their phones, so it looks more natural than someone holding a random garage remote or something similar.

One of the spookiest and best features of this project is that the housing has suction feet, allowing it to be mounted on various surfaces without the need for drilling the solenoids in place or propping it up with objects. This adds an extra layer of mystery and allows you to place the prop anywhere.

Note: This trick requires two people to pull off. You need an inside man, a plant, a partner to make it work!

Required library:
ESP8266WiFI and ESP8266WebServer Library - Easily Installable through the Arduino Software - Thanks to its creators

 Materials Used:

    Wemos D1 Mini (Arduino programmed) - eBay
    2x Solenoids - https://www.digikey.com.au/en/products/detail/ledex-dormeyer-saia-a-division-of-johnson-electric/195207-225/9676205
    2x MOSFET Power Switch Module - https://bit.ly/47aGjeH
    1N4001 Diode - https://bit.ly/3MgfApa
    12V Step Down (to 5v) - eBay
    Heat Shrink Tubing
    12V DC Power Supply
    Female DC Power plug
    Solder

 Tools:

    Clippers
    Pliers
    Soldering Iron
    Ender 3 3D printer (I had to 3D Print a enclosure)

   and a few other bits and bobs....




## The Wiring Diagram
[![IMAGE ALT TEXT HERE](https://github.com/Thats-so-Mo/Knock-Knock-Contraption/blob/main/Wiring%20Diagram%20for%20Solenoids.png?raw=true)](https://github.com/Thats-so-Mo/Knock-Knock-Contraption/blob/main/Wiring%20Diagram%20for%20Solenoids.png?raw=true)


