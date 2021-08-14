#!/bin/bash

nohup python3 upd_image.py &

nohup python3 upd_position.py &

python3 equipment.py 
