#include "SpiffsFilePrint.h"

SpiffsFilePrint::SpiffsFilePrint(Print *const alsoPrintTo)
    : logfileName(DEFAULT_LOGFILE_NAME),
      filesCount(1),
      targetedFileSize(UINT8_MAX),
      alsoPrintTo(alsoPrintTo) {}

SpiffsFilePrint::SpiffsFilePrint(String logfileName, uint8_t logfilesCount,
                                 unsigned int targetedFileSize, Print *const alsoPrintTo)
    : logfileName(logfileName),
      filesCount(logfilesCount),
      targetedFileSize(targetedFileSize),
      alsoPrintTo(alsoPrintTo) {}

SpiffsFilePrint::~SpiffsFilePrint() { close(); }

void SpiffsFilePrint::open() {
    close();
    checkSizeAndAdjustCurrentFilename();
    if (!SPIFFS.exists(currentFilename)) {
        file = SPIFFS.open(currentFilename, FILE_WRITE);
    } else {
        file = SPIFFS.open(currentFilename, FILE_APPEND);
    }
    if (!file) {
        Serial.print("Error opening file ");
        Serial.println(currentFilename);
    }
}

void SpiffsFilePrint::close() {
    if (file) {
        flush();
        file.close();
    }
}

void SpiffsFilePrint::flush() {
    if (!file) {
        return;
    }

    noInterrupts();
    char fileWriteBuf[nextWritePos];
    memcpy(&fileWriteBuf, &buf, nextWritePos + 1);
    fileWriteBuf[nextWritePos] = '\0';
    nextWritePos = 0;
    interrupts();
    // file.print() must be called when interrupts are enabled
    file.print(fileWriteBuf);
    // flush does not work reliably, only close and reopen does
    file.close();
    checkSizeAndAdjustCurrentFilename();
    file = SPIFFS.open(currentFilename, FILE_APPEND);
}

size_t SpiffsFilePrint::write(uint8_t n) {
    const char c = n;
    if (alsoPrintTo != NULL) {
        alsoPrintTo->print(c);
    }
    if (!file) {
        return 1;
    }

    noInterrupts();
    buf[nextWritePos++] = c;
    if (nextWritePos == BUFFER_SIZE - 2 || c == '\n') {
        interrupts();
        flush();
    }
    interrupts();
    return 1;
}

void SpiffsFilePrint::checkSizeAndAdjustCurrentFilename() {
    bool foundFile = false;
    for (int i = 0; i < filesCount; i++) {
        String filename = assembleCurrentFilename(i);
        if (SPIFFS.exists(filename)) {
            File currentFile = SPIFFS.open(filename, FILE_READ);
            size_t size = 0;
            if (currentFile) {
                size = currentFile.size();
                currentFile.close();
            }
            if (size < targetedFileSize) {
                currentFilename = filename;
            } else {
                SPIFFS.rename(filename, assembleFilename(i));
                if (i < filesCount - 1) {
                    SPIFFS.remove(assembleFilename(i + 1));
                    currentFilename = assembleCurrentFilename(i + 1);
                } else {
                    SPIFFS.remove(assembleFilename(0));
                    currentFilename = assembleCurrentFilename(0);
                }
            }
            foundFile = true;
            break;
        }
    }
    if (!foundFile) {
        currentFilename = assembleCurrentFilename(0);
    }
}

String SpiffsFilePrint::assembleCurrentFilename(uint8_t index) {
    return logfileName + index + CURRENT_FILE_POSTFIX + LOGFILE_EXTENSION;
}

String SpiffsFilePrint::assembleFilename(uint8_t index) {
    return logfileName + index + LOGFILE_EXTENSION;
}
