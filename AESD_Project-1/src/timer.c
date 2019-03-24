#include "timer.h"

err_t timer_init(uint8_t timer_handle)
{
    if (timer_handle == TIMER_TEMP)
    {
        timer_t timeout_temp;
        struct itimerspec trigger_temp;
        struct sigevent sev_temp;
        memset(&sev_temp, 0, sizeof(struct sigevent));
        memset(&trigger_temp, 0, sizeof(struct itimerspec));

        sev_temp.sigev_notify = SIGEV_THREAD;
        sev_temp.sigev_notify_function = &timer_handler;
        sev_temp.sigev_value.sival_int = timer_handle;
        timer_create(CLOCK_REALTIME, &sev_temp, &timeout_temp);

        //Setting the first timer interval and the repeating timer interval
        trigger_temp.it_value.tv_sec = TEMP_INTERVAL_SEC;
        trigger_temp.it_interval.tv_sec = TEMP_INTERVAL_SEC;
        trigger_temp.it_value.tv_nsec = TEMP_INTERVAL_NSEC;
        trigger_temp.it_interval.tv_nsec = TEMP_INTERVAL_NSEC;

        timer_settime(timeout_temp, 0, &trigger_temp, NULL);
    }
    else if (timer_handle == TIMER_LIGHT)
    {
        timer_t timeout_light;
        struct itimerspec trigger_light;
        struct sigevent sev_light;
        memset(&sev_light, 0, sizeof(struct sigevent));
        memset(&trigger_light, 0, sizeof(struct itimerspec));

        sev_light.sigev_notify = SIGEV_THREAD;
        sev_light.sigev_notify_function = &timer_handler;
        sev_light.sigev_value.sival_int = timer_handle;
        timer_create(CLOCK_REALTIME, &sev_light, &timeout_light);

        //Setting the first timer interval and the repeating timer interval
        trigger_light.it_value.tv_sec = LIGHT_INTERVAL_SEC;
        trigger_light.it_interval.tv_sec = LIGHT_INTERVAL_SEC;
        trigger_light.it_value.tv_nsec = LIGHT_INTERVAL_NSEC;
        trigger_light.it_interval.tv_nsec = LIGHT_INTERVAL_NSEC;

        timer_settime(timeout_light, 0, &trigger_light, NULL);
    }
    return OK;
}

void timer_handler(union sigval sv)
{
    if (sv.sival_int == TIMER_TEMP)
    {
        //pthread_mutex_lock(&mutex_a);
        temp_timerflag = 1;
        //timer_event |= TEMP_EVENT;
        //pthread_mutex_unlock(&mutex_a);
        printf("In Timer Handler: Temperature Sensor Timer fired.\n");
    }
    else if (sv.sival_int == TIMER_LIGHT)
    {
        //pthread_mutex_lock(&mutex_a);
        light_timerflag = 1;
        //timer_event |= LIGHT_EVENT;
        //pthread_mutex_unlock(&mutex_a);
        printf("In Timer Handler: Light Sensor Timer fired.\n");
    }
}
