# Simple MS43 CAN Decoder
![MS43 CAN DECODER](https://mcmillan.website/wp-content/uploads/2019/08/Screenshot-from-2017-06-06-17-46-39.png)

As part of an effort in converting an analog cluster to a digital dashboard I’ve been slowly taking steps to approach
the project to successful completion. I wanted to make sure I was a bit familiarized with Qt’s several APIs and I wanted
to see the performance of Qt displaying real time information. I’ve put together a simple program which opens a serial
connection to an arduino with a pre-loaded arduino sketch and reads the data, computes them to readable human units
(RPM, MPH, etc) and displays them. Since this program was developed around by reverse engineering CAN BUS data packets
from multiple BMW models, I found that during my initial test the speed (MPH) to be off by a certain degree, at one
point I was speculating that the formula used to compute speed was being reported in KPH. More testing has yet to be
done.
