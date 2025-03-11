#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <Mmsystem.h>
#include <conio.h>

#define ALIAS "kid_named_audio_device"
#define OUTPUT_FILE "audio.wav"

int sendMCICommand(const char* command, char* returnString, int returnSize) {
	//For sending command strings to a MCI device
    int error = mciSendString(command, returnString, returnSize, NULL);
    if (error) {
        mciGetErrorString(error, returnString, returnSize);
        printf("MCI Error: %s\n", returnString);
        exit(EXIT_FAILURE);
    }
    return error;
}

int main() {
    char mci_command[100];
    char returnString[300];
    int mci_error;

    //Open a new waveaudio device
    sprintf(mci_command, "open new type waveaudio alias %s", ALIAS);
    sendMCICommand(mci_command, returnString, sizeof(returnString));

    //Set time format to milliseconds
    sprintf(mci_command, "set %s time format ms", ALIAS);
    sendMCICommand(mci_command, returnString, sizeof(returnString));

    //Start recording
    sprintf(mci_command, "record %s notify", ALIAS);
    sendMCICommand(mci_command, returnString, sizeof(returnString));

    printf("Recording now, press any key to stop...\n");
    _getch(); 

    //Stop recording
    sprintf(mci_command, "stop %s", ALIAS);
    sendMCICommand(mci_command, returnString, sizeof(returnString));

    //Save the recorded audio
    sprintf(mci_command, "save %s %s", ALIAS, OUTPUT_FILE);
    sendMCICommand(mci_command, returnString, sizeof(returnString));

    //Close opened device
    sprintf(mci_command, "close %s", ALIAS);
    sendMCICommand(mci_command, returnString, sizeof(returnString));

    printf("Recording saved to %s\n", OUTPUT_FILE);
    return 0;
}