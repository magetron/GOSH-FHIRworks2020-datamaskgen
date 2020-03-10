# GOSH FHIRworks 2020 Data Masker - Generator [![Build Status](https://travis-ci.com/magetron/GOSH-FHIRworks2020-datamasker.svg?token=1egyyzxUBmAzQpnmo8g4&branch=master)](https://travis-ci.com/magetron/GOSH-FHIRworks2020-datamasker)

## Introduction

A data synthesizer and masker that takes in real FHIR patient data and generate data providing certain rules.

This tool is developed with performance and customisation in mind. See [TODO: UPDATES] on how to customise with custom data modules.

## Installation

```shell script
mkdir build
cd build
cmake ..
```

To compile and Use under current folder.

```shell script
make
```

Or to install in system,

```shell script
make install
```

## Usage

* `--quiet` for `SILENT` Mode
* `--use-cache` for loading cached `patients.json` file at a custom location, to be used with `--cache-loc`
* `--api ${YOUR_CUSTOM_API}`
* `--cache-loc ${CACHE_FILE_LOCATION}`
* `-g ${NO OF PATIENTS TO BE GENERATED}`
* `-o ${OUTPUT_FILE_LOCATION}`

### Sample

Note: Create your own output directory before writing output files.

```shell script
./GOSH_FHIRworks2020_datamasker -v --api https://localhost:5001/api/Patient -g 100 -o ./output/
```
