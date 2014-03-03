#!/bin/bash

readonly script_path=$(dirname "$0")
"$script_path"/city-server --port 80 >messages.txt 2>errors.txt
