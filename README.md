# GOSH FHIRworks 2020 Data MaskGen 

[![Build Status](https://travis-ci.com/magetron/GOSH-FHIRworks2020-datamaskgen.svg?token=1egyyzxUBmAzQpnmo8g4&branch=master)](https://travis-ci.com/magetron/GOSH-FHIRworks2020-datamaskgen)
![C++](https://img.shields.io/badge/C%2B%2B-1z-red)
![License](https://img.shields.io/badge/license-Apache--2.0-blue)

## Screenshot

![Screenshot](https://raw.githubusercontent.com/magetron/GOSH-FHIRworks2020-datamaskgen/master/README.png)


## Introduction

A data synthesizer and masker that takes in real FHIR patient data and generate data providing certain rules.

This tool is developed with performance and customisation in mind. See below on how to customise with custom data modules.

## Installation

```shell script
mkdir build
cd build
cmake ..
```

To compile and use under current folder.

```shell script
make
```

Or to install in system **(POSIX system only)**,

```shell script
make install
```

## Usage

Note : To be used with Patients API endpoints, official version from [GOSH](https://github.com/goshdrive/FHIRworks_2020), or unofficial ones here from [@henryz00](https://henryz.cc:5001/api/), or simply a [gist - Github](https://gist.githubusercontent.com/magetron/cf8e0de347e333c67f8e66c13572b111/raw/7046cca2915f6e9b68bed9c409e6e02a6cc5709e/patients.json), whichever you chose, please specify when calling the application.

* `--quiet` for `SILENT` Mode
* `--use-cache` for loading cached `patients.json` file at a custom location, to be used with `--cache-loc`
* `--api ${YOUR_CUSTOM_API}`
* `--cache-loc ${CACHE_FILE_LOCATION}`
* `-g ${NO OF PATIENTS TO BE GENERATED}`
* `-o ${OUTPUT_FILE_LOCATION}`
* `-h` or `--help` for showing the help message

### Sample

```shell script
./GOSH_FHIRworks2020_datamaskgen --api https://localhost:5001/api/Patient -g 100 -o ./
```

## Performance

Build with performance in mind, `Data MaskGen` utilises system resources much better than the industrial standard `synthea` and therefore archives much better running time with similar results.

| Patient Amount | Data MaskGen | Synthea  |
|------	|-----------------	|------------------	|
| 1 	| 98% cpu, 1.836s 	| 10% cpu, 13.067s 	|
| 50 	| 99% cpu, 1.863s 	| 9% cpu, 15.817s 	|
| 100 	| 99% cpu, 1.917s 	| 6% cpu, 23.035s 	|
| 500 	| 99% cpu, 2.258s 	| 5% cpu, 30.726s 	|
| 1000 	| 99% cpu, 2.601s 	| 4% cpu, 41.757s 	|

## Customisation

Customise any of the `generator` in the `src/generator` folder, or add your own  class with suffix `_generator`.

Your customised class will be required to feed in a `const` reference to original patients list `vector`, and then generate required information based own your customised algorithm.

Specify your output of custom data set in `jsonify()` function in `src/patient/patient.hh`, and sit back to see the new data getting generated.


