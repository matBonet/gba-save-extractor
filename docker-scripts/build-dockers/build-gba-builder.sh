#!/bin/bash
docker image rm matbonet/gba-save-extractor:gba_builder
docker build --target gba-build . -t matbonet/gba-save-extractor:gba_builder
