#include "pid.h"
//#include "stdio.h"

void PID_init(){
		pid.SetSpeed=0.0;
		pid.ActualSpeed=0.0;
		pid.err=0.0;
		pid.err_last=0.0;
		pid.voltage=0.0;
		pid.integral=0.0;
		pid.Kp=0.2;
		pid.Ki=0.015; //注意，和上几次相比，这里加大了积分环节的值
		pid.Kd=0.2;
}
float PID_realize(float speed){
	pid.SetSpeed=speed;
	pid.err=pid.SetSpeed-pid.ActualSpeed;
	pid.integral+=pid.err;
	pid.voltage=pid.Kp*pid.err+pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);
	pid.err_last=pid.err;
	pid.ActualSpeed=pid.voltage*1.0;
	return pid.ActualSpeed;
}	

