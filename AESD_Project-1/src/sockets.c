#include "sockets.h"

void socket_init(void)
{
    port = PORT;
    int opt = 1;
    char string[40];
    if ((serv = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        error_log("ERROR: socket() initialization");
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);
    if (setsockopt(serv, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1)
    {
        error_log("ERROR: setsockopt() in socket_init function");
    }
    if (bind(serv, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error_log("ERROR: bind() failed in socket_init function");
    }
}

void socket_listen()
{
    if (listen(serv, 5) == -1)
    {
        error_log("ERROR: listen() in sockekt_init");
    }
    client_len = sizeof(client_addr);
    if ((ser = accept(serv, (struct sockaddr *)&client_addr, &client_len)) == -1)
    {
        error_log("ERROR: accept() in socket_init");
    }
    printf("Connected\n");
}

void socket_send(sensor_struct data_send)
{
    printf("BEFORE SOCKET SEND\n\n");
    printf("%d\n", data_send.id);
    fprintf(stdout, "Timestamp: %lu seconds and %lu nanoseconds.\n", data_send.sensor_data.temp_data.data_time.tv_sec, data_send.sensor_data.temp_data.data_time.tv_nsec);
    fprintf(stdout, "Value: %f.\n", data_send.sensor_data.temp_data.temp_c);
    fprintf(stdout, "\n***********************************\n\n");
    send(ser, (void *)&data_send, sizeof(sensor_struct), 0);
    // float data = data_send.sensor_data.light_data.light;
    // send(ser, (void *)&data, sizeof(sensor_struct), 0);
}

int socket_recv(void)
{
    int len, data;
    // len = recv(ser, (void *)&data, sizeof(data), MSG_WAITALL);
    len = read(ser, (void *)&data, sizeof(data));
    if (len == 0)
    {
        return 0;
    }
    printf("Receieved %d bytes\n\n", len);
    printf("Received String %d\n", data);
    fflush(stdout);
    return data;
}

void handle_socket_req()
{
    switch (socket_recv())
    {
    case 100:
        socket_flag |= TC;
        break;
    case 101:
        socket_flag |= TF;
        break;
    case 102:
        socket_flag |= TK;
        break;
    case 103:
        socket_flag |= L;
        break;
    case 104:
        socket_flag |= TCL;
        break;
    case 105:
        socket_flag |= TFL;
        break;
    case 106:
        socket_flag |= TKL;
        break;
    default:
        socket_flag = 0;
        break;
    }
}