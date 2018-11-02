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
* [KEIL](https://www.keil.com/download/product/)(or other ARM) IDE with all the dependencies.

## Connect

Specific pins used in this example to connect STM32 and SD-CARD are shown in table below. Pinout can be adjusted in the software.

| Interface | SD Card Pin | Pin Mapping for STM32f103 |
| :--- | :---: | :---: | 
| SPI Clock | SCK | B13 |
| SPI Data(from Master) | MOSI | B15|
| SPI Data(from SD- Card) | MISO | B14 |
| SPI Chip Select | CS | C14|
| SD Power | VCC | A15|
| SD Ground | GND | GND |

<br>

The Music output/control pins are :-

| Interface  | Pin Mapping for STM32f103 |
| :--- | :---: | 
| Audio Out | A1|
| Music Start/Stop LED | A15|


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
