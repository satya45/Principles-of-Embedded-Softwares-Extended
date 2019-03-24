#include "logger.h"

void log_error(char *str, int errno)
{
}

void log_data(sensor_struct data_rcv)
{
	switch (data_rcv.id)
	{

	case TEMP_RCV_ID:
	{	
		FILE *logfile = fopen(filename, "a");
		fprintf(stdout, "In logger thread temperature Value: %f.\n", data_rcv.sensor_data.temp_data.temp_c);
		fprintf(logfile, "In logger Thread temperature Value: %f.\n", data_rcv.sensor_data.temp_data.temp_c);
		fclose(logfile);
		break;
	}

	case LIGHT_RCV_ID:
	{
		FILE *logfile = fopen(filename, "a");
		fprintf(stdout, "In logger thread Light Value: %f.\n", data_rcv.sensor_data.light_data.light);
		fprintf(logfile, "In logger Thread Light Value: %f.\n", data_rcv.sensor_data.light_data.light);
		fclose(logfile);
		break;
	}

	case ERROR_RCV_ID:
	{
		FILE *logfile = fopen(filename, "a");
		fprintf(stdout, "%s.\n", data_rcv.sensor_data.error_data.error_str);
		fprintf(stdout, "%s.\n", strerror(data_rcv.sensor_data.error_data.error_value));
		fprintf(logfile, "%s.\n", data_rcv.sensor_data.error_data.error_str);
		fprintf(logfile, "%s.\n", strerror(data_rcv.sensor_data.error_data.error_value));
		fclose(logfile);
		break;
	}
	}
}
