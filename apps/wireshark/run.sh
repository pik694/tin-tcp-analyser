#!/bin/bash

tshark -X lua_script:tcp_dissector.lua
