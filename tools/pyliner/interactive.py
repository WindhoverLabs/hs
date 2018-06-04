from os.path import basename

import pyliner
from communication import Communication
from util import read_json, enable_logging

enable_logging(script=basename(__file__))

rocky = pyliner.Pyliner(
    vehicle_id='001',
    communication=Communication(
        airliner_map=read_json("airliner.json"),
        ci_port=5009,
        to_port=5012)
)
