#ifndef SPIFFS_FILE_PRINT_H
#define SPIFFS_FILE_PRINT_H

#include <Arduino.h>
#if defined(ESP32)
#include <SPIFFS.h>
#elif defined(ESP8266)
#include <FS.h>
#define FILE_WRITE "w"
#define FILE_APPEND "a"
#define FILE_READ "r"
#else
#error "Not supported CPU"
#endif

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif
#ifndef CURRENT_FILE_POSTFIX
#define CURRENT_FILE_POSTFIX ".current"
#endif
#ifndef LOGFILE_EXTENSION
#define LOGFILE_EXTENSION ".log"
#endif
#ifndef DEFAULT_LOGFILE_NAME
#define DEFAULT_LOGFILE_NAME "/logfile"
#endif

class SpiffsFilePrint : public Print {
   public:
    /**
     * Print the output to a single file. Ensure that the file system has enough space.
     * @param alsoPrintTo a Print to additionally print to, usually &Serial
     */
    SpiffsFilePrint(Print *const alsoPrintTo = NULL);
    /**
     * @param logfileName name of the logfiles without number and extension
     * @param logfilesCount amount of files to be used for logging
     * @param targetedFileSize the targeted file size of a single file in bytes. The files will
     * become slighly bigger than this value.
     * @param alsoPrintTo a Print to additionally print to, usually &Serial
     */
    SpiffsFilePrint(String logfileName, uint8_t logfilesCount = 1,
                    unsigned int targetedFileSize = UINT8_MAX, Print *const alsoPrintTo = NULL);
    virtual ~SpiffsFilePrint();
    void open();
    void close();
    virtual void flush();

   protected:
    virtual size_t write(uint8_t n);

   private:
    const String logfileName;
    const uint8_t filesCount;
    const unsigned int targetedFileSize;
    Print *const alsoPrintTo;

    char buf[BUFFER_SIZE];
    String currentFilename;
    int nextWritePos = 0;
    File file;
    void checkSizeAndAdjustCurrentFilename();
    inline String assembleCurrentFilename(uint8_t index);
    inline String assembleFilename(uint8_t index);
};

#endif  // #ifndef SPIFFS_FILE_PRINT_H
