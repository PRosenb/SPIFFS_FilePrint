# Arduino PIFFS FilePrint Library #
https://github.com/PRosenb/PIFFS_FilePrint

PIFFS FilePrint is a lightweight, simple library for rolling file print to log to SPIFFS.  

## Features ##
- Easy to use

## Installation ##
- The library can be installed directly in the [Arduino Software (IDE)](https://www.arduino.cc/en/Main/Software) as follows:
  - Menu Sketch->Include Library->Manage Libraries...
  - On top right in "Filter your search..." type: PIFFS FilePrint
  - The PIFFS FilePrint library will show
  - Click on it and then click "Install"
  - For more details see manual [Installing Additional Arduino Libraries](https://www.arduino.cc/en/Guide/Libraries#toc3)
- If you do not use the [Arduino Software (IDE)](https://www.arduino.cc/en/Main/Software):
  - [Download the latest version](https://github.com/PRosenb/PIFFS_FilePrint/releases/latest)
  - Uncompress the downloaded file
  - This will result in a folder containing all the files for the library. The folder name includes the version: **PIFFS_FilePrint-x.y.z**
  - Rename the folder to **PIFFS_FilePrint**
  - Copy the renamed folder to your **libraries** folder
  - From time to time, check on https://github.com/PRosenb/PIFFS_FilePrint if updates become available

## Getting Started ##
Simple Logger:
```c++
#include <SpiffsFilePrint.h>

void setup() {
    Serial.begin(115200);

    if (!SPIFFS.begin()) {
        Serial.println("SPIFFS Mount Failed, we format it");
        SPIFFS.format();
    }
    // SPIFFS.format();

    SpiffsFilePrint filePrint("/logfile", 2, 500, &Serial);
    filePrint.open();

    filePrint.print("Millis since start: ");
    filePrint.println(millis());

    filePrint.close();
}

void loop() {
}
```

## Examples ##
The following example sketches are included in the **PIFFS FilePrint** library.  
You can also see them in the [Arduino Software (IDE)](https://www.arduino.cc/en/Main/Software) in menu File->Examples->PIFFS FilePrint.  

- [**Simple Logging**](https://github.com/PRosenb/PIFFS_FilePrint/blob/master/examples/LogWithArduinoLog/LogWithArduinoLog.ino): Simple example how to use this library.  
- [**Print to file and console**](https://github.com/PRosenb/PIFFS_FilePrint/blob/master/examples/PrintFileToConsole/PrintFileToConsole.ino): Print to the console and to a file at the same time and show the content of the logfile.   
- [**Log with ArduinoLog**](https://github.com/PRosenb/PIFFS_FilePrint/blob/master/examples/LogWithArduinoLog/LogWithArduinoLog.ino): Use ArduinoLog and configure it to log to a log file. Show the content of the logfile afterwards.  

## Contributions ##
Enhancements and improvements are welcome.

## License ##
```
Arduino PIFFS FilePrint Library
Copyright (c) 2019 Peter Rosenberg (https://github.com/PRosenb).

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```
