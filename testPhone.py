import os
os.environ["MAVLINK20"] = "1"

from pymavlink import mavutil
import random
import time

master = mavutil.mavlink_connection(
    'udpout:127.0.0.1:14551',
    source_system=1,
    source_component=191,
    dialect='ardupilotmega'
)

while True:
    time_boot_ms = int(time.time() * 1000) % 4294967295

    # Send heartbeat (important)
    master.mav.heartbeat_send(
        mavutil.mavlink.MAV_TYPE_ONBOARD_CONTROLLER,
        mavutil.mavlink.MAV_AUTOPILOT_INVALID,
        0, 0, 0
    )

    mac_address = float(input("Enter Foot Radius: "))

    master.mav.named_value_float_send(
            time_boot_ms,
            b"PHONE",
            mac_address
    )

    time.sleep(1)

