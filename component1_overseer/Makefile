CC = gcc
CFLAGS = -Wall

all: component1_overseer component2_cardreader_controller component3_Door_controller component4_firealarm_unit component5_cam_controller component6_Elevator_controller component7_detinationselect_controller component8_simulator component9_temperature_sensor call_point

component1_overseer: overseerlogic.c
	$(CC) $(CFLAGS) -o component1_overseer overseerlogic.c -lpthread

component2_cardreader_controller: component2_cardreader_controller/cardreader.c
	$(CC) $(CFLAGS) -o c2 component2_cardreader_controller/cardreader.c
	
component3_Door_controller: component3_Door_controller/doorcontroller.c
	$(CC) $(CFLAGS) -o c3 component3_Door_controller/doorcontroller.c -lpthread

component4_firealarm_unit: component4_firealarm_unit/firealarm.c
	$(CC) $(CFLAGS) -o c4 component4_firealarm_unit/firealarm.c -lpthread

component5_cam_controller: component5_cam_controller/cam_controller.c
	$(CC) $(CFLAGS) -o c5 component5_cam_controller/cam_controller.c

component6_Elevator_controller: component6_Elevator_controller/elevatorcontroller.c
	$(CC) $(CFLAGS) -o c6 component6_Elevator_controller/elevatorcontroller.c -lpthread
	
component7_detinationselect_controller: component7_detinationselect_controller/destination_select.c
	$(CC) $(CFLAGS) -o c7 component7_detinationselect_controller/destination_select.c -lpthread

component8_simulator: component8_simulator/simulator.c
	$(CC) $(CFLAGS) -o c8 component8_simulator/simulator.c -lpthread

component9_temperature_sensor: component9_temperature_sensor/temp_sensor.c
	$(CC) $(CFLAGS) -o c9 component9_temperature_sensor/temp_sensor.c

call_point: call_point/callpoint.c
	$(CC) $(CFLAGS) -o c10 call_point/callpoint.c

clean:
	rm -f component1_overseer c2 c3 c4 c5 c6 c7 c8 c9 c10