#!/bin/bash

ps -ef | grep server_video | grep -v grep | cut -c 9-15 | xargs kill -9
ps -ef | grep client_video | grep -v grep | cut -c 9-15 | xargs kill -9

