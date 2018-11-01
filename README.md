# Project Title

STM32 Based Music Player

## Getting Started

The code provided in this repository can be used to play any .wav audio file using the STM32f103c8t6. The audio file should be locally stored in an SD card 
and the PWM output is provided through the outputPin defined in the Music_config file. The pin needs to be connected to one of the AUX input of any speaker/earphones 
along with the ground. The music can be started/stopped by the use of a user button attached on buttonInput pin.

### Prerequisites

The components required for a proper build of the project are - 

* [STM32F103](https://www.st.com/en/microcontrollers/stm32f103.html?querycriteria=productId=LN1565)
* SD Card
* KEIL(or other ARM) IDE with all the dependencies.

```
Give examples
```
## Connect

Specific pins used in this example to connect ESP32 and camera are shown in table below. Pinout can be adjusted to some extent in software. Table below provides two options of pin mapping (last two columns).

| Interface | Camera Pin | Pin Mapping for ESP32 DevKitJ | Alternate ESP32 Pin Mapping |
| :--- | :---: | :---: | :---: |
| SCCB Clock | SIOC | IO27 | IO23 |
| SCCB Data | SIOD | IO26 | IO25 |
| System Clock | XCLK | IO21 | IO27 |
| Vertical Sync | VSYNC | IO25 | IO22 |
| Horizontal Reference | HREF | IO23 | IO26 |
| Pixel Clock | PCLK | IO22 | IO21 |
| Pixel Data Bit 0 | D2 | IO4 | IO35 |
| Pixel Data Bit 1 | D3 | IO5 | IO17 |
| Pixel Data Bit 2 | D4 | IO18 | IO34 |
| Pixel Data Bit 3 | D5 | IO19 | IO5 |
| Pixel Data Bit 4 | D6 | IO36 | IO39 |
| Pixel Data Bit 5 | D7 | IO39 | IO18 |
| Pixel Data Bit 6 | D8 | IO34 | IO36 |
| Pixel Data Bit 7 | D9 | IO35 | IO19 |
| Camera Reset | RESET | IO2 | IO15 |
| Camera Power Down | PWDN | *see Note 3* | *see Note 3* |
| Power Supply 3.3V | 3V3 | 3V3 | 3V3 |
| Ground | GND | GND | GND |


### Installing

A step by step series of examples that tell you how to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Billie Thompson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone whose code was used
* Inspiration
* etc
