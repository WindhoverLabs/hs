"""
Fly in a rising spiral.

Requirements Fulfilled:
    PYLINER001
    PYLINER003
    PYLINER004
    PYLINER009
    PYLINER010
    PYLINER011
    PYLINER012
    PYLINER013
    PYLINER014
    PYLINER016
"""
import time
from os.path import basename

import pyliner
from communication import Communication
from controller import FlightMode
from util import read_json, enable_logging, ScriptingWrapper


def critical_failure(vehicle, errors):
    print(errors)
    print('Error in execution. Returning to Launch')
    vehicle.ctrl.rtl()


enable_logging(script=basename(__file__))

rky = pyliner.Pyliner(
    vehicle_id='001',
    communication=Communication(
        airliner_map=read_json("airliner.json"),
        ci_port=5009,
        to_port=5012)
)

with ScriptingWrapper(rky, critical_failure) as rocky:
    while rocky.nav.altitude == "NULL":
        time.sleep(1)
        print "Waiting for telemetry downlink..."
    
    rocky.ctrl.atp('Arm')
    rocky.ctrl.arm()
    rocky.ctrl.atp('Takeoff')
    rocky.ctrl.takeoff()
    rocky.ctrl.flight_mode(FlightMode.PosCtl)

    start_altitude = rocky.nav.altitude

    rocky.ctrl.atp('Start Spiral')
    rocky.fd.y = 0.75
    rocky.fd.z = 0.5
    rocky.fd.r = -0.2

    while rocky.nav.altitude < start_altitude + 10:
        time.sleep(1)
    rocky.fd.zero()

    rocky.ctrl.atp('Return')
    rocky.ctrl.rtl()
