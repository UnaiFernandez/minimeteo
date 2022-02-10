#ifndef WIFI_H
#define WIFI_h


enum RESPONSE_STATUS{
    RESPONSE_WAITING,
    RESPONSE_OK,
    RESPONSE_TIMEOUT,
    RESPONSE_ERROR
};

int response_status;


int send_command(char * command, char * resp);

#endif //WIFI_H
