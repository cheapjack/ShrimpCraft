# ShrimpCraft

![shrimpcraft copy](https://cloud.githubusercontent.com/assets/128456/7733192/9103e4a8-ff25-11e4-93b1-a7c8c4e9ce5c.jpg)

### Prototype Kits for Shrimped Arduino sensor boards and code

**ShrimpCraft** is a project initialised from [Amanda Steggell](http://www.testingtesting.org/) and [Ross Dalziel's](http://cheapjack.org.uk) project, [Currently](http:/currently.no) to introduce young people to DIY water sensing with basic electronics using kits from the Morecambe based [Shrimping.it](http://start.shrimping.it) project. In this case the kits measure temperature with a **DS1820 Water Proof Temperature Sensor** and a DIY turbidity sensor

It uses the *brilliant* **Shrimped Arduino kits** from [Shrimping.it](http://start.shrimping.it) at its core and also features prototype methods for visualising data on onboard LED flashers, in Processing and in Minecraft using a modified version of Martin O'Hanlon's [mcpi API](https://github.com/martinohanlon/mcpi) and the [FACT](http://fact.co.uk) [Minecraft CloudMaker Server](http://89.34.96.47:8125/)

### Background

It's part of [The Minecraft Of Things](http://minecraftofthings.tumblr.com) which sprang from research with FACT, Mark Wright, Adrian McEwen and Paul Harter funded by AHRC for the [CloudMaker](http://www.fact.co.uk/projects/cloudmaker-making-minecraft-real.aspx) project

### Getting Started

First off buy your kits or source and assemble your own at [Shrimping.it](http://start.shrimping.it). You can source **DS1820 Water Proof Temperature Sensors** and LDR's from pretty much any where on the internet.

The easiest way to make our arduino sketches work with libraries is to download or clone this repo, `unzip` if necessary and then in your **Arduino IDE** temporarily change your sketchbook location in `Menu/Arduino/preferences` to `path/to/my/download/ShrimpCraft/resources/sketchbook` which will make sure the libraries are in the right place.

Now you'll see the different sketches in the IDE in the `Menu/File/Sketchbook` dropdown menu.

Then just change it back to your normal location afterwards.

### Is This Open Source?

The project is essentially about data, software and hardware literacy in the context of doing and exploring our relationship to Water. It's released under a highly permissive MIT License but not necessarily recursively; some elements are released under certain different terms and you will need follow back to source to see this.

This project and the wider CloudMaker project follows the `spirit` of open source although some elements used may not **strictly** be `open-source`: 

 * Minecraft is not open source but has a large modding culture and are famously vague about IP. You have to buy the game basically to play most servers. This project however is based on the use of [Minecraft Pi Edition](http://pi.minecraft.net/?page_id=14) which is free to download and use and initiated by Mojang but maintained by the Minecraft and [Raspberry Pi](http://elinux.org/RPi_Hub) community
 * Processing is used under a GPL license
 * `mcpi` is an API for Minecraft Pi Edition, released under an MIT License and is maintained by Martin O'Hanlon's [Stuff About Code](http://www.stuffaboutcode.com/p/minecraft.html) project.
 * [Shrimping.it](http://shrimping.it/blog/) is open source even if some components may not be and also clearly about pedagogy and technological literacy which is reflected in their views on [Breadboards](http://shrimping.it/blog/why-no-pcbs/) 

### Useage

For more detail about using the resources go [here](https://github.com/cheapjack/ShrimpCraft/blob/master/resources/README.md)

### Workshops

#### [Workshop Details](https://github.com/cheapjack/ShrimpCraft/blob/master/Events.md)

It has been run as pop up workshops for families and children at

 * Walney Primary School, Walney Island, Cumbria with [Octopus Collective](http://www.octopuscollective.org)
 * Liverpool Maritime Museum
 * [Do-It-Anyway festival](http://opensourcingfestivals.eu/events/do-it-anyway-festival-sheffield-uk) at [Access Space](http://access-space.org/) in partnership with [Piksel](http://piksel.no/) [Sheffield Images](https://www.flickr.com/photos/ajsteggell/sets/72157653152049145)
 * [Piksel15 Get A Life! City-Water Workshop](http://15.piksel.no/city-water/) with Gemma May Latham and Elizabeth Weihe

### Health & Saftey

Any launching of software or hardware on the water must be done under adult supervision with appropriate considerations to health and safety. None of the authors or copyright holders of this Repo nor its components accept any liability in any event arising from the use of this software or hardware.

Please look at the LICENSE.txt file. By using any of the repo contents you agree to it's terms



